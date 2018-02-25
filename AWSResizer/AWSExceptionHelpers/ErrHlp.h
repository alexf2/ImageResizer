#if !defined(_ERR_HLP_H_)
#define _ERR_HLP_H_

#pragma once

#ifndef __ATLCOM_H__
	#error ErrHlp.h requires "atlcom.h" to be included first
#endif

#ifndef _WINDOWS_
	#error ErrHlp.h requires "windows.h" to be included first
#endif

/*#ifndef _INC_TCHAR
	#error ErrHlp.h requires "tchar.h" to be included first
#endif*/

#ifndef _STRING_
	#error ErrHlp.h requires "string" to be included first
#endif

#ifndef _EXCEPTION_
	#error ErrHlp.h requires "exception" to be included first
#endif

#ifndef _INC_COMUTIL
	#error ErrHlp.h requires "ComUtil.h" to be included first
#endif

#ifdef _DEBUG
	#ifndef _INC_CRTDBG
		#error ErrHlp.h requires "CrtDbg.h" to be included first
	#endif
#endif

#ifdef __ACROBAT_ERRORS_
	#ifndef _H_AcroErr
		#error ErrHlp.h requires "AcroErr.h" to be included first
	#endif
	#ifndef _H_ASCalls
		#error ErrHlp.h requires "ASCalls.h" to be included first
	#endif
#endif

#ifdef _MFC_ERRORS_
	#ifndef __AFXWIN_H__ 
		#error ErrHlp.h requires "Afxwin.h" to be included first
	#endif
#endif


inline LPCWSTR SafeGetBSTR( BSTR bs ) throw()
{
	return bs ? bs:L"";
}



DWORD __fastcall Win32Err( std::basic_string<_TCHAR>& rStr, DWORD dwErr ) throw();
void __fastcall ThrowSimpleSTDExc( LPCSTR lpMsgOn, LPCSTR lpMsgWhat, LPCSTR lpFile, int iLine );
void __fastcall ThrowSimpleSTDExc( LPCSTR lpMsgOn, LPCSTR lpMsgWhat );
void __fastcall ThrowBadAllocExc( LPCSTR lpFile, int iLine );
CComBSTR __fastcall ComErrDescr( _com_error& rCE ) throw();

class CGenericError
{
public:
	CGenericError( LPCTSTR	lpctFileName, DWORD	dwLine, LPCWSTR	lpcwActivity = NULL ) throw():
	  m_lpctFileName( lpctFileName ),
	  m_dwLine( dwLine ),
	  m_lpcwActivity( lpcwActivity ),
	  m_bPutSourceInMessage( true )
	  {
		  _ASSERTE( lpctFileName != NULL );
	  }

	CGenericError( LPCWSTR lpcwActivity ) throw():
	  m_lpctFileName( NULL ),
	  m_dwLine( 0 ),
	  m_lpcwActivity( lpcwActivity ),
	  m_bPutSourceInMessage( false )
	  {
	  }

	virtual ~CGenericError() {}

	virtual BSTR __fastcall GetDescription() throw() = 0;
	virtual HRESULT __fastcall GetHRESULT() throw() = 0;

	BSTR __fastcall FormatSource() throw();
	BSTR __fastcall ToString() throw();

#ifdef _DEBUG
	void __fastcall DbgReport() throw()
	{
		USES_CONVERSION;
		OutputDebugString( W2T( ToString() ) );
	}
#endif

	template<class T> void __fastcall SetErrorInfo( T& rT, const IID& rIID ) throw()
	{
		rT.Error( ToString(), rIID, GetHRESULT() );
	}

	void __fastcall SetErrorInfo() throw();

private:
	LPCTSTR		m_lpctFileName;
	DWORD		m_dwLine;
	LPCWSTR		m_lpcwActivity;
	bool		m_bPutSourceInMessage;

	CComBSTR	m_ccbFSource, m_ccbFString;
};

class CWin32Error: public CGenericError
{
public:
	CWin32Error( DWORD dwErr, LPCTSTR lpctFileName, DWORD dwLine, LPCWSTR lpcwActivity = NULL ) throw():
	  CGenericError( lpctFileName, dwLine, lpcwActivity ),
	  m_dwErr( dwErr )
	  {
	  }

	CWin32Error( DWORD dwErr, LPCWSTR lpcwActivity ) throw():
	  CGenericError( lpcwActivity ),
	  m_dwErr( dwErr )
	  {
	  }

