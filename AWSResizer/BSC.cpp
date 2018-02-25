#include "stdafx.h"
#include "CMultipartForm.h"
#include "BSC.h"


HRESULT __fastcall CAwsBindStatusCallback::InternalStartAsyncUpload(  std::auto_ptr<CMultipartForm> apFrm, IBindingNotify* pNotify, BSTR bstrURL, bool bRelative, IUnknown* pUnkContainer )
{
	m_apFrm = apFrm;
	m_spNotify = pNotify;

	HRESULT hr = S_OK;
	CComQIPtr<IServiceProvider, &IID_IServiceProvider> spServiceProvider( pUnkContainer );
	CComPtr<IBindHost> spBindHost;
	if( spServiceProvider )
			spServiceProvider->QueryService( SID_IBindHost, IID_IBindHost, (void**)&spBindHost );

	if( spBindHost == NULL )
	{
		if( bRelative )
			return E_NOINTERFACE;  // relative asked for, but no IBindHost
		hr = CreateURLMoniker( NULL, bstrURL, &m_spMoniker );

		if( SUCCEEDED(hr) )
			//hr = CreateBindCtx( 0, &m_spBindCtx );
			hr = CreateAsyncBindCtx( 0, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallback*>(this)), NULL, &m_spBindCtx );

		if( SUCCEEDED(hr) )
			hr = RegisterBindStatusCallback( m_spBindCtx, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallback*>(this)), 0, 0L );

		if( SUCCEEDED(hr) )
			pNotify->PreBindMoniker( m_spBindCtx.p, m_spMoniker.p );

		if( SUCCEEDED(hr) )
		{
			IStream* pStream;
			hr = m_spMoniker->BindToStorage( m_spBindCtx, 0, IID_IStream, (void**)&pStream );
			if( pStream != NULL ) // ADDED
				pStream->Release();
			ATLTRACE( _T("Bound") );
		}
	}
	else
	{
		//hr = CreateBindCtx( 0, &m_spBindCtx );
		hr = CreateAsyncBindCtx( 0, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallback*>(this)), NULL, &m_spBindCtx );

		if( SUCCEEDED(hr) )
		{
			if( bRelative )
				hr = spBindHost->CreateMoniker( bstrURL, m_spBindCtx, &m_spMoniker, 0 );
			else
				hr = CreateURLMoniker( NULL, bstrURL, &m_spMoniker );			
		}

		if( SUCCEEDED(hr) )
			pNotify->PreBindMoniker( m_spBindCtx.p, m_spMoniker.p );

		if( SUCCEEDED(hr) )
		{
			IStream* pStream;
			hr = spBindHost->MonikerBindToStorage( m_spMoniker, m_spBindCtx, reinterpret_cast<IBindStatusCallback*>(static_cast<IBindStatusCallback*>(this)), IID_IStream, (void**)&pStream );
			if( pStream != NULL ) // ADDED
				pStream->Release();
			ATLTRACE( _T("Bound") );
		}
	}

	if( FAILED(hr) )
	{
		m_spMoniker.Release();
		m_spBindCtx.Release();
		m_spNotify.Release();
	}

	return hr;
}

//static
HRESULT __fastcall CAwsBindStatusCallback::StartAsyncUpload( std::auto_ptr<CMultipartForm> apFrm, IBindingNotify* pNotify, BSTR bsUrl, bool bRelative, IUnknown* pUnkContainer )
{
	CComObject<CAwsBindStatusCallback> *pbsc = NULL;
	HRESULT hRes = CComObject<CAwsBindStatusCallback>::CreateInstance( &pbsc );
	if( SUCCEEDED(hRes) )
	{		
		hRes = pbsc->InternalStartAsyncUpload( apFrm, pNotify, bsUrl, bRelative, pUnkContainer );
		if( FAILED(hRes) )
			delete pbsc;
	}
	return hRes;
}

STDMETHODIMP CAwsBindStatusCallback::OnStartBinding( DWORD dwReserved, IBinding* pbinding ) throw()
{
	HRESULT hr = S_OK;
	if( m_spNotify.p )
		hr = m_spNotify->OnStartBinding( dwReserved, pbinding );
	return hr;
}
STDMETHODIMP CAwsBindStatusCallback::GetPriority( LONG* pnPriority ) throw()
{
	return E_NOTIMPL;
}
STDMETHODIMP CAwsBindStatusCallback::OnLowResource( DWORD dwReserved ) throw()
{
	return E_NOTIMPL;
}

