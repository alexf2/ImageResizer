#include "stdafx.h"
#include "ErrHlp.h"
#include "GDIPHlp.h"

#pragma warning( disable : 4715 )

BYTE __fastcall HexVal( BYTE bVal )
{
	bVal = toupper( bVal );

	if( (bVal >= '0' && bVal <= '9') || (bVal >= 'A' && bVal <= 'F') )
		return (bVal >= '0' && bVal <= '9') ? (bVal - '0'):(bVal - 'A' + 10);
	else
		THROW_SIMPLE_STD_EXC( "converting HEX to byte", "bad hex digit is founded" );
}

#pragma warning( default : 4715 )

void __fastcall HexToBin( LPCWSTR lpwsz, void* pOut_, long lSz )
{
	LPBYTE lpTmp = (LPBYTE)_alloca( lSz * 2 );
	WideCharToMultiByte( CP_ACP, 0, lpwsz, -1, (char*)lpTmp, lSz * 2, NULL, NULL );

	LPBYTE pOut = (LPBYTE)pOut_;
	for( ; lSz > 0; --lSz, lpTmp += 2, ++pOut )
		*pOut = (HexVal( lpTmp[0] ) << 4) + HexVal( lpTmp[1] );
}


bool __fastcall AssignColor( CComVariant& rColor, const VARIANT& rVal )
{
	bool bResult;
	switch( V_VT(&rVal) )
	{
		case VT_EMPTY:
		{
			if( V_VT(&rColor) == VT_EMPTY ) bResult = false;
			else rColor.Clear(), bResult = true;
			break;
		}
		case VT_I4:
		{			
			if( V_VT(&rColor) != VT_I4 ) rColor.Clear();
			if( V_VT(&rColor) == VT_I4 && V_I4(&rColor) == V_I4(&rVal) ) bResult = false;
			else bResult = true, rColor = rVal;
			break;
		}
		case VT_I2:
		{			
			if( V_VT(&rColor) != VT_I4 ) rColor.Clear();
			if( V_VT(&rColor) == VT_I4 && V_I4(&rColor) == V_I2(&rVal) ) bResult = false;
			else bResult = true, V_VT(&rColor) = VT_I4, V_I4(&rColor) = V_I2(&rVal);
			break;
		}
		case VT_BSTR:
		{			
			if( SysStringLen(V_BSTR(&rVal)) == 0 )
			{
				if( V_VT(&rColor) == VT_EMPTY ) bResult = false;
				else rColor.Clear(), bResult = true;
				break;
			}
			else if( V_BSTR(&rVal)[ 0 ] != L'#' )
			{
				CComVariant cv( V_BSTR(&rVal) );
				CHK_COM( cv.ChangeType(VT_I4), L"Converting BSTR into Long" );
				bResult = true, V_VT(&rColor) = VT_I4, V_I4(&rColor) = V_I4(&cv);
				break;
			}
			else if( SysStringLen(V_BSTR(&rVal)) != 7 )
				THROW_SIMPLE_STD_EXC( "decoding color from string",
					"String is incorrect. Example: #C0AF27" );

			if( V_BSTR(&rVal)[ 0 ] != L'#' )
				THROW_SIMPLE_STD_EXC( "decoding color from string",
					"prefix # is not found" );

			if( V_VT(&rColor) != VT_I4 ) rColor.Clear();

						
			long lVal = 0;
			HexToBin( &V_BSTR(&rVal)[ 1 ], &lVal, 3 );

			if( V_VT(&rColor) == VT_I4 && V_I4(&rColor) == lVal ) bResult = false;
			else bResult = true, V_VT(&rColor) = VT_I4, V_I4(&rColor) = lVal;
			break;
		}
		default:
			THROW_SIMPLE_STD_EXC( "putting Color",
				"Not allowed type. You can use empty, integer or string format of color" );
	};

	return bResult;
}



int __fastcall GetEncoderClsid( const WCHAR* format, CLSID* pClsid ) throw()
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}


int __fastcall GetMime( CLSID& rClsid, BSTR* pbsOut ) throw()
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageDecodersSize(&num, &size);
   if( size == 0 ) return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)( malloc(size) );
   if( pImageCodecInfo == NULL )
      return -1;  // Failure

   Gdiplus::GetImageDecoders( num, size, pImageCodecInfo );

   for( UINT j = 0; j < num; ++j )
   {
	   if( ::InlineIsEqualGUID(rClsid, pImageCodecInfo[j].Clsid) )
	  {
		  *pbsOut = ::SysAllocString( pImageCodecInfo[j].MimeType );
		  free( pImageCodecInfo );
	      return j;  // Success
	  }      
   }

   free( pImageCodecInfo );
   return -1;  // Failure
}

int __fastcall GetEncoderClsidByMimeClsid( GUID& rClsidFmt, GUID& rClsidEncoder ) throw()
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes	

	Gdiplus::GetImageDecodersSize( &num, &size );
	if( size == 0 ) return -1;  // Failure

	std::auto_ptr<Gdiplus::ImageCodecInfo> apInf( (Gdiplus::ImageCodecInfo*)new BYTE[size] );
	if( apInf.get() == NULL )
		return -1;
	Gdiplus::GetImageDecoders( num, size, apInf.get() );

	for( UINT j = 0; j < num; ++j )
	{
		if( ::InlineIsEqualGUID(rClsidFmt, apInf.get()[j].FormatID) )
		{
			rClsidEncoder = apInf.get()[ j ].Clsid;
			return j;
		}
	}
	return -1;
}

int __fastcall GetMimeByRowFormat( GUID& rClsid, BSTR* pbsOut ) throw()
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

   Gdiplus::GetImageDecodersSize(&num, &size);
   if( size == 0 ) return -1;  // Failure

   pImageCodecInfo = (Gdiplus::ImageCodecInfo*)( malloc(size) );
   if( pImageCodecInfo == NULL )
      return -1;  // Failure

   Gdiplus::GetImageDecoders( num, size, pImageCodecInfo );

   for( UINT j = 0; j < num; ++j )
   {
	  if( ::InlineIsEqualGUID(rClsid, pImageCodecInfo[j].FormatID) )
	  {
		  *pbsOut = ::SysAllocString( pImageCodecInfo[j].MimeType );
		  free( pImageCodecInfo );
	      return j;  // Success
	  }      
   }

   free( pImageCodecInfo );
   return -1;  // Failure
}

SIZE __fastcall GetStringWidth( Gdiplus::Font& rF, Gdiplus::Graphics& rGr, LPCTSTR lpsz ) throw()
{
	LOGFONTA lf; memset( &lf, 0, sizeof lf );
	rF.GetLogFontA( &rGr, &lf );

	HFONT hf = CreateFontIndirectA( &lf );

	HDC hdc = rGr.GetHDC();
	HFONT hfOld = (HFONT)SelectObject( hdc, hf );

	SIZE sz = { 0, 0 };
	GetTextExtentPoint32( hdc, lpsz, (int)_tcslen(lpsz), &sz );

	SelectObject( hdc, hfOld );
	rGr.ReleaseHDC( hdc );

	::DeleteObject( hf );

	return sz;
}
