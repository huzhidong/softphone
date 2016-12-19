#if !defined(AFX_CONSULTDLG_H__1648C3FA_C166_477A_BC71_8F466D8C3C24__INCLUDED_)
#define AFX_CONSULTDLG_H__1648C3FA_C166_477A_BC71_8F466D8C3C24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConsultDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConsultDlg dialog

class CConsultDlg : public CDialog
{
// Construction
public:
	CConsultDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConsultDlg)
	enum { IDD = IDD_DIALOG_CONSULT };
	CListCtrl	m_AgentList;
	CListCtrl	m_GroupList;
	CString	m_strDialNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsultDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConsultDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnConsult();
	virtual void OnCancel();
	afx_msg void OnClickGroupList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickAgentList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSULTDLG_H__1648C3FA_C166_477A_BC71_8F466D8C3C24__INCLUDED_)
