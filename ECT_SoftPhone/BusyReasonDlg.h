#if !defined(AFX_BUSYREASONDLG_H__011D9568_4144_480C_81EA_74869DF2FE6E__INCLUDED_)
#define AFX_BUSYREASONDLG_H__011D9568_4144_480C_81EA_74869DF2FE6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BusyReasonDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBusyReasonDlg dialog

class CBusyReasonDlg : public CDialog
{
// Construction
public:
	CBusyReasonDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBusyReasonDlg)
	enum { IDD = IDD_DIALOG_SETBUSYREASON };
	CString     str_reason;
	CString     str_Index;
	CEdit	    m_EditBusyReason;
	CListCtrl	m_ListBusy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBusyReasonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBusyReasonDlg)
	afx_msg void OnClickBusyreason(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUSYREASONDLG_H__011D9568_4144_480C_81EA_74869DF2FE6E__INCLUDED_)
