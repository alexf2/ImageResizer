#include "stdafx.h"
#include <sstream>
#include <string>
#include <iomanip>
#include <exception>
using namespace std;

#include <cderr.h>

#include "ErrHlp.h"

#ifdef _MFC_ERRORS_
	#include <Afxwin.h>
#endif

//#pragma comment(lib, "mapi32.lib")


#define CONV_LCID MAKELCID( MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), SORT_DEFAULT)


DWORD __fastcall Win32Err( std::basic_string<_TCHAR>& rStr, DWORD dwErr ) throw()
{   	
	LPTSTR lpszMsgBuf = NULL;
	DWORD dw = FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR)&lpszMsgBuf,
		0,
		NULL 
   );
   
	try {
		if( dw && lpszMsgBuf != NULL )
		{						
			int iLen = lstrlen( lpszMsgBuf );
			if( iLen > 1 && lpszMsgBuf[ iLen - 1 ] == _T('\n') ) 
			{
				lpszMsgBuf[ iLen - 1 ] = 0;
				if( lpszMsgBuf[ iLen - 2 ] == _T('\r') ) lpszMsgBuf[ iLen - 2 ] = 0;
			}

			/*iLen = lstrlen( lpszMsgBuf );
			if( iLen > 1 )
			{
				if( *lpszMsgBuf == _T('\"') && lpszMsgBuf[iLen - 1] == _T('\"') )
					rStr.assign( lpszMsgBuf + 1, lpszMsgBuf + iLen - 1 );
				else
					rStr = lpszMsgBuf;
			}
			else*/
			rStr = lpszMsgBuf;
		}
		else rStr = _T("<Cant't get error info>");		
	}
	catch( ... ) {
	}
      
	if( lpszMsgBuf ) LocalFree( lpszMsgBuf );

	return dwErr;
}


void __fastcall CGenericError::SetErrorInfo() throw()
{
	MySetError( ToString(), GetHRESULT() );
}

BSTR __fastcall CGenericError::FormatSource() throw()
{
	USES_CONVERSION;

	if( !m_bPutSourceInMessage )
		m_ccbFSource = L"";
	else
	{
		try {
			if( m_ccbFSource.m_str == NULL )
			{
				basic_stringstream<wchar_t> bs;

				bs << L"In file \"" << (m_lpctFileName == NULL ? L"<Unknown>":T2CW(m_lpctFileName)) <<
					L"\" and line " << m_dwLine;
				
				m_ccbFSource = bs.str().c_str();
			}			
		}
		catch( ... )
		{
			m_ccbFSource = L"Unexpected error on getting error source";
		}
	}

	return m_ccbFSource;
}

BSTR __fastcall CGenericError::ToString() throw()
{
	try {
		if( m_ccbFString.m_str == NULL )
		{
			basic_stringstream<wchar_t> bs;
			BSTR bsDescr = GetDescription();

			if( m_ccbFSource.m_str == NULL )
				FormatSource();

			/*if( m_bPutSourceInMessage )
			{
				bs << m_ccbFSource.m_str << L"\n" << 
					L"on " << (m_lpcwActivity == NULL ? L"<Unknown>":m_lpcwActivity) << L"\n" <<
					L"happened exception " << showbase << hex <<

				(DWORD)GetHRESULT() << L":\n" <<
					L"\"" << (bsDescr == NULL ? L"Unknown":bsDescr) << L"\"";
			}
			else
			{
				bs << L"On " << (m_lpcwActivity == NULL ? L"<Unknown>":m_lpcwActivity) << L"\n" <<
					L"happened exception " << showbase << hex <<

				(DWORD)GetHRESULT() << L":\n" <<
						L"\"" << (bsDescr == NULL ? L"Unknown":bsDescr) << L"\"";
			}*/
 
			if( m_bPutSourceInMessage )
			{
				if( NULL == m_lpcwActivity || wcslen(m_lpcwActivity) == 0 )
					bs << m_ccbFSource.m_str << L"\n" <<
#if defined(_DEBUG) || defined(_RELEASE_LINES_)
						  showbase << hex <<
						  (DWORD)GetHRESULT() << L":\n" <<
#endif
						  (bsDescr == NULL ? L"Unknown":bsDescr);

				else
					bs << m_ccbFSource.m_str << L"\n" <<
						  m_lpcwActivity << L"\n" <<
#if defined(_DEBUG) || defined(_RELEASE_LINES_)
						  showbase << hex <<
						  (DWORD)GetHRESULT() << L":\n" <<
#endif

						  (bsDescr == NULL ? L"Unknown":bsDescr);
			}
			else
			{
				if( NULL == m_lpcwActivity || wcslen(m_lpcwActivity) == 0 )
					bs  <<
#if defined(_DEBUG) || defined(_RELEASE_LINES_)
							showbase << hex <<
							(DWORD)GetHRESULT() << L":\n" <<
#endif
							(bsDescr == NULL ? L"Unknown":bsDescr);

				else
					bs << m_lpcwActivity << L"\n" <<
#if defined(_DEBUG) || defined(_RELEASE_LINES_)
						  showbase << hex <<
						  (DWORD)GetHRESULT() << L":\n" <<
#endif
						  (bsDescr == NULL ? L"Unknown":bsDescr);
			}

			m_ccbFString = bs.str().c_str();
		}
	}
	catch( ... )
	{
		m_ccbFString = L"Unexpected error on converting error to string";
	}

	return m_ccbFString;
}

