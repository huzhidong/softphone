// AgentFormDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ECT_SoftPhone.h"
#include "AgentFormDlg.h"
#include "BusyReasonDlg.h"
#include "ConsultDlg.h"
#include "DialDlg.h"
#include "ListenDlg.h"
#include "TransferDlg.h"
#include "Define.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAgentFormDlg dialog


CAgentFormDlg::CAgentFormDlg(CWnd* pParent /*=NULL*/)
  : CBitmapDialog(CAgentFormDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CAgentFormDlg)
  //}}AFX_DATA_INIT
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_bTpinWaitFlag = false;

}


CAgentFormDlg::~CAgentFormDlg()
{
  ::DestroyWindow(m_hWnd);
}


void CAgentFormDlg::OnDestroy() 
{//
  CBitmapDialog::OnDestroy();
  WriteLog("Ready to destroy the dialog of ocx!",SYSTEM_LOG,BASE_LOG_LEVEL);

  m_CtrlCenter.Stop();	
}


void CAgentFormDlg::DoDataExchange(CDataExchange* pDX)
{
  CBitmapDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAgentFormDlg)
  DDX_Control(pDX, IDC_TEXT_STATUS, m_stStatus);
  DDX_Control(pDX, IDC_TIME, m_stTime);
  DDX_Control(pDX, IDC_DIALNUM, m_stDialnum);
  DDX_Control(pDX, IDC_TEXT_EXTENSION, m_stExt);
  DDX_Control(pDX, IDC_TEXT_AGENTID, m_stAgentID);
  DDX_Control(pDX, IDC_FORCEBREAK, m_btnForceBreak);
  DDX_Control(pDX, IDC_BARGEIN, m_btnBargein);
  DDX_Control(pDX, IDC_LISTEN, m_btnListen);
  DDX_Control(pDX, IDC_RECONNECT, m_btnReconnect);
  DDX_Control(pDX, IDC_CONSULT, m_btnConsult);
  DDX_Control(pDX, IDC_TRANSFER, m_btnTransfer);
  DDX_Control(pDX, IDC_DIAL, m_btnDial);
  DDX_Control(pDX, IDC_HOLD, m_btnHold);
  DDX_Control(pDX, IDC_SETBUSY, m_btnSetbusy);
  DDX_Control(pDX, IDC_LOGIN, m_btnLogin);
  DDX_Control(pDX, IDC_ANSWER, m_btnAnswer);
  DDX_Control(pDX, IDC_SETBYSYTYPE, m_btnSetBusyType);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAgentFormDlg, CBitmapDialog)
  //{{AFX_MSG_MAP(CAgentFormDlg)
  ON_BN_CLICKED(IDC_LOGIN, OnLogin)
  ON_BN_CLICKED(IDC_SETBUSY, OnSetbusy)
  ON_BN_CLICKED(IDC_ANSWER, OnAnswer)
  ON_BN_CLICKED(IDC_HOLD, OnHold)
  ON_BN_CLICKED(IDC_DIAL, OnDial)
  ON_BN_CLICKED(IDC_TRANSFER, OnTransfer)
  ON_BN_CLICKED(IDC_CONSULT, OnConsult)
  ON_BN_CLICKED(IDC_RECONNECT, OnReconnect)
  ON_BN_CLICKED(IDC_LISTEN, OnListen)
  ON_BN_CLICKED(IDC_BARGEIN, OnBargein)
  ON_BN_CLICKED(IDC_FORCEBREAK, OnForcebreak)
  ON_WM_TIMER()
  ON_WM_CTLCOLOR()
  ON_WM_DESTROY()
  ON_WM_RBUTTONDBLCLK()

  //}}AFX_MSG_MAP
  ON_MESSAGE(WM_STATE_CHANGE, OnStateChange)
  ON_MESSAGE(WM_DISPATCH_EVENT,OnDispatchEvent)
  ON_MESSAGE(WM_START_TPIN_TIMER,OnStartTpinEvent)
  ON_MESSAGE(WM_END_TPIN_TIMER,OnEndTpinEvent)
  ON_BN_CLICKED(IDC_SETBYSYTYPE, &CAgentFormDlg::OnBnClickedSetbysytype)
END_MESSAGE_MAP()

