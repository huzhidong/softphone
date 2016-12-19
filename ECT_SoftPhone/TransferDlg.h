#if !defined(AFX_TRANSFERDLG_H__B9406B33_EEF6_4850_B13F_2EF35281B65F__INCLUDED_)
#define AFX_TRANSFERDLG_H__B9406B33_EEF6_4850_B13F_2EF35281B65F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransferDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransferDlg dialog

class CTransferDlg : public CDialog
{
// Construction
public:
	CTransferDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransferDlg)
	enum { IDD = IDD_DIALOG_TRANSFER };
	CListCtrl	m_AgentList;
	CListCtrl	m_GroupList;
	CString	    m_strDialNum;
	TransType   m_TransType;
	//}}AFX_DATA
    HTREEITEM activeItem;//活动子项
	HTREEITEM activeparentItem;//活动父项
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransferDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTransAgent();
	afx_msg void OnTransGroup();
	afx_msg void OnClickGroupList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAgentList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFERDLG_H__B9406B33_EEF6_4850_B13F_2EF35281B65F__INCLUDED_)