BSTR __fastcall CWin32Error::GetDescription() throw()
{
	//USES_CONVERSION;
	try {
		if( m_ccbFDescr.m_str == NULL )
		{
		  basic_string<_TCHAR> bs;
		  Win32Err( bs, m_dwErr );
		  m_ccbFDescr = bs.c_str();
		}

		return m_ccbFDescr;
	}
	catch( ... )
	{
		return (m_ccbFDescr = L"Unexpected error on getting error description");
	}
}

#if defined(_GDIPLUS_H)

BSTR __fastcall CGDIPError::GetDescription() throw()
{
	typedef std::pair<Gdiplus::Status, LPCWSTR> TPairDescr;
	static const TPairDescr arrStatDescr[] =
	{
		TPairDescr( Gdiplus::GenericError, L"Generic Error" ),
		TPairDescr( Gdiplus::InvalidParameter, L"Invalid Parameter" ),
		TPairDescr( Gdiplus::OutOfMemory, L"Out of Memory" ),
		TPairDescr( Gdiplus::ObjectBusy, L"Object Busy" ),
		TPairDescr( Gdiplus::InsufficientBuffer, L"Insufficient Buffer" ),
		TPairDescr( Gdiplus::NotImplemented, L"Not Implemented" ),
		TPairDescr( Gdiplus::Win32Error, L"Win32Error" ),
		TPairDescr( Gdiplus::WrongState, L"Wrong State" ),
		TPairDescr( Gdiplus::Aborted, L"Aborted" ),
		TPairDescr( Gdiplus::FileNotFound, L"FileNotFound" ),

		TPairDescr( Gdiplus::ValueOverflow, L"Value Overflow" ),
		TPairDescr( Gdiplus::AccessDenied, L"Access Denied" ),
		TPairDescr( Gdiplus::UnknownImageFormat, L"Unknown Image Format" ),
		TPairDescr( Gdiplus::FontFamilyNotFound, L"Font Family Not Found" ),
		TPairDescr( Gdiplus::FontStyleNotFound, L"Font Style Not Found" ),

		TPairDescr( Gdiplus::NotTrueTypeFont, L"Not True Type Font" ),
		TPairDescr( Gdiplus::UnsupportedGdiplusVersion, L"Unsupported Gdiplus Version" ),
		TPairDescr( Gdiplus::GdiplusNotInitialized, L"Gdiplus Not Initialized" ),
		TPairDescr( Gdiplus::PropertyNotFound, L"Property Not Found" ),
		TPairDescr( Gdiplus::PropertyNotSupported, L"Property Not Supported" )
	};

	try {
		if( m_ccbFDescr.m_str == NULL )
		{		  
		  if( m_stErr == Gdiplus::Win32Error )
		  {
			  basic_string<_TCHAR> bs;
			  Win32Err( bs, ::GetLastError() );
			  m_ccbFDescr = (basic_string<_TCHAR>(_T("Win32 FROM GDI+: ")) + bs).c_str();
		  }
		  else
		  {
			  for( int i = sizeof(arrStatDescr) / sizeof(arrStatDescr[0]) - 1; i >= 0; --i )
				  if( arrStatDescr[ i ].first == m_stErr )
				  {
					  m_ccbFDescr = arrStatDescr[ i ].second;
					  break;
				  }

			  if( i == -1 ) m_ccbFDescr = L"<UNKNOWN GDI+ Error happened>";
		  }
		}

		return m_ccbFDescr;
	}
	catch( ... )
	{
		return (m_ccbFDescr = L"Unexpected error on getting error description");
	}
}