    ~CWin32Error() {}

	BSTR __fastcall GetDescription() throw();
	HRESULT __fastcall GetHRESULT() throw()
	{
		return HRESULT_FROM_WIN32( m_dwErr );
	}

	DWORD __fastcall GetErrCode() { return m_dwErr; }

private:
	DWORD		m_dwErr;
	CComBSTR	m_ccbFDescr;
};


class CComError: public CGenericError
{
public:
	CComError( HRESULT hrErr, LPCTSTR lpctFileName, DWORD dwLine, LPCWSTR lpcwActivity = NULL ) throw():
	  CGenericError( lpctFileName, dwLine, lpcwActivity ),
	  m_hrErr( hrErr )
	  {
		  GetErrorInfo( 0, &m_spIErr );
	  }

	CComError( HRESULT hrErr, LPCWSTR lpcwActivity ) throw():
	  CGenericError( lpcwActivity ),
	  m_hrErr( hrErr )
	  {
		  GetErrorInfo( 0, &m_spIErr );
	  }

	~CComError() {}

	BSTR __fastcall GetDescription() throw();
	HRESULT __fastcall GetHRESULT() throw()
	{
		return m_hrErr;
	}

private:
	HRESULT		m_hrErr;
	CComBSTR	m_ccbFDescr;
	CComPtr<IErrorInfo> m_spIErr;
};



template<class T> T __fastcall ChkWin32( T tVal, T tBadVal, LPCWSTR lpcwActivity, LPCTSTR lpctFile, DWORD dwLine )
{
	if( tVal == tBadVal ) throw CWin32Error( GetLastError(), lpctFile, dwLine, lpcwActivity );
	return tVal;
}

template<class T> T __fastcall ChkWin32( T tVal, T tBadVal, LPCWSTR lpcwActivity )
{
	if( tVal == tBadVal ) throw CWin32Error( GetLastError(), lpcwActivity );
	return tVal;
}

#define CHK_W32( RESULT, BAD_VAL, ACTIVITY ) \
	ChkWin32( RESULT, BAD_VAL, ACTIVITY, _T(__FILE__), __LINE__ )

#define ERR_W32( RESULT, BAD_VAL, ACTIVITY ) \
	ChkWin32( RESULT, BAD_VAL, ACTIVITY )
	

inline HRESULT __fastcall ChkCOM( HRESULT hr, LPCWSTR lpcwActivity, LPCTSTR lpctFile, DWORD dwLine )
{
	if( FAILED(hr) ) throw CComError( hr, lpctFile, dwLine, lpcwActivity );
	return hr;
}

inline HRESULT __fastcall ChkCOM( HRESULT hr, LPCWSTR lpcwActivity )
{
	if( FAILED(hr) ) throw CComError( hr, lpcwActivity );
	return hr;
}

#define CHK_COM( RESULT, ACTIVITY ) \
	ChkCOM( RESULT, ACTIVITY, _T(__FILE__), __LINE__ )

#define ERR_COM( RESULT, ACTIVITY ) \
	ChkCOM( RESULT, ACTIVITY )


template<class T_RES> inline T_RES __fastcall ChkAlloc( T_RES trRes, LPCSTR lpFile, int iLine )
{
	if( trRes == NULL ) ThrowBadAllocExc( lpFile, iLine );
	return trRes;
}

#define CHK_ALLOC( RESULT ) \
	ChkAlloc( RESULT, __FILE__, __LINE__ )

#define THROW_SIMPLE_STD_EXC( MSG_ON, MSG_WHAT )\
	ThrowSimpleSTDExc( MSG_ON, MSG_WHAT, __FILE__, __LINE__ )

#define THROW_SIMPLE_STD_ERR( MSG_ON, MSG_WHAT )\
	ThrowSimpleSTDExc( MSG_ON, MSG_WHAT )



#ifndef _NO_ATL_ERRORS_

