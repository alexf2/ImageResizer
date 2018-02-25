// Resizer.cpp : Implementation of CResizer
#include "stdafx.h"
#include "CMultipartForm.h"
#include "BSC.h"
#include "Resizer.h"

STDMETHODIMP CResizer::GetInterfaceSafetyOptions( REFIID riid,
	DWORD *pdwSupportedOptions,
	DWORD *pdwEnabledOptions ) throw()
{
   if( !pdwSupportedOptions || !pdwEnabledOptions )
	  return E_FAIL;
   LPUNKNOWN pUnk;
   if( _InternalQueryInterface (riid, (void**)&pUnk) == E_NOINTERFACE )
	  // Our object doesn't even support this interface.
	  return E_NOINTERFACE;
   else
   {
	  // Cleanup after ourselves.
	  pUnk->Release();
	  pUnk = NULL;
   }
   if (riid == IID_IDispatch) 
   {
	  *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
	  *pdwEnabledOptions = m_dwSafety &
						   INTERFACESAFE_FOR_UNTRUSTED_CALLER;
	  return S_OK;
	// IEMime only supports persistence via IPersistPropertyBag
   }
   else if( riid == IID_IPersistPropertyBag )
   {
	  *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
	  *pdwEnabledOptions = m_dwSafety &
						   INTERFACESAFE_FOR_UNTRUSTED_DATA;
	  return S_OK;
   }
   else
   {
	  // No other interfaces in this control are
	  // safe for initializing or scripting.
	  *pdwSupportedOptions = 0;
	  *pdwEnabledOptions = 0;
	  return E_FAIL;
   }
}

STDMETHODIMP CResizer::SetInterfaceSafetyOptions( REFIID riid,
	DWORD dwOptionSetMask,
    DWORD dwEnabledOptions ) throw()
{
   if( !dwOptionSetMask && !dwEnabledOptions ) return E_FAIL;
   LPUNKNOWN pUnk;
   if( _InternalQueryInterface (riid, (void**)&pUnk) == E_NOINTERFACE )
	  // Our object doesn't even support this interface.
	  return E_NOINTERFACE;
   else
   {
	  // Cleanup after ourselves.
	  pUnk->Release();
	  pUnk = NULL;
   }
   // Store our current safety level to return in
   // GetInterfaceSafetyOptions
   m_dwSafety |= dwEnabledOptions & dwOptionSetMask;
   if( (riid == IID_IDispatch) &&
	   (m_dwSafety & INTERFACESAFE_FOR_UNTRUSTED_CALLER) )
	  return S_OK;
   else if ((riid == IID_IPersistPropertyBag) &&
			 (m_dwSafety & INTERFACESAFE_FOR_UNTRUSTED_DATA))
	  return S_OK;
   else
	  return E_FAIL;
}

HRESULT CResizer::FinalConstruct() throw()
{
BEGIN_TRY;

    CGDIPlusInitializer::Instance().Initialize();     

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}	
void CResizer::FinalRelease() throw()
{
    try
    {
        DiscardAllGRIResources();
        CGDIPlusInitializer::Instance().Uninitialize();
    }
    catch( ... )
    {
    }
}

