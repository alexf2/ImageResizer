// Created by Microsoft (R) C/C++ Compiler Version 13.10.3077
//
// c:\work\resizersln\awsresizer\resizer.mrg.h
// compiler-generated file created 11/18/05 at 21:18:15
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//


//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

// M00PRAGMA("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code

// Resizer.h : Declaration of the CResizer
#pragma once
#include "resource.h"       // main symbols



#define DISPID_WIDTH                    1
#define DISPID_HEIGHT                   2
#define DISPID_NAVIGATEONFINISHURL      3
#define DISPID_IMAGEFULLNAME            4
#define DISPID_SELECTIMAGE              5
#define DISPID_UPLOADIMAGE              6
#define DISPID_UPLOADURL                7
#define DISPID_MAXWIDTH                 8
#define DISPID_MAXHEIGHT                9
#define DISPID_IMAGEPROPSDESCRIPTION    10

#define DISPID_INITIALPATH              11
#define DISPID_DIALOGTITLE              12
#define DISPID_DIALOGMASKS              13
#define DISPID_DIALOGDEFAULTEXT         14
#define DISPID_DIALOGCENTERINPARENT     15

class ATL_NO_VTABLE CResizer;

typedef MSHTML::HTMLDocumentEvents2 CPINTF_Doc;
typedef IDispEventImpl< 0, CResizer, &__uuidof(CPINTF_Doc), &LIBID_MSHTML, 4, 0 > 
	THTMLDocumentEvents;

typedef MSHTML::HTMLWindowEvents2 CPINTF_Window;
typedef IDispEventImpl< 1, CResizer, &__uuidof(CPINTF_Window), &LIBID_MSHTML, 4, 0 >
	THTMLWindowEvents;