struct TBndStatDescr
{
	BINDSTATUS stat;
	const wchar_t* descr;
};
const static TBndStatDescr bndDescrs[]  =
{
	{ BINDSTATUS_FINDINGRESOURCE, L"Finding resource" },
	{ BINDSTATUS_CONNECTING, L"Connecting" },
	{ BINDSTATUS_REDIRECTING, L"Redirectiong" },
	{ BINDSTATUS_BEGINDOWNLOADDATA, L"Begin downloading" },
	{ BINDSTATUS_DOWNLOADINGDATA, L"Downoloading" },
	{ BINDSTATUS_ENDDOWNLOADDATA, L"End downloading" },
	{ BINDSTATUS_BEGINDOWNLOADCOMPONENTS, L"Begin downloading DCOM" },
	{ BINDSTATUS_INSTALLINGCOMPONENTS, L"Installing components" },
	{ BINDSTATUS_ENDDOWNLOADCOMPONENTS, L"End downloading components" },
	{ BINDSTATUS_USINGCACHEDCOPY, L"Using cached copy" },
	{ BINDSTATUS_SENDINGREQUEST, L"Sending request" },
	{ BINDSTATUS_CLASSIDAVAILABLE, L"Class available" },
	{ BINDSTATUS_MIMETYPEAVAILABLE, L"MIME type available" },
	{ BINDSTATUS_CACHEFILENAMEAVAILABLE, L"Cache file name available" },
	{ BINDSTATUS_BEGINSYNCOPERATION, L"Begin sync operation" },
	{ BINDSTATUS_ENDSYNCOPERATION, L"End sync operation" },
	{ BINDSTATUS_BEGINUPLOADDATA, L"Begin uploading data" },
	{ BINDSTATUS_UPLOADINGDATA, L"Uploading data" },
	{ BINDSTATUS_ENDUPLOADDATA, L"End uploading data" },
	{ BINDSTATUS_PROTOCOLCLASSID, L"Protocol class ID" },
	{ BINDSTATUS_ENCODING, L"Encoding" },
	{ BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE, L"BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE" },
	{ BINDSTATUS_CLASSINSTALLLOCATION, L"BINDSTATUS_CLASSINSTALLLOCATION" },
	{ BINDSTATUS_DECODING, L"BINDSTATUS_DECODING" },
	{ BINDSTATUS_LOADINGMIMEHANDLER, L"BINDSTATUS_LOADINGMIMEHANDLER" },
	{ BINDSTATUS_CONTENTDISPOSITIONATTACH, L"BINDSTATUS_CONTENTDISPOSITIONATTACH" },
	{ BINDSTATUS_FILTERREPORTMIMETYPE, L"BINDSTATUS_FILTERREPORTMIMETYPE" },
	{ BINDSTATUS_CLSIDCANINSTANTIATE, L"BINDSTATUS_CLSIDCANINSTANTIATE" },
	{ BINDSTATUS_IUNKNOWNAVAILABLE, L"BINDSTATUS_IUNKNOWNAVAILABLE" },
	{ BINDSTATUS_DIRECTBIND, L"BINDSTATUS_DIRECTBIND" },
	{ BINDSTATUS_RAWMIMETYPE, L"BINDSTATUS_RAWMIMETYPE" },
	{ BINDSTATUS_PROXYDETECTING, L"BINDSTATUS_PROXYDETECTING" },
	{ BINDSTATUS_ACCEPTRANGES, L"BINDSTATUS_ACCEPTRANGES" },
	{ BINDSTATUS_COOKIE_SENT, L"BINDSTATUS_COOKIE_SENT" },
	{ BINDSTATUS_COMPACT_POLICY_RECEIVED, L"BINDSTATUS_COMPACT_POLICY_RECEIVED" },
	{ BINDSTATUS_COOKIE_SUPPRESSED, L"BINDSTATUS_COOKIE_SUPPRESSED" },
	{ BINDSTATUS_COOKIE_STATE_UNKNOWN, L"BINDSTATUS_COOKIE_STATE_UNKNOWN" },
	{ BINDSTATUS_COOKIE_STATE_ACCEPT, L"BINDSTATUS_COOKIE_STATE_ACCEPT" },
	{ BINDSTATUS_COOKIE_STATE_REJECT, L"BINDSTATUS_COOKIE_STATE_REJECT" },
	{ BINDSTATUS_COOKIE_STATE_PROMPT, L"BINDSTATUS_COOKIE_STATE_PROMPT" },
	{ BINDSTATUS_COOKIE_STATE_LEASH, L"BINDSTATUS_COOKIE_STATE_LEASH" },
	{ BINDSTATUS_COOKIE_STATE_DOWNGRADE, L"BINDSTATUS_COOKIE_STATE_DOWNGRADE" },
	{ BINDSTATUS_POLICY_HREF, L"BINDSTATUS_POLICY_HREF" },
	{ BINDSTATUS_P3P_HEADER, L"BINDSTATUS_P3P_HEADER" },
	{ BINDSTATUS_SESSION_COOKIE_RECEIVED, L"BINDSTATUS_SESSION_COOKIE_RECEIVED" },
	{ BINDSTATUS_PERSISTENT_COOKIE_RECEIVED, L"BINDSTATUS_PERSISTENT_COOKIE_RECEIVED" },
	{ BINDSTATUS_PERSISTENT_COOKIE_RECEIVED, L"BINDSTATUS_PERSISTENT_COOKIE_RECEIVED" },
	{ BINDSTATUS_SESSION_COOKIES_ALLOWED, L"BINDSTATUS_SESSION_COOKIES_ALLOWED" }
};