BOOL CAgentFormDlg::OnInitDialog() 
{//初始化
  CBitmapDialog::OnInitDialog();

  SetBitmap(IDB_BACKGND, CBitmapDialog::BITMAP_TILE);

  m_btnLogin.AutoLoad(IDB_LOGIN, 4, 6, 6, 6, 6);	
  m_btnLogin.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnLogin.SetTextColor(RGB(0, 0, 0));		//SET text color


  m_btnSetbusy.AutoLoad(IDB_READY, 4, 6, 6, 6, 6);	
  m_btnSetbusy.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnSetbusy.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnSetBusyType.AutoLoad(IDB_READY, 4, 6, 6, 6, 6);	
  m_btnSetBusyType.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnSetBusyType.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnAnswer.AutoLoad(IDB_ANSWER, 4, 6, 6, 6, 6);	
  m_btnAnswer.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnAnswer.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnDial.AutoLoad(IDB_DIAL, 4, 6, 6, 6, 6);	
  m_btnDial.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnDial.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnHold.AutoLoad(IDB_HOLD, 4, 6, 6, 6, 6);	
  m_btnHold.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnHold.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnTransfer.AutoLoad(IDB_TRANSFER, 4, 6, 6, 6, 6);	
  m_btnTransfer.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnTransfer.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnConsult.AutoLoad(IDB_CONSULT, 4, 6, 6, 6, 6);	
  m_btnConsult.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnConsult.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnReconnect.AutoLoad(IDB_RECONNECT, 4, 6, 6, 6, 6);	
  m_btnReconnect.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnReconnect.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnListen.AutoLoad(IDB_LISTEN, 4, 6, 6, 6, 6);	
  m_btnListen.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnListen.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnBargein.AutoLoad(IDB_BARGEIN, 4, 6, 6, 6, 6);	
  m_btnBargein.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnBargein.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_btnForceBreak.AutoLoad(IDB_FORCEBREAK, 4, 6, 6, 6, 6);	
  m_btnForceBreak.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
  m_btnForceBreak.SetTextColor(RGB(0, 0, 0));		//SET text color

  m_stAgentID.SetTextColor(RGB(0,0,255));
  m_stDialnum.SetTextColor(RGB(128,0,0));
  m_stExt.SetTextColor(RGB(0,0,255));
  m_stStatus.SetTextColor(RGB(128,0,0));
  m_stTime.SetTextColor(RGB(0,0,255));
  m_stStatus.SetRedraw();

  m_pPhoneCtrl = NULL;
  SetTimer(0,1000,NULL);
  SetButtonState(PHONE_STATE_INIT);



  //启动控制中心
  m_CtrlCenter.SetHwnd(this->GetSafeHwnd());
  g_pCtrlCenter = &m_CtrlCenter;
  //	m_CtrlCenter.Start();

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}




void CAgentFormDlg::OnTimer(UINT nIDEvent) 
{//计时
  CTime curTime;  //获取当前时间
  CTimeSpan   spanTime; //获取时长：
  CString strTime;   //显示时长：
  CTime     OriginTime;
  switch(g_TimerType) 
  {
  case TIMER_OPER_INIT:
    strTime = "00:00:00";
    break;
  case TIMER_OPER_START:
    curTime= CTime::GetCurrentTime();
    spanTime = curTime - g_CallBeginTime;
    strTime = spanTime.Format("%H:%M:%S");			
    break;
  case TIMER_OPER_STOP:
    spanTime = g_CallEndTime - g_CallBeginTime;
    strTime = spanTime.Format("%H:%M:%S");			
    break;
  case TIMER_OPER_PAUSE:
    break;
  case TIMER_OPER_SHOWSTATUS:
    curTime= CTime::GetCurrentTime();
    spanTime = curTime - g_CurStatusBeginTime;
    strTime = spanTime.Format("%H:%M:%S");			
    break;
  case TIMER_OPER_RESTART:
    g_CurStatusBeginTime=CTime::GetCurrentTime();
    break;
  }

  //TPIN
  if (m_bTpinWaitFlag)
  {
    CString tmpstr;

    curTime= CTime::GetCurrentTime();
    spanTime = curTime - m_TpinStartTime;
    int n = spanTime.GetSeconds() + spanTime.GetMinutes()*60 + spanTime.GetHours()*3600;

    if(TPIN_WAIT_TIME<n)
    {
      m_CtrlCenter.UpdateState(PHONE_STATE_BUSY);
      g_strBusyReason = "TPIN超时";
      g_bTpinFlag = false;
      m_bTpinWaitFlag = false;
      g_strConnID = "";
      g_strConsultConnID = "";
      g_TimerType = TIMER_OPER_INIT;
      tmpstr.Format("Tpin is OVERTIME after %d seconds. Maybe user hangup in IVR.",n);
      WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
    }
  }

  if (TIMER_OPER_INIT != g_TimerType && TIMER_OPER_STOP != g_TimerType)
  {
    GetDlgItem(IDC_TIME)->SetWindowText(strTime);
    GetDlgItem(IDC_TIME)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_TIME)->ShowWindow(SW_SHOW);
  }

  CDialog::OnTimer(nIDEvent);
}


void CAgentFormDlg::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
  CDialog dlgAbout(IDD_ABOUTBOX_ECT_SOFTPHONE);
  dlgAbout.DoModal();

  CBitmapDialog::OnRButtonDblClk(nFlags, point);
}

