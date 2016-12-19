// ECT_SoftPhone.cpp : Implementation of CECT_SoftPhoneApp and DLL registration.

#include "stdafx.h"
#include "ECT_SoftPhone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CECT_SoftPhoneApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xbc7a45d6, 0x6f22, 0x4403, { 0xab, 0x65, 0x89, 0xa3, 0x9c, 0xae, 0x61, 0x5c } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhoneApp::InitInstance - DLL initialization

BOOL CECT_SoftPhoneApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhoneApp::ExitInstance - DLL termination

int CECT_SoftPhoneApp::ExitInstance()
{
	// TODO: Add your own module termination code here.
	TRACE("*******ExitInstance*******\n");

	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