STDMETHODIMP CAwsBindStatusCallback::OnProgress( 
							ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode,
							LPCWSTR pwzStatusText ) throw()
{
	CComBSTR bsStatusText = L"Unknown status code";

	for( int i = 0; i < sizeof(bndDescrs) / sizeof(TBndStatDescr); ++i )
		if( bndDescrs[i].stat == ulStatusCode )
		{
			bsStatusText = bndDescrs[ i ].descr;
			break;
		}
	/*switch( ulStatusCode )
	{
		case BINDSTATUS_REDIRECTING:
			bsStatusText = L"Server redirecting client";
			m_bRedirect = true;
			break;

		case BINDSTATUS_FINDINGRESOURCE:
			bsStatusText = L"Finding resource";			
			break;

		case BINDSTATUS_CONNECTING:
			bsStatusText = L"Connecting";
			break;

		case BINDSTATUS_BEGINDOWNLOADDATA:
			bsStatusText = L"Beginning to download data";
			break;

		case BINDSTATUS_DOWNLOADINGDATA:
			bsStatusText = L"Downloading data";
			break;

		case BINDSTATUS_ENDDOWNLOADDATA:
			bsStatusText = L"Ending data download";
			break;

		case BINDSTATUS_BEGINDOWNLOADCOMPONENTS:
			bsStatusText = L"Beginning to download components";
			break;

		case BINDSTATUS_INSTALLINGCOMPONENTS:
			bsStatusText = L"Installing components";
			break;

		case BINDSTATUS_ENDDOWNLOADCOMPONENTS:
			bsStatusText = L"Ending component download";
			break;

		case BINDSTATUS_USINGCACHEDCOPY:
			bsStatusText = L"Using cached copy";
			break;

		case BINDSTATUS_SENDINGREQUEST:
			bsStatusText = L"Sending request";
			break;

		case BINDSTATUS_CLASSIDAVAILABLE:
			bsStatusText = L"CLSID available";
			break;

		case BINDSTATUS_MIMETYPEAVAILABLE:
			bsStatusText = L"MIME type available";
			break;

		case BINDSTATUS_CACHEFILENAMEAVAILABLE:
			bsStatusText = L"Cache file name available";
			break;

		default:
			bsStatusText = L"Unknown binding status code";
			break;
	};*/

	HRESULT hr = S_OK;
	if( m_spNotify.p )
		hr = m_spNotify->OnProgress( static_cast<IBindStatusCallback*>(this), ulProgress, ulProgressMax, ulStatusCode, bsStatusText );
	return hr;
}
STDMETHODIMP CAwsBindStatusCallback::OnStopBinding( HRESULT hrResult, LPCWSTR szError ) throw()
{
	HRESULT hr = S_OK;
	if( m_spNotify.p )
	{
		CComBSTR bsTmp( szError );
		hr = m_spNotify->OnBindingFailure( hrResult, bsTmp );
	}
	HandsoffData();
	return hr;
}
STDMETHODIMP CAwsBindStatusCallback::GetBindInfo( DWORD* pgrfBINDF, BINDINFO* pbindInfo ) throw()
{
	HRESULT hr = S_OK;
	if( m_bRedirect && BINDVERB_POST == m_dwAction )
	{
		m_dwAction = BINDVERB_GET;
	}
	*pgrfBINDF = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA |
		BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE;

	pbindInfo->cbSize = sizeof( BINDINFO );
	pbindInfo->dwBindVerb = BINDVERB_POST;
	pbindInfo->szExtraInfo = NULL;

	memset( &pbindInfo->stgmedData, 0, sizeof(STGMEDIUM) );
	pbindInfo->grfBindInfoF = 0;
	pbindInfo->szCustomVerb = NULL;

	if( m_apFrm.get() != NULL )
	{
		pbindInfo->stgmedData.tymed = TYMED_HGLOBAL;
		pbindInfo->cbstgmedData = (DWORD)m_apFrm->GetStream().GetSize();
		pbindInfo->stgmedData.hGlobal = m_apFrm->GetAsHGLOBAL();
		pbindInfo->stgmedData.pUnkForRelease = (IUnknown*)(IBindStatusCallback*)this;
		AddRef();
		//((IBindStatusCallback*)this)->AddRef();
	}

	return hr;
}
STDMETHODIMP CAwsBindStatusCallback::OnDataAvailable( DWORD grfBSCF, DWORD dwSize, FORMATETC *pfmtetc,
									STGMEDIUM* pstgmed ) throw()
{
	HRESULT hr = S_OK;
	if( BSCF_FIRSTDATANOTIFICATION & grfBSCF )
	{
		if( !m_spInputStm.p && pstgmed->tymed == TYMED_ISTREAM )
			m_spInputStm = pstgmed->pstm;
	}

	/*if( m_pstm.p && dwSize > m_cbOld )
	{
	}*/

	if( BSCF_LASTDATANOTIFICATION & grfBSCF )
	{
		if( m_spInputStm.p )
			m_spInputStm.Release();
	}
	return hr;
}
STDMETHODIMP CAwsBindStatusCallback::OnObjectAvailable( REFIID riid, IUnknown* punk ) throw()
{
	return E_NOTIMPL;
}