// CResizer
HRESULT CResizer::OnDrawAdvanced( ATL_DRAWINFO& di ) throw()
{
BEGIN_TRY;
    if( di.dwDrawAspect == DVASPECT_CONTENT )
    {
        RECT& rc = *(RECT*)di.prcBounds;
        RECT rClip; GetClipBox( di.hdcDraw, &rClip );

        /*DWORD dwObjTyp = GetObjectType( di.hdcDraw );
        if( OBJ_ENHMETADC == dwObjTyp || OBJ_METADC == dwObjTyp )
		{
        }*/
        Gdiplus::Graphics grTmp( di.hdcDraw );

        LONG lW = RWidth(rClip), lH = RHeight(rClip);
        if( lW && lH )
        {
            Gdiplus::Bitmap bmClip( lW, lH, &grTmp );
            CHK_GDIP( bmClip.GetLastStatus(), L"creating clipped offscreen image" );
            Gdiplus::Graphics grClip( &bmClip );
            CHK_GDIP( grClip.GetLastStatus(), L"creating compatible DC" );

            DrawClip( &bmClip, &grClip, rClip, rc.left, rc.top );

            grTmp.SetSmoothingMode( Gdiplus::SmoothingModeNone );
            grTmp.SetCompositingMode( Gdiplus::CompositingModeSourceOver ); 
			grTmp.SetCompositingQuality( Gdiplus::CompositingQualityHighSpeed );
			grTmp.SetInterpolationMode( Gdiplus::InterpolationModeLowQuality );

            grTmp.DrawImage( &bmClip, rClip.left, rClip.top, RWidth(rClip), RHeight(rClip) );
        }
    }
END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
#pragma warning( disable: 4244 )
void __fastcall CResizer::DrawClip( Gdiplus::Bitmap* pbmpDraw, Gdiplus::Graphics* pGr, RECT& rcVis, int iXOff, int iYOff )
{
    /*IUnknown *pp = GetUnknown();
    IDispatch *dsp = NULL;
    HRESULT hh = pp->QueryInterface( __uuidof(IDispatch), (void**)&dsp );*/

    RECT rcPos = m_rcPos;
	NormalizeRect( rcPos );

    ContainerToControl( rcPos );
    Gdiplus::RectF rg3 = GRECTF( rcPos );

    Gdiplus::Rect rcDraw = GRECT( rcVis );
    ContainerToControl( rcDraw );
    pGr->TranslateTransform( -rcDraw.X, -rcDraw.Y, Gdiplus::MatrixOrderAppend );

    pGr->SetSmoothingMode( Gdiplus::SmoothingModeNone );
	pGr->SetCompositingMode( Gdiplus::CompositingModeSourceOver );
	pGr->SetCompositingQuality( Gdiplus::CompositingQualityHighQuality );
	pGr->SetInterpolationMode( Gdiplus::InterpolationModeHighQuality );
	pGr->SetTextRenderingHint( Gdiplus::TextRenderingHintAntiAlias );

    pGr->Clear( *GetClrBack() );
    if( m_bBorderVisible == VARIANT_TRUE )
        pGr->DrawRectangle( GetPenBorder(), 0, 0, RWidth(rcPos), RHeight(rcPos) );

L_ERR:
    if( m_bsErrLoadingImgMsg.m_str != NULL && m_bsErrLoadingImgMsg.Length() > 0 )
    {
        Gdiplus::StringFormat format(  Gdiplus::StringFormatFlagsNoWrap | Gdiplus::StringFormatFlagsLineLimit );
		format.SetAlignment( Gdiplus::StringAlignmentCenter );
		format.SetLineAlignment( Gdiplus::StringAlignmentCenter );

        Gdiplus::FontFamily fontFamily( L"Arial" );
        std::auto_ptr<Gdiplus::Font> spFnt( CHK_ALLOC(new Gdiplus::Font(&fontFamily, 12, Gdiplus::FontStyleBold, Gdiplus::UnitPixel)) );

        rg3.Inflate( -m_nBorderWidth, -m_nBorderWidth );
        pGr->DrawString( (BSTR)m_bsErrLoadingImgMsg, -1, spFnt.get(), rg3, &format,
				&Gdiplus::SolidBrush(*GetClrFore()) );
    }
    else
    {
        Gdiplus::Image* pThumb = GetImgThumb( true );
        if( pThumb )
        {
            INT x = ((long)RWidth(rcPos) - pThumb->GetWidth()) / 2.0;
            INT y = ((long)RHeight(rcPos) - pThumb->GetHeight()) / 2.0;
            pGr->DrawImage( pThumb, x, y, pThumb->GetWidth(), pThumb->GetHeight() );
        }
        else if( m_bsErrLoadingImgMsg.m_str != NULL && m_bsErrLoadingImgMsg.Length() > 0 )
            goto L_ERR;
    }

    pGr->ResetTransform();
}
#pragma warning( default: 4244 )

void CResizer::OnBackColorChanged()
{
	ATLTRACE(_T("OnBackColorChanged\n"));
    FreeAutoPtr( m_apBrushBack );
    FreeAutoPtr( m_apClrBack );
}
void CResizer::OnBorderColorChanged()
{
	ATLTRACE(_T("OnBorderColorChanged\n"));
    FreeAutoPtr( m_apClrBorder );
    FreeAutoPtr( m_apPenBorder );
}
void CResizer::OnBorderVisibleChanged()
{
	ATLTRACE(_T("OnBorderVisibleChanged\n"));
}
void CResizer::OnBorderWidthChanged()
{
	ATLTRACE(_T("OnBorderWidthChanged\n"));
    FreeAutoPtr( m_apPenBorder );
}
void CResizer::OnForeColorChanged()
{
	ATLTRACE(_T("OnForeColorChanged\n"));
    FreeAutoPtr( m_apForeColor );
    FreeAutoPtr( m_apBrushProgress );
}

void CResizer::OnWidthChanged()
{
    RECT rcKeep = m_rcOld;
	AdjustBounds();
	m_rcOld = rcKeep;
}
void CResizer::OnHeightChanged()
{
    RECT rcKeep = m_rcOld;
	AdjustBounds();
	m_rcOld = rcKeep;
}
void CResizer::OnNavigateOnFinishUrlChanged()
{
}
void CResizer::OnImageFullNameChanged()
{
    FreeAutoPtr( m_apImgOrig );
    FreeAutoPtr( m_apImgThumb );
}
void CResizer::OnUploadUrlChanged()
{    
}
void CResizer::OnMaxWidthChanged()
{
}
void CResizer::OnMaxHeightChanged()
{
}

STDMETHODIMP CResizer::get_ImagePropsDescription( BSTR* pbsDescr ) throw()
{
BEGIN_TRY;
    Gdiplus::Image* pImg = GetImgOrig();
    if( pImg == NULL )
    {
        CComBSTR bsRes( L"No image loaded" );
        CHK_COM( bsRes.CopyTo(pbsDescr), L"returning description string" );
    }
    else
    {
        CComBSTR bsMime;
        CLSID cMimeId;
        CHK_GDIP( pImg->GetRawFormat(&cMimeId), L"getting image MIME type" );
        if( GetMimeByRowFormat(cMimeId, &bsMime) == -1 )
            THROW_SIMPLE_STD_EXC( "get_ImagePropsDescription", "Mime ID is not found" );

        /*wchar_t fname[ _MAX_FNAME ];
        wchar_t ext[ _MAX_EXT ];
        _wsplitpath( SafeGetBSTR(m_bsImageFullName),  NULL, NULL, fname, ext );*/
        

        std::basic_stringstream<wchar_t> bsStm;
        //bsStm << fname << ext << L": " ;
        bsStm <<
            SafeGetBSTR(bsMime) << L", " << (int)pImg->GetWidth() << L"x" << (int)pImg->GetHeight();
        
        float m1, m2;
        m1 = float(m_lMaxWidth) / float(pImg->GetWidth());
        m2 = float(m_lMaxHeight) / float(pImg->GetHeight());
        m1 = min( m1, m2 );

       long w, h;
       if( m1 < 1 )
           w = long(float(pImg->GetWidth()) * m1), h = long(float(pImg->GetHeight()) * m1);
       else
           w = pImg->GetWidth(), h = pImg->GetHeight();

        //Gdiplus::Image* pImgThumb = GetImgThumb( false );
        if( w != pImg->GetWidth() || h != pImg->GetHeight() )
            bsStm << L", will resampled to: " <<
                (int)w << L"x" << (int)h;

        CComBSTR bsRes( bsStm.str().c_str() );
        CHK_COM( bsRes.CopyTo(pbsDescr), L"returning description string" );
    }
END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::SelectImage( BSTR* bsImgFileName ) throw()
{
BEGIN_TRY;
    CComBSTR bsName = AskFileName();
    CHK_COM( bsName.CopyTo(bsImgFileName), L"returning selected file path" );
END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::UploadImage( void ) throw()
{
	USES_CONVERSION;

BEGIN_TRY;
    GetImgThumb( false );
    std::auto_ptr<Gdiplus::Image>  apImg = m_apImgThumb;
    FreeAutoPtr( m_apImgThumb );

    CLSID imgFmtClsid; m_apImgOrig->GetRawFormat( &imgFmtClsid );
    //GetEncoderClsid( L"image/png", &pngClsid );
    //m_apImgThumb->
	CMemoryStream stmImg;
	stmImg.Init();
	CLSID encoderClsid;
	if( GetEncoderClsidByMimeClsid(imgFmtClsid, encoderClsid) == -1 )
		THROW_SIMPLE_STD_EXC( "UploadImage", "Mime ID is not found" );
	CHK_GDIP( apImg->Save((IStream*)stmImg, &encoderClsid, NULL), L"streaming resized image" );

	std::auto_ptr<CMultipartForm> spForm( new CMultipartForm() );
	spForm->Init();
	CComBSTR bsMime;
	if( GetMimeByRowFormat(imgFmtClsid, &bsMime) == -1 )
		THROW_SIMPLE_STD_EXC( "UploadImage", "Mime ID is not found" );
	spForm->AddPostingFile( "nFile", 
		W2CA(SafeGetBSTR(m_bsImageFullName)), W2CA(SafeGetBSTR(bsMime)), (IStream*)stmImg );
	spForm->FinalizeStream();
	spForm->GetStream().SeekToStart();
	//spForm->GetStream().CopyStreamToFile( _T("C:\\Work\\ResizerSln\\frm.bin") );

	CAwsBindStatusCallback::StartAsyncUpload(
		spForm,
		static_cast<IBindingNotify*>(this), m_bsUploadUrl, 
		IsRelativeURL(m_bsUploadUrl), m_spClientSite.p
	);

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}

bool CResizer::IsRelativeURL( BSTR bs )
{
	return wcsstr(SafeGetBSTR(bs), L"://") == NULL ? true:false;
}

Gdiplus::SolidBrush* __fastcall CResizer::GetBrushBack()
{
    if( !m_apBrushBack.get() )
        m_apBrushBack = std::auto_ptr<Gdiplus::SolidBrush>(
            CHK_ALLOC(new Gdiplus::SolidBrush(*GetClrBack()))
        );

    return m_apBrushBack.get();
}
Gdiplus::SolidBrush* __fastcall CResizer::GetBrushProgress()
{
    if( !m_apBrushProgress.get() )
        m_apBrushProgress = std::auto_ptr<Gdiplus::SolidBrush>(
            CHK_ALLOC(new Gdiplus::SolidBrush(*GetClrFore()))
        );

    return m_apBrushProgress.get();
}
Gdiplus::Color* __fastcall CResizer::GetClrBack()
{
    if( !m_apClrBack.get() )
        m_apClrBack = GetNewColor( m_clrBackColorCust );

    return m_apClrBack.get();
}
Gdiplus::Color* __fastcall CResizer::GetClrBorder()
{
    if( !m_apClrBorder.get() )
        m_apClrBorder = GetNewColor( m_clrBorderColorCust );

    return m_apClrBorder.get();
}
Gdiplus::Color* __fastcall CResizer::GetClrFore()
{
    if( !m_apForeColor.get() )
        m_apForeColor = GetNewColor( m_clrForeColorCust );        

    return m_apForeColor.get();
}
std::auto_ptr<Gdiplus::Color> __fastcall CResizer::GetNewColor( CComVariant& rClr )
{
    std::auto_ptr<Gdiplus::Color> res;
    if( V_VT(&rClr) == VT_EMPTY )    
        res = std::auto_ptr<Gdiplus::Color>(
				CHK_ALLOC(new Gdiplus::Color(0, 0, 0, 0)) );
    else
    {
        COLORREF clrRef;
        CComVariant vClrTmp;
        AssignColor( vClrTmp, rClr ); //convets 

        OleTranslateColor( V_I4(&vClrTmp), NULL, &clrRef );
        res = std::auto_ptr<Gdiplus::Color>( new Gdiplus::Color() );
        res->SetFromCOLORREF( clrRef );
    }
    return res;
}
Gdiplus::Pen* __fastcall CResizer::GetPenBorder()
{
    if( !m_apPenBorder.get() )
    {
        m_apPenBorder = std::auto_ptr<Gdiplus::Pen>(
            CHK_ALLOC(new Gdiplus::Pen(*GetClrBorder(), (Gdiplus::REAL)m_nBorderWidth))
        );
        m_apPenBorder->SetAlignment( Gdiplus::PenAlignmentInset );
    }

    return m_apPenBorder.get();
}
Gdiplus::Pen* __fastcall CResizer::GetPenProgress()
{
    if( !m_apPenProgress.get() )
        m_apPenProgress = std::auto_ptr<Gdiplus::Pen>(
            CHK_ALLOC(new Gdiplus::Pen(*GetClrFore(), 1))
        );

    return m_apPenProgress.get();
}
Gdiplus::Image* __fastcall CResizer::GetImgOrig()
{
    USES_CONVERSION;

    m_bsErrLoadingImgMsg.Empty();
BEGIN_TRY;
    if( !m_apImgOrig.get() )
    {
        if( m_bsImageFullName.m_str != NULL && m_bsImageFullName.Length() > 0 )        
        {
            CRcHolder< HANDLE, CFile_Manager > crhFile =
                CHK_W32(
                    ::CreateFile(W2CT(m_bsImageFullName.m_str), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL),
                    (HANDLE)INVALID_HANDLE_VALUE,
                    L"Opening selected image"
                );
            crhFile.Release();

            m_apImgOrig = std::auto_ptr<Gdiplus::Image>( CHK_ALLOC(new Gdiplus::Image((BSTR)m_bsImageFullName)) );
            CHK_GDIP( m_apImgOrig->GetLastStatus(), L"creating GDI+ image" );
        }
    }
END_TRY( this, __uuidof(IResizer) );
    if( FAILED(_hr) )
    {
        m_bsErrLoadingImgMsg.Empty();
        _spIEI->GetDescription( &m_bsErrLoadingImgMsg );
        _spIEI.Release();
        return NULL;
    }
    else
        return m_apImgOrig.get();
}
#pragma warning( disable: 4244 )
Gdiplus::Image* __fastcall CResizer::GetImgThumb( bool bForPreview )
{
    if( !m_apImgThumb.get() )
    {
        Gdiplus::Image* pImgOrig = GetImgOrig();
        if( pImgOrig )
        {
            float m1, m2;
            if( bForPreview )
            {
                m1 = float(m_lWidth -  2 * m_nBorderWidth) / float(pImgOrig->GetWidth());
                m2 = float(m_lHeight -  2 * m_nBorderWidth) / float(pImgOrig->GetHeight());                
            }
            else
            {
                m1 = float(m_lMaxWidth) / float(pImgOrig->GetWidth());
                m2 = float(m_lMaxHeight) / float(pImgOrig->GetHeight());
            }
            m1 = min( m1, m2 );

            if( m1 >= 1 )
                return pImgOrig;

            long w = float(pImgOrig->GetWidth()) * m1;
            long h = float(pImgOrig->GetHeight()) * m1;

			std::auto_ptr<Gdiplus::Bitmap> apTrg( 
				CHK_ALLOC(new Gdiplus::Bitmap(w, h, PixelFormat24bppRGB)) );
				/*pImgOrig->GetPixelFormat()*/

            CHK_GDIP( apTrg->GetLastStatus(), L"creating clipped offscreen image" );
            std::auto_ptr<Gdiplus::Graphics> apGrT( CHK_ALLOC(Gdiplus::Graphics::FromImage(apTrg.get())) );
            CHK_GDIP( apGrT->GetLastStatus(), L"creating context from clipped offscreen image" );

            apGrT->SetSmoothingMode( Gdiplus::SmoothingModeNone );
	        apGrT->SetCompositingMode( Gdiplus::CompositingModeSourceOver );
	        apGrT->SetCompositingQuality( Gdiplus::CompositingQualityHighQuality );
	        apGrT->SetInterpolationMode( Gdiplus::InterpolationModeHighQualityBicubic );
            apGrT->DrawImage( pImgOrig, 0, 0, w, h );

            FreeAutoPtr( apGrT );
          
            m_apImgThumb = apTrg;
/*CLSID pngClsid;
GetEncoderClsid( L"image/png", &pngClsid );
m_apImgThumb->Save( L"c:\\t1.png", &pngClsid, NULL );*/

            CHK_GDIP( m_apImgThumb->GetLastStatus(), L"Creating thumbinal image" );
        }
    }
    return m_apImgThumb.get();
}
#pragma warning( default: 4244 )


STDMETHODIMP CResizer::put_Width( long lWidth ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_WIDTH) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	
    if( lWidth <= 0 )
        THROW_SIMPLE_STD_EXC( "Setting Width", "Width should be > 0." );

    if( m_lWidth != lWidth )
    {
        FreeAutoPtr( m_apImgThumb );
        m_lWidth = lWidth, m_bRequiresSave = TRUE;
        OnWidthChanged();
        if( !m_nFreezeEvents )
            FireViewChange(), 
            SendOnDataChange(NULL), FireOnChanged( DISPID_WIDTH );
    }

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_Width( long* lWidth ) throw()
{
    if( !lWidth )
        return E_POINTER;
    *lWidth = m_lWidth;
    return S_OK;
}

STDMETHODIMP CResizer::put_Height( long lHeight ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_HEIGHT) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	
    if( lHeight <= 0 )
        THROW_SIMPLE_STD_EXC( "Setting Height", "Height should be > 0." );

    if( m_lHeight != lHeight )
    {
        FreeAutoPtr( m_apImgThumb );
        m_lHeight = lHeight, m_bRequiresSave = TRUE;
        OnHeightChanged();
        if( !m_nFreezeEvents )
            FireViewChange(), 
            SendOnDataChange(NULL), FireOnChanged( DISPID_HEIGHT );
    }

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_Height( long* lHeight ) throw()
{
    if( !lHeight )
        return E_POINTER;
    *lHeight = m_lHeight;
    return S_OK;
}

STDMETHODIMP CResizer::put_NavigateOnFinishUrl( BSTR bsURL ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_NAVIGATEONFINISHURL) == S_FALSE ) return S_FALSE;

BEGIN_TRY;
    if( m_bsNavigateOnFinishUrl != bsURL )
    {
        m_bsNavigateOnFinishUrl = bsURL, m_bRequiresSave = TRUE;
        OnNavigateOnFinishUrlChanged();
        if( !m_nFreezeEvents )
            FireViewChange(), 
            SendOnDataChange(NULL), FireOnChanged( DISPID_NAVIGATEONFINISHURL );
    }

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_NavigateOnFinishUrl( BSTR* pbsURL ) throw()
{
    if( !pbsURL )
        return E_POINTER;
    return m_bsNavigateOnFinishUrl.CopyTo( pbsURL );
}

STDMETHODIMP CResizer::put_ImageFullName( BSTR bsURL ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_IMAGEFULLNAME) == S_FALSE ) return S_FALSE;

BEGIN_TRY;

    if( m_bsImageFullName != bsURL )
    {
        m_bsImageFullName = bsURL, m_bRequiresSave = TRUE;
        FreeAutoPtr( m_apImgOrig );
        FreeAutoPtr( m_apImgThumb );
        m_bsErrLoadingImgMsg.Empty();

        OnImageFullNameChanged();
        if( !m_nFreezeEvents )
            FireViewChange(), 
            SendOnDataChange(NULL), FireOnChanged( DISPID_IMAGEFULLNAME );
    }    

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_ImageFullName( BSTR* pbsURL ) throw()
{
    if( !pbsURL )
        return E_POINTER;
    return m_bsImageFullName.CopyTo( pbsURL );
}

STDMETHODIMP CResizer::put_UploadUrl( BSTR bsURL ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_UPLOADURL) == S_FALSE ) return S_FALSE;