// IResizer
[
	object,
	uuid(DE079467-E2D6-40BD-81EE-B63DF5BE3C46),
	dual, oleautomation, nonextensible, hidden,
	helpstring("IResizer Interface"),
	pointer_default(unique)
]
__interface IResizer: public IDispatch
{
    //Custom props
    [propput, bindable, requestedit, id(DISPID_WIDTH)]
    HRESULT Width( [in]long lWidth );
    [propget, bindable, requestedit, id(DISPID_WIDTH)]
    HRESULT Width( [out,retval]long* lWidth );

    [propput, bindable, requestedit, id(DISPID_HEIGHT)]
    HRESULT Height( [in]long lHeight );
    [propget, bindable, requestedit, id(DISPID_HEIGHT)]
    HRESULT Height( [out,retval]long* lHeight );

    [propput, bindable, requestedit, id(DISPID_NAVIGATEONFINISHURL)]
    HRESULT NavigateOnFinishUrl( [in]BSTR bsURL );
    [propget, bindable, requestedit, id(DISPID_NAVIGATEONFINISHURL)]
    HRESULT NavigateOnFinishUrl( [out,retval]BSTR* pbsURL );

    [propput, bindable, requestedit, id(DISPID_IMAGEFULLNAME)]
    HRESULT ImageFullName( [in]BSTR bsURL );
    [propget, bindable, requestedit, id(DISPID_IMAGEFULLNAME)]
    HRESULT ImageFullName( [out,retval]BSTR* pbsURL );

    [propput, bindable, requestedit, id(DISPID_UPLOADURL)]
    HRESULT UploadUrl( [in]BSTR bsURL );
    [propget, bindable, requestedit, id(DISPID_UPLOADURL)]
    HRESULT UploadUrl( [out,retval]BSTR* pbsURL );

    [propput, bindable, requestedit, id(DISPID_MAXWIDTH)]
    HRESULT MaxWidth( [in]long lWidth );
    [propget, bindable, requestedit, id(DISPID_MAXWIDTH)]
    HRESULT MaxWidth( [out,retval]long* plWidth );

    [propput, bindable, requestedit, id(DISPID_MAXHEIGHT)]
    HRESULT MaxHeight( [in]long lHeight );
    [propget, bindable, requestedit, id(DISPID_MAXHEIGHT)]
    HRESULT MaxHeight( [out,retval]long* plHeight );

    [propget, id(DISPID_IMAGEPROPSDESCRIPTION)]
    HRESULT ImagePropsDescription( [out,retval]BSTR* pbsDescr );
    //End Custom props

    //Custom Mthods
    [id(DISPID_SELECTIMAGE)]
    HRESULT SelectImage( [out,retval]BSTR* bsImgFileName );

    [id(DISPID_UPLOADIMAGE)]
    HRESULT UploadImage( void );
    //End Custom Mthods

    //Stock props
	[propput, bindable, requestedit, id(DISPID_BACKCOLOR)]
	HRESULT BackColor([in]VARIANT* clr);
	[propget, bindable, requestedit, id(DISPID_BACKCOLOR)]
	HRESULT BackColor([out,retval]VARIANT* pclr);

	[propput, bindable, requestedit, id(DISPID_BORDERCOLOR)]
	HRESULT BorderColor([in]VARIANT* style);
	[propget, bindable, requestedit, id(DISPID_BORDERCOLOR)]
	HRESULT BorderColor([out, retval]VARIANT* pstyle);

	[propput, bindable, requestedit, id(DISPID_BORDERWIDTH)]
	HRESULT BorderWidth([in]long width);
	[propget, bindable, requestedit, id(DISPID_BORDERWIDTH)]
	HRESULT BorderWidth([out, retval]long* width);

	[propput, bindable, requestedit, id(DISPID_FORECOLOR)]
	HRESULT ForeColor([in]VARIANT* clr);
	[propget, bindable, requestedit, id(DISPID_FORECOLOR)]
	HRESULT ForeColor([out,retval]VARIANT* pclr);

	[propput, bindable, requestedit, id(DISPID_BORDERVISIBLE)]
	HRESULT BorderVisible([in]VARIANT_BOOL vbool);

	[propget, bindable, requestedit, id(DISPID_BORDERVISIBLE)]
	HRESULT BorderVisible([out, retval]VARIANT_BOOL* pbool);
    //End Stock Props

    //File selector props
    [propput, bindable, requestedit, id(DISPID_INITIALPATH)]
    HRESULT InitialPath( [in]BSTR bsPath );

    [propput, bindable, requestedit, id(DISPID_DIALOGTITLE)]
    HRESULT DialogTitle( [in]BSTR bsPath );
    [propget, bindable, requestedit, id(DISPID_DIALOGTITLE)]
    HRESULT DialogTitle( [out, retval]BSTR* pbs );

    [propput, bindable, requestedit, id(DISPID_DIALOGMASKS)]
    HRESULT DialogMasks( [in]BSTR bsMasks );
    [propget, bindable, requestedit, id(DISPID_DIALOGMASKS)]
    HRESULT DialogMasks( [out, retval]BSTR* pbsMasks );

    [propput, bindable, requestedit, id(DISPID_DIALOGDEFAULTEXT)]
    HRESULT DialogDefaultExt( [in]BSTR bsExt );
    [propget, bindable, requestedit, id(DISPID_DIALOGDEFAULTEXT)]
    HRESULT DialogDefaultExt( [out, retval]BSTR* pbsExt );

    [propput, bindable, requestedit, id(DISPID_DIALOGCENTERINPARENT)]
    HRESULT DialogCenterInParent( [in]VARIANT_BOOL vCenter );
    [propget, bindable, requestedit, id(DISPID_DIALOGCENTERINPARENT)]
    HRESULT DialogCenterInParent( [out, retval]VARIANT_BOOL* pvCenter );
};


// _IResizerEvents
[
	uuid("8E27D881-DA9C-471A-86E9-D45FB12CE2B4"),
	dispinterface,
	helpstring("_IResizerEvents Interface")
]
__interface _IResizerEvents
{
}; 

class CGDIPlusInitializer;
extern CGDIPlusInitializer _GDIPInitializer;

//+++ Start Injected Code For Attribute 'event'
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
#pragma comment(lib, "comsupp.lib")

//--- End Injected Code For Attribute 'event'


