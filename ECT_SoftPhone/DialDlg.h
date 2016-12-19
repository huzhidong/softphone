#if !defined(AFX_DIALDLG_H__4DB20B31_578D_4AE3_BD2E_A82888D1A9FA__INCLUDED_)
#define AFX_DIALDLG_H__4DB20B31_578D_4AE3_BD2E_A82888D1A9FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialDlg dialog

class CDialDlg : public CDialog
{
// Construction
public:
	CDialDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialDlg)
	enum { IDD = IDD_DIALOG_DIAL };
	CListCtrl	m_GroupList;
	CListCtrl	m_AgentList;
	CString     m_strDialNum;
	//}}AFX_DATA
    HTREEITEM activeItem;//活动子项
	HTREEITEM activeparentItem;//活动父项

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNumdial();
	afx_msg void OnClickGroupList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAgentList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALDLG_H__4DB20B31_578D_4AE3_BD2E_A82888D1A9FA__INCLUDED_)