#ifdef __ACROBAT_ERRORS_

Gdiplus::Status __fastcall AcrobatChkGDIP( Gdiplus::Status stat, LPCWSTR lpcwActivity, LPCTSTR lpctFile, DWORD dwLine )
{	
	if( stat != Gdiplus::Ok )
	{
		CGDIPError cweErr( stat, lpctFile, dwLine, lpcwActivity );
		MyAcrRaise( ErrAlways, SafeGetBSTR(cweErr.ToString()) );
	}
	return stat;
}

#endif

#endif //GDIPLUS_H

BSTR __fastcall CComError::GetDescription() throw()
{
	try {
		if( m_ccbFDescr.m_str == NULL )
		{
		  if( m_spIErr.p != NULL ) 
			m_spIErr->GetDescription( &m_ccbFDescr );
		  else 
		  {
			  basic_string<_TCHAR> bs;
			  Win32Err( bs, m_hrErr );
			  m_ccbFDescr = bs.c_str();
		  }
		}

		return m_ccbFDescr;
	}
	catch( ... )
	{
		return (m_ccbFDescr = L"Unexpected error on getting error description");
	}
}


void __fastcall ThrowSimpleSTDExc( LPCSTR lpMsgOn, LPCSTR lpMsgWhat, LPCSTR lpFile, int iLine )
{
	_ASSERTE( lpMsgOn != NULL && lpMsgWhat != NULL && lpFile != NULL );


	basic_stringstream<char> bsStrm;

	try {
				
		bsStrm << "\nIn file \"" << lpFile <<
			"\" and line " << iLine << "\n";


		if( NULL == lpMsgOn || strlen(lpMsgOn) == 0 )
			bsStrm 
				<< lpMsgWhat;
		else
			bsStrm << "On [" << lpMsgOn <<
				"]\n" << lpMsgWhat << "\n";
	}
	catch( ... ) {
		throw  exception( "Unexpected exception" );
	}

	throw exception( bsStrm.str().c_str() );
}

void __fastcall ThrowSimpleSTDExc( LPCSTR lpMsgOn, LPCSTR lpMsgWhat )
{
	_ASSERTE( lpMsgOn != NULL && lpMsgWhat != NULL );

	basic_stringstream<char> bsStrm;

	try {
		if( NULL == lpMsgOn || strlen(lpMsgOn) == 0 )
			bsStrm << lpMsgWhat;
		else
			bsStrm << "On [" << lpMsgOn <<
				"] taking place error:\n\"" << lpMsgWhat << "\"\n";
	}
	catch( ... )
	{
		throw  exception( "Unexpected exception" );
	}

	throw exception( bsStrm.str().c_str() );	
}

void __fastcall ThrowBadAllocExc( LPCSTR lpFile, int iLine )
{
	_ASSERTE( lpFile != NULL );

	basic_stringstream<char> bsStrm;

	try {
				
		bsStrm << "\nIn file \"" << lpFile <<
			"\" and line " << iLine << " insufficient memory at alloc";					
	}	
	catch( ... ) { 
		throw  exception( "Unexpected exception" );
	}

	throw exception( bsStrm.str().c_str() );
}

void __fastcall ReportCurrentError( HWND hw ) throw()
{
	USES_CONVERSION;

	CComBSTR bs;
	bs = GetCurrentCOMErrorDescr();
	::MessageBox( hw, W2CT(SafeGetBSTR(bs)), _T("Error"), MB_OK|MB_ICONASTERISK );
}

