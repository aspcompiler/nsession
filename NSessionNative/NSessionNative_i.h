

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Apr 26 12:09:41 2015
 */
/* Compiler settings for NSessionNative.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __NSessionNative_i_h__
#define __NSessionNative_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IReadWriteSession_FWD_DEFINED__
#define __IReadWriteSession_FWD_DEFINED__
typedef interface IReadWriteSession IReadWriteSession;

#endif 	/* __IReadWriteSession_FWD_DEFINED__ */


#ifndef __IReadOnlySession_FWD_DEFINED__
#define __IReadOnlySession_FWD_DEFINED__
typedef interface IReadOnlySession IReadOnlySession;

#endif 	/* __IReadOnlySession_FWD_DEFINED__ */


#ifndef __ReadWriteSession_FWD_DEFINED__
#define __ReadWriteSession_FWD_DEFINED__

#ifdef __cplusplus
typedef class ReadWriteSession ReadWriteSession;
#else
typedef struct ReadWriteSession ReadWriteSession;
#endif /* __cplusplus */

#endif 	/* __ReadWriteSession_FWD_DEFINED__ */


#ifndef __ReadOnlySession_FWD_DEFINED__
#define __ReadOnlySession_FWD_DEFINED__

#ifdef __cplusplus
typedef class ReadOnlySession ReadOnlySession;
#else
typedef struct ReadOnlySession ReadOnlySession;
#endif /* __cplusplus */

#endif 	/* __ReadOnlySession_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IReadWriteSession_INTERFACE_DEFINED__
#define __IReadWriteSession_INTERFACE_DEFINED__

/* interface IReadWriteSession */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IReadWriteSession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D2CA1FD-A8BF-4826-A9F3-4C91108C8C97")
    IReadWriteSession : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IReadWriteSessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReadWriteSession * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReadWriteSession * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReadWriteSession * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IReadWriteSession * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IReadWriteSession * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IReadWriteSession * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IReadWriteSession * This,
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
    } IReadWriteSessionVtbl;

    interface IReadWriteSession
    {
        CONST_VTBL struct IReadWriteSessionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReadWriteSession_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IReadWriteSession_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IReadWriteSession_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IReadWriteSession_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IReadWriteSession_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IReadWriteSession_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IReadWriteSession_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IReadWriteSession_INTERFACE_DEFINED__ */


#ifndef __IReadOnlySession_INTERFACE_DEFINED__
#define __IReadOnlySession_INTERFACE_DEFINED__

/* interface IReadOnlySession */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IReadOnlySession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B275E749-F3D8-48DF-B34A-39900300A37F")
    IReadOnlySession : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IReadOnlySessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReadOnlySession * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReadOnlySession * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReadOnlySession * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IReadOnlySession * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IReadOnlySession * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IReadOnlySession * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IReadOnlySession * This,
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
    } IReadOnlySessionVtbl;

    interface IReadOnlySession
    {
        CONST_VTBL struct IReadOnlySessionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReadOnlySession_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IReadOnlySession_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IReadOnlySession_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IReadOnlySession_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IReadOnlySession_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IReadOnlySession_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IReadOnlySession_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IReadOnlySession_INTERFACE_DEFINED__ */



#ifndef __NSessionNativeLib_LIBRARY_DEFINED__
#define __NSessionNativeLib_LIBRARY_DEFINED__

/* library NSessionNativeLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_NSessionNativeLib;

EXTERN_C const CLSID CLSID_ReadWriteSession;

#ifdef __cplusplus

class DECLSPEC_UUID("39C42850-A349-45A0-8FCE-488519F6FEC2")
ReadWriteSession;
#endif

EXTERN_C const CLSID CLSID_ReadOnlySession;

#ifdef __cplusplus

class DECLSPEC_UUID("5F07415C-0C7B-4B9C-A067-93FCD4581FF3")
ReadOnlySession;
#endif
#endif /* __NSessionNativeLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