#define BEGIN_TRY \
	::SetErrorInfo( 0, NULL );\
	HRESULT _hr = S_OK;\
	CComPtr<IErrorInfo> _spIEI;\
	try {

#define BEGIN_TRY_NO_DECL \
	::SetErrorInfo( 0, NULL );\
	_hr = S_OK;\
	try {

//void __fastcall TRAPLVL_();

void __fastcall _InternalMySetError( const CLSID&, std::exception& rE, const IID& iid, HRESULT hr ) throw();

template<typename T>
void __fastcall MySetError( T pClass, std::exception& rE, const IID& iid, HRESULT hr ) throw()
{	
	_InternalMySetError( pClass ? pClass->GetObjectCLSID():GUID_NULL, rE, iid, hr );
}

void __fastcall MySetError( LPCWSTR lpcwDescr, HRESULT hr ) throw();
void __fastcall MySetError( LPCSTR lpcDescr, HRESULT hr ) throw();

#define END_TRY( THIS, rIID ) \
	} \
	catch( CGenericError& rCge ) \
	{ \
		rCge.SetErrorInfo( *THIS, rIID ); \
		_hr = rCge.GetHRESULT(); \
		GetErrorInfo( 0, &_spIEI ); \
	}\
	catch( _com_error& rCE )\
	{\
		_hr = rCE.Error();\
		_spIEI.Attach( rCE.ErrorInfo() ); \
	}\
	catch( std::bad_alloc& )\
	{\
		THIS->Error( L"Not enough memory", rIID, (_hr = E_OUTOFMEMORY) );\
		GetErrorInfo( 0, &_spIEI ); \
	}\
	catch( std::exception& rE )\
	{\
		MySetError( THIS, rE, rIID, (_hr = E_FAIL) );\
		GetErrorInfo( 0, &_spIEI ); \
	}\
	catch( ... )\
	{\
		THIS->Error( L"Unknown exception", rIID, (_hr = E_UNEXPECTED) );\
		GetErrorInfo( 0, &_spIEI ); \
	}

#define TRY_END \
	SetErrorInfo( 0, _spIEI );\
	_spIEI.Release()\
	

#define TRY_EXIT \
	TRY_END; \
	return _hr


#define END_TRY_NOCOM \
	} \
	catch( CGenericError& rCge ) \
	{ \
		rCge.SetErrorInfo(); \
		_hr = rCge.GetHRESULT(); \
		GetErrorInfo( 0, &_spIEI ); \
	}\
	catch( _com_error& rCE )\
	{\
		_hr = rCE.Error();\
		_spIEI.Attach( rCE.ErrorInfo() ); \
	}\
	catch( std::bad_alloc& )\
	{\
		MySetError( L"Not enough memory", (_hr = E_OUTOFMEMORY) );\
		GetErrorInfo( 0, &_spIEI ); \
	}\
	catch( std::exception& rE )\
	{\
		MySetError( rE.what(), (_hr = E_FAIL) );\
		GetErrorInfo( 0, &_spIEI ); \
	}\
	catch( ... )\
	{\
		MySetError( L"Unknown exception", (_hr = E_UNEXPECTED) );\
		GetErrorInfo( 0, &_spIEI ); \
	}

#endif //_NO_ATL_ERRORS_


#ifdef _MFC_ERRORS_

#define BEGIN_TRY_MFC \
	HRESULT _hr = S_OK;\
	try {

HRESULT __fastcall MFCReportError( CGenericError& ) throw();
HRESULT __fastcall MFCReportError( _com_error& ) throw();
HRESULT __fastcall MFCReportError( std::bad_alloc& ) throw();
HRESULT __fastcall MFCReportError( std::exception& ) throw();

#define END_TRY_MFC \
	} \
	catch( CGenericError& rCge ) \
	{ \
		_hr = MFCReportError( rCge );\
	}\
	catch( CException *pE )\
	{\
		pE->ReportError();\
		pE->Delete();\
		_hr = E_FAIL;\
	}\
	catch( _com_error& rCE )\
	{\
		_hr = MFCReportError( rCE );\
	}\
	catch( std::bad_alloc& rba )\
	{\
		_hr = MFCReportError( rba );\
	}\
	catch( std::exception& rE )\
	{\
		_hr = MFCReportError( rE );\
	}\
	catch( ... )\
	{\
		AfxMessageBox( _T("<Unknown error>"), MB_OK|MB_ICONSTOP, 0 );\
		_hr = E_UNEXPECTED;\
	}

#endif //_MFC_ERRORS_


//----------- ACROBAT_ERRORS ----------- 
#ifdef __ACROBAT_ERRORS_

void __fastcall AcrobatThrowSimpleSTDExc( LPCSTR lpMsgOn, LPCSTR lpMsgWhat, LPCSTR lpFile, int iLine );

