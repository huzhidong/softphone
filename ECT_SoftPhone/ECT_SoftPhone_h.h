

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Wed Dec 07 14:47:06 2016
 */
/* Compiler settings for ECT_SoftPhone.odl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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


#ifndef __ECT_SoftPhone_h_h__
#define __ECT_SoftPhone_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DECT_SoftPhone_FWD_DEFINED__
#define ___DECT_SoftPhone_FWD_DEFINED__
typedef interface _DECT_SoftPhone _DECT_SoftPhone;

#endif 	/* ___DECT_SoftPhone_FWD_DEFINED__ */


#ifndef ___DECT_SoftPhoneEvents_FWD_DEFINED__
#define ___DECT_SoftPhoneEvents_FWD_DEFINED__
typedef interface _DECT_SoftPhoneEvents _DECT_SoftPhoneEvents;

#endif 	/* ___DECT_SoftPhoneEvents_FWD_DEFINED__ */


#ifndef __ECT_SoftPhone_FWD_DEFINED__
#define __ECT_SoftPhone_FWD_DEFINED__

#ifdef __cplusplus
typedef class ECT_SoftPhone ECT_SoftPhone;
#else
typedef struct ECT_SoftPhone ECT_SoftPhone;
#endif /* __cplusplus */

#endif 	/* __ECT_SoftPhone_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_ECT_SoftPhone_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_ECT_SoftPhone_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ECT_SoftPhone_0000_0000_v0_0_s_ifspec;


#ifndef __ECT_SOFTPHONELib_LIBRARY_DEFINED__
#define __ECT_SOFTPHONELib_LIBRARY_DEFINED__

/* library ECT_SOFTPHONELib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_ECT_SOFTPHONELib;

#ifndef ___DECT_SoftPhone_DISPINTERFACE_DEFINED__
#define ___DECT_SoftPhone_DISPINTERFACE_DEFINED__

/* dispinterface _DECT_SoftPhone */
/* [hidden][helpstring][uuid] */ 


EXTERN_C const IID DIID__DECT_SoftPhone;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("85D170CC-1FE9-41F3-9EEC-CEBF4443A5C9")
    _DECT_SoftPhone : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DECT_SoftPhoneVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DECT_SoftPhone * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DECT_SoftPhone * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DECT_SoftPhone * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DECT_SoftPhone * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DECT_SoftPhone * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DECT_SoftPhone * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DECT_SoftPhone * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DECT_SoftPhoneVtbl;

    interface _DECT_SoftPhone
    {
        CONST_VTBL struct _DECT_SoftPhoneVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DECT_SoftPhone_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DECT_SoftPhone_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DECT_SoftPhone_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DECT_SoftPhone_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DECT_SoftPhone_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DECT_SoftPhone_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DECT_SoftPhone_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DECT_SoftPhone_DISPINTERFACE_DEFINED__ */


#ifndef ___DECT_SoftPhoneEvents_DISPINTERFACE_DEFINED__
#define ___DECT_SoftPhoneEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DECT_SoftPhoneEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DECT_SoftPhoneEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B9BFCEE8-098E-4283-8F7D-E3859EEE0426")
    _DECT_SoftPhoneEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DECT_SoftPhoneEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DECT_SoftPhoneEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DECT_SoftPhoneEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DECT_SoftPhoneEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DECT_SoftPhoneEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DECT_SoftPhoneEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DECT_SoftPhoneEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DECT_SoftPhoneEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DECT_SoftPhoneEventsVtbl;

    interface _DECT_SoftPhoneEvents
    {
        CONST_VTBL struct _DECT_SoftPhoneEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DECT_SoftPhoneEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DECT_SoftPhoneEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DECT_SoftPhoneEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DECT_SoftPhoneEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DECT_SoftPhoneEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DECT_SoftPhoneEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DECT_SoftPhoneEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DECT_SoftPhoneEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ECT_SoftPhone;

#ifdef __cplusplus

class DECLSPEC_UUID("77DD447B-0336-4EF5-9BB2-EFD17123B3A3")
ECT_SoftPhone;
#endif
#endif /* __ECT_SOFTPHONELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