BEGIN_TRY;

    if( m_bsUploadUrl != bsURL )
    {
        m_bsUploadUrl = bsURL, m_bRequiresSave = TRUE;
        OnUploadUrlChanged();
        if( !m_nFreezeEvents )
            FireViewChange(),
            SendOnDataChange(NULL), FireOnChanged( DISPID_UPLOADURL );
    }

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_UploadUrl( BSTR* pbsURL ) throw()
{
    if( !pbsURL )
        return E_POINTER;
    return m_bsUploadUrl.CopyTo( pbsURL );
}

STDMETHODIMP CResizer::put_MaxWidth( long lWidth ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_MAXWIDTH) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	
    if( lWidth <= 0 )
        THROW_SIMPLE_STD_EXC( "Setting MaxWidth", "Width should be > 0." );

    if( m_lMaxWidth != lWidth )
    {
        m_lMaxWidth = lWidth, m_bRequiresSave = TRUE;
        OnMaxWidthChanged();
        if( !m_nFreezeEvents )
            FireViewChange(), 
            SendOnDataChange(NULL), FireOnChanged( DISPID_MAXWIDTH );
    }

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_MaxWidth( long* plWidth ) throw()
{
    if( !plWidth )
        return E_POINTER;
    *plWidth = m_lMaxWidth;
    return S_OK;
}