STDMETHODIMP CAwsBindStatusCallback::BeginningTransaction( /* [in] */ LPCWSTR szURL,
					/* [unique][in] */ LPCWSTR szHeaders,
					/* [in] */ DWORD dwReserved,
					/* [out] */ LPWSTR __RPC_FAR *pszAdditionalHeaders ) throw()
{
	if( !pszAdditionalHeaders )
		return E_POINTER;
	*pszAdditionalHeaders = NULL;

	if( BINDVERB_POST == m_dwAction && m_apFrm.get() )
	{
		//const WCHAR c_wszHeaders[] = L"Content-Type: multipart/form-data;";
		WCHAR wc[ 1024 ];
		swprintf( wc, L"Content-Type: multipart/form-data; boundary=%S", m_apFrm->GetBoundary() );
		LPWSTR wszAdditionalHeaders = 
			(LPWSTR)CoTaskMemAlloc( (wcslen(wc)+1) * sizeof(WCHAR) );
		if( !wszAdditionalHeaders )
			return E_OUTOFMEMORY;

		wcscpy( wszAdditionalHeaders, wc );
		*pszAdditionalHeaders = wszAdditionalHeaders;
	}
	return S_OK;
} 

STDMETHODIMP CAwsBindStatusCallback::OnResponse( /* [in] */ DWORD dwResponseCode,
    /* [unique][in] */ LPCWSTR szResponseHeaders,
    /* [unique][in] */ LPCWSTR szRequestHeaders,
    /* [out] */ LPWSTR __RPC_FAR *pszAdditionalRequestHeaders ) throw()
{
	if( !pszAdditionalRequestHeaders )
		return E_POINTER;
	*pszAdditionalRequestHeaders = NULL;
	return S_OK;
}