// CResizer
[
	coclass,
	threading( "apartment" ),
	aggregatable( "never" ),
	vi_progid( "AWSResizer.Resizer" ),
	progid( "AWSResizer.Resizer.1" ),
	version( 1.0 ),
	uuid( "5A0E70A5-9569-4408-B1C8-01BF404634AD" ),
	helpstring( "Resizer Class" ),
	event_source( "com" ),    
	support_error_info( IResizer ),
	registration_script( "control.rgs" ),
    default(IResizer),
    implements_category( "CATID_Control" ),
    implements_category( "CATID_Insertable" ),
    implements_category( "CATID_SafeForScripting" ),
    implements_category( "CATID_SafeForInitializing" )
]
class ATL_NO_VTABLE CResizer:
	//public CStockPropImpl<CResizer, IResizer>,

	//public IPersistStreamInitImpl<CResizer>,
    public IPersistPropertyBagImpl<CResizer>,
    //public IPersistStorageImpl<CResizer>,

	public IOleControlImpl<CResizer>,
	public IOleObjectImpl<CResizer>,
	public IOleInPlaceActiveObjectImpl<CResizer>,
    public IOleInPlaceObjectWindowlessImpl<CResizer>,
	public IViewObjectExImpl<CResizer>,

	//public IObjectWithSiteImpl<CResizer>,
	public IQuickActivateImpl<CResizer>,
    public IObjectSafetyImpl<CResizer,
		INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,

    public IProvideClassInfo2Impl<&__uuidof(CResizer), NULL, &CAtlModule::m_libid>,
    //public IConnectionPointContainerImpl<CResizer>,
    //public IPropertyNotifySinkCP<CResizer>,

	public CComControl<CResizer>,
    public IDispatchImpl<IResizer, &__uuidof(IResizer)>,

    public THTMLWindowEvents,
    public THTMLDocumentEvents,

	public IBindingNotify
,
    /*+++ Added Baseclass */ public IConnectionPointContainerImpl<CResizer>,
    /*+++ Added Baseclass */ public IPropertyNotifySinkCP<CResizer>,
    /*+++ Added Baseclass */ public CComCoClass<CResizer, &__uuidof(CResizer)>,
    /*+++ Added Baseclass */ public CComObjectRootEx<CComSingleThreadModel>,
    /*+++ Added Baseclass */ public ISupportErrorInfo