STDMETHODIMP CResizer::put_MaxHeight( long lHeight ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_MAXHEIGHT) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	
    if( lHeight <= 0 )
        THROW_SIMPLE_STD_EXC( "Setting MaxHeight", "Height should be > 0." );

    if( m_lMaxHeight != lHeight )
    {
        m_lMaxHeight = lHeight, m_bRequiresSave = TRUE;
        OnMaxHeightChanged();
        if( !m_nFreezeEvents )
            FireViewChange(), 
            SendOnDataChange(NULL), FireOnChanged( DISPID_MAXHEIGHT );
    }

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_MaxHeight( long* plHeight ) throw()
{
    if( !plHeight )
        return E_POINTER;
    *plHeight = m_lMaxHeight;
    return S_OK;
}

STDMETHODIMP CResizer::put_BackColor( VARIANT* pV ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_BACKCOLOR) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	

    m_clrBackColorCust = *pV, m_bRequiresSave = TRUE;
    OnBackColorChanged();

    if( !m_nFreezeEvents )
        FireViewChange(), 
        SendOnDataChange(NULL), FireOnChanged( DISPID_BACKCOLOR );

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_BackColor( VARIANT* pV ) throw()
{
    if( !pV )
        return E_POINTER;
    ::VariantInit( pV );
    if( V_VT(&m_clrBackColorCust) != VT_EMPTY ) 
        return ::VariantCopy( pV, &m_clrBackColorCust );
    else
        return S_OK;
}