HBRUSH CAgentFormDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
  HBRUSH hbr; 


  switch (nCtlColor) 
  { 
    // process my edit controls by ID.
  case CTLCOLOR_EDIT:
  case CTLCOLOR_MSGBOX:
    switch (pWnd->GetDlgCtrlID())
    {     
      // first CEdit control ID
    case 200:         // put your own CONTROL ID
      {// here
        pDC->SetBkColor(RGB(255,0,0));    // change the background
        // color [background colour
        // of the text ONLY]
        pDC->SetTextColor(RGB(0,255,0));  // change the text color
        CBrush brush(RGB(0,255,0));
        hbr = brush;    // apply the blue brush
        // [this fills the control
        // rectangle]
        break;  
      }

    default: 
      hbr=CDialog::OnCtlColor(pDC,pWnd,nCtlColor); 
      break;
    }  
    break;
    // process Static text, READONLY controls, DISABLED * controls.
    // * NOTE: Disabled controls can NOT have their text color
    //         changed.
    //         Suggest you change all your DISABLED controls to
    //         READONLY.
  case CTLCOLOR_STATIC:
    // process my edit controls by ID
    switch (pWnd->GetDlgCtrlID())
    {     
      // one of my READONLY edit controls (could also be disabled or
      // static text)
    case 100:
      {
        //	pDC->SetBkColor(RGB(0,0,255));   // change the background color
        //	pDC->SetTextColor(RGB(244,0,0)); // change the text color
        CBrush brush(RGB(244,0,0));
        hbr = brush;   // apply the brush
        break;
      }
      // otherwise, do default handling of OnCtlColor
    default:
      hbr=CDialog::OnCtlColor(pDC,pWnd,nCtlColor);
      break;
    }
    // otherwise, do default handling of OnCtlColor
  default:
    hbr=CBitmapDialog::OnCtlColor(pDC,pWnd,nCtlColor);
    break;
  }

  return hbr; // return brush
}

/////////////////////////////////////////////////////////////////////////////
// CAgentFormDlg message handlers

