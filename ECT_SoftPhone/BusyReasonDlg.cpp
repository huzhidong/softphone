// BusyReasonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ECT_SoftPhone.h"
#include "BusyReasonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBusyReasonDlg dialog


CBusyReasonDlg::CBusyReasonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBusyReasonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBusyReasonDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBusyReasonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBusyReasonDlg)
	DDX_Control(pDX, IDC_REASON, m_EditBusyReason);
	DDX_Control(pDX, IDC_BUSYREASON, m_ListBusy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBusyReasonDlg, CDialog)
	//{{AFX_MSG_MAP(CBusyReasonDlg)
	ON_NOTIFY(NM_CLICK, IDC_BUSYREASON, OnClickBusyreason)
	ON_BN_CLICKED(IDC_OK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBusyReasonDlg message handlers

BOOL CBusyReasonDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	m_EditBusyReason.SetWindowText(_T(""));
	
	m_ListBusy.SetExtendedStyle(
		m_ListBusy.GetExtendedStyle()
		|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT
		|LVS_EX_INFOTIP|LVS_SHOWSELALWAYS);
	m_ListBusy.InsertColumn(0,"原因列表",LVCFMT_CENTER,170);
	int i=0;
	CString str=SearchStr(g_strBusyReasonList+"|",'|',i);
	while(!str.IsEmpty())
	{
		CString tmpstr = SearchStr(str+",",',',1);

		m_ListBusy.InsertItem(i,tmpstr);

		i++;
		str=SearchStr(g_strBusyReasonList+"|",'|',i);
	}
	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBusyReasonDlg::OnClickBusyreason(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_ListBusy.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
      int nItem = m_ListBusy.GetNextSelectedItem(pos);
	  str_reason.Format("%d",nItem);
	  //str_Index.Format("%d",nItem + 1);
	  m_EditBusyReason.SetWindowText(m_ListBusy.GetItemText(nItem,0));
	  str_reason = m_ListBusy.GetItemText(nItem,0);
	}
	m_EditBusyReason.GetWindowText(str_reason);
	*pResult = 0;
}


void CBusyReasonDlg::OnOk() 
{
	if(str_reason.IsEmpty())
		AfxMessageBox("选择置忙原因！");
	else
	   CDialog::OnOK();
	
}
