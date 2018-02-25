#include "stdafx.h"
#include "CMultipartForm.h"
#include <math.h>

void __fastcall CMemoryStream::CopyStreamToFile( LPCTSTR lpszFileName, DWORD dwCreationDisposition )
{
	USES_CONVERSION;

	CRcHolder< HANDLE, CFile_Manager > crhFile;
	crhFile = CHK_W32(
		::CreateFile( lpszFileName, GENERIC_WRITE, 0,
			NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL ),
		INVALID_HANDLE_VALUE,
		L"creating copy file" );

	STATSTG stg;
	CHK_COM( m_spStream->Stat(&stg, STATFLAG_NONAME), L"getting stream status" );
	/*std::auto_ptr<BYTE> spBytes( CHK_ALLOC(new BYTE[stg.cbSize.LowPart]) );

	ULONG ulReaded;
	CHK_COM( m_spStream->Read(spBytes.get(), stg.cbSize.LowPart, &ulReaded), L"reading from stream" );*/
	HGLOBAL hgTmp;
	//CHK_COM( GetHGlobalFromILockBytes(m_spLockBytes.p, &hgTmp), L"getting stream data" );
	CHK_COM( GetHGlobalFromStream(m_spStream.p, &hgTmp), L"getting stream data" );

	CRcHolder< LPVOID, CGlobalLock_Manager > crhHandle;
	crhHandle = GlobalLock( hgTmp );
	DWORD w;
	CHK_W32( ::WriteFile(crhFile, (LPVOID)crhHandle, stg.cbSize.LowPart, &w, NULL), FALSE, L"writting file" );
}
void __fastcall CMemoryStream::Init( SIZE_T szInitSize )
{
	CRcHolder<HGLOBAL, CGlobalManager> crhMem;
	if( szInitSize != 0 )
		crhMem = CHK_ALLOC(::GlobalAlloc(GMEM_MOVEABLE|GMEM_NODISCARD|GMEM_ZEROINIT, szInitSize));

	/*CHK_COM( ::CreateILockBytesOnHGlobal((HGLOBAL)crhMem, TRUE, &m_spLockBytes), L"creating Lockbytes" );
	crhMem.Clear();

	CHK_COM( StgCreateDocfileOnILockBytes(m_spLockBytes,
			 STGM_READWRITE|STGM_CREATE|STGM_DIRECT|STGM_SHARE_EXCLUSIVE,
			 0, &m_spStorage),
		L"creating storage on ILockBytes"
	);

	CHK_COM( m_spStorage->CreateStream(
			 m_wsStreamName.c_str(),
			 STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE,
			 0, 0, &m_spStream),
		L"creating stream in memory"
	);*/

	CHK_COM( CreateStreamOnHGlobal((HGLOBAL)crhMem, TRUE, &m_spStream), L"creating stream in memory" );
	crhMem.Clear();
}
SIZE_T __fastcall CMemoryStream::GetSize()
{
	STATSTG stg;
	CHK_COM( m_spStream->Stat(&stg, STATFLAG_NONAME), L"getting stream status" );
	return (SIZE_T)stg.cbSize.LowPart;
}
void __fastcall CMemoryStream::SeekToStart()
{
	LARGE_INTEGER pos; memset( &pos, 0, sizeof(pos) );
	CHK_COM( m_spStream->Seek(pos, STREAM_SEEK_SET, NULL), L"seek memory stream to begin" );
}