void CAgentFormDlg::SetButtonState(int nState)
{//设置界面显示信息及按钮状态
  m_btnListen.EnableWindow(FALSE);
  m_btnReconnect.EnableWindow(FALSE);
  m_btnForceBreak.EnableWindow(FALSE);
  m_btnBargein.EnableWindow(FALSE);
  GetDlgItem(IDC_TEXT_AGENTID)->SetWindowText(g_strAgentID);
  GetDlgItem(IDC_TEXT_EXTENSION)->SetWindowText(g_strAgentExt);

  GetDlgItem(IDC_TEXT_AGENTID)->ShowWindow(SW_HIDE);
  GetDlgItem(IDC_TEXT_AGENTID)->ShowWindow(SW_SHOW);
  GetDlgItem(IDC_TEXT_EXTENSION)->ShowWindow(SW_HIDE);
  GetDlgItem(IDC_TEXT_EXTENSION)->ShowWindow(SW_SHOW);

  switch(nState)
  {
  case PHONE_STATE_DISABLE:
    { 
      m_btnLogin.EnableWindow(FALSE);
      m_btnLogin.SetWindowText("签入");
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnSetbusy.SetWindowText("置闲");
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);		
      m_btnConsult.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("网络中断");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      break;
    }
  case PHONE_STATE_INIT:
    {
      m_btnLogin.EnableWindow(TRUE);
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);		
      m_btnConsult.EnableWindow(FALSE);
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("未就绪");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_SETBYSYTYPE)->EnableWindow(FALSE);
      g_TimerType=TIMER_OPER_INIT;
      break;
    }
  case PHONE_STATE_LOGIN:
    {
      m_btnLogin.EnableWindow(TRUE);
      m_btnLogin.SetWindowText("签出");
      m_btnSetbusy.EnableWindow(TRUE);
      m_btnSetbusy.SetWindowText("置闲");
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(TRUE);		
      m_btnConsult.EnableWindow(FALSE);
      GetDlgItem(IDC_SETBYSYTYPE)->EnableWindow(FALSE);

      if (SUPERVISOR==g_nLoginType)	  
      {
        m_btnListen.EnableWindow(TRUE);
        m_btnReconnect.EnableWindow(FALSE);
        m_btnForceBreak.EnableWindow(FALSE);
        m_btnBargein.EnableWindow(FALSE);		  
      }
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("签入");
      GetDlgItem(IDC_TEXT_AGENTID)->SetWindowText(g_strAgentID);
      GetDlgItem(IDC_TEXT_EXTENSION)->SetWindowText(g_strAgentExt);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      break;
    }
  case PHONE_STATE_LOGOUT:
    {
      m_btnLogin.EnableWindow(TRUE);
      m_btnLogin.SetWindowText("签入");
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);		
      m_btnConsult.EnableWindow(FALSE);
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("签出");
      GetDlgItem(IDC_TEXT_AGENTID)->SetWindowText(g_strAgentID);
      GetDlgItem(IDC_TEXT_EXTENSION)->SetWindowText(g_strAgentExt);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      g_TimerType=TIMER_OPER_STOP;
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;
      GetDlgItem(IDC_TIME)->SetWindowText("00:00:00");
      GetDlgItem(IDC_TIME)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TIME)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_SETBYSYTYPE)->EnableWindow(FALSE);
      break;
    }
  case PHONE_STATE_BUSY:
    {
      m_btnLogin.EnableWindow(TRUE);
      m_btnLogin.SetWindowText("签出");
      m_btnSetbusy.EnableWindow(TRUE);
      m_btnSetbusy.SetWindowText("置闲");
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(TRUE);	
      m_btnDial.SetWindowText("拨号");
      m_btnConsult.EnableWindow(FALSE);
      m_btnReconnect.EnableWindow(FALSE);
      if (SUPERVISOR==g_nLoginType)	  
      {
        m_btnListen.EnableWindow(TRUE);
        m_btnReconnect.EnableWindow(FALSE);
        m_btnForceBreak.EnableWindow(FALSE);
        m_btnBargein.EnableWindow(FALSE);		  
      }
      GetDlgItem(IDC_SETBYSYTYPE)->EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText(g_strBusyReason);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);

      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;
      break;
    }
  case PHONE_STATE_IDLE:
    {
      m_btnLogin.EnableWindow(TRUE);
      m_btnLogin.SetWindowText("签出");
      m_btnSetbusy.EnableWindow(TRUE);
      m_btnSetbusy.SetWindowText("置忙");
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(TRUE);
      m_btnDial.SetWindowText("拨号");
      m_btnConsult.EnableWindow(FALSE);
      if (SUPERVISOR==g_nLoginType)	  
      {
        m_btnListen.EnableWindow(TRUE);
        m_btnReconnect.EnableWindow(FALSE);
        m_btnForceBreak.EnableWindow(FALSE);
        m_btnBargein.EnableWindow(FALSE);		  
      }
      if (true == g_bSetBusyFlag) GetDlgItem(IDC_SETBYSYTYPE)->EnableWindow(FALSE);
      else GetDlgItem(IDC_SETBYSYTYPE)->EnableWindow(TRUE);      
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("置闲");
      GetDlgItem(IDC_TEXT_AGENTID)->SetWindowText(g_strAgentID);
      GetDlgItem(IDC_TEXT_EXTENSION)->SetWindowText(g_strAgentExt);
      GetDlgItem(IDC_DIALNUM)->SetWindowText("");
      GetDlgItem(IDC_DIALNUM)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_DIALNUM)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;
      g_strBusyReason = "";

      break; 
    }
  case PHONE_STATE_DIALING:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnAnswer.EnableWindow(TRUE);
      m_btnAnswer.SetWindowText("挂机");
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);		
      m_btnConsult.EnableWindow(FALSE);
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("拨号");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;
      break;
    }
  case PHONE_STATE_TALKING:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnLogin.SetWindowText("签出");
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnSetbusy.SetWindowText("置闲");
      m_btnAnswer.EnableWindow(TRUE);
      m_btnAnswer.SetWindowText("挂机");		  
      m_btnDial.EnableWindow(FALSE);		  
      m_btnHold.EnableWindow(TRUE);
      m_btnHold.SetWindowText("保持");
      m_btnTransfer.EnableWindow(TRUE);
      m_btnTransfer.SetWindowText("转接");
      m_btnConsult.EnableWindow(TRUE);
      m_btnConsult.SetWindowText("咨询");
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("通话");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_DIALNUM)->SetWindowText(g_strANI);
      GetDlgItem(IDC_DIALNUM)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_DIALNUM)->ShowWindow(SW_SHOW);
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_START;
      break;
    }
  case PHONE_STATE_BELISTEN:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnLogin.SetWindowText("签出");
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnSetbusy.SetWindowText("置闲");
      m_btnAnswer.EnableWindow(TRUE);
      m_btnAnswer.SetWindowText("挂机");		  
      m_btnDial.EnableWindow(FALSE);		  
      m_btnHold.EnableWindow(TRUE);
      m_btnHold.SetWindowText("保持");
      m_btnTransfer.EnableWindow(TRUE);
      m_btnTransfer.SetWindowText("转接");
      m_btnConsult.EnableWindow(TRUE);
      m_btnConsult.SetWindowText("咨询");
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("通话");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      break;
    }	
  case PHONE_STATE_RING:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnLogin.SetWindowText("签出");
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnSetbusy.SetWindowText("置闲");
      m_btnAnswer.EnableWindow(TRUE);
      m_btnAnswer.SetWindowText("摘机");
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);
      m_btnDial.SetWindowText("拨号");
      m_btnConsult.EnableWindow(FALSE);
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("振铃");
      GetDlgItem(IDC_DIALNUM)->SetWindowText(g_strANI);
      GetDlgItem(IDC_DIALNUM)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_DIALNUM)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;
      break;
    }

  case PHONE_STATE_HOLD:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(TRUE);
      m_btnHold.SetWindowText("恢复");
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);
      m_btnDial.SetWindowText("拨号");
      m_btnConsult.EnableWindow(FALSE);
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("保持");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;

      break;
    }

  case PHONE_STATE_AFTERTALK:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnSetbusy.EnableWindow(TRUE);
      m_btnSetbusy.SetWindowText("置闲");
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);
      m_btnDial.SetWindowText("拨号");
      m_btnConsult.EnableWindow(FALSE);
      m_btnConsult.SetWindowText("会议");
      m_btnReconnect.EnableWindow(FALSE);
      if (true == g_bSetBusyFlag)
      {
        g_strBusyReason = "置忙";
        GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("置忙");
      }
      else
      {
        g_strBusyReason = "话后处理";
        GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("话后处理");
      }
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;

      break;
    }
  case PHONE_STATE_CONSULT:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnSetbusy.SetWindowText("置闲");
      m_btnAnswer.EnableWindow(FALSE);
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(TRUE);
      m_btnDial.EnableWindow(FALSE);
      m_btnDial.SetWindowText("拨号");
      m_btnTransfer.EnableWindow(TRUE);
      m_btnTransfer.SetWindowText("转接");
      if (!g_bTransFlag)
      {
        m_btnConsult.EnableWindow(TRUE);
        m_btnConsult.SetWindowText("会议");			
      }

      m_btnReconnect.EnableWindow(TRUE);
      m_btnReconnect.SetWindowText("取回");
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("咨询");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;

      break;
    }
  case PHONE_STATE_CONFERENCE:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnAnswer.EnableWindow(TRUE);
      m_btnAnswer.SetWindowText("挂机");
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);
      m_btnConsult.EnableWindow(FALSE);
      m_btnConsult.SetWindowText("咨询");
      if (SUPERVISOR==g_nLoginType)	  
      {
        m_btnListen.EnableWindow(FALSE);
        m_btnReconnect.EnableWindow(FALSE);
        m_btnReconnect.SetWindowText("取回");
        if (!g_strBeMonitorAgentID.IsEmpty())
          m_btnForceBreak.EnableWindow(TRUE);
        else
          m_btnForceBreak.EnableWindow(FALSE);;
        m_btnBargein.EnableWindow(FALSE);		  
      }
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("会议");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_DIALNUM)->SetWindowText(g_strANI);
      GetDlgItem(IDC_DIALNUM)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_DIALNUM)->ShowWindow(SW_SHOW);
      break;
    }
  case PHONE_STATE_ANSWER_CONSULT:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnAnswer.EnableWindow(TRUE);
      m_btnAnswer.SetWindowText("挂机");
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);
      m_btnConsult.EnableWindow(FALSE);
      m_btnConsult.SetWindowText("咨询");
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("被咨询");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      break;
    }
  case PHONE_STATE_TPIN:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnAnswer.EnableWindow(FALSE);
      m_btnAnswer.SetWindowText("挂机");
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);
      m_btnConsult.EnableWindow(FALSE);
      m_btnConsult.SetWindowText("咨询");
      m_btnReconnect.EnableWindow(FALSE);
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("TPIN等待");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      g_CurStatusBeginTime=CTime::GetCurrentTime();
      g_TimerType=TIMER_OPER_SHOWSTATUS;
      break;
    }	
  case PHONE_STATE_LISTEN:
    {
      m_btnLogin.EnableWindow(FALSE);
      m_btnSetbusy.EnableWindow(FALSE);
      m_btnAnswer.EnableWindow(FALSE);
      m_btnAnswer.SetWindowText("挂机");
      m_btnHold.EnableWindow(FALSE);
      m_btnTransfer.EnableWindow(FALSE);
      m_btnDial.EnableWindow(FALSE);
      m_btnConsult.EnableWindow(FALSE);
      m_btnConsult.SetWindowText("咨询");
      if (SUPERVISOR==g_nLoginType)	  
      {
        m_btnReconnect.EnableWindow(TRUE);
        m_btnReconnect.SetWindowText("取消");
        m_btnForceBreak.EnableWindow(FALSE);
        m_btnBargein.EnableWindow(TRUE);
      }
      GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("监听");
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
      break;
    }
  }


}


