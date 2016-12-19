

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

MIDL_DEFINE_GUID(IID, LIBID_ECT_SOFTPHONELib,0xBC7A45D6,0x6F22,0x4403,0xAB,0x65,0x89,0xA3,0x9C,0xAE,0x61,0x5C);


MIDL_DEFINE_GUID(IID, DIID__DECT_SoftPhone,0x85D170CC,0x1FE9,0x41F3,0x9E,0xEC,0xCE,0xBF,0x44,0x43,0xA5,0xC9);


MIDL_DEFINE_GUID(IID, DIID__DECT_SoftPhoneEvents,0xB9BFCEE8,0x098E,0x4283,0x8F,0x7D,0xE3,0x85,0x9E,0xEE,0x04,0x26);


MIDL_DEFINE_GUID(CLSID, CLSID_ECT_SoftPhone,0x77DD447B,0x0336,0x4EF5,0x9B,0xB2,0xEF,0xD1,0x71,0x23,0xB3,0xA3);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



