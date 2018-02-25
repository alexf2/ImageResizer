

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Fri Nov 18 21:18:17 2005
 */
/* Compiler settings for _AWSResizer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___AWSResizer_h__
#define ___AWSResizer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBindingNotify_FWD_DEFINED__
#define __IBindingNotify_FWD_DEFINED__
typedef interface IBindingNotify IBindingNotify;
#endif 	/* __IBindingNotify_FWD_DEFINED__ */


#ifndef __IResizer_FWD_DEFINED__
#define __IResizer_FWD_DEFINED__
typedef interface IResizer IResizer;
#endif 	/* __IResizer_FWD_DEFINED__ */


#ifndef ___IResizerEvents_FWD_DEFINED__
#define ___IResizerEvents_FWD_DEFINED__
typedef interface _IResizerEvents _IResizerEvents;
#endif 	/* ___IResizerEvents_FWD_DEFINED__ */


#ifndef __CResizer_FWD_DEFINED__
#define __CResizer_FWD_DEFINED__

#ifdef __cplusplus
typedef class CResizer CResizer;
#else
typedef struct CResizer CResizer;
#endif /* __cplusplus */

#endif 	/* __CResizer_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IBindingNotify_INTERFACE_DEFINED__
#define __IBindingNotify_INTERFACE_DEFINED__