void CAgentFormDlg::OnLogin() 
{//签入/签出
  CString strTitle;
  m_btnLogin.GetWindowText(strTitle);
  if(strTitle == "签出")
  {
    if (PHONE_STATE_BUSY==m_CtrlCenter.QueryState() && g_bCheckPassword)
    {
      g_strPasswordReason = "logout";
      m_CtrlCenter.DispatchEvent(DISPATCH_EVENT_CHECKPASSWORD);
    }
    else
      m_CtrlCenter.ExecuteOperation(OPER_LOGOUT);
  }
  if(strTitle == "签入")
  {
    if (g_bCheckPassword)
    {
      g_strPasswordReason = "login";
      m_CtrlCenter.DispatchEvent(DISPATCH_EVENT_CHECKPASSWORD);
    }
    else
      m_CtrlCenter.ExecuteOperation(OPER_LOGIN);
  }

}

void CAgentFormDlg::OnSetbusy() 
{//置闲/置忙
  CBusyReasonDlg Dlg;
  CString strTitle;
  m_btnSetbusy.GetWindowText(strTitle);
  if(strTitle == "置忙")
  {
    if(IDOK == Dlg.DoModal())
    {  
      m_CtrlCenter.ExecuteOperation(OPER_SETBUSY,Dlg.str_reason);
      //	 GetDlgItem(IDC_TEXT_STATUS)->SetWindowText(g_strBusyReason);
    }
  }
  if(strTitle == "置闲")
  {
    if (g_bCheckPassword && m_CtrlCenter.QueryState()!=PHONE_STATE_AFTERTALK)
    {
      g_strPasswordReason = "ready";
      m_CtrlCenter.DispatchEvent(DISPATCH_EVENT_CHECKPASSWORD);
    }
    else
    {
      // 置闲改变预约置忙按钮状态
      if (true == g_bSetBusyFlag)
      {
        g_bSetBusyFlag = false;
        m_btnSetBusyType.EnableWindow(TRUE);
      }      

      m_CtrlCenter.ExecuteOperation(OPER_SETIDLE);
      //		GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("置闲");
    }
  }
  GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
  GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
}