CComBSTR __fastcall GetCurrentCOMErrorDescr() throw()
{
	CComPtr<IErrorInfo> spIE;
	CComBSTR bs;
	::GetErrorInfo( 0, &spIE );
	if( spIE.p )
	{
		spIE->GetDescription( &bs );
		if( bs.m_str == NULL ) bs = L"";
	}
	else bs = L"";
	
	return bs;
}

void __fastcall TrimBSTR( const BSTR bsIn, BSTR& bsOut )
{
	if( bsIn == NULL ) bsOut = NULL;
	else
	{
		BSTR pbsSta = bsIn, pbsEnd = bsIn + ::SysStringLen( bsIn );
		if( pbsSta != pbsEnd )
		{
			for( ; pbsSta < pbsEnd && iswspace(*pbsSta); ++pbsSta );

			if( pbsSta != pbsEnd )
			{
				for( pbsEnd--; pbsEnd > pbsSta && iswspace(*pbsEnd); --pbsEnd );
				
				bsOut = ::SysAllocStringLen( pbsSta, (UINT)(pbsEnd - pbsSta + 1) );
#ifdef __ACROBAT_ERRORS_
				ACROBAT_CHK_ALLOC( bsOut );
#else
				CHK_ALLOC( bsOut );
#endif
				return;				
			}
		}

		bsOut = ::SysAllocString( L"" );
	}
}

#ifdef _STRING_
void __fastcall TrimBasicString( std::basic_string<wchar_t>& rbs )
{
	int stLen = (int)rbs.length();

	if( stLen > 0 )
	{
		int stSta;
		int stEnd;

		if( L' ' == rbs.at(0) )
		{
			for( stEnd = stSta = 0; stEnd < stLen && L' ' == rbs.at(stEnd); ++stEnd );
			rbs.replace( stSta, stEnd - stSta, L"" );
		}

		stLen = (int)rbs.length();
		if( stLen > 0 )
		{
			if( L' ' == rbs.at(stLen - 1) )
			{
				for( stEnd = stSta = stLen - 1; stSta >= 0 && L' ' == rbs.at(stSta); --stSta );
				rbs.replace( stSta + 1, stEnd - stSta, L"" );
			}
		}
	}
}

void __fastcall TrimBasicString( std::basic_string<char>& rbs )
{
	int stLen = (int)rbs.length();

	if( stLen > 0 )
	{
		int stSta;
		int stEnd;

		if( ' ' == rbs.at(0) )
		{
			for( stEnd = stSta = 0; stEnd < stLen && ' ' == rbs.at(stEnd); ++stEnd );
			rbs.replace( stSta, --stEnd, "" );
		}

		stLen = (int)rbs.length();
		if( stLen > 0 )
		{
			if( ' ' == rbs.at(stLen - 1) )
			{
				for( stEnd = stSta = stLen - 1; stSta >= 0 && ' ' == rbs.at(stSta); --stSta );
				rbs.replace( ++stSta, stEnd, "" );
			}
		}
	}
}
#endif

short __fastcall NormAndChk_I2( VARIANT& rV )
{
	CComVariant cvTmp, cvClear; cvClear.Attach( &rV ); 	
	CHK_COM( ::VariantChangeTypeEx(&cvTmp, &cvClear, CONV_LCID, 0, VT_I2), L"Converting VARIANT to VT_I2" );	
	return V_I2( &cvTmp );
}
long __fastcall NormAndChk_I4( VARIANT& rV )
{
	CComVariant cvTmp, cvClear; cvClear.Attach( &rV ); 	
	CHK_COM( VariantChangeTypeEx(&cvTmp, &cvClear, CONV_LCID, 0, VT_I4), L"Converting VARIANT to VT_I4" );	
	return V_I4( &cvTmp );
}
float __fastcall NormAndChk_R4( VARIANT& rV )
{
	CComVariant cvTmp, cvClear; cvClear.Attach( &rV ); 	
	CHK_COM( VariantChangeTypeEx(&cvTmp, &cvClear, 
		CONV_LCID, 0,
		VT_R4), L"Converting VARIANT to VT_R4" );	
	return V_R4( &cvTmp );
}
double __fastcall NormAndChk_R8( VARIANT& rV )
{
	CComVariant cvTmp, cvClear; cvClear.Attach( &rV ); 	
	CHK_COM( VariantChangeTypeEx(&cvTmp, &cvClear,
		CONV_LCID, 0,
		VT_R8), L"Converting VARIANT to VT_R8" );	
	return V_R8( &cvTmp );
}
VARIANT_BOOL __fastcall NormAndChk_VBOOL( VARIANT& rV )
{
	CComVariant cvTmp, cvClear; cvClear.Attach( &rV ); 	
	CHK_COM( VariantChangeTypeEx(&cvTmp, &cvClear, CONV_LCID, 0, VT_BOOL), L"Converting VARIANT to VT_BOOL" );	
	return V_BOOL( &cvTmp );
}
CComBSTR __fastcall NormAndChk_BSTR( VARIANT& rV )
{
	CComVariant cvTmp, cvClear; cvClear.Attach( &rV ); 	
	CHK_COM( VariantChangeTypeEx(&cvTmp, &cvClear, CONV_LCID, 0, VT_BSTR), L"Converting VARIANT to VT_BSTR" );	
	return CComBSTR( V_BSTR(&cvTmp) ); 
}

