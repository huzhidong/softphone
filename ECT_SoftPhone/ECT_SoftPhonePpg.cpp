// ECT_SoftPhonePpg.cpp : Implementation of the CECT_SoftPhonePropPage property page class.

#include "stdafx.h"
#include "ECT_SoftPhone.h"
#include "ECT_SoftPhonePpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CECT_SoftPhonePropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CECT_SoftPhonePropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CECT_SoftPhonePropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CECT_SoftPhonePropPage, "ECTSOFTPHONE.ECTSoftPhonePropPage.1",
	0x950dd51d, 0x7de8, 0x498f, 0xbe, 0xc7, 0x50, 0xf6, 0xc2, 0x38, 0xf3, 0xfe)


/////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhonePropPage::CECT_SoftPhonePropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CECT_SoftPhonePropPage

BOOL CECT_SoftPhonePropPage::CECT_SoftPhonePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ECT_SOFTPHONE_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhonePropPage::CECT_SoftPhonePropPage - Constructor

CECT_SoftPhonePropPage::CECT_SoftPhonePropPage() :
	COlePropertyPage(IDD, IDS_ECT_SOFTPHONE_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CECT_SoftPhonePropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhonePropPage::DoDataExchange - Moves data between page and properties

void CECT_SoftPhonePropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CECT_SoftPhonePropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhonePropPage message handlers