void CAgentFormDlg::OnAnswer() 
{//摘机/挂机
  CString strTitle;
  m_btnAnswer.GetWindowText(strTitle);
  if(strTitle == "挂机")
  {
    if(1==AfxMessageBox(_T("确定要挂机吗?"), MB_OKCANCEL | MB_ICONEXCLAMATION))
    {
      m_CtrlCenter.ExecuteOperation(OPER_RELEASE);
      m_btnAnswer.SetWindowText("挂机");
    }

  }
  if(strTitle == "摘机")
  {
    m_CtrlCenter.ExecuteOperation(OPER_ANSWER);
    m_btnAnswer.SetWindowText("摘机");
  }
}

void CAgentFormDlg::OnHold() 
{//保持/恢复
  CString strTitle;
  m_btnHold.GetWindowText(strTitle);
  if(strTitle == "保持")
  {
    m_CtrlCenter.ExecuteOperation(OPER_HOLD);
    m_btnHold.SetWindowText("保持");
  }
  if(strTitle == "恢复")
  {
    m_CtrlCenter.ExecuteOperation(OPER_RETRIEVE);
    m_btnHold.SetWindowText("恢复");
  }	
}

void CAgentFormDlg::OnDial() 
{//拨号
  CDialDlg Dlg;
  if(IDOK == Dlg.DoModal())
  {
    m_CtrlCenter.ExecuteOperation(OPER_DIAL,Dlg.m_strDialNum);
    GetDlgItem(IDC_TEXT_STATUS)->SetWindowText("外拨");
    GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_TEXT_STATUS)->ShowWindow(SW_SHOW);
  }
}

void CAgentFormDlg::OnTransfer() 
{//转接
  if (PHONE_STATE_CONSULT==m_CtrlCenter.QueryState())
  {
    m_CtrlCenter.ExecuteOperation(OPER_TRANSFER);
  }
  else
  {
    CTransferDlg Dlg;
    if(Dlg.DoModal() == IDOK)
    {
      if (TRANS_TYPE_GROUP==Dlg.m_TransType)
      {
        m_CtrlCenter.ExecuteOperation(OPER_SINGLE_STEP_TRANSFER,Dlg.m_strDialNum);
      }
      else if (TRANS_TYPE_AGENT==Dlg.m_TransType)
        m_CtrlCenter.ExecuteOperation(OPER_TRANSFER,Dlg.m_strDialNum);
    }
  }
}

void CAgentFormDlg::OnConsult() 
{//咨询
  CConsultDlg Dlg;

  CString strTitle;
  m_btnConsult.GetWindowText(strTitle);
  if(strTitle == "咨询")
  {
    if(Dlg.DoModal() == IDOK)
    {
      m_CtrlCenter.ExecuteOperation(OPER_CONSULT,Dlg.m_strDialNum);
      m_btnConsult.SetWindowText("咨询");
    }

  }
  else if(strTitle == "会议")
  {
    m_CtrlCenter.ExecuteOperation(OPER_CONFERENCE);
    m_btnConsult.SetWindowText("会议");
  }

  return;
}