#define ACROBAT_CHK_W32( RESULT, BAD_VAL, ACTIVITY ) \
	AcrobatChkWin32( RESULT, BAD_VAL, ACTIVITY, _T(__FILE__), __LINE__ )

#define ACROBAT_CHK_COM( RESULT, ACTIVITY ) \
	AcrobatChkCOM( RESULT, ACTIVITY, _T(__FILE__), __LINE__ )

#define ACROBAT_CHK_ALLOC( RESULT ) \
	AcrobatChkAlloc( RESULT, __FILE__, __LINE__ )

#define ACROBAT_THROW_SIMPLE_STD_EXC( MSG_ON, MSG_WHAT )\
	AcrobatThrowSimpleSTDExc( MSG_ON, MSG_WHAT, __FILE__, __LINE__ )

#define ACRO_ERR_TO_COM( THIS, rIID ) \
	char errorBuf[ 1024 ]; \
	AVSysSetWaitCursor( false, 0 ); \
	ASGetErrorString( ASGetExceptionErrorCode(), errorBuf, sizeof errorBuf ); \
	THIS->Error( errorBuf, rIID, E_FAIL ); \
	return E_FAIL

template<class T> T __fastcall AcrobatChkWin32( T tVal, T tBadVal, LPCWSTR lpcwActivity, LPCTSTR lpctFile, DWORD dwLine )
{
	if( tVal == tBadVal )
	{
		CWin32Error cweErr( GetLastError(), lpctFile, dwLine, lpcwActivity );
		MyAcrRaise( ErrAlways, SafeGetBSTR(cweErr.ToString()) );
	}
	return tVal;
}

HRESULT __fastcall AcrobatChkCOM( HRESULT hr, LPCWSTR lpcwActivity, LPCTSTR lpctFile, DWORD dwLine );


template<class T_RES> inline T_RES __fastcall AcrobatChkAlloc( T_RES trRes, LPCSTR lpFile, int iLine )
{
	_ASSERTE( lpFile != NULL );

	if( trRes == NULL )
	{		
		std::basic_stringstream<char> bsStrm;
		try {
					
			bsStrm << "\nIn file \"" << lpFile <<
				"\" and line " << iLine << " insufficient memory at alloc";					
		}	
		catch( ... ) { 			
			MyAcrRaise( ErrAlways, "Unexpected exception" );
		}		
		MyAcrRaise( ErrAlways, bsStrm.str().c_str() );
	}
	return trRes;
}