,
    /*+++ Added Baseclass */ public IConnectionPointImpl<CResizer, &__uuidof(::_IResizerEvents), CComDynamicUnkArray>
{

friend class CStockPropImpl<CResizer, IResizer>;
friend class IQuickActivateImpl<CResizer>;

public:
BEGIN_SINK_MAP( CResizer )
    SINK_ENTRY_EX( 0, (__uuidof(CPINTF_Doc)), DISPID_HTMLDOCUMENTEVENTS2_ONSTOP, OnStop_Document )
    SINK_ENTRY_EX( 1, (__uuidof(CPINTF_Window)), DISPID_HTMLWINDOWEVENTS2_ONUNLOAD, OnUnload )	
END_SINK_MAP()

public:
    CResizer():
      m_clrBackColorCust( (long)RGB(0xE7, 0xB9, 0x8A), VT_I4 ),
      m_clrBorderColorCust( (long)RGB(0xae, 0x7e, 0x48), VT_I4 ),
      m_clrForeColorCust( (long)RGB(0x75, 0x12, 0x0D), VT_I4 )
	{
        m_bAdvised = m_bAdviseDoc = m_bADviseWindow = false;
        m_dwSafety = 0;

        m_bBorderVisible = VARIANT_TRUE;
        m_lHeight = m_lWidth = 200;
        m_lMaxHeight = m_lMaxWidth = 500;
        m_nBorderWidth = 1;

        memset( &m_rcClip, 0, sizeof m_rcClip );		
		memset( &m_rcOld, 0, sizeof m_rcOld );        
        m_lNewW = m_lNewH = 0;

        try
        {
            _TCHAR buff[ _MAX_PATH ];
            if( _tgetcwd(buff, MAX_PATH) != NULL )
                m_bsInitialPath = buff;
            else
                m_bsInitialPath = L".\\";

            CComBSTR bsTmp( L"All files (*.*)\\*.*" );
            put_DialogMasks( bsTmp );
            m_pfd.nFilterIndex = 0;
        }
        catch(...)
        {
        }
	}

DECLARE_OLEMISC_STATUS(
    OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST |
    OLEMISC_NOUIACTIVATE
)

/*BEGIN_CONNECTION_POINT_MAP( CResizer )
	CONNECTION_POINT_ENTRY( IID_IPropertyNotifySink )
END_CONNECTION_POINT_MAP()*/

BEGIN_PROP_MAP( CResizer )
	PROP_DATA_ENTRY( "_cx", m_sizeExtent.cx, VT_UI4 )
	PROP_DATA_ENTRY( "_cy", m_sizeExtent.cy, VT_UI4 )    

    //Stock Props
	PROP_ENTRY( "BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage )
	PROP_ENTRY( "BorderColor", DISPID_BORDERCOLOR, CLSID_NULL )
	PROP_ENTRY( "BorderVisible", DISPID_BORDERVISIBLE, CLSID_NULL )
	PROP_ENTRY( "BorderWidth", DISPID_BORDERWIDTH, CLSID_NULL )
	PROP_ENTRY( "ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage )

    //Persistable Custom Props
    PROP_ENTRY( "Width", DISPID_WIDTH, CLSID_NULL )
    PROP_ENTRY( "Height", DISPID_HEIGHT, CLSID_NULL )
    PROP_ENTRY( "NavigateOnFinishUrl", DISPID_NAVIGATEONFINISHURL, CLSID_NULL )
    PROP_ENTRY( "ImageFullName", DISPID_IMAGEFULLNAME, CLSID_NULL )
    PROP_ENTRY( "UploadUrl", DISPID_UPLOADURL, CLSID_NULL )
    PROP_ENTRY( "MaxWidth", DISPID_MAXWIDTH, CLSID_NULL )
    PROP_ENTRY( "MaxHeight", DISPID_MAXHEIGHT, CLSID_NULL )

    //PROP_ENTRY( "InitialPath", DISPID_INITIALPATH, CLSID_NULL )
    PROP_ENTRY( "DialogTitle", DISPID_DIALOGTITLE, CLSID_NULL )
    PROP_ENTRY( "DialogMasks", DISPID_DIALOGMASKS, CLSID_NULL )
    PROP_ENTRY( "DialogDefaultExt", DISPID_DIALOGDEFAULTEXT, CLSID_NULL )
    PROP_ENTRY( "DialogCenterInParent", DISPID_DIALOGCENTERINPARENT, CLSID_NULL )        

	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

/*BEGIN_COM_MAP( CResizer )
    COM_INTERFACE_ENTRY( IResizer )
	COM_INTERFACE_ENTRY( IDispatch )

    COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
    COM_INTERFACE_ENTRY( IObjectWithSite )

    COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
    COM_INTERFACE_ENTRY2(IPersist, IPersistPropertyBag)

    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IObjectSafety)
    COM_INTERFACE_ENTRY(IConnectionPointContainer)

    COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IID(IID_IProvideClassInfo, IProvideClassInfo2)
END_COM_MAP()*/

BEGIN_MSG_MAP( CResizer )
	CHAIN_MSG_MAP( CComControl<CResizer> )
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	__event __interface _IResizerEvents;
// IViewObjectEx
	DECLARE_VIEW_STATUS( VIEWSTATUS_OPAQUE ) //VIEWSTATUS_SOLIDBKGND

// IResizer
public:
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT OnDrawAdvanced( ATL_DRAWINFO& di )  throw();
    void __fastcall DrawClip( Gdiplus::Bitmap* pbmpDraw, Gdiplus::Graphics* pGr, RECT& rcVis, int iXOff, int iYOff );

    void __fastcall Internal_ContainerToControl( LONG*, int iCountPoints ) const throw() ;
	void __fastcall Internal_ContainerToControl( INT*, int iCountPoints ) const throw() ;
	void __fastcall Internal_ContainerToControl( Gdiplus::REAL*, int iCountPoints ) const throw() ;

    long __fastcall XOff() const throw()
	{
		return m_rcPos.left;
	}
	long __fastcall YOff() const throw()
	{
		return m_rcPos.top;
	}

    void __fastcall ContainerToControl( RECT& rr ) const throw()
	{
		Internal_ContainerToControl( (LONG*)&rr, 2 );
	}
	void __fastcall ContainerToControl( POINT& rpt ) const throw()
	{
		Internal_ContainerToControl( (LONG*)&rpt, 1 );
	}
	void __fastcall ContainerToControl( LONG& lX, LONG& lY ) const throw()
	{
		LONG larr[ 2 ] = { lX, lY };
		Internal_ContainerToControl( larr, 1 );
		lX = larr[ 0 ], lY = larr[ 1 ];
	}
	void __fastcall ContainerToControl( Gdiplus::Point& rpt ) const throw()
	{
		Internal_ContainerToControl( (INT*)&rpt, 1 );
	}
	void __fastcall ContainerToControl( Gdiplus::PointF& rptf ) const throw()
	{
		Internal_ContainerToControl( (Gdiplus::REAL*)&rptf, 1 );
	}
	void __fastcall ContainerToControl( Gdiplus::Rect& rr ) const throw()
	{
		Internal_ContainerToControl( (INT*)&rr, 1 );
	}
	void __fastcall ContainerToControl( Gdiplus::RectF& rrf ) const throw()
	{
		Internal_ContainerToControl( (Gdiplus::REAL*)&rrf, 1 );
	}

    HRESULT FinalConstruct() throw();
	void FinalRelease() throw();

//IObjectSafety
public:
	STDMETHOD(GetInterfaceSafetyOptions)( REFIID riid,
										  DWORD *pdwSupportedOptions,
										  DWORD *pdwEnabledOptions ) throw();
	STDMETHOD(SetInterfaceSafetyOptions)( REFIID riid,
                                          DWORD dwOptionSetMask,
                                          DWORD dwEnabledOptions ) throw();
//IObjectWithSite
public:
    //STDMETHOD(SetSite)( IUnknown *pUnkSite ) throw();
//IOleObject
public:
    STDMETHOD(SetClientSite)( IOleClientSite *pUnkSite ) throw();

public:
    HRESULT IOleInPlaceObject_SetObjectRects( LPCRECT prcPos, LPCRECT prcClip );
    RECT m_rcClip, m_rcOld;
    long m_lNewW, m_lNewH;

    void __fastcall AdjustBounds();
    void __fastcall GetRecommendedControlSize( SIZEL& rSz );

protected:
    //Stock
    void OnBackColorChanged();
    void OnBorderColorChanged();
    void OnBorderVisibleChanged();
    void OnBorderWidthChanged();
    void OnForeColorChanged();

    //Custom
    void OnWidthChanged();
    void OnHeightChanged();
    void OnNavigateOnFinishUrlChanged();
    void OnImageFullNameChanged();
    void OnUploadUrlChanged();
    void OnMaxWidthChanged();
    void OnMaxHeightChanged();

private:
    std::auto_ptr<Gdiplus::SolidBrush> m_apBrushBack, m_apBrushProgress;
    std::auto_ptr<Gdiplus::Color> m_apClrBack, m_apClrBorder, m_apForeColor;
    std::auto_ptr<Gdiplus::Pen> m_apPenBorder, m_apPenProgress;
    std::auto_ptr<Gdiplus::Image> m_apImgOrig, m_apImgThumb;

    Gdiplus::SolidBrush* __fastcall GetBrushBack();
    Gdiplus::SolidBrush* __fastcall GetBrushProgress();
    Gdiplus::Color* __fastcall GetClrBack();
    Gdiplus::Color* __fastcall GetClrBorder();
    Gdiplus::Color* __fastcall GetClrFore();
    Gdiplus::Pen* __fastcall GetPenBorder();
    Gdiplus::Pen* __fastcall GetPenProgress();
    Gdiplus::Image* __fastcall GetImgOrig();
    Gdiplus::Image* __fastcall GetImgThumb( bool bForPreview );

    static std::auto_ptr<Gdiplus::Color> __fastcall GetNewColor( CComVariant& rClr );


    void __fastcall DiscardAllGRIResources()
    {
        FreeAutoPtr( m_apBrushBack );
        FreeAutoPtr( m_apBrushProgress );                
        FreeAutoPtr( m_apPenBorder );
        FreeAutoPtr( m_apPenProgress );
        FreeAutoPtr( m_apImgOrig );
        FreeAutoPtr( m_apImgThumb );

        FreeAutoPtr( m_apForeColor );
        FreeAutoPtr( m_apClrBack );
        FreeAutoPtr( m_apClrBorder );
    }
    

//Custom Props
public:
    /*IMPLEMENT_STOCKPROP( long, Width, lWidth, DISPID_WIDTH )
    IMPLEMENT_STOCKPROP( long, Height, lHeight, DISPID_HEIGHT )
    IMPLEMENT_BSTR_STOCKPROP( NavigateOnFinishUrl, bsNavigateOnFinishUrl, DISPID_NAVIGATEONFINISHURL )
    IMPLEMENT_BSTR_STOCKPROP( ImageFullName, bsImageFullName, DISPID_IMAGEFULLNAME )
    IMPLEMENT_BSTR_STOCKPROP( UploadUrl, bsUploadUrl, DISPID_UPLOADURL )
    IMPLEMENT_STOCKPROP( long, MaxWidth, lMaxWidth, DISPID_MAXWIDTH )
    IMPLEMENT_STOCKPROP( long, MaxHeight, lMaxHeight, DISPID_MAXHEIGHT )*/

    STDMETHOD(put_Width)( long lWidth ) throw();
    STDMETHOD(get_Width)( long* lWidth ) throw();

    STDMETHOD(put_Height)( long lHeight ) throw();
    STDMETHOD(get_Height)( long* lHeight ) throw();

    STDMETHOD(put_NavigateOnFinishUrl)( BSTR bsURL ) throw();
    STDMETHOD(get_NavigateOnFinishUrl)( BSTR* pbsURL ) throw();

    STDMETHOD(put_ImageFullName)( BSTR bsURL ) throw();
    STDMETHOD(get_ImageFullName)( BSTR* pbsURL ) throw();

    STDMETHOD(put_UploadUrl)( BSTR bsURL ) throw();
    STDMETHOD(get_UploadUrl)( BSTR* pbsURL ) throw();

    STDMETHOD(put_MaxWidth)( long lWidth ) throw();
    STDMETHOD(get_MaxWidth)( long* plWidth ) throw();

    STDMETHOD(put_MaxHeight)( long lHeight ) throw();
    STDMETHOD(get_MaxHeight)( long* plHeight ) throw();

    STDMETHOD(get_ImagePropsDescription)( BSTR* pbsDescr ) throw();

//dialog management
public:
    STDMETHOD(put_InitialPath)( BSTR bsPath );

    STDMETHOD(put_DialogTitle)( BSTR bsPath );    
    STDMETHOD(get_DialogTitle)( BSTR* pbs );

    STDMETHOD(put_DialogMasks)( BSTR bsMasks );    
    STDMETHOD(get_DialogMasks)( BSTR* pbsMasks );

    STDMETHOD(put_DialogDefaultExt)( BSTR bsExt );    
    STDMETHOD(get_DialogDefaultExt)( BSTR* pbsExt );

    STDMETHOD(put_DialogCenterInParent)( VARIANT_BOOL vCenter );    
    STDMETHOD(get_DialogCenterInParent)( VARIANT_BOOL* pvCenter );

//Custom Methods
public:
    STDMETHOD(SelectImage)( BSTR* bsImgFileName ) throw();
    STDMETHOD(UploadImage)( void ) throw();

//Stock properties overridees
public:
    /*IMPLEMENT_STOCKPROP_VARIANT( BackColor, clrBackColorCust, DISPID_BACKCOLOR )
    IMPLEMENT_STOCKPROP_VARIANT( BorderColor, clrBorderColorCust, DISPID_BORDERCOLOR )
    IMPLEMENT_STOCKPROP_VARIANT( ForeColor, clrForeColorCust, DISPID_FORECOLOR )*/

    STDMETHOD(put_BackColor)( VARIANT* pV ) throw();
    STDMETHOD(get_BackColor)( VARIANT* pV ) throw();

    STDMETHOD(put_BorderColor)( VARIANT* pV ) throw();
    STDMETHOD(get_BorderColor)( VARIANT* pV ) throw();

    STDMETHOD(put_BorderVisible)( VARIANT_BOOL pV ) throw();
    STDMETHOD(get_BorderVisible)( VARIANT_BOOL* pV ) throw();

    STDMETHOD(put_BorderWidth)( long pV ) throw();
    STDMETHOD(get_BorderWidth)( long* pV ) throw();

    STDMETHOD(put_ForeColor)( VARIANT* pV ) throw();
    STDMETHOD(get_ForeColor)( VARIANT* pV ) throw();

protected:
    //Stock prop. members
	CComVariant m_clrBackColorCust; //suffix Cust added to override standard impl
    CComVariant m_clrBorderColorCust;
    CComVariant m_clrForeColorCust;
    LONG m_nBorderWidth;
    VARIANT_BOOL m_bBorderVisible;

protected:
    //Custom prop. members
    long m_lWidth;
    long m_lHeight;
    CComBSTR m_bsNavigateOnFinishUrl;
    CComBSTR m_bsImageFullName;
    CComBSTR m_bsUploadUrl;
    long m_lMaxWidth;
    long m_lMaxHeight;    

protected:
    DWORD  m_dwSafety;
    CComBSTR m_bsErrLoadingImgMsg;

private:
    TParamsFileDlg m_pfd;    
    CComBSTR m_bsInitialPath;
    //CComPtr< IOleInPlaceSite > m_spSite;

    HWND __fastcall GetHWNDOfParent();
    void __fastcall SetInitialPath( BSTR );
    CComBSTR __fastcall AskFileName();

    //SHDocVw::IWebBrowser2Ptr  m_spWebBrowser2;
	MSHTML::IHTMLWindow2Ptr   m_spWindow2;
	MSHTML::IHTMLDocument2Ptr m_spHDoc2;
    MSHTML::IHTMLElementPtr   m_spObjectTag;

    bool m_bAdviseDoc, m_bADviseWindow, m_bAdvised;
    void __fastcall HandsoffEvents()
    {
		StopBinding();

        if( m_bAdviseDoc && m_spHDoc2.GetInterfacePtr() )
        {
            m_bAdviseDoc = false;
            THTMLDocumentEvents::DispEventUnadvise( m_spHDoc2.GetInterfacePtr() );
        }
        if( m_bADviseWindow && m_spWindow2.GetInterfacePtr() )
        {
            m_bADviseWindow = false;
            THTMLWindowEvents::DispEventUnadvise( m_spWindow2.GetInterfacePtr() );
        }

        m_bAdvised = false;

        m_spWindow2 = NULL;
        m_spHDoc2 = NULL;
        m_spObjectTag = NULL;
    }

public:
    void __stdcall OnStop_Document( MSHTML::IHTMLEventObj* pEvtObj ) throw()
    {
		StopBinding();
    }
    HRESULT __stdcall OnUnload( MSHTML::IHTMLEventObj* pEvtObj ) throw()
    {		
        HandsoffEvents();	
	    return S_OK;
    }

//IBindingNotify
public:
	STDMETHOD(OnProgress)( /*[in]*/IBindStatusCallback* pSender, /*[in]*/ULONG ulProgress,
		/*[in]*/ULONG ulProgressMax, /*[in]*/ULONG ulStatusCode, /*[in]*/BSTR bsStatusText );

	STDMETHOD(OnStartBinding)( /*[in]*/DWORD dwReserved, /*[in]*/IBinding* pBinding );
	STDMETHOD(PreBindMoniker)( /*[in]*/IBindCtx* pBindCtx, /*[in]*/IMoniker* pMoniker );
	STDMETHOD(OnBindingFailure)( /*[in]*/HRESULT hr, /*[in]*/BSTR bsError );

private:
	CComPtr<IBinding> m_spBinding;
	CComBSTR m_bsUploadError;
	CComBSTR m_bsProgressMsg;
	void __fastcall StopBinding()
	{
		if( m_spBinding.p )
			m_spBinding->Abort();
		m_bsUploadError = L"Upload is aborted";
	}
	bool static IsRelativeURL( BSTR bs );

	//+++ Start Injected Code For Attribute 'event'
    #injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"

	//--- End Injected Code For Attribute 'event'

	//+++ Start Injected Code For Attribute 'support_error_info'
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    BEGIN_CONNECTION_POINT_MAP(CResizer)
        CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
        #injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
        CONNECTION_POINT_ENTRY(__uuidof(::_IResizerEvents))
        #injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    END_CONNECTION_POINT_MAP()
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    static DWORD* GetOpCodes() 
    {
        static DWORD rgOps[] = 
            					{
            						0x70000000,
            0x30004000,
            0x80000002,
            0x50000000,
            0x3000c000,
            0x80000004,
            0x60000000,
            0x30014000,
            0x80000002,
            0x50000000,
            0x3000c000,
            0x80000004,
            0x30018000,
            0x80000001,
            0x60000000,
            0x1000c000,
            0x3000c000,
            0x50000000,
            0x20010000,
            0x30010000,
            0x80000002,
            0x50000000,
            0x3001c000,
            0x80000001,
            0x30020000,
            0x80000005,
            0x30024000,
            0x8000000a,
            0x50000000,
            0x8002c00c,
            0x60000000,
            0x20034000,
            0x30034000,
            0x20038000,
            0x30038000,
            0x8000000f,
            0x30040000,
            0x80000011,
            0x50000000,
            0x30048000,
            0x80000013,
            0x60000000,
            0x80050015,
            0x30058000,
            0x80000017,
            0x30060000,
            0x80000019,
            0x60000000,
            0x60000000,
            0x60000000,
            0
            					};
        return rgOps;
    }
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    static RGSDWORD* GetOpcodeDWORDVals() 
    {
        static RGSDWORD rgDWORDS[] = 
            					{
            						{0, 0}
            					};
        return rgDWORDS;
    }
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    static RGSBinary* GetOpcodeBinaryVals() 
    {

        static RGSBinary rgBinary[] = 
            					{
            						{0, 0}
            					};
        return rgBinary;
    }
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    static RGSStrings* GetOpcodeStringVals() 
    {
        static RGSStrings rgStrings[] = 
            					{
            						{_T(""),0 }, 
            {_T("AWSResizer.Resizer.1"),0 }, 
            {_T("%FriendlyName%"),1 }, 
            {_T("CLSID"),0 }, 
            {_T("{5A0E70A5-9569-4408-B1C8-01BF404634AD}"),0 }, 
            {_T("AWSResizer.Resizer"),0 }, 
            {_T("CurVer"),0 }, 
            {_T("ProgID"),0 }, 
            {_T("VersionIndependentProgID"),0 }, 
            {_T("%MODULETYPE%"),1 }, 
            {_T("%MODULE%"),1 }, 
            {_T("ThreadingModel"),0 }, 
            {_T("apartment"),0 }, 
            {_T("Control"),0 }, 
            {_T("ToolboxBitmap32"),0 }, 
            {_T("%MODULE%, 1"),1 }, 
            {_T("MiscStatus"),0 }, 
            {_T("0"),0 }, 
            {_T("1"),0 }, 
            {_T("131473"),0 }, 
            {_T("AppID"),0 }, 
            {_T("%APPID%"),1 }, 
            {_T("TypeLib"),0 }, 
            {_T("%MODULEGUID%"),1 }, 
            {_T("Version"),0 }, 
            {_T("1.0"),0 }, 
            {NULL, 0}
            					};
        return rgStrings;
    }
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister) 
    {
        CRegistryVirtualMachine rvm;
        HRESULT hr;
        if (FAILED(hr = rvm.AddStandardReplacements()))
            return hr;
        rvm.AddReplacement(_T("FriendlyName"), GetObjectFriendlyName());
        return rvm.VMUpdateRegistry(GetOpCodes(), GetOpcodeStringVals(), GetOpcodeDWORDVals(), GetOpcodeBinaryVals(), bRegister);
    }
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    static const TCHAR* GetObjectFriendlyName() 
    {
        return _T("CResizer Object");
    }
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"

    DECLARE_NOT_AGGREGATABLE(CResizer);

#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    static const TCHAR* GetProgID() 
    {
        return _T("AWSResizer.Resizer.1");
    }
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    static const TCHAR* GetVersionIndependentProgID() 
    {
        return _T("AWSResizer.Resizer");
    }
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"
    BEGIN_COM_MAP(CResizer)
        COM_INTERFACE_ENTRY(IPersistPropertyBag)
        COM_INTERFACE_ENTRY(IPersist)
        COM_INTERFACE_ENTRY(IOleControl)
        COM_INTERFACE_ENTRY(IOleObject)
        COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
        COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceActiveObject)
        COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
        COM_INTERFACE_ENTRY(IOleInPlaceObject)
        COM_INTERFACE_ENTRY(IViewObjectEx)
        COM_INTERFACE_ENTRY(IViewObject2)
        COM_INTERFACE_ENTRY(IViewObject)
        COM_INTERFACE_ENTRY(IQuickActivate)
        COM_INTERFACE_ENTRY(IObjectSafety)
        COM_INTERFACE_ENTRY(IProvideClassInfo2)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
        COM_INTERFACE_ENTRY(IResizer)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(IBindingNotify)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()
#injected_line 332 "c:\\work\\resizersln\\awsresizer\\resizer.h"

    BEGIN_CATEGORY_MAP(CResizer)
        IMPLEMENTED_CATEGORY(CATID_Control)
        IMPLEMENTED_CATEGORY(CATID_Insertable)
        IMPLEMENTED_CATEGORY(CATID_SafeForScripting)
        IMPLEMENTED_CATEGORY(CATID_SafeForInitializing)
    END_CATEGORY_MAP()
#injected_line 170 "c:\\work\\resizersln\\awsresizer\\resizer.h"

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) 
        					
    {
        static const IID* rgErrorGuids[] = 
            						{
            							&__uuidof(IResizer)
            						};
        for (int i=0; i < sizeof(rgErrorGuids) / sizeof(rgErrorGuids[0]); i++)
						{
            if (InlineIsEqualGUID(*rgErrorGuids[i],riid))
                return S_OK;
        }
        return S_FALSE;
    } 

	//--- End Injected Code For Attribute 'support_error_info'
};

//+++ Start Injected Code For Attribute 'support_error_info'
#injected_line 170 "c:\\work\\resizersln\\awsresizer\\resizer.h"

				OBJECT_ENTRY_AUTO(__uuidof(CResizer), CResizer)
			
//--- End Injected Code For Attribute 'support_error_info'