void CAgentFormDlg::OnReconnect() 
{//取回
  CString strTitle;
  m_btnReconnect.GetWindowText(strTitle);
  if(strTitle == "取回")
  {
    m_CtrlCenter.ExecuteOperation(OPER_RECONNECT);
  }
  else if(strTitle == "取消")
  {
    m_CtrlCenter.ExecuteOperation(OPER_RELEASE);
  }

}

void CAgentFormDlg::OnListen() 
{//监听
  CListenDlg Dlg;
  if(IDOK == Dlg.DoModal())
  {
    m_CtrlCenter.ExecuteOperation(OPER_LISTEN,Dlg.m_strListenNum);
  }
}

void CAgentFormDlg::OnBargein() 
{//强插

  m_CtrlCenter.ExecuteOperation(OPER_BARGEIN,g_strBeMonitorAgentID);
}

void CAgentFormDlg::OnForcebreak() 
{//强拆
  m_CtrlCenter.ExecuteOperation(OPER_FORCEBREAK,g_strBeMonitorAgentID);
}


LRESULT CAgentFormDlg::OnStateChange(WPARAM wParam, LPARAM lParam)
{//接收从控制中心发来的状态变化消息，刷新界面显示
  int nState = (int) wParam;
  SetButtonState(nState);

  m_pOcxCtrl->FireAgentStatusChangeEvent(nState);
  //	WriteLog("Dispatch AgentStatusChangeEvent!",INFO_LOG,RUN_LOG_LEVEL);

  return 0;
}

LRESULT CAgentFormDlg::OnStartTpinEvent(WPARAM wParam, LPARAM lParam)
{//开始TPIN
  WriteLog("Start TPIN count time......!",SYSTEM_LOG,RUN_LOG_LEVEL);
  m_TpinStartTime = CTime::GetCurrentTime();
  m_bTpinWaitFlag = true;
  return OK;
}

LRESULT CAgentFormDlg::OnEndTpinEvent(WPARAM wParam, LPARAM lParam)
{//结束TPIN
  WriteLog("Stop TPIN count time!",SYSTEM_LOG,RUN_LOG_LEVEL);
  m_bTpinWaitFlag = false;
  return OK;
}


