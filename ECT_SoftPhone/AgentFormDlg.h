#if !defined(AFX_AGENTFORMDLG_H__2267CEBF_71A7_400C_8658_C09001216829__INCLUDED_)
#define AFX_AGENTFORMDLG_H__2267CEBF_71A7_400C_8658_C09001216829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AgentFormDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CAgentFormDlg dialog

#include "ControlCenter.h"
#include "ECT_SoftPhoneCtl.h"
#include "bitmapdialog.h"
#include "ImageButton.h"
#include "ColorStaticST.h"

class CECT_SoftPhoneCtrl;
class CAgentFormDlg : public CBitmapDialog
{
  // Construction
public:
  CAgentFormDlg(CWnd* pParent = NULL);   // standard constructor
  ~CAgentFormDlg();
  // Dialog Data
  //{{AFX_DATA(CAgentFormDlg)
  enum { IDD = IDD_AGENTFORM_DIALOG };
  CColorStaticST	m_stStatus;
  CColorStaticST	m_stTime;
  CColorStaticST	m_stDialnum;
  CColorStaticST	m_stExt;
  CColorStaticST	m_stAgentID;
  CImageButton	m_btnForceBreak;
  CImageButton	m_btnBargein;
  CImageButton	m_btnListen;
  CImageButton	m_btnReconnect;
  CImageButton	m_btnConsult;
  CImageButton	m_btnTransfer;
  CImageButton	m_btnDial;
  CImageButton	m_btnHold;
  CImageButton	m_btnSetbusy;
  CImageButton	m_btnLogin;
  CImageButton	m_btnAnswer;
  CImageButton  m_btnSetBusyType;
  //}}AFX_DATA


  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAgentFormDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
public:
  // Implementation
public:
  BOOL	m_bWriteLog;	//是否写日志
  CString	m_LogPath;//日志路径
  CGenesysInterface *m_pPhoneCtrl;

  CControlCenter m_CtrlCenter;
  CECT_SoftPhoneCtrl *m_pOcxCtrl;
  HICON m_hIcon;
public:
  void SetButtonState(int nState);
  void SetPhoneCtrlPtr(CECT_SoftPhoneCtrl *pPtr) {m_pOcxCtrl=pPtr;};
protected:

  // Generated message map functions
  //{{AFX_MSG(CAgentFormDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnLogin();
  afx_msg void OnSetbusy();
  afx_msg void OnAnswer();
  afx_msg void OnHold();
  afx_msg void OnDial();
  afx_msg void OnTransfer();
  afx_msg void OnConsult();
  afx_msg void OnReconnect();
  afx_msg void OnListen();
  afx_msg void OnBargein();
  afx_msg void OnForcebreak();
  afx_msg void OnTimer(UINT nIDEvent);
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg void OnDestroy();
  afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
  LRESULT OnStateChange(WPARAM wParam, LPARAM lParam);
  LRESULT OnDispatchEvent(WPARAM wParam, LPARAM lParam);
  LRESULT OnStartTpinEvent(WPARAM wParam, LPARAM lParam);
  LRESULT OnEndTpinEvent(WPARAM wParam, LPARAM lParam);
private:
  bool m_bTpinWaitFlag;
  CTime m_TpinStartTime;
  SOCKET m_socket;

public:
  afx_msg void OnBnClickedSetbysytype();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGENTFORMDLG_H__2267CEBF_71A7_400C_8658_C09001216829__INCLUDED_)