#ifdef _URL_MONIKER_ERRORS_

#pragma pack( push, 1 )
struct TURLErrPair
{
	HRESULT hr;
	LPCWSTR lpcsz;
};
#pragma pack( pop )

bool __fastcall GetURLMonikerError( HRESULT hr, CComBSTR& rbsErr ) throw()
{
	static const TURLErrPair arrlpcsz[] = 
	{
		{ INET_E_AUTHENTICATION_REQUIRED, L"Authentication is needed to access the object" },
		{ INET_E_CANNOT_CONNECT, L"The attempt to connect to the Internet has failed" },
		{ INET_E_CANNOT_INSTANTIATE_OBJECT , L"CoCreateInstance failed" },
		{ INET_E_CANNOT_LOAD_DATA, L"The object could not be loaded" },
		{ INET_E_CANNOT_LOCK_REQUEST, L"The requested resource could not be locked" },
		{ INET_E_CANNOT_REPLACE_SFP_FILE, L"The exact version requested by a component download cannot be found" },
		{ INET_E_CODE_DOWNLOAD_DECLINED, L"The component download was declined by the user" },
		{ INET_E_CONNECTION_TIMEOUT, L"The Internet connection has timed out" },
		{ INET_E_DATA_NOT_AVAILABLE, L"An Internet connection was established, but the data cannot be retrieved" },
		{ INET_E_DEFAULT_ACTION, L"Use the default action" },
		{ INET_E_DOWNLOAD_FAILURE, L"The download has failed (the connection was interrupted)" },
		{ INET_E_INVALID_REQUEST, L"The request was invalid" },
		{ INET_E_INVALID_URL, L"The URL could not be parsed" },
		{ INET_E_NO_SESSION, L"No Internet session was established" },
		{ INET_E_NO_VALID_MEDIA, L"The object is not in one of the acceptable MIME types" },
		{ INET_E_OBJECT_NOT_FOUND, L"The object was not found" },
		{ INET_E_QUERYOPTION_UNKNOWN, L"The requested option is unknown" },
		{ INET_E_REDIRECT_TO_DIR, L"The request is being redirected to a directory" },
		{ INET_E_REDIRECTING, L"The request is being redirected" },
		{ INET_E_RESOURCE_NOT_FOUND, L"The server or proxy was not found" },
		{ INET_E_RESULT_DISPATCHED, L"The binding has already been completed and the result has been dispatched, so your abort call has been canceled" },
		{ INET_E_SECURITY_PROBLEM, L"A security problem was encountered" },
		{ INET_E_UNKNOWN_PROTOCOL, L"The protocol is not known and no pluggable protocols have been entered that match" },
		{ INET_E_USE_DEFAULT_PROTOCOLHANDLER, L"Use the default protocol handler" },
		{ INET_E_USE_DEFAULT_SETTING, L"Use the default settings" }
	};

	for( int i = 0; i < sizeof(arrlpcsz) / sizeof(arrlpcsz[0]); ++i )
		if( arrlpcsz[ i ].hr == hr ) 
		{
			rbsErr = arrlpcsz[ i ].lpcsz;
			return true;
		}

	basic_string<_TCHAR> bs;
	Win32Err( bs, hr );
	rbsErr = bs.c_str();

	return true;
}

