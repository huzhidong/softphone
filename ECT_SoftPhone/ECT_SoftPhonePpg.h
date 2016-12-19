#if !defined(AFX_ECT_SOFTPHONEPPG_H__E11168BA_8AC3_45FA_B9F0_FEEF0FBD614B__INCLUDED_)
#define AFX_ECT_SOFTPHONEPPG_H__E11168BA_8AC3_45FA_B9F0_FEEF0FBD614B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ECT_SoftPhonePpg.h : Declaration of the CECT_SoftPhonePropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhonePropPage : See ECT_SoftPhonePpg.cpp.cpp for implementation.

class CECT_SoftPhonePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CECT_SoftPhonePropPage)
	DECLARE_OLECREATE_EX(CECT_SoftPhonePropPage)

// Constructor
public:
	CECT_SoftPhonePropPage();

// Dialog Data
	//{{AFX_DATA(CECT_SoftPhonePropPage)
	enum { IDD = IDD_PROPPAGE_ECT_SOFTPHONE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CECT_SoftPhonePropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECT_SOFTPHONEPPG_H__E11168BA_8AC3_45FA_B9F0_FEEF0FBD614B__INCLUDED)
