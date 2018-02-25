#if !defined(_GDIP_HLP_H_)
#define _GDIP_HLP_H_

#pragma once

#ifndef _GDIPLUS_H
	#error GDIPHlp.h requires "Gdiplus.h" to be included first
#endif

#ifndef _ERR_HLP_H_
	#error GDIPHlp.h requires "ErrHlp.h" to be included first
#endif

#ifndef _WINDOWS_
	#error GDIPHlp.h requires "windows.h" to be included first
#endif

#ifndef _INC_MATH
	#error GDIPHlp.h requires "math.h" to be included first
#endif

#ifdef _DEBUG
	#ifndef _INC_CRTDBG
		#error GDIPHlp.h requires "CrtDbg.h" to be included first
	#endif
#endif

inline void __fastcall NormalizeRect( RECT& rRC ) throw()
{
	if( rRC.left > rRC.right ) 
		rRC.left ^= rRC.right, rRC.right ^= rRC.left, rRC.left ^= rRC.right;

	if( rRC.top > rRC.bottom ) 
		rRC.top ^= rRC.bottom, rRC.bottom ^= rRC.top, rRC.top ^= rRC.bottom;
}

inline LONG __fastcall RWidth( const RECT& rRC ) throw()
{
	return (rRC.left < rRC.right) ? (rRC.right - rRC.left):(rRC.left - rRC.right);
}

inline LONG __fastcall RHeight( const RECT& rRC ) throw()
{
	return (rRC.top < rRC.bottom) ? (rRC.bottom - rRC.top):(rRC.top - rRC.bottom);
}

inline void __fastcall RECTtoGPRECT( const RECT& rRC, Gdiplus::Rect& rpRC ) throw()
{
	RECT rTmp = rRC;
	NormalizeRect( rTmp );

	rpRC.X = rTmp.left, rpRC.Y = rTmp.top;
	rpRC.Width = rRC.right - rRC.left;
	rpRC.Height = rRC.bottom - rRC.top;
}

inline void __fastcall RECTtoGPRECTF( const RECT& rRC, Gdiplus::RectF& rpRC ) throw()
{
	RECT rTmp = rRC;
	NormalizeRect( rTmp );
#pragma warning( disable: 4244 )
	rpRC.X = rTmp.left, rpRC.Y = rTmp.top;
	rpRC.Width = rRC.right - rRC.left;
	rpRC.Height = rRC.bottom - rRC.top;
#pragma warning( default: 4244 )
}

inline void __fastcall GPRECTtoRECT( const Gdiplus::Rect& rpRC, RECT& rRC ) throw()
{
	rRC.left = rpRC.X, rRC.top = rpRC.Y;
	rRC.right = rRC.left + rpRC.Width;
	rRC.bottom = rRC.top + rpRC.Height;
}

inline void __fastcall GPRECTFtoRECT( const Gdiplus::RectF& rpRC, RECT& rRC ) throw()
{
#pragma warning( disable: 4244 )
	rRC.left = floor( rpRC.X ), rRC.top = floor( rpRC.Y );
	rRC.right = ceil( rRC.left + rpRC.Width );
	rRC.bottom = ceil( rRC.top + rpRC.Height );
#pragma warning( default: 4244 )
}

inline void __fastcall GRECTtoGPRECTF( const Gdiplus::Rect& rpRC, Gdiplus::RectF& rrF) throw()
{
#pragma warning( disable: 4244 )
	rrF.X = rpRC.X, rrF.Y = rpRC.Y;
	rrF.Width = rpRC.Width, rrF.Height = rpRC.Height;
#pragma warning( default: 4244 )
}

inline Gdiplus::Rect __fastcall GRECT( const RECT& rRC ) throw()
{
	Gdiplus::Rect gr;
	RECTtoGPRECT( rRC, gr );
	return gr;
}

inline Gdiplus::RectF __fastcall GRECTF( const RECT& rRC ) throw()
{
	Gdiplus::RectF gr;
	RECTtoGPRECTF( rRC, gr );
	return gr;
}

inline Gdiplus::RectF __fastcall GRECTF( const Gdiplus::Rect& rrg ) throw()
{
	Gdiplus::RectF gr;
	GRECTtoGPRECTF( rrg, gr );
	return gr;
}



void __fastcall HexToBin( LPCWSTR lpwsz, void* pOut, long lSz );
bool __fastcall AssignColor( CComVariant& rColor, const VARIANT& rVal );

int __fastcall GetEncoderClsid( const WCHAR* format, CLSID* pClsid ) throw();
int __fastcall GetMime( CLSID& rClsid, BSTR* pbsOut ) throw();
int __fastcall GetMimeByRowFormat( GUID& rClsid, BSTR* pbsOut ) throw();
int __fastcall GetEncoderClsidByMimeClsid( GUID& rClsidFmt, GUID& rClsidEncoder ) throw();

SIZE __fastcall GetStringWidth( Gdiplus::Font& rF, Gdiplus::Graphics& rGr, LPCTSTR lpsz ) throw();

#endif