#endif //_URL_MONIKER_ERRORS_

#pragma pack( push, 1 )
struct TDWORDPair
{
	DWORD dwErr;
	LPCSTR lpcsz;
};
#pragma pack( pop )
void __fastcall ThrowCommonDlgError( DWORD dwErr )
{
	if( dwErr )
	{
		static const TDWORDPair arrlpcsz[] = 
		{
			{ CDERR_DIALOGFAILURE,		"The dialog box could not be created" },
			{ CDERR_FINDRESFAILURE,		"The common dialog box function failed to find a specified resource." },
			{ CDERR_INITIALIZATION,		"The common dialog box function failed during initialization." },
			{ CDERR_LOADRESFAILURE,		"The common dialog box function failed to load a specified resource." },
			{ CDERR_LOADSTRFAILURE,		"The common dialog box function failed to load a specified string." },
			{ CDERR_LOCKRESFAILURE,		"The common dialog box function failed to lock a specified resource." },
			{ CDERR_MEMALLOCFAILURE,	"The common dialog box function was unable to allocate memory for internal structures." },
			{ CDERR_MEMLOCKFAILURE,		"The common dialog box function was unable to lock the memory associated with a handle." },
			{ CDERR_NOHINSTANCE,		"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding instance handle." },
			{ CDERR_NOHOOK,				"The ENABLEHOOK flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a pointer to a corresponding hook procedure." },
			{ CDERR_NOTEMPLATE,			"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding template." },
			{ CDERR_REGISTERMSGFAIL,	"The RegisterWindowMessage function returned an error code when it was called by the common dialog box function." },
			{ CDERR_STRUCTSIZE,			"The lStructSize member of the initialization structure for the corresponding common dialog box is invalid." },
			{ PDERR_CREATEICFAILURE,	"The PrintDlg function failed when it attempted to create an information context." },
			{ PDERR_DEFAULTDIFFERENT,	"The other structure members did not match the current default printer." },
			{ PDERR_DNDMMISMATCH,		"The data in the DEVMODE and DEVNAMES structures describes two different printers." },
			{ PDERR_GETDEVMODEFAIL,		"The printer driver failed to initialize a DEVMODE structure." },
			{ PDERR_INITFAILURE,		"The PrintDlg function failed during initialization, and there is no more specific extended error code to describe the failure." },
			{ PDERR_LOADDRVFAILURE,		"The PrintDlg function failed to load the device driver for the specified printer." },
			{ PDERR_NODEFAULTPRN,		"A default printer does not exist." },
			{ PDERR_NODEVICES,			"No printer drivers were found." },
			{ PDERR_PARSEFAILURE,		"The PrintDlg function failed to parse the strings in the [devices] section of the WIN.INI file." },
			{ PDERR_PRINTERNOTFOUND,	"The [devices] section of the WIN.INI file did not contain an entry for the requested printer." },
			{ PDERR_RETDEFFAILURE,		"The PD_RETURNDEFAULT flag was specified in the Flags member of the PRINTDLG structure, but the hDevMode or hDevNames member was not NULL." },
			{ PDERR_SETUPFAILURE,		"The PrintDlg function failed to load the required resources." },
			{ CFERR_MAXLESSTHANMIN,		"The size specified in the nSizeMax member of the CHOOSEFONT structure is less than the size specified in the nSizeMin member." },
			{ CFERR_NOFONTS,			"No fonts exist." },
			{ FNERR_BUFFERTOOSMALL,		"The buffer pointed to by the lpstrFile member of the OPENFILENAME structure is too small for the file name specified by the user." },
			{ FNERR_INVALIDFILENAME,	"A file name is invalid." },
			{ FNERR_SUBCLASSFAILURE,	"An attempt to subclass a list box failed because sufficient memory was not available." },
			{ FRERR_BUFFERLENGTHZERO,	"A member of the FINDREPLACE structure points to an invalid buffer." }
		};

		for( int i = 0; i < sizeof(arrlpcsz) / sizeof(arrlpcsz[0]); ++i )
			if( arrlpcsz[ i ].dwErr == dwErr ) 
				throw  exception( arrlpcsz[i].lpcsz );		

		throw  exception( "Unknown error from CommonDialog" );
	}
}