SIZE_T __fastcall CMemoryStream::WriteString( const char* psz )
{
	SIZE_T res = (SIZE_T)strlen( psz );
	CHK_COM( m_spStream->Write((LPVOID)psz, (ULONG)res, NULL), L"write string to memory stream" );
	m_szWrittenSize += res;
	return res;
}
SIZE_T __fastcall CMemoryStream::WriteBytes( LPBYTE lpb, SIZE_T sz )
{
	CHK_COM( m_spStream->Write((LPVOID)lpb, (ULONG)sz, NULL), L"write string to memory stream" );
	m_szWrittenSize += sz;
	return sz;
}
SIZE_T __fastcall CMemoryStream::WriteStream( IStream* pStm )
{
	LARGE_INTEGER pos; memset( &pos, 0, sizeof(pos) );
	CHK_COM( pStm->Seek(pos, STREAM_SEEK_SET, NULL), L"seek stream to begin" );
	STATSTG stg;
	CHK_COM( pStm->Stat(&stg, STATFLAG_NONAME), L"getting stream status" );

	/*std::auto_ptr<BYTE> spBytes( CHK_ALLOC(new BYTE[stg.cbSize]) );
	ULONG ulReaded;
	CHK_COM( pStm->Read(spBytes.get(), stg.cbSize, &ulReaded), L"reading from stream" );

	ULONG ulW;
	CHK_COM( m_spStream->Write((LPVOID)spBytes.get(), ulReaded, &ulW), L"write string to memory stream" );
	CHK_COM( pStm->Seek(0, STREAM_SEEK_SET, NULL), L"seek stream to begin" );

	m_szWrittenSize += ulW;
	return (SIZE_T)ulW;*/
	ULARGE_INTEGER ulW;
	CHK_COM( pStm->CopyTo(m_spStream, stg.cbSize, NULL, &ulW), L"copying stream" );
	m_szWrittenSize += ulW.LowPart;
	return (SIZE_T)ulW.LowPart;
}


CMultipartForm::CMultipartForm( char* pszBnd ):
	m_strDelim( "\x0D\x0A" ),
	m_strContDespositition( "Content-Disposition: form-data; " )
{
	const static char* CHRS = "0123456789abcdef";

	if( pszBnd != NULL )
		m_strBoundry = pszBnd;
	else
	{
		std::basic_stringstream<char> bsStm;
		bsStm << "-----------------------------"; 		
		//bsStm.setbase( ios_base::hex );
		srand( (unsigned)time(NULL) );

		for( int i = 0; i < 13; ++i )
		{
			int val = int(float(rand()) / float(RAND_MAX) * 15.0);
			bsStm << CHRS[ val ];
		}

		m_strBoundry = bsStm.str().c_str();
		m_strBoundry += m_strDelim;
	}
}

void  __fastcall CMultipartForm::AddPostingData( const char* pszName, LPBYTE lpbValue, SIZE_T size )
{
	m_stm.WriteString( m_strBoundry.c_str() );
	//m_stm.WriteString( m_strDelim.c_str() );
	m_stm.WriteString( m_strContDespositition.c_str() );
	m_stm.WriteString( "name=\"" );
	m_stm.WriteString( pszName );
	m_stm.WriteString( "\"" );
	m_stm.WriteString( m_strDelim.c_str() );
	m_stm.WriteString( m_strDelim.c_str() );
	m_stm.WriteBytes( lpbValue, size );
	m_stm.WriteString( m_strDelim.c_str() );
}
void  __fastcall CMultipartForm::AddPostingFile( const char* pszName, const char* pszFileName, const char* pszContentType, IStream* pContent )
{
	m_stm.WriteString( m_strBoundry.c_str() );
	//m_stm.WriteString( m_strDelim.c_str() );
	m_stm.WriteString( m_strContDespositition.c_str() );
	m_stm.WriteString( "name=\"" );
	m_stm.WriteString( pszName );
	m_stm.WriteString( "\"; filename=\"" );
	m_stm.WriteString( pszFileName );
	m_stm.WriteString( "\"" );
	m_stm.WriteString( m_strDelim.c_str() );
	m_stm.WriteString( "Content-Type: " );
	m_stm.WriteString( pszContentType );
	m_stm.WriteString( m_strDelim.c_str() );
	m_stm.WriteString( m_strDelim.c_str() );
	m_stm.WriteStream( pContent );
	m_stm.WriteString( m_strDelim.c_str() );
}

HGLOBAL __fastcall CMultipartForm::GetAsHGLOBAL()
{
	/*SIZE_T sz = GetSize();
	CRcHolder< HGLOBAL, CGlobalManager > crhHG;
	crhHG = CHK_W32( ::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, sz), (HGLOBAL)NULL, L"allocating " );*/

	return m_stm.GetHANDLE();
}


