

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Apr 05 11:33:21 2015
 */
/* Compiler settings for NSessionNative.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IReadWriteSession,0x7D2CA1FD,0xA8BF,0x4826,0xA9,0xF3,0x4C,0x91,0x10,0x8C,0x8C,0x97);


MIDL_DEFINE_GUID(IID, IID_IReadOnlySession,0xB275E749,0xF3D8,0x48DF,0xB3,0x4A,0x39,0x90,0x03,0x00,0xA3,0x7F);


MIDL_DEFINE_GUID(IID, LIBID_NSessionNativeLib,0xEFBF0C2B,0x6DEE,0x4D6A,0xB6,0xB0,0xA8,0x4C,0x0E,0xCD,0x9C,0xF3);


MIDL_DEFINE_GUID(CLSID, CLSID_ReadWriteSession,0x39C42850,0xA349,0x45A0,0x8F,0xCE,0x48,0x85,0x19,0xF6,0xFE,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_ReadOnlySession,0x5F07415C,0x0C7B,0x4B9C,0xA0,0x67,0x93,0xFC,0xD4,0x58,0x1F,0xF3);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