int DoubleNullSize( LPCTSTR lp ) throw()
{
	int iSz = 0;
	bool bFl = false;
	while( !bFl || *lp ) bFl = !*(lp++), ++iSz;
	return (iSz + 1) * sizeof(TCHAR);
}

LPBYTE __fastcall FindSubBytes( LPBYTE lp, LPBYTE lpSub, int lSz, int lSzSub ) throw()
{
	LPBYTE lp2 = lpSub;
	int i2 = 1;
	for( int i = lSz; i > 0; --i, ++lp )
	{
		if( *lp2 == *lp )
		{
			if( i2 == lSzSub ) return lp - i2 + 1;
			++i2, ++lp2;
		}
		else lp2 = lpSub, i2 = 1;
	}
	return NULL;
}

void DebuPrint( LPCWSTR lpcwMsg, long lData ) throw()
{
	USES_CONVERSION;
	wchar_t wcTmpTick[ 1024 ];
	swprintf( wcTmpTick, L"%s: %d\n", lpcwMsg, lData );
	OutputDebugString( W2CT(wcTmpTick) );
}

void __fastcall _InternalMySetError( const CLSID& clsid, std::exception& rE, const IID& iid, HRESULT hr ) throw()
{
	USES_CONVERSION;
	//THIS->Error( A2CT(rE.what()), rIID, (_hr = E_FAIL) );
	AtlSetErrorInfo( clsid, A2COLE(rE.what()), 0, NULL, iid, hr, NULL );
	//AtlSetErrorInfo( clsid, L"PPP", 0, NULL, iid, hr, NULL );
}

#ifdef __ACROBAT_ERRORS_
void MyAcrRaise( ASErrSeverity asSeverity, LPCWSTR lpcwDescr )
{
	USES_CONVERSION;
	ASRaise( ASRegisterErrorString(asSeverity, W2CA(lpcwDescr)) );
}

void MyAcrRaise( ASErrSeverity asSeverity, LPCSTR lpcwDescr )
{	
	ASRaise( ASRegisterErrorString(asSeverity, lpcwDescr) );
}


HRESULT __fastcall AcrobatChkCOM( HRESULT hr, LPCWSTR lpcwActivity, LPCTSTR lpctFile, DWORD dwLine )
{
	if( FAILED(hr) ) 
	{
		CComError ceErr( hr, lpctFile, dwLine, lpcwActivity );
		MyAcrRaise( ErrAlways, SafeGetBSTR(ceErr.ToString()) );
	}
	return hr;
}

void __fastcall AcrobatThrowSimpleSTDExc( LPCSTR lpMsgOn, LPCSTR lpMsgWhat, LPCSTR lpFile, int iLine )
{
	_ASSERTE( lpMsgOn != NULL && lpMsgWhat != NULL && lpFile != NULL );

	basic_stringstream<char> bsStrm;

	try {
				
		bsStrm << "\nIn file \"" << lpFile <<
			"\" and line " << iLine << "\n";
			
		bsStrm << "On [" << lpMsgOn <<
			"] taking place error:\n\"" << lpMsgWhat << "\"\n";
	}	
	catch( ... ) { 		
		MyAcrRaise( ErrAlways, "Unexpected exception" );
	}
	
	MyAcrRaise( ErrAlways, bsStrm.str().c_str() );
}

#endif

#ifdef _MFC_ERRORS_

