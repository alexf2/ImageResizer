#ifndef _PROPS_HELPER_
#define _PROPS_HELPER_

#pragma once

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#include <atlwin.h>

#define IMPLEMENT_STOCKPROP_VARIANT(fname, pname, dispid) \
	HRESULT STDMETHODCALLTYPE put_##fname(VARIANT* pVar) \
	{ \
		__if_exists(T::m_##pname) \
		{ \
			ATLTRACE(ATL::atlTraceControls,2,_T("CStockPropImpl::put_%s\n"), #fname); \
			T* pT = (T*) this; \
			if (pT->m_nFreezeEvents == 0 && pT->FireOnRequestEdit(dispid) == S_FALSE) \
				return S_FALSE; \
			pT->m_##pname = *pVar; \
			pT->m_bRequiresSave = TRUE; \
			if (pT->m_nFreezeEvents == 0) \
				pT->FireOnChanged(dispid); \
			__if_exists(T::On##fname##Changed) \
			{ \
				pT->On##fname##Changed(); \
			} \
			pT->FireViewChange(); \
			pT->SendOnDataChange(NULL); \
		} \
		return S_OK; \
	} \
	HRESULT STDMETHODCALLTYPE get_##fname(VARIANT* pVar) \
	{ \
		__if_exists(T::m_##pname) \
		{ \
			ATLTRACE(ATL::atlTraceControls,2,_T("CStockPropImpl::get_%s\n"), #fname); \
			ATLASSERT(p##pname != NULL); \
			if (p##pname == NULL) \
				return E_POINTER; \
			T* pT = (T*) this; \
            ::VariantInit( pVar ); \
            if( V_VT(&pT->m_##pname) != VT_EMPTY ) \
            return ::VariantCopy( pVar, &pT->m_##pname ); \
		} \
		return S_OK; \
	}

#endif //_PROPS_HELPER_