STDMETHODIMP CResizer::put_BorderColor( VARIANT* pV ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_BORDERCOLOR) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	

    m_clrBorderColorCust = *pV, m_bRequiresSave = TRUE;
    OnBorderColorChanged();

    if( !m_nFreezeEvents )
        FireViewChange(), 
        SendOnDataChange(NULL), FireOnChanged( DISPID_BORDERCOLOR );

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_BorderColor( VARIANT* pV ) throw()
{
    if( !pV )
        return E_POINTER;
    ::VariantInit( pV );
    if( V_VT(&m_clrBorderColorCust) != VT_EMPTY ) 
        return ::VariantCopy( pV, &m_clrBorderColorCust );
    else
        return S_OK;
}

STDMETHODIMP CResizer::put_BorderVisible( VARIANT_BOOL pV ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_BORDERVISIBLE) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	
    if( pV < 0 )
        THROW_SIMPLE_STD_EXC( "Setting Border width", "Width should be => 0." );

    if( m_bBorderVisible != pV )
    {
        m_bBorderVisible = pV, m_bRequiresSave = TRUE;
        OnBorderVisibleChanged();
        if( !m_nFreezeEvents )
            FireViewChange(), 
            SendOnDataChange(NULL), FireOnChanged( DISPID_BORDERVISIBLE );
    }

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_BorderVisible( VARIANT_BOOL* pV ) throw()
{
    if( !pV )
        return E_POINTER;
    *pV = m_bBorderVisible;
    return S_OK;
}

