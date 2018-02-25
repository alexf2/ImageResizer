#ifndef _RESOURCE_MANAGERS_
#define _RESOURCE_MANAGERS_

#pragma once

#ifdef __WINCRYPT_H__

struct __declspec(novtable) CCertProviderRcManager: public CBaseRcManager< HCRYPTPROV, bool >
{	
	bool __fastcall IsValidRes( HCRYPTPROV trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( HCRYPTPROV trt ) throw()  { return CryptReleaseContext(trt, 0) == TRUE; }
	void __fastcall ClearRes( HCRYPTPROV& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CCertStoreRcManager: public CBaseRcManager< HCERTSTORE, bool >
{	
	bool __fastcall IsValidRes( HCERTSTORE trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( HCERTSTORE trt ) throw()  { return CertCloseStore(trt, CERT_CLOSE_STORE_CHECK_FLAG) == TRUE; }
	void __fastcall ClearRes( HCERTSTORE& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CCertRcManager: public CBaseRcManager< PCCERT_CONTEXT, bool >
{	
	bool __fastcall IsValidRes( PCCERT_CONTEXT trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( PCCERT_CONTEXT trt ) throw()  { return CertFreeCertificateContext(trt) == TRUE; }
	void __fastcall ClearRes( PCCERT_CONTEXT& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CCertChainManager: public CBaseRcManager< PCCERT_CHAIN_CONTEXT, bool >
{	
	bool __fastcall IsValidRes( PCCERT_CHAIN_CONTEXT trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( PCCERT_CHAIN_CONTEXT trt ) throw()  { CertFreeCertificateChain(trt); return true; }
	void __fastcall ClearRes( PCCERT_CHAIN_CONTEXT& rTrt ) throw()  { rTrt = NULL; }
};

#endif //__WINCRYPT_H__


#ifdef _WINGDI_

struct __declspec(novtable) CDCManager: public CBaseRcManager< HDC, bool >
{	
	bool __fastcall IsValidRes( HDC trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( HDC trt ) throw()  { return ::DeleteDC(trt) != 0; }
	void __fastcall ClearRes( HDC& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CRGNManager: public CBaseRcManager< HRGN, bool >
{	
	bool __fastcall IsValidRes( HRGN trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( HRGN trt ) throw()  { return ::DeleteObject(trt) != 0; }
	void __fastcall ClearRes( HRGN& rTrt ) throw()  { rTrt = NULL; }
};

#endif //_WINGDI_


struct __declspec(novtable) CGlobalManager: public CBaseRcManager< HGLOBAL, bool >
{	
	bool __fastcall IsValidRes( HGLOBAL trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( HGLOBAL trt ) throw()  { return GlobalFree(trt) == NULL; }
	void __fastcall ClearRes( HGLOBAL& rTrt ) throw()  { rTrt = NULL; }
};


struct __declspec(novtable) CWin32HEAPManager: public CBaseRcManager< LPVOID, bool >
{	
	bool __fastcall IsValidRes( LPVOID trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( LPVOID trt ) throw()  { return HeapFree( GetProcessHeap(), 0, trt) == TRUE; }
	void __fastcall ClearRes( LPVOID& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CFORMATETC_Manager: public CBaseRcManager< FORMATETC*, bool >
{	
	bool __fastcall IsValidRes( FORMATETC* trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( FORMATETC* trt ) throw()  
	{ 
		if( trt && trt->ptd ) ::CoTaskMemFree( trt->ptd );
		return true;
	}
	void __fastcall ClearRes( FORMATETC*& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CSTGMEDIUM_Manager: public CBaseRcManager< STGMEDIUM*, bool >
{	
	bool __fastcall IsValidRes( STGMEDIUM* trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( STGMEDIUM* trt ) throw()  
	{ 
		if( trt )
			::ReleaseStgMedium( trt );
		return true;
	}
	void __fastcall ClearRes( STGMEDIUM*& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CIAlloc_Manager: public CBaseRcManager< LPOLESTR, bool >
{	
	bool __fastcall IsValidRes( LPOLESTR trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( LPOLESTR trt ) throw()  
	{ 
		if( trt ) ::CoTaskMemFree( trt );
		return true;
	}
	void __fastcall ClearRes( LPOLESTR& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CGlobalLock_Manager: public CBaseRcManager< LPVOID, bool >
{	
	bool __fastcall IsValidRes( LPVOID trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( LPVOID trt ) throw()  
	{ 
		if( trt ) ::GlobalUnlock( trt );
		return true;
	}
	void __fastcall ClearRes( LPVOID& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CFile_Manager: public CBaseRcManager< HANDLE, bool >
{	
	bool __fastcall IsValidRes( HANDLE trt ) const throw() { return trt != INVALID_HANDLE_VALUE; }
	bool __fastcall ReleaseRes( HANDLE trt ) throw()  
	{
		if( INVALID_HANDLE_VALUE != trt )
			return ::CloseHandle( trt ) != 0;
		return true;
	}
	void __fastcall ClearRes( HANDLE& rTrt ) throw()  { rTrt = INVALID_HANDLE_VALUE; }
};

struct __declspec(novtable) CProcess_Manager: public CBaseRcManager< HANDLE, bool >
{	
	bool __fastcall IsValidRes( HANDLE trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( HANDLE trt ) throw()  
	{
		if( NULL != trt )
			return ::CloseHandle( trt ) != 0;
		return true;
	}
	void __fastcall ClearRes( HANDLE& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CSafeArrayLock_Manager: public CBaseRcManager< SAFEARRAY*, bool >
{	
	bool __fastcall IsValidRes( SAFEARRAY* trt ) const throw() { return NULL != trt; }
	bool __fastcall ReleaseRes( SAFEARRAY* trt ) throw()  
	{
		if( NULL != trt )
			return SUCCEEDED( ::SafeArrayUnlock(trt) );
		return true;
	}
	void __fastcall ClearRes( SAFEARRAY*& rTrt ) throw()  { rTrt = NULL; }
};

struct __declspec(novtable) CSafeArrayDestr_Manager: public CBaseRcManager< SAFEARRAY*, bool >
{	
	bool __fastcall IsValidRes( SAFEARRAY* trt ) const throw() { return NULL != trt; }
	bool __fastcall ReleaseRes( SAFEARRAY* trt ) throw()  
	{
		if( NULL != trt )
			return SUCCEEDED( ::SafeArrayDestroy(trt) );
		return true;
	}
	void __fastcall ClearRes( SAFEARRAY*& rTrt ) throw()  { rTrt = NULL; }
};


#ifdef _INC_TOOLHELP32

struct __declspec(novtable) CToolHelpSnapshot_Manager: public CBaseRcManager< HANDLE, bool >
{	
	bool __fastcall IsValidRes( HANDLE trt ) const throw() { return trt != INVALID_HANDLE_VALUE; }
	bool __fastcall ReleaseRes( HANDLE trt ) throw()  
	{
		if( INVALID_HANDLE_VALUE != trt )
			return ::CloseHandle( trt ) != FALSE;
		return true;
	}
	void __fastcall ClearRes( HANDLE& rTrt ) throw()  { rTrt = INVALID_HANDLE_VALUE; }
};

#endif //_INC_TOOLHELP32

struct __declspec(novtable) CRegManager: public CBaseRcManager< HKEY, bool >
{	
	bool __fastcall IsValidRes( HKEY trt ) const throw() { return trt != NULL; }
	bool __fastcall ReleaseRes( HKEY trt ) throw()  { RegCloseKey(trt); return true; }
	void __fastcall ClearRes( HKEY& rTrt ) throw()  { rTrt = NULL; }
};

#endif
