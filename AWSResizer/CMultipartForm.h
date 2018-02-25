#if !defined(_CMULTIPART_FORM_)
#define _CMULTIPART_FORM_

#pragma once

#include "resource.h"

#ifndef _ERR_HLP_H_
	#error CMultipartForm.h requires "ErrHlp.h" to be included first
#endif
#ifndef _RESOURCE_MANAGERS_
	#error CMultipartForm.h requires "resourcemanagers.h" to be included first
#endif


class CMemoryStream
{
private:
	//CComPtr<ILockBytes> m_spLockBytes;
	//CComPtr<IStorage> m_spStorage;
	CComPtr<IStream> m_spStream;
	std::basic_string<wchar_t> m_wsStreamName;
	SIZE_T m_szWrittenSize;
public:
	CMemoryStream( wchar_t* wcStreamName = L"Tmp" ): m_wsStreamName(wcStreamName)
	{
		m_szWrittenSize = 0;
	}
	void __fastcall Init( SIZE_T szInitSize = 0 );

	HGLOBAL __fastcall GetHANDLE()
	{
		HGLOBAL hgTmp = NULL;
		if( m_spStream.p )		
			CHK_COM( GetHGlobalFromStream(m_spStream.p, &hgTmp), L"getting stream data" );

		return hgTmp;
	}

	operator  IStream*()
	{
		return m_spStream.p;
	}
	SIZE_T __fastcall GetSize();
	SIZE_T __fastcall GetWrittenSize()
	{
		return m_szWrittenSize;
	}
	void __fastcall SeekToStart();

	SIZE_T __fastcall WriteString( const char* );
	SIZE_T __fastcall WriteBytes( LPBYTE lpb, SIZE_T sz );
	SIZE_T __fastcall WriteStream( IStream* pStm );

	void __fastcall CopyStreamToFile( LPCTSTR lpszFileName, DWORD dwCreationDisposition = CREATE_ALWAYS );	
};

class CMultipartForm
{
private:
	CMemoryStream m_stm;
	std::basic_string<char> m_strBoundry;	
	std::basic_string<char> m_strDelim;
	std::basic_string<char> m_strContDespositition;
public:
	CMultipartForm( char* pszBnd = NULL );
	~CMultipartForm()
	{
		/*if( NULL != m_hg )
			::GlobalFree( m_hg );
		m_hg = NULL;*/
	}

	void __fastcall Init( SIZE_T szInitSize = 0 )
	{
		m_stm.Init( szInitSize );
	}

	void  __fastcall AddPostingData( const char* pszName, LPBYTE lpbValue, SIZE_T size );
	void  __fastcall AddPostingFile( const char* pszName, const char* pszFileName, const char* pszContentType, IStream* pContent );
	void  __fastcall FinalizeStream()
	{
		m_stm.WriteString( m_strBoundry.substr(0, m_strBoundry.length() - 2).c_str() );
		m_stm.WriteString( "--" );
		m_stm.WriteString( m_strDelim.c_str() );
	}

	CMemoryStream& __fastcall GetStream()
	{
		return m_stm;
	}
	HGLOBAL __fastcall GetAsHGLOBAL();
	const char* __fastcall GetBoundary()
	{		
		return m_strBoundry.c_str();
	}
private:
	//std::basic_string<char> m_strFullBoundry;
	//HGLOBAL m_hg;
};
#endif
