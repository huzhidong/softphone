#if !defined(AFX_LISTENDLG_H__C319F05C_3D35_49C6_B2AC_5E1BEBBD7B02__INCLUDED_)
#define AFX_LISTENDLG_H__C319F05C_3D35_49C6_B2AC_5E1BEBBD7B02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListenDlg dialog

class CListenDlg : public CDialog
{
// Construction
public:
	CListenDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListenDlg)
	enum { IDD = IDD_DIALOG_LISTEN };
	CListCtrl	m_GroupList;
	CListCtrl	m_AgentList;
	CString     m_strListenNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListenDlg)
	afx_msg void OnListen();
	afx_msg void OnClickGroupList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAgentList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENDLG_H__C319F05C_3D35_49C6_B2AC_5E1BEBBD7B02__INCLUDED_)
