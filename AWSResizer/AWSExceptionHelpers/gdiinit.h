#if !defined(_GDI_INIT_)
#define _GDI_INIT_

#pragma once

#ifndef _GDIPLUS_H
	#error GDIInit.h requires "Gdiplus.h" to be included first
#endif

#ifndef _ERR_HLP_H_
	#error GDIInit.h requires "ErrHlp.h" to be included first
#endif

#ifndef __ATLBASE_H__
	#error GDIInit.h requires "AtlBase.h" to be included first
#endif

#ifndef _INC_CRTDBG
	#error GDIInit.h requires "CRTDBG.H" to be included first
#endif


class CGDIPlusInitializer
{
public:

	typedef CMyLock<CComAutoCriticalSection> TLock;

	static CGDIPlusInitializer& __fastcall Instance() throw()
	{
		return m_gpiInstance;
	}

	void __fastcall Initialize()
	{
		TLock lock( m_csRefCount );
		if( m_lRefCount++ == 0 )
			CHK_GDIP( Gdiplus::GdiplusStartup(&m_pulToken, &m_gdiplusStartupInput, NULL),
				L"On GdiplusStartup" );
	}

	void __fastcall Uninitialize()
	{
		TLock lock( m_csRefCount );
		_ASSERTE( m_lRefCount > 0 );

		if( --m_lRefCount == 0 ) 
			Gdiplus::GdiplusShutdown( m_pulToken );
	}

	~CGDIPlusInitializer() throw()
	{
		//_ASSERTE( m_lRefCount == 0 );
		if( m_lRefCount ) m_lRefCount = 1, Uninitialize();
	}

protected:
	CGDIPlusInitializer() throw(): m_lRefCount( 0L ), m_pulToken( NULL ) 
	{
	}

	
private:
	static CGDIPlusInitializer m_gpiInstance;

	__int64 m_lRefCount;
	CComAutoCriticalSection m_csRefCount;

	ULONG_PTR m_pulToken;
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
};


#endif