STDMETHODIMP CResizer::put_BorderWidth( long pV ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_BORDERWIDTH) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	
    if( pV < 0 )
        THROW_SIMPLE_STD_EXC( "Setting Border width", "Width should be => 0." );

    if( m_nBorderWidth != pV )
    {
        FreeAutoPtr( m_apImgThumb );
        m_nBorderWidth = pV, m_bRequiresSave = TRUE;
        OnBorderWidthChanged();
        if( !m_nFreezeEvents )
            FireViewChange(), 
            SendOnDataChange(NULL), FireOnChanged( DISPID_BORDERWIDTH );
    }

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_BorderWidth( long* pV ) throw()
{
    if( !pV )
        return E_POINTER;
    *pV = m_nBorderWidth;
    return S_OK;
}

STDMETHODIMP CResizer::put_ForeColor( VARIANT* pV ) throw()
{
    if( !m_nFreezeEvents && FireOnRequestEdit(DISPID_FORECOLOR) == S_FALSE ) return S_FALSE;

BEGIN_TRY;	

    m_clrForeColorCust = *pV, m_bRequiresSave = TRUE;
    OnForeColorChanged();

    if( !m_nFreezeEvents )
        FireViewChange(), 
        SendOnDataChange(NULL), FireOnChanged( DISPID_FORECOLOR );

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_ForeColor( VARIANT* pV ) throw()
{
    if( !pV )
        return E_POINTER;
    ::VariantInit( pV );
    if( V_VT(&m_clrForeColorCust) != VT_EMPTY ) 
        return ::VariantCopy( pV, &m_clrForeColorCust );
    else
        return S_OK;
}

HRESULT CResizer::IOleInPlaceObject_SetObjectRects( LPCRECT prcPos, LPCRECT prcClip )
{
    if( prcClip ) m_rcClip = *prcClip;
    return CComControlBase::IOleInPlaceObject_SetObjectRects( prcPos, prcClip );
}

void __fastcall CResizer::AdjustBounds()
{
    SIZEL sz;
	GetRecommendedControlSize( sz );

    SIZEL szOld = m_sizeExtent;	
	AtlPixelToHiMetric( &sz, &m_sizeExtent );
	m_sizeNatural = m_sizeExtent;

    m_rcOld = m_rcPos;
    m_lNewW = sz.cx, m_lNewH = sz.cy;

    if( m_spClientSite.p && memcmp(&szOld, &m_sizeExtent, sizeof m_sizeExtent) != 0 )
		m_spClientSite->RequestNewObjectLayout();
}

void __fastcall CResizer::GetRecommendedControlSize( SIZEL& rSz )
{
    rSz.cx = m_lWidth, rSz.cy = m_lHeight;	
}

void __fastcall CResizer::Internal_ContainerToControl( LONG* p, int iCountPoints ) const throw() 
{
	LONG x = XOff(), y = YOff();
	for( ; iCountPoints > 0; --iCountPoints )
		*p++ -= x, *p++ -= y;	
}
void __fastcall CResizer::Internal_ContainerToControl( INT* p, int iCountPoints ) const throw() 
{
	INT x = XOff(), y = YOff();
	for( ; iCountPoints > 0; --iCountPoints )
		*p++ -= x, *p++ -= y;	
}
#pragma warning( disable: 4244 )
void __fastcall CResizer::Internal_ContainerToControl( Gdiplus::REAL* p, int iCountPoints ) const throw() 
{
	Gdiplus::REAL x = XOff(), y = YOff();
	for( ; iCountPoints > 0; --iCountPoints )
		*p++ -= x, *p++ -= y;	
}
#pragma warning( default: 4244 )

/*STDMETHODIMP CResizer::SetSite( IUnknown *pUnkSite ) throw()
{
BEGIN_TRY;
    CHK_COM( IObjectWithSiteImpl<CResizer>::SetSite(pUnkSite), L"base::SetSite" );

    if( NULL != pUnkSite )
    {
        CHK_COM(
			pUnkSite->QueryInterface(__uuidof(IOleInPlaceSite), (void**)&m_spSite),
				L"QI IOleInPlaceSite" );
    }
    else
		m_spSite = NULL;

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}*/
HWND __fastcall CResizer::GetHWNDOfParent()
{
    HWND hwnd;
    CComPtr< IOleInPlaceSite > spSite;
    CHK_COM(
			m_spClientSite->QueryInterface(__uuidof(IOleInPlaceSite), (void**)&spSite),
				L"QI IOleInPlaceSite" );
	CHK_COM( spSite->GetWindow(&hwnd), L"Getting HWND of IE" );
	return hwnd;
}
void __fastcall CResizer::SetInitialPath( BSTR bs )
{
    wchar_t wcDrive[ _MAX_DRIVE ], wcDir[ _MAX_DIR ];	
	_wsplitpath( (BSTR)bs, wcDrive, wcDir, NULL, NULL );
	
	m_bsInitialPath.Empty();

	int iLenDrive;
	m_bsInitialPath.Attach( ::SysAllocStringLen(NULL,
		(iLenDrive = (int)wcslen(wcDrive)) + (int)wcslen(wcDir)) );

	if( NULL == (BSTR)m_bsInitialPath )
		_com_issue_error( E_OUTOFMEMORY );
	else
	{
		wcsncpy( (BSTR)m_bsInitialPath, wcDrive, iLenDrive );
		wcscpy( ((BSTR)m_bsInitialPath) + iLenDrive, wcDir );		
	}
}

CComBSTR __fastcall CResizer::AskFileName()
{
	USES_CONVERSION;

	m_pfd.hParent = GetHWNDOfParent();
	m_pfd.hInstance = _AtlBaseModule.GetModuleInstance();
	
	_tcsncpy( m_pfd.arrInitialDir, W2T(SafeGetBSTR(m_bsInitialPath)), _MAX_PATH - 1 );
	m_pfd.arrInitialDir[ _MAX_PATH - 1 ] = 0;

	if( SelectFileForSave(m_pfd) )
		return m_pfd.arrFile;
	else
		return CComBSTR();	
}

STDMETHODIMP CResizer::put_InitialPath( BSTR bsInitPath )
{
BEGIN_TRY;
	
	if( NULL == bsInitPath )
		m_bsInitialPath = L".\\";
	else
	{
		int iSz = ::SysStringLen( bsInitPath );		
		bool bADdSlash = (L'\\' != bsInitPath[ iSz - 1 ]);

		m_bsInitialPath.Attach( CHK_ALLOC(::SysAllocStringLen(NULL, iSz + (bADdSlash ? 1:0))) ); 
		memcpy( (BSTR)m_bsInitialPath, bsInitPath, iSz * sizeof(OLECHAR) );
		if( bADdSlash )
			memcpy( ((BSTR)m_bsInitialPath) + iSz++, L"\\", 1 * sizeof(OLECHAR) );

		((BSTR)m_bsInitialPath)[ iSz ] = 0;
	}	

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}

STDMETHODIMP CResizer::put_DialogTitle( BSTR Title )
{
BEGIN_TRY;
	
	DWORD dwLen = ::SysStringLen( Title );
	if( 0 == dwLen ) m_pfd.arrTitle[ 0 ] = 0;
	else if( sizeof(m_pfd.arrTitle)/sizeof(m_pfd.arrTitle[0]) <= dwLen )
		THROW_SIMPLE_STD_EXC( "put_DialogTitle", "Title has too long size." );
	else
	{
		USES_CONVERSION;
		_tcscpy( m_pfd.arrTitle, W2T(Title) );
	}

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_DialogTitle( BSTR* pbsTitle )
{
    HRESULT hr;

	if( NULL == pbsTitle )
		hr = E_POINTER;	
	else 
	{		
		CComBSTR bsTmp( m_pfd.arrTitle );
		*pbsTitle = bsTmp.Detach();
		hr = S_OK;
	}

	return hr;
}

//comma separated masks
STDMETHODIMP CResizer::put_DialogMasks( BSTR bsMasks )
{
BEGIN_TRY;
	DWORD dwSz = ::SysStringLen( bsMasks );
	if( dwSz >= sizeof(m_pfd.arrFilter)/sizeof(m_pfd.arrFilter[0]) - 1 )
		THROW_SIMPLE_STD_EXC( "put_DialogMaks", "Extension has too long size." );

	BSTR bsIn = bsMasks;
	LPTSTR lpszOut = m_pfd.arrFilter;
	for( int i = dwSz; 0 < i; --i, ++bsIn, ++lpszOut )
        *lpszOut = (*bsIn == _T('\\') ? _T('\0'):(TCHAR)*bsIn);

    *lpszOut++ = _T('\0'); *lpszOut = _T('\0');

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_DialogMasks( BSTR* pbsMasks )
{
BEGIN_TRY;

	if( NULL == pbsMasks )
		_com_issue_error( E_POINTER );
	else
	{		
		DWORD dwSz = DoubleNullSize( m_pfd.arrFilter );
        std::auto_ptr<TCHAR> apTmp( new TCHAR[dwSz + 1] );

		TCHAR *pDst = apTmp.get();
		LPCTSTR lpcsz = m_pfd.arrFilter;
		for( int i = dwSz - 2; 0 < i; --i, ++pDst, ++lpcsz )
            *pDst = (*lpcsz == _T('\0') ? _T('\\'):*lpcsz);
		
        *pDst = _T('\0');
        CComBSTR bsT( apTmp.get() );
		*pbsMasks = bsT.Detach();
	}

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}

STDMETHODIMP CResizer::put_DialogDefaultExt( BSTR Ext )
{
USES_CONVERSION;

BEGIN_TRY;

	if( ::SysStringLen(Ext) >= sizeof(m_pfd.arrDefExt)/sizeof(m_pfd.arrDefExt[0]) )
		THROW_SIMPLE_STD_EXC( "put_DialogDefaultExt", "Extension has too long size." );

	_tcscpy( m_pfd.arrDefExt, OLE2T(SafeGetBSTR(Ext)) );

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::get_DialogDefaultExt( BSTR* pbsExt )
{
BEGIN_TRY;

	if( NULL == pbsExt )
		_com_issue_error( E_POINTER );
	else
		*pbsExt = CComBSTR( m_pfd.arrDefExt ).Detach();

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}

STDMETHODIMP CResizer::put_DialogCenterInParent( VARIANT_BOOL vCenter )
{
    m_pfd.bCenterInParent = (vCenter == VARIANT_TRUE ? true:false);
	return S_OK;
}
STDMETHODIMP CResizer::get_DialogCenterInParent( VARIANT_BOOL* pvCenter )
{
    HRESULT hr;
	if( NULL == pvCenter )
		hr = E_POINTER;
	else
		*pvCenter = (m_pfd.bCenterInParent ? VARIANT_TRUE:VARIANT_FALSE),
		hr = S_OK;

	return hr;
}

STDMETHODIMP CResizer::SetClientSite( IOleClientSite *pClientSite ) throw()
{
BEGIN_TRY;
    CHK_COM( __super::SetClientSite(pClientSite), L"calling SetClientSite" );

    if( pClientSite )
    {
        IServiceProviderPtr spSP( m_spClientSite.p );
        if( !spSP.GetInterfacePtr() )
			THROW_SIMPLE_STD_EXC( "QI IServiceProvider", "No interface" );

        CComPtr<IOleControlSite> spCnt;
		CHK_COM( pClientSite->QueryInterface( &spCnt ), L"QI IOleControlSite" );

        IDispatchPtr spDSP;
		CHK_COM( spCnt->GetExtendedControl( &spDSP ), L"GetExtendedControl" );

        m_spObjectTag = spDSP;

        if( m_spObjectTag.GetInterfacePtr() == NULL )
			THROW_SIMPLE_STD_EXC( "QI IHTMLElement", "No interface" );

        m_spHDoc2 = m_spObjectTag->document;
		m_spWindow2 = m_spHDoc2->parentWindow;

        if( !m_bAdvised )
        {              
            //__hook( &MSHTML::HTMLWindowEvents2::onunload, m_spWindow2.GetInterfacePtr(), &CResizer::OnUnload );
            CHK_COM( THTMLWindowEvents::DispEventAdvise(m_spWindow2.GetInterfacePtr()),
				L"Advising on events from Window" );
            m_bADviseWindow = true;

            
            //__hook( &MSHTML::HTMLDocumentEvents2::onstop, m_spHDoc2.GetInterfacePtr(), &CResizer::OnStop_Document );
            CHK_COM( THTMLDocumentEvents::DispEventAdvise(m_spHDoc2.GetInterfacePtr()),
				L"Advising on events from HTML document" );
            m_bAdviseDoc = true;
            m_bAdviseDoc = true;
        }
    }
    else
        HandsoffEvents();

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}

//IBindingNotify
STDMETHODIMP CResizer::OnProgress( /*[in]*/IBindStatusCallback* pSender, /*[in]*/ULONG ulProgress,
/*[in]*/ULONG ulProgressMax, /*[in]*/ULONG ulStatusCode, /*[in]*/BSTR bsStatusText )
{
BEGIN_TRY;

	wchar_t wc[ 1024 ];
	swprintf( wc, L"Uploading %d%%", (int)(ulProgressMax ? ulProgress*100/ulProgressMax:0) );
	m_bsProgressMsg = wc;

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}
STDMETHODIMP CResizer::OnStartBinding( /*[in]*/DWORD dwReserved, /*[in]*/IBinding* pBinding )
{
	m_spBinding = pBinding;
	m_bsProgressMsg = L"Uploading 0%";
	return S_OK;
}
STDMETHODIMP CResizer::PreBindMoniker( /*[in]*/IBindCtx* pBindCtx, /*[in]*/IMoniker* pMoniker )
{	
	return S_OK;
}
STDMETHODIMP CResizer::OnBindingFailure( /*[in]*/HRESULT hr, /*[in]*/BSTR bsError )
{
BEGIN_TRY;

	if( FAILED(hr) )
		m_bsUploadError = bsError;

	m_spBinding = NULL;

END_TRY( this, __uuidof(IResizer) );
TRY_EXIT;
}

