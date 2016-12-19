// DialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ECT_SoftPhone.h"
#include "DialDlg.h"
#include "ControlCenter.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialDlg dialog


CDialDlg::CDialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialDlg)
	m_strDialNum = _T("");
	//}}AFX_DATA_INIT
}


void CDialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialDlg)
	DDX_Control(pDX, IDC_GROUP_LIST, m_GroupList);
	DDX_Control(pDX, IDC_AGENT_LIST, m_AgentList);
	DDX_Text(pDX, IDC_NUM, m_strDialNum);
	DDV_MaxChars(pDX, m_strDialNum, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialDlg, CDialog)
	//{{AFX_MSG_MAP(CDialDlg)
	ON_BN_CLICKED(IDC_NUMDIAL, OnNumdial)
	ON_NOTIFY(NM_CLICK, IDC_GROUP_LIST, OnClickGroupList)
	ON_NOTIFY(NM_CLICK, IDC_AGENT_LIST, OnClickAgentList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialDlg message handlers

BOOL CDialDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_AgentList.SetExtendedStyle(
		m_AgentList.GetExtendedStyle()
		|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT
		|LVS_EX_INFOTIP|LVS_SHOWSELALWAYS);
	m_GroupList.SetExtendedStyle(
		m_GroupList.GetExtendedStyle()
		|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT
		|LVS_EX_INFOTIP|LVS_SHOWSELALWAYS);
	m_GroupList.InsertColumn(0,"座席组列表",LVCFMT_LEFT, 130);
	m_AgentList.InsertColumn(0,"座席姓名",LVCFMT_LEFT, 70);
	m_AgentList.InsertColumn(1,"座席工号",LVCFMT_LEFT, 80);

	for (int i=0;i<g_AgentGroupList.GetCount();i++)
	{
		CAgentGroup ag = g_AgentGroupList.agtGroupList.GetAt(i);
		m_GroupList.InsertItem(i,ag.GroupName);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDialDlg::OnNumdial() 
{
	GetDlgItemText(IDC_NUM,m_strDialNum);
	if(m_strDialNum == "")
	{
		AfxMessageBox("请输入目标号码!");
	}
   else
	 CDialDlg::OnOK();		
}

void CDialDlg::OnClickGroupList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_GroupList.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		int nItem = m_GroupList.GetNextSelectedItem(pos);

		CString  groupname = m_GroupList.GetItemText(nItem,0);
		m_AgentList.DeleteAllItems();

		g_pCtrlCenter->ExecuteOperation(OPER_UPDATEGROUPINFO,groupname);

		CAgentGroup ag = g_AgentGroupList.GetGroup(groupname);
		int index = 0;
//		GetDlgItem(IDC_NUM)->SetWindowText(ag.GroupIndex);  //edit by wyh 2009-4-8
		GetDlgItem(IDC_NUM)->SetWindowText("");
		for (int i=0;i<ag.agtList.GetSize();i++)
		{
			CAgentInfo agt = ag.agtList.GetAt(i);
			if (agt.AgentExtension!=g_strAgentExt && 2==agt.AgentState && 0==agt.CallInfo.CallState)
			{
				m_AgentList.InsertItem(index,agt.AgentName);
				m_AgentList.SetItemText(index,1,agt.AgentID);
				index++;
			}
		}

	}
	*pResult = 0;
}

void CDialDlg::OnClickAgentList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_AgentList.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		int nItem = m_AgentList.GetNextSelectedItem(pos);
		
		CString  agentid = m_AgentList.GetItemText(nItem,1);
		GetDlgItem(IDC_NUM)->SetWindowText(agentid);
	}	
	*pResult = 0;
}
