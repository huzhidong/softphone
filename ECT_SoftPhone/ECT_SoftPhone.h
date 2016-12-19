#if !defined(AFX_ECT_SOFTPHONE_H__26750285_4BB3_4455_8C56_7D8E90F764B7__INCLUDED_)
#define AFX_ECT_SOFTPHONE_H__26750285_4BB3_4455_8C56_7D8E90F764B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ECT_SoftPhone.h : main header file for ECT_SOFTPHONE.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhoneApp : See ECT_SoftPhone.cpp for implementation.

class CECT_SoftPhoneApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECT_SOFTPHONE_H__26750285_4BB3_4455_8C56_7D8E90F764B7__INCLUDED)