#define ACROBAT_NESTED_BEGIN_TRY \
	HRESULT _hr = S_OK;\
	try {

#define ACROBAT_NESTED_BEGIN_TRY2 \
	_hr = S_OK;\
	try {

//void __fastcall TRAPLVL_();

void MyAcrRaise( ASErrSeverity asSeverity, LPCWSTR lpcwDescr );
void MyAcrRaise( ASErrSeverity asSeverity, LPCSTR lpcwDescr );

#define ACROBAT_NESTED_END_TRY \
	} \
	catch( CGenericError& rCge ) \
	{ \
		_hr = rCge.GetHRESULT(); \
		MyAcrRaise( ErrAlways, SafeGetBSTR(rCge.ToString()) );\
	}\
	catch( _com_error& rCE )\
	{\
		_hr = rCE.Error();\
		MyAcrRaise( ErrAlways, SafeGetBSTR(ComErrDescr(rCE)) );\
	}\
	catch( std::bad_alloc& )\
	{\
		_hr = E_OUTOFMEMORY; \
		ASRaise( GenError(genErrNoMemory) ); \
	}\
	catch( std::exception& rE )\
	{\
		_hr = E_FAIL; \
		ASRaise( ASRegisterErrorString(ErrAlways, rE.what())); \
	}\
	catch( ... )\
	{\
		_hr = E_UNEXPECTED; \
		ASRaise( GenError(genErrGeneral) ); \
	}

#endif //__ACROBAT_ERRORS_
//----------- ACROBAT_ERRORS END ----------- 

CComBSTR __fastcall GetCurrentCOMErrorDescr() throw();
void __fastcall ReportCurrentError( HWND hw ) throw();

#ifdef _URL_MONIKER_ERRORS_
bool __fastcall GetURLMonikerError( HRESULT hr, CComBSTR& rbsErr ) throw();
#endif

#define MPUT_PROPERTY( OldV, NewV ) \
  if( OldV != NewV ) \
    OldV = NewV, SetDirty()

#define MPUT_PROPERTY_NM( OldV, NewV ) \
  if( OldV != NewV ) \
    OldV = NewV

#define MGET_PROPERTY( To, From ) \
	if( To == NULL ) _com_issue_error( E_POINTER ); \
  else *To = From

#define CHECK_ARG( Arg ) \
  if( Arg == NULL ) _com_issue_error( E_POINTER )


//----------- Locking helpers ----------- 

template<class T> class CMyLock
{
public:
	CMyLock( T& tObj, bool bLocked = true ): m_tRef( tObj )
	{
		m_bLocked = false;
		if( bLocked ) Lock();		
	}
	~CMyLock()
	{
		Unlock();
	}
	void __fastcall Unlock()
	{
		if( m_bLocked ) m_tRef.Unlock(), m_bLocked = false;
	}
	void __fastcall Lock()
	{
		if( !m_bLocked ) m_tRef.Lock(), m_bLocked = true;
	}
private:
	bool m_bLocked;
	T& m_tRef;	
};
//----------- Locking helpers END ----------- 

#if defined(_GDIPLUS_H)

class CGDIPError: public CGenericError
{
public:
	CGDIPError( Gdiplus::Status stat, LPCTSTR lpctFileName, DWORD dwLine, LPCWSTR lpcwActivity = NULL ) throw():
	  CGenericError( lpctFileName, dwLine, lpcwActivity ),
	  m_stErr( stat )
	  {		  
	  }

	~CGDIPError() {}

	BSTR __fastcall GetDescription() throw();
	HRESULT __fastcall GetHRESULT() throw()
	{
		return HRESULT_FROM_WIN32( (DWORD)m_stErr );
	}

	Gdiplus::Status __fastcall GetStatus() throw()
	{
		return m_stErr;
	}

private:
	Gdiplus::Status		m_stErr;
	CComBSTR			m_ccbFDescr;
};

inline Gdiplus::Status __fastcall ChkGDIP( Gdiplus::Status stat, LPCWSTR lpcwActivity, LPCTSTR lpctFile, DWORD dwLine )
{
	if( stat != Gdiplus::Ok ) throw CGDIPError( stat, lpctFile, dwLine, lpcwActivity );
	return stat;
}

#define CHK_GDIP( RESULT, ACTIVITY ) \
	ChkGDIP( RESULT, ACTIVITY, _T(__FILE__), __LINE__ )

#ifdef __ACROBAT_ERRORS_

Gdiplus::Status __fastcall AcrobatChkGDIP( Gdiplus::Status stat, LPCWSTR lpcwActivity, LPCTSTR lpctFile, DWORD dwLine );

#define ACROBAT_CHK_GDIP( RESULT, ACTIVITY ) \
	AcrobatChkGDIP( RESULT, ACTIVITY, _T(__FILE__), __LINE__ )

#endif

#endif //_GDIPLUS_H

#define DECLARE_TICK \
	DWORD _dwTickSta = GetTickCount(), _dwTickCurr
#define BEGIN_TICK \
	_dwTickCurr = GetTickCount()
#define END_TICK( SLINCE ) \
	SLINCE = GetTickCount() - _dwTickCurr


#define BEGIN_TICK2( VARNAME ) \
	VARNAME = GetTickCount()
#define END_TICK2( VARNAME, SLINCE ) \
	SLINCE = GetTickCount() - VARNAME




//----------- String helpers ----------- 
void __fastcall TrimBSTR( const BSTR bsIn, BSTR& bsOut );
#ifdef _STRING_
void __fastcall TrimBasicString( std::basic_string<wchar_t>& rbs );
void __fastcall TrimBasicString( std::basic_string<char>& rbs );
#endif
//----------- String helpers ----------- 

//----------- Variant extractors ----------- 
short			__fastcall NormAndChk_I2( VARIANT& );
long			__fastcall NormAndChk_I4( VARIANT& );
float			__fastcall NormAndChk_R4( VARIANT& );
double			__fastcall NormAndChk_R8( VARIANT& );
VARIANT_BOOL	__fastcall NormAndChk_VBOOL( VARIANT& );
CComBSTR		__fastcall NormAndChk_BSTR( VARIANT& );
//----------- Variant extractors END ----------- 


void __fastcall ThrowCommonDlgError( DWORD );

int DoubleNullSize( LPCTSTR ) throw();

#pragma pack( push, 1 )
struct _CThunk
{	
	BYTE	m_pop1, m_pop2; //pop dword ptr [ReturnAddr]
	DWORD   m_AddrReturn1;

	BYTE	m_push;         // push m_this
	DWORD   m_this;         //

	BYTE	m_push1, m_push2; //push dword ptr [ReturnAddr]
	DWORD	m_AddrReturn2;

	BYTE    m_jmp;          // jmp SHORT WndProc
	DWORD   m_relproc;      // relative jmp Addr.

	DWORD   m_storeReturn;	//Return address
};
#pragma pack( pop )

template<class T> class CMyThunk
{
public:
	typedef void (CALLBACK T::*TPFN)();

	_CThunk m_thunk;
	
	void Init( TPFN proc, T* pThis )
	{
#pragma warning( disable: 4311 )
		union {
		  DWORD dwFunc;
		  TPFN pfn;
		} pfn;

		pfn.pfn = proc;	

		m_thunk.m_pop1 = 0x8F, m_thunk.m_pop2 = 0x05;
		m_thunk.m_AddrReturn1 = (DWORD)&m_thunk.m_storeReturn;

		m_thunk.m_push1 = 0xFF, m_thunk.m_push2 = 0x35;
		m_thunk.m_AddrReturn2 = (DWORD)&m_thunk.m_storeReturn;

		m_thunk.m_push = 0x68;  //push
		m_thunk.m_this = (DWORD)pThis;
		m_thunk.m_jmp = 0xe9;
		m_thunk.m_relproc = int(pfn.dwFunc) - ( int(this) + sizeof(_CThunk) - sizeof(m_thunk.m_storeReturn) );
		// write block from data cache and
		//  flush from instruction cache
		m_thunk.m_storeReturn = 0;

		FlushInstructionCache( GetCurrentProcess(), &m_thunk, sizeof m_thunk );
#pragma warning( default: 4311 )
	}
};


LPBYTE __fastcall FindSubBytes( LPBYTE lp, LPBYTE lpSub, int lSz, int lSzSub ) throw();


//#ifdef _DEBUG
	void DebuPrint( LPCWSTR lpcwMsg, long lData ) throw();
//#endif


//----------- XML Helpers ----------- 
_bstr_t __fastcall NumberToUserLocale( _bstr_t& );
float __fastcall FloatFromVar( _variant_t& vt );
//----------- END XML Helpers ----------- 

//----------- Memory helpers ----------- 

#if defined(_MEMORY_)


template<class _Ty>
	class auto_ptr_arr {
public:

	typedef _Ty element_type;

	explicit auto_ptr_arr(_Ty *_P = 0) _THROW0()
		: _Owns(_P != 0), _Ptr(_P) {}

	auto_ptr_arr(const auto_ptr_arr<_Ty>& _Y) _THROW0()
		: _Owns(_Y._Owns), _Ptr(_Y.release()) {}

	auto_ptr_arr<_Ty>& operator=( const auto_ptr_arr<_Ty>& _Y ) _THROW0()
	{
		if( this != &_Y )
		{
			if( _Ptr != _Y.get() )
			{
				if( _Owns )
					delete[] _Ptr;
				_Owns = _Y._Owns; 
			}
			else if( _Y._Owns )
				_Owns = true;

			_Ptr = _Y.release(); 
		}
		return (*this); 
	}

	~auto_ptr_arr()
		{
			if(_Owns )
				delete[] _Ptr; 
		}

	_Ty& operator*() const _THROW0()
		{return (*get()); }
	_Ty *operator->() const _THROW0()
		{return (get()); }
	_Ty *get() const _THROW0()
		{return (_Ptr); }

	_Ty *release() const _THROW0()
		{			 
			((auto_ptr_arr<_Ty>*)this)->_Owns = false;
			return (_Ptr); 
		}

private:
	bool _Owns;
	_Ty *_Ptr;
};

template<class T> inline void __fastcall FreeAutoPtr( std::auto_ptr<T>& rap ) throw()
{
	rap = std::auto_ptr<T>( NULL );
}

template<class T> inline void __fastcall FreeAutoPtr( auto_ptr_arr<T>& rap ) throw()
{
	rap = auto_ptr_arr<T>( NULL );
}

//----------- Memory helpers END ----------- 
#endif //_MEMORY_

#endif //_ERR_HLP_H_