LRESULT CAgentFormDlg::OnDispatchEvent(WPARAM wParam, LPARAM lParam)
{//向IE发送的事件接口
  int nEventType = (int) wParam;
  char *buf = (char *)lParam;
  CString recvstr = buf;
  CString tmpstr;
  switch (nEventType)
  {
  case DISPATCH_EVENT_LOGIN:
    m_pOcxCtrl->FireLoginEvent(g_strAgentID,g_strAgentExt);
    WriteLog("Dispatch LoginEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_LOGOUT:
    m_pOcxCtrl->FireLogoutEvent(g_strAgentID,g_strAgentExt);
    WriteLog("Dispatch LogoutEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_ACW:
    m_pOcxCtrl->FireACWEvent(g_strANI);
    WriteLog("Dispatch ACWEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_AGENTIDLE:
    m_pOcxCtrl->FireAgentReadyEvent(g_strAgentID,g_strAgentExt);
    WriteLog("Dispatch AgentReadyEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_AGENTBUSY:
    m_pOcxCtrl->FireAgentBusyEvent(g_strAgentID,g_strAgentExt,g_strBusyReason);
    WriteLog("Dispatch AgentBusyEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_ABANDON:
    m_pOcxCtrl->FireCallAbandonEvent();
    WriteLog("Dispatch CallAbandonEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_ESTABLISHED:
    m_pOcxCtrl->FireEstablishedEvent(g_strANI,g_nCallType);
    WriteLog("Dispatch EstablishedEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_HANGUP:
    m_pOcxCtrl->FireHangupEvent();
    WriteLog("Dispatch HangupEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_HELD:
    m_pOcxCtrl->FireHoldEvent();
    WriteLog("Dispatch HoldEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_MONITORCALL:
    m_pOcxCtrl->FireMonitorCallEvent(g_strBeMonitorAgentID,g_strAgentID,g_strAgentExt,g_strConnID,g_nCallType);
    WriteLog("Dispatch MonitorCallEvent!",INFO_LOG,RUN_LOG_LEVEL);		
    break;
  case DISPATCH_EVENT_NEWCALL:
    m_pOcxCtrl->FireNewCallEvent(g_strANI,g_nCallType);
    WriteLog("Dispatch NewCallEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_DIALING:
    m_pOcxCtrl->FireDialingEvent(g_strDNIS,g_nCallType);
    WriteLog("Dispatch DialingEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;	
  case DISPATCH_EVENT_RETRIEVED:
    m_pOcxCtrl->FireRetrieveEvent();
    WriteLog("Dispatch RetrieveEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_AFTERTPIN:
    m_pOcxCtrl->FireAfterTPINEvent(g_strANI);
    WriteLog("Dispatch AfterTPINEvent!",INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_SERVICEEND:
    {
      CTimeSpan   spanTime; 
      spanTime = g_CallEndTime - g_CallBeginTime;
      m_pOcxCtrl->FireServiceEfficiencyEvent(
        g_strAgentID,g_strAgentGroup,g_strCallID,
        g_strANI,g_strDNIS,
        g_CallBeginTime.Format(/*"%Y-%m-%d */"%H:%M:%S"),    //考虑与目前阿郞软电话一致，如果替换阿郞的后，要送全日期时间
        g_CallEndTime.Format(/*"%Y-%m-%d */"%H:%M:%S"), long(spanTime.GetTotalSeconds()),
        g_strRouteSource,
        g_strRouteDest
        );
      WriteLog("Dispatch ServiceEfficiencyEvent!",INFO_LOG,RUN_LOG_LEVEL);
    }
    break;
  case DISPATCH_EVENT_CHECKPASSWORD:
    {
      tmpstr.Format("Dispatch CheckPasswordEvent! check reason is [%s].",g_strPasswordReason.GetString());
      m_pOcxCtrl->FireCheckPasswordEvent(g_strPasswordReason);
      WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
    }
    break;
  case DISPATCH_EVENT_QUERYAGENT:
    {
      recvstr = recvstr+"|";
      CString agentid = SearchStr(recvstr,'|',0);
      CString agentExt = SearchStr(recvstr,'|',1);
      int agentstatus = atoi(SearchStr(recvstr,'|',2));
      tmpstr.Format("Dispatch QueryAgentEvent! AgentID %s, AgentExtension %s ,AgentStatus %d",agentid.GetString(),agentExt.GetString(),agentstatus);
      m_pOcxCtrl->FireQueryAgentEvent(agentid,agentExt,agentstatus);
      WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
    }
    break;	
  case DISPATCH_EVENT_QUERYCALL:
    {
      recvstr = recvstr+"|";
      CString agentid = SearchStr(recvstr,'|',0);
      CString agentExt = SearchStr(recvstr,'|',1);
      int agentstatus = atoi(SearchStr(recvstr,'|',2));
      tmpstr.Format("Dispatch QueryCallEvent! AgentID %s, AgentExtension %s, CallStatus %d",agentid.GetString(),agentExt.GetString(),agentstatus);
      m_pOcxCtrl->FireQueryCallEvent(agentid,agentExt,agentstatus);
      WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
    }
    break;		
  case DISPATCH_EVENT_ERROR:
    {
      tmpstr.Format("Dispatch ErrorEvent! error code[%d], error info[%s].",g_nErrorCode,g_strErrorStr.GetString());
      m_pOcxCtrl->FireErrorEvent(g_nErrorCode,g_strErrorStr);
      WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
      if(272==g_nErrorCode)
        AfxMessageBox("此工号在其他地方已签入!",MB_OK|MB_ICONINFORMATION);
    }
    break;
  case DISPATCH_EVENT_CONFERENCE:
    tmpstr.Format("Dispatch ConferenceEvent! OtherExtension %s.",recvstr.GetString());
    m_pOcxCtrl->FireConferenceEvent(g_strANI,recvstr,g_nCallType);
    WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_CONFERENCEEND:
    tmpstr.Format("Dispatch ConferenceEndEvent! OtherExtension %s.",recvstr.GetString());
    m_pOcxCtrl->FireConferenceEndEvent(g_strANI,recvstr);
    WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_CALLTYPECHANGED:
    tmpstr.Format("Dispatch CallTypeChangedEvent! CallType %d.",g_nCallType);
    m_pOcxCtrl->FireCallTypeChangedEvent(g_strANI,g_nCallType);
    WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
    break;
  case DISPATCH_EVENT_RECORD://add by 09 08 03
    tmpstr.Format("Dispatch RecordEvent! RecordID %s.",g_RecordID.GetString());
    m_pOcxCtrl->FireRecordEvent(g_RecordIP,g_RecordPort,g_RecordID.GetString());
    WriteLog(tmpstr,INFO_LOG,RUN_LOG_LEVEL);
    break;
  }

  delete buf;
  return 0;
}


void CAgentFormDlg::OnBnClickedSetbysytype()
{
  // TODO: 在此添加控件通知处理程序代码
  g_bSetBusyFlag = true;
  m_btnSetBusyType.EnableWindow(FALSE);
}
