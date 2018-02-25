// Resizer.h : Declaration of the CResizer
#if !defined(_BSC_)
#define _BSC_

#pragma once
#include "resource.h"       // main symbols

[
	object,
	uuid(9319D551-94DB-4ec1-93AF-792FC7AB1B37),
	helpstring("IBindingNotify Interface"),
	pointer_default(unique)
]
__interface IBindingNotify: public IUnknown
{
	HRESULT OnProgress( [in]IBindStatusCallback* pSender, [in]ULONG ulProgress,
		[in]ULONG ulProgressMax, [in]ULONG ulStatusCode, [in]BSTR bsStatusText );

	HRESULT OnStartBinding( [in]DWORD dwReserved, [in]IBinding* pBinding );
	HRESULT PreBindMoniker( [in]IBindCtx* pBindCtx, [in]IMoniker* pMoniker );
	HRESULT OnBindingFailure( [in]HRESULT hr, [in]BSTR bsError );
};


class ATL_NO_VTABLE CAwsBindStatusCallback: 
	public CComObjectRootEx<CComMultiThreadModel>,
	public IBindStatusCallback,
	public IHttpNegotiate,
	public IServiceProvider
{
private:
	std::auto_ptr<CMultipartForm> m_apFrm;
	CComPtr<IBindingNotify> m_spNotify;

	bool m_bRedirect;
	DWORD m_dwAction;
	CComPtr<IMoniker> m_spMoniker;
	CComPtr<IBindCtx> m_spBindCtx;
	CComPtr<IBinding> m_spBinding;

	CComPtr<IStream> m_spInputStm; //stream for downloading

public:
	CAwsBindStatusCallback(): m_dwAction(BINDVERB_POST), m_bRedirect( false )
	{
	}
	~CAwsBindStatusCallback()
	{
	}

	void __fastcall HandsoffData()
	{
		FreeAutoPtr( m_apFrm );
		m_spNotify = NULL;

		m_spInputStm = NULL;

		m_spBinding = NULL;
		m_spBindCtx = NULL;
		m_spMoniker = NULL;
	}
	
	static HRESULT __fastcall StartAsyncUpload( std::auto_ptr<CMultipartForm> apFrm, IBindingNotify* pNotify, BSTR bsUrl, bool bRelative = false, IUnknown* pUnkContainer = NULL );


BEGIN_COM_MAP( CAwsBindStatusCallback )
	COM_INTERFACE_ENTRY_IID( IID_IBindStatusCallback, IBindStatusCallback )
	COM_INTERFACE_ENTRY_IID( IID_IHttpNegotiate, IHttpNegotiate )
	COM_INTERFACE_ENTRY_IID( IID_IServiceProvider, IServiceProvider )
END_COM_MAP()

STDMETHOD(QueryService)( REFGUID guidService,
    REFIID riid,
    void **ppv
)
{
	if( riid == IID_IHttpNegotiate )
	{
		*ppv = static_cast<IHttpNegotiate*>( this );
		AddRef();
		return S_OK;
	}
	else
		return E_NOINTERFACE;
}


/*HRESULT _InternalQueryInterface( REFIID riid, void** ppv ) throw()
//STDMETHOD(QueryInterface)( REFIID riid, void ** ppv )
{
	if( riid==IID_IUnknown || riid==IID_IBindStatusCallback )
	{
		*ppv = (IBindStatusCallback*)this;
		((IBindStatusCallback*)this)->AddRef();
		return S_OK;
	}
	if( riid==IID_IHttpNegotiate )
	{
	    *ppv = (IHttpNegotiate*)this;
		((IBindStatusCallback*)this)->AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}*/

// IBindStatusCallback methods
public:
	STDMETHOD(OnStartBinding)( DWORD dwReserved, IBinding* pbinding ) throw();
    STDMETHOD(GetPriority)( LONG* pnPriority ) throw();
    STDMETHOD(OnLowResource)( DWORD dwReserved ) throw();
    STDMETHOD(OnProgress)( ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode,
						   LPCWSTR pwzStatusText ) throw();
    STDMETHOD(OnStopBinding)( HRESULT hrResult, LPCWSTR szError ) throw();
    STDMETHOD(GetBindInfo)( DWORD* pgrfBINDF, BINDINFO* pbindinfo ) throw();
    STDMETHOD(OnDataAvailable)( DWORD grfBSCF, DWORD dwSize, FORMATETC *pfmtetc,
								STGMEDIUM* pstgmed ) throw();
    STDMETHOD(OnObjectAvailable)( REFIID riid, IUnknown* punk ) throw();

// IHttpNegotiate methods
public:
	STDMETHOD(BeginningTransaction)(/* [in] */ LPCWSTR szURL,
					/* [unique][in] */ LPCWSTR szHeaders,
					/* [in] */ DWORD dwReserved,
					/* [out] */ LPWSTR __RPC_FAR *pszAdditionalHeaders) throw();
        
    STDMETHOD(OnResponse)(/* [in] */ DWORD dwResponseCode,
        /* [unique][in] */ LPCWSTR szResponseHeaders,
        /* [unique][in] */ LPCWSTR szRequestHeaders,
        /* [out] */ LPWSTR __RPC_FAR *pszAdditionalRequestHeaders) throw();

private:
	HRESULT __fastcall InternalStartAsyncUpload( std::auto_ptr<CMultipartForm> apFrm, IBindingNotify* pNotify, BSTR bsUrl, bool bRelative = false, IUnknown* pUnkContainer = NULL );
};


#endif