HRESULT __fastcall MFCReportError( CGenericError& rE ) throw()
{
	USES_CONVERSION;
	AfxMessageBox( W2T(SafeGetBSTR(rE.ToString())), MB_OK|MB_ICONEXCLAMATION, 0 );
	return rE.GetHRESULT();
}
HRESULT __fastcall MFCReportError( _com_error& rE ) throw()
{
	USES_CONVERSION;
	AfxMessageBox( W2T(SafeGetBSTR((BSTR)rE.Description())), MB_OK|MB_ICONEXCLAMATION, 0 );
	return rE.Error();
}
HRESULT __fastcall MFCReportError( std::bad_alloc& rE ) throw()
{	
	AfxMessageBox( _T("No memory"), MB_OK|MB_ICONEXCLAMATION, 0 );
	return E_OUTOFMEMORY;
}
HRESULT __fastcall MFCReportError( std::exception& rE ) throw()
{
	USES_CONVERSION;
	AfxMessageBox( A2CT(rE.what()), MB_OK|MB_ICONEXCLAMATION, 0 );
	return E_FAIL;
}


#endif //_MFC_ERRORS_



//----------- XML Helpers ----------- 
_bstr_t __fastcall NumberToUserLocale( _bstr_t& rbs )
{
	/*USES_CONVERSION;
	LPCTSTR lpszTmp = W2CT( SafeGetBSTR(rbs) );
	int iCharCnt = ::GetNumberFormat( LOCALE_USER_DEFAULT, 0, lpszTmp, NULL, NULL, 0 );*/

	return L"";
}
float __fastcall FloatFromVar( _variant_t& vt )
{
	_variant_t vtFl;

	//LCID lc1 = ::GetUserDefaultLCID();
	//LCID lc2 = ::GetSystemDefaultLCID();

	/*HRESULT hr1 = VariantChangeTypeEx( &vtFl, &_variant_t(L"85.5"), ::GetUserDefaultLCID(), 0, VT_R4 );
	HRESULT hr2 = VariantChangeTypeEx( &vtFl, &_variant_t(L"85.5"), ::GetSystemDefaultLCID(), 0, VT_R4 );
	HRESULT hr3 = VariantChangeTypeEx( &vtFl, &_variant_t(L"85.5"), ::GetSystemDefaultLCID(), 0, VT_R4 );*/
	//HRESULT hr2 = VariantChangeType( &vtFl, &_variant_t(L"85,5"), 0, VT_R4 );

	CHK_COM(
		VariantChangeTypeEx(
			&vtFl, &vt, MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT), SORT_DEFAULT), 0, VT_R4),
				L"FloatFromVar" );
	//vtFl.ChangeType( VT_R4, &vt );
	return V_R4( &vtFl );
}

//----------- END XML Helpers ----------- 

void __fastcall MySetError( LPCWSTR lpcwDescr, HRESULT hr ) throw()
{
	CComPtr<ICreateErrorInfo> pICEI;
	if( SUCCEEDED(CreateErrorInfo(&pICEI)) )
	{
		CComPtr<IErrorInfo> pErrorInfo;
		pICEI->SetGUID( GUID_NULL );
		pICEI->SetDescription( CComBSTR(lpcwDescr ? lpcwDescr:L"") );

		if( SUCCEEDED(pICEI->QueryInterface(IID_IErrorInfo, (void**)&pErrorInfo)) )
			SetErrorInfo( 0, pErrorInfo );
	}
}

void __fastcall MySetError( LPCSTR lpcDescr, HRESULT hr ) throw()
{
	CComPtr<ICreateErrorInfo> pICEI;
	if( SUCCEEDED(CreateErrorInfo(&pICEI)) )
	{
		CComPtr<IErrorInfo> pErrorInfo;
		pICEI->SetGUID( GUID_NULL );
		pICEI->SetDescription( CComBSTR(lpcDescr ? lpcDescr:"") );

		if( SUCCEEDED(pICEI->QueryInterface(IID_IErrorInfo, (void**)&pErrorInfo)) )
			SetErrorInfo( 0, pErrorInfo );
	}
}

CComBSTR __fastcall ComErrDescr( _com_error& rCE ) throw()
{
	basic_stringstream<wchar_t> bsStrm;

	try {
		wchar_t wcTmp[ 64 ];
		swprintf( wcTmp, L"0x%x", (unsigned int)rCE.Error() );
		bsStrm << L"[" << wcTmp << L"]";
		if( (BSTR)rCE.Description() != NULL )
			bsStrm << L" '" << SafeGetBSTR(rCE.Description()) << L"'";
	}
	catch( ... ) {
		return L"Unexpected exception";
	}

	return bsStrm.str().c_str();
}