/* interface IBindingNotify */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IBindingNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9319D551-94DB-4ec1-93AF-792FC7AB1B37")
    IBindingNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnProgress( 
            /* [in] */ IBindStatusCallback *pSender,
            /* [in] */ ULONG ulProgress,
            /* [in] */ ULONG ulProgressMax,
            /* [in] */ ULONG ulStatusCode,
            /* [in] */ BSTR bsStatusText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnStartBinding( 
            /* [in] */ DWORD dwReserved,
            /* [in] */ IBinding *pBinding) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreBindMoniker( 
            /* [in] */ IBindCtx *pBindCtx,
            /* [in] */ IMoniker *pMoniker) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnBindingFailure( 
            /* [in] */ HRESULT hr,
            /* [in] */ BSTR bsError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBindingNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBindingNotify * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBindingNotify * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBindingNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnProgress )( 
            IBindingNotify * This,
            /* [in] */ IBindStatusCallback *pSender,
            /* [in] */ ULONG ulProgress,
            /* [in] */ ULONG ulProgressMax,
            /* [in] */ ULONG ulStatusCode,
            /* [in] */ BSTR bsStatusText);
        
        HRESULT ( STDMETHODCALLTYPE *OnStartBinding )( 
            IBindingNotify * This,
            /* [in] */ DWORD dwReserved,
            /* [in] */ IBinding *pBinding);
        
        HRESULT ( STDMETHODCALLTYPE *PreBindMoniker )( 
            IBindingNotify * This,
            /* [in] */ IBindCtx *pBindCtx,
            /* [in] */ IMoniker *pMoniker);
        
        HRESULT ( STDMETHODCALLTYPE *OnBindingFailure )( 
            IBindingNotify * This,
            /* [in] */ HRESULT hr,
            /* [in] */ BSTR bsError);
        
        END_INTERFACE
    } IBindingNotifyVtbl;

    interface IBindingNotify
    {
        CONST_VTBL struct IBindingNotifyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBindingNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBindingNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBindingNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBindingNotify_OnProgress(This,pSender,ulProgress,ulProgressMax,ulStatusCode,bsStatusText)	\
    (This)->lpVtbl -> OnProgress(This,pSender,ulProgress,ulProgressMax,ulStatusCode,bsStatusText)

#define IBindingNotify_OnStartBinding(This,dwReserved,pBinding)	\
    (This)->lpVtbl -> OnStartBinding(This,dwReserved,pBinding)

#define IBindingNotify_PreBindMoniker(This,pBindCtx,pMoniker)	\
    (This)->lpVtbl -> PreBindMoniker(This,pBindCtx,pMoniker)

#define IBindingNotify_OnBindingFailure(This,hr,bsError)	\
    (This)->lpVtbl -> OnBindingFailure(This,hr,bsError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBindingNotify_OnProgress_Proxy( 
    IBindingNotify * This,
    /* [in] */ IBindStatusCallback *pSender,
    /* [in] */ ULONG ulProgress,
    /* [in] */ ULONG ulProgressMax,
    /* [in] */ ULONG ulStatusCode,
    /* [in] */ BSTR bsStatusText);


void __RPC_STUB IBindingNotify_OnProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBindingNotify_OnStartBinding_Proxy( 
    IBindingNotify * This,
    /* [in] */ DWORD dwReserved,
    /* [in] */ IBinding *pBinding);


void __RPC_STUB IBindingNotify_OnStartBinding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBindingNotify_PreBindMoniker_Proxy( 
    IBindingNotify * This,
    /* [in] */ IBindCtx *pBindCtx,
    /* [in] */ IMoniker *pMoniker);


void __RPC_STUB IBindingNotify_PreBindMoniker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBindingNotify_OnBindingFailure_Proxy( 
    IBindingNotify * This,
    /* [in] */ HRESULT hr,
    /* [in] */ BSTR bsError);


void __RPC_STUB IBindingNotify_OnBindingFailure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBindingNotify_INTERFACE_DEFINED__ */


#ifndef __IResizer_INTERFACE_DEFINED__
#define __IResizer_INTERFACE_DEFINED__

/* interface IResizer */
/* [unique][helpstring][hidden][nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IResizer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE079467-E2D6-40BD-81EE-B63DF5BE3C46")
    IResizer : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long lWidth) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long *lWidth) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long lHeight) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long *lHeight) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_NavigateOnFinishUrl( 
            /* [in] */ BSTR bsURL) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_NavigateOnFinishUrl( 
            /* [retval][out] */ BSTR *pbsURL) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_ImageFullName( 
            /* [in] */ BSTR bsURL) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_ImageFullName( 
            /* [retval][out] */ BSTR *pbsURL) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_UploadUrl( 
            /* [in] */ BSTR bsURL) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_UploadUrl( 
            /* [retval][out] */ BSTR *pbsURL) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_MaxWidth( 
            /* [in] */ long lWidth) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_MaxWidth( 
            /* [retval][out] */ long *plWidth) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_MaxHeight( 
            /* [in] */ long lHeight) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_MaxHeight( 
            /* [retval][out] */ long *plHeight) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ImagePropsDescription( 
            /* [retval][out] */ BSTR *pbsDescr) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SelectImage( 
            /* [retval][out] */ BSTR *bsImgFileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UploadImage( void) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ VARIANT *clr) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ VARIANT *pclr) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BorderColor( 
            /* [in] */ VARIANT *style) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BorderColor( 
            /* [retval][out] */ VARIANT *pstyle) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BorderWidth( 
            /* [in] */ long width) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BorderWidth( 
            /* [retval][out] */ long *width) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_ForeColor( 
            /* [in] */ VARIANT *clr) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ VARIANT *pclr) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BorderVisible( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BorderVisible( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_InitialPath( 
            /* [in] */ BSTR bsPath) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_DialogTitle( 
            /* [in] */ BSTR bsPath) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_DialogTitle( 
            /* [retval][out] */ BSTR *pbs) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_DialogMasks( 
            /* [in] */ BSTR bsMasks) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_DialogMasks( 
            /* [retval][out] */ BSTR *pbsMasks) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_DialogDefaultExt( 
            /* [in] */ BSTR bsExt) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_DialogDefaultExt( 
            /* [retval][out] */ BSTR *pbsExt) = 0;
        
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_DialogCenterInParent( 
            /* [in] */ VARIANT_BOOL vCenter) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_DialogCenterInParent( 
            /* [retval][out] */ VARIANT_BOOL *pvCenter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IResizer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IResizer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IResizer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IResizer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IResizer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IResizer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IResizer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IResizer * This,
            /* [in] */ long lWidth);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IResizer * This,
            /* [retval][out] */ long *lWidth);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IResizer * This,
            /* [in] */ long lHeight);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IResizer * This,
            /* [retval][out] */ long *lHeight);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_NavigateOnFinishUrl )( 
            IResizer * This,
            /* [in] */ BSTR bsURL);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NavigateOnFinishUrl )( 
            IResizer * This,
            /* [retval][out] */ BSTR *pbsURL);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageFullName )( 
            IResizer * This,
            /* [in] */ BSTR bsURL);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageFullName )( 
            IResizer * This,
            /* [retval][out] */ BSTR *pbsURL);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UploadUrl )( 
            IResizer * This,
            /* [in] */ BSTR bsURL);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UploadUrl )( 
            IResizer * This,
            /* [retval][out] */ BSTR *pbsURL);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxWidth )( 
            IResizer * This,
            /* [in] */ long lWidth);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxWidth )( 
            IResizer * This,
            /* [retval][out] */ long *plWidth);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MaxHeight )( 
            IResizer * This,
            /* [in] */ long lHeight);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxHeight )( 
            IResizer * This,
            /* [retval][out] */ long *plHeight);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImagePropsDescription )( 
            IResizer * This,
            /* [retval][out] */ BSTR *pbsDescr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SelectImage )( 
            IResizer * This,
            /* [retval][out] */ BSTR *bsImgFileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UploadImage )( 
            IResizer * This);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IResizer * This,
            /* [in] */ VARIANT *clr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IResizer * This,
            /* [retval][out] */ VARIANT *pclr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderColor )( 
            IResizer * This,
            /* [in] */ VARIANT *style);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderColor )( 
            IResizer * This,
            /* [retval][out] */ VARIANT *pstyle);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderWidth )( 
            IResizer * This,
            /* [in] */ long width);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderWidth )( 
            IResizer * This,
            /* [retval][out] */ long *width);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ForeColor )( 
            IResizer * This,
            /* [in] */ VARIANT *clr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ForeColor )( 
            IResizer * This,
            /* [retval][out] */ VARIANT *pclr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BorderVisible )( 
            IResizer * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderVisible )( 
            IResizer * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InitialPath )( 
            IResizer * This,
            /* [in] */ BSTR bsPath);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DialogTitle )( 
            IResizer * This,
            /* [in] */ BSTR bsPath);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DialogTitle )( 
            IResizer * This,
            /* [retval][out] */ BSTR *pbs);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DialogMasks )( 
            IResizer * This,
            /* [in] */ BSTR bsMasks);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DialogMasks )( 
            IResizer * This,
            /* [retval][out] */ BSTR *pbsMasks);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DialogDefaultExt )( 
            IResizer * This,
            /* [in] */ BSTR bsExt);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DialogDefaultExt )( 
            IResizer * This,
            /* [retval][out] */ BSTR *pbsExt);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DialogCenterInParent )( 
            IResizer * This,
            /* [in] */ VARIANT_BOOL vCenter);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DialogCenterInParent )( 
            IResizer * This,
            /* [retval][out] */ VARIANT_BOOL *pvCenter);
        
        END_INTERFACE
    } IResizerVtbl;

    interface IResizer
    {
        CONST_VTBL struct IResizerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResizer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResizer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResizer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResizer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IResizer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IResizer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IResizer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IResizer_put_Width(This,lWidth)	\
    (This)->lpVtbl -> put_Width(This,lWidth)

#define IResizer_get_Width(This,lWidth)	\
    (This)->lpVtbl -> get_Width(This,lWidth)

#define IResizer_put_Height(This,lHeight)	\
    (This)->lpVtbl -> put_Height(This,lHeight)

#define IResizer_get_Height(This,lHeight)	\
    (This)->lpVtbl -> get_Height(This,lHeight)

#define IResizer_put_NavigateOnFinishUrl(This,bsURL)	\
    (This)->lpVtbl -> put_NavigateOnFinishUrl(This,bsURL)

#define IResizer_get_NavigateOnFinishUrl(This,pbsURL)	\
    (This)->lpVtbl -> get_NavigateOnFinishUrl(This,pbsURL)

#define IResizer_put_ImageFullName(This,bsURL)	\
    (This)->lpVtbl -> put_ImageFullName(This,bsURL)

#define IResizer_get_ImageFullName(This,pbsURL)	\
    (This)->lpVtbl -> get_ImageFullName(This,pbsURL)

#define IResizer_put_UploadUrl(This,bsURL)	\
    (This)->lpVtbl -> put_UploadUrl(This,bsURL)

#define IResizer_get_UploadUrl(This,pbsURL)	\
    (This)->lpVtbl -> get_UploadUrl(This,pbsURL)

#define IResizer_put_MaxWidth(This,lWidth)	\
    (This)->lpVtbl -> put_MaxWidth(This,lWidth)

#define IResizer_get_MaxWidth(This,plWidth)	\
    (This)->lpVtbl -> get_MaxWidth(This,plWidth)

#define IResizer_put_MaxHeight(This,lHeight)	\
    (This)->lpVtbl -> put_MaxHeight(This,lHeight)

#define IResizer_get_MaxHeight(This,plHeight)	\
    (This)->lpVtbl -> get_MaxHeight(This,plHeight)

#define IResizer_get_ImagePropsDescription(This,pbsDescr)	\
    (This)->lpVtbl -> get_ImagePropsDescription(This,pbsDescr)

#define IResizer_SelectImage(This,bsImgFileName)	\
    (This)->lpVtbl -> SelectImage(This,bsImgFileName)

#define IResizer_UploadImage(This)	\
    (This)->lpVtbl -> UploadImage(This)

#define IResizer_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IResizer_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IResizer_put_BorderColor(This,style)	\
    (This)->lpVtbl -> put_BorderColor(This,style)

#define IResizer_get_BorderColor(This,pstyle)	\
    (This)->lpVtbl -> get_BorderColor(This,pstyle)

#define IResizer_put_BorderWidth(This,width)	\
    (This)->lpVtbl -> put_BorderWidth(This,width)

#define IResizer_get_BorderWidth(This,width)	\
    (This)->lpVtbl -> get_BorderWidth(This,width)

#define IResizer_put_ForeColor(This,clr)	\
    (This)->lpVtbl -> put_ForeColor(This,clr)

#define IResizer_get_ForeColor(This,pclr)	\
    (This)->lpVtbl -> get_ForeColor(This,pclr)

#define IResizer_put_BorderVisible(This,vbool)	\
    (This)->lpVtbl -> put_BorderVisible(This,vbool)

#define IResizer_get_BorderVisible(This,pbool)	\
    (This)->lpVtbl -> get_BorderVisible(This,pbool)

#define IResizer_put_InitialPath(This,bsPath)	\
    (This)->lpVtbl -> put_InitialPath(This,bsPath)

#define IResizer_put_DialogTitle(This,bsPath)	\
    (This)->lpVtbl -> put_DialogTitle(This,bsPath)

#define IResizer_get_DialogTitle(This,pbs)	\
    (This)->lpVtbl -> get_DialogTitle(This,pbs)

#define IResizer_put_DialogMasks(This,bsMasks)	\
    (This)->lpVtbl -> put_DialogMasks(This,bsMasks)

#define IResizer_get_DialogMasks(This,pbsMasks)	\
    (This)->lpVtbl -> get_DialogMasks(This,pbsMasks)

#define IResizer_put_DialogDefaultExt(This,bsExt)	\
    (This)->lpVtbl -> put_DialogDefaultExt(This,bsExt)

#define IResizer_get_DialogDefaultExt(This,pbsExt)	\
    (This)->lpVtbl -> get_DialogDefaultExt(This,pbsExt)

#define IResizer_put_DialogCenterInParent(This,vCenter)	\
    (This)->lpVtbl -> put_DialogCenterInParent(This,vCenter)

#define IResizer_get_DialogCenterInParent(This,pvCenter)	\
    (This)->lpVtbl -> get_DialogCenterInParent(This,pvCenter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_Width_Proxy( 
    IResizer * This,
    /* [in] */ long lWidth);


void __RPC_STUB IResizer_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_Width_Proxy( 
    IResizer * This,
    /* [retval][out] */ long *lWidth);


void __RPC_STUB IResizer_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_Height_Proxy( 
    IResizer * This,
    /* [in] */ long lHeight);


void __RPC_STUB IResizer_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_Height_Proxy( 
    IResizer * This,
    /* [retval][out] */ long *lHeight);


void __RPC_STUB IResizer_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_NavigateOnFinishUrl_Proxy( 
    IResizer * This,
    /* [in] */ BSTR bsURL);


void __RPC_STUB IResizer_put_NavigateOnFinishUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_NavigateOnFinishUrl_Proxy( 
    IResizer * This,
    /* [retval][out] */ BSTR *pbsURL);


void __RPC_STUB IResizer_get_NavigateOnFinishUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_ImageFullName_Proxy( 
    IResizer * This,
    /* [in] */ BSTR bsURL);


void __RPC_STUB IResizer_put_ImageFullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_ImageFullName_Proxy( 
    IResizer * This,
    /* [retval][out] */ BSTR *pbsURL);


void __RPC_STUB IResizer_get_ImageFullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_UploadUrl_Proxy( 
    IResizer * This,
    /* [in] */ BSTR bsURL);


void __RPC_STUB IResizer_put_UploadUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_UploadUrl_Proxy( 
    IResizer * This,
    /* [retval][out] */ BSTR *pbsURL);


void __RPC_STUB IResizer_get_UploadUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_MaxWidth_Proxy( 
    IResizer * This,
    /* [in] */ long lWidth);


void __RPC_STUB IResizer_put_MaxWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_MaxWidth_Proxy( 
    IResizer * This,
    /* [retval][out] */ long *plWidth);


void __RPC_STUB IResizer_get_MaxWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_MaxHeight_Proxy( 
    IResizer * This,
    /* [in] */ long lHeight);


void __RPC_STUB IResizer_put_MaxHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_MaxHeight_Proxy( 
    IResizer * This,
    /* [retval][out] */ long *plHeight);


void __RPC_STUB IResizer_get_MaxHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_ImagePropsDescription_Proxy( 
    IResizer * This,
    /* [retval][out] */ BSTR *pbsDescr);


void __RPC_STUB IResizer_get_ImagePropsDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IResizer_SelectImage_Proxy( 
    IResizer * This,
    /* [retval][out] */ BSTR *bsImgFileName);


void __RPC_STUB IResizer_SelectImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IResizer_UploadImage_Proxy( 
    IResizer * This);


void __RPC_STUB IResizer_UploadImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_BackColor_Proxy( 
    IResizer * This,
    /* [in] */ VARIANT *clr);


void __RPC_STUB IResizer_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_BackColor_Proxy( 
    IResizer * This,
    /* [retval][out] */ VARIANT *pclr);


void __RPC_STUB IResizer_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_BorderColor_Proxy( 
    IResizer * This,
    /* [in] */ VARIANT *style);


void __RPC_STUB IResizer_put_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_BorderColor_Proxy( 
    IResizer * This,
    /* [retval][out] */ VARIANT *pstyle);


void __RPC_STUB IResizer_get_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_BorderWidth_Proxy( 
    IResizer * This,
    /* [in] */ long width);


void __RPC_STUB IResizer_put_BorderWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_BorderWidth_Proxy( 
    IResizer * This,
    /* [retval][out] */ long *width);


void __RPC_STUB IResizer_get_BorderWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_ForeColor_Proxy( 
    IResizer * This,
    /* [in] */ VARIANT *clr);


void __RPC_STUB IResizer_put_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_ForeColor_Proxy( 
    IResizer * This,
    /* [retval][out] */ VARIANT *pclr);


void __RPC_STUB IResizer_get_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_BorderVisible_Proxy( 
    IResizer * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IResizer_put_BorderVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_BorderVisible_Proxy( 
    IResizer * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IResizer_get_BorderVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_InitialPath_Proxy( 
    IResizer * This,
    /* [in] */ BSTR bsPath);


void __RPC_STUB IResizer_put_InitialPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_DialogTitle_Proxy( 
    IResizer * This,
    /* [in] */ BSTR bsPath);


void __RPC_STUB IResizer_put_DialogTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_DialogTitle_Proxy( 
    IResizer * This,
    /* [retval][out] */ BSTR *pbs);


void __RPC_STUB IResizer_get_DialogTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_DialogMasks_Proxy( 
    IResizer * This,
    /* [in] */ BSTR bsMasks);


void __RPC_STUB IResizer_put_DialogMasks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_DialogMasks_Proxy( 
    IResizer * This,
    /* [retval][out] */ BSTR *pbsMasks);


void __RPC_STUB IResizer_get_DialogMasks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_DialogDefaultExt_Proxy( 
    IResizer * This,
    /* [in] */ BSTR bsExt);


void __RPC_STUB IResizer_put_DialogDefaultExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_DialogDefaultExt_Proxy( 
    IResizer * This,
    /* [retval][out] */ BSTR *pbsExt);


void __RPC_STUB IResizer_get_DialogDefaultExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IResizer_put_DialogCenterInParent_Proxy( 
    IResizer * This,
    /* [in] */ VARIANT_BOOL vCenter);


void __RPC_STUB IResizer_put_DialogCenterInParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IResizer_get_DialogCenterInParent_Proxy( 
    IResizer * This,
    /* [retval][out] */ VARIANT_BOOL *pvCenter);


void __RPC_STUB IResizer_get_DialogCenterInParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResizer_INTERFACE_DEFINED__ */



#ifndef __AWSResizer_LIBRARY_DEFINED__
#define __AWSResizer_LIBRARY_DEFINED__

/* library AWSResizer */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_AWSResizer;

#ifndef ___IResizerEvents_DISPINTERFACE_DEFINED__
#define ___IResizerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IResizerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IResizerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8E27D881-DA9C-471A-86E9-D45FB12CE2B4")
    _IResizerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IResizerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IResizerEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IResizerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IResizerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IResizerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IResizerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IResizerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IResizerEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IResizerEventsVtbl;

    interface _IResizerEvents
    {
        CONST_VTBL struct _IResizerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IResizerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IResizerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IResizerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IResizerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IResizerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IResizerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IResizerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IResizerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CResizer;

#ifdef __cplusplus

class DECLSPEC_UUID("5A0E70A5-9569-4408-B1C8-01BF404634AD")
CResizer;
#endif
#endif /* __AWSResizer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


