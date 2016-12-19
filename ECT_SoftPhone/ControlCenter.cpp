// ControlCenter.cpp: implementation of the CControlCenter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ECT_SoftPhone.h"
#include "ControlCenter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CControlCenter::CControlCenter()
{

  m_UIHwnd = NULL;
  m_pPhone = NULL;
  m_bStartFlag = false;

}

CControlCenter::~CControlCenter()
{
  m_pPhone = NULL;

}

void CControlCenter::ConfigCTIServer(CString svrIP, long svrPort, long svrType, CString pbx)
{//配置CTI参数
  g_strCTISvrIp = svrIP;
  g_strCTISvrPort = svrPort;
  g_nCTISvrType = svrType;
  g_PBX = pbx;
}

// add by hzd 2016-11-7 增加录音相关
void CControlCenter::ConfigRECServer(CString svrIP, long svrPort, CString urlPath, CString ccid, CString usrname, CString passWord)
{//配置录音服务器参数
  g_strRecSvrIp = svrIP;
  g_strRecSvrPort = svrPort;
  g_strRecUrlPath = urlPath;
  g_strRecCCID = ccid;
  g_strRecUsrName = usrname;
  g_strRecPassWord = passWord;

  g_strRecParaSetFlag = true;
}

void CControlCenter::ConfigSoftPhone(CString AgtID, CString AgtExt, CString AgtGroup, AgentLoginType loginType)
{//配置软电话参数
  g_strAgentID = AgtID;
  g_strAgentExt = AgtExt;
  g_strAgentGroup = AgtGroup;
  g_nLoginType = loginType;
}

int CControlCenter::QueryState()
{//查询状态
  return m_stateMachine.QueryCurState();;
}

int CControlCenter::UpdateState(int state, CString connID)
{
  m_stateMachine.UpdateState(state, connID);

  int curState = m_stateMachine.QueryCurState();
  NotifyStateChange(curState);
  return curState;
}

int CControlCenter::UpdateState(int state)
{//更新状态
  m_stateMachine.UpdateState(state, "");

  int curState = m_stateMachine.QueryCurState();
  if (m_bStartFlag)
  {
    m_pPhone->SetState(curState);
  }
  NotifyStateChange(curState);
  return curState;
}

CString CControlCenter::ExecuteOperation(int opertype, CString param1, CString param2)
{//操作执行
  CString strRet = "";
  switch (opertype)
  {
  case OPER_LOGIN:
    m_pPhone->Login(g_strAgentID, g_strAgentExt, g_strAgentGroup, g_nLoginType);
    break;
  case OPER_LOGOUT:
    m_pPhone->Logout();
    break;
  case OPER_ANSWER:
    m_pPhone->Answer();
    break;
  case OPER_DIAL:
    m_pPhone->DialNum(param1);
    break;
  case OPER_TRANSFER:
    m_pPhone->Transfer(param1);
    break;
  case OPER_SINGLE_STEP_TRANSFER:
    m_pPhone->SingleStepTransfer(param1);
    break;
  case OPER_CONSULT:
    m_pPhone->Consult(param1);
    break;
  case OPER_HOLD:
    m_pPhone->Hold();
    break;
  case OPER_RETRIEVE:
    m_pPhone->Retrieve();
    break;
  case OPER_RECONNECT:
    m_pPhone->Reconnect();
    break;
  case OPER_CONFERENCE:
    m_pPhone->Conference();
    break;
  case OPER_RELEASE:
    m_pPhone->Hangup();
    break;
  case OPER_SETIDLE:
    m_pPhone->SetIdle();
    break;
  case OPER_SETBUSY:
    g_strBusyReason = param1;
    m_pPhone->SetBusy(param1);
    break;
  case OPER_TPIN:
    m_pPhone->ConferenceTPin(param1);
    break;
  case OPER_LISTEN:
    m_pPhone->Listen(param1);
    break;
  case OPER_BARGEIN:
    m_pPhone->BargeIn(param1);
    break;
  case OPER_QUERYAGENT:
    m_pPhone->QueryAgentStatus(param1);
    break;
  case OPER_QUERYCALL:
    m_pPhone->QueryCallStatus(param1);
    break;
  case OPER_FORCEBREAK:
    m_pPhone->ForceBreak(param1);
    break;
  case OPER_FORCELOGOUT:
    m_pPhone->ForceLogout(param1);
    break;
  case OPER_SETONEUSERDATA:
    m_pPhone->SetSyncData(param1, param2);
    break;
  case OPER_GETONEUSERDATA:
    strRet = m_pPhone->GetSyncData(param1);
    break;
  case OPER_SETUSERDATA:
    {
      // 			CString tmpstr = SearchStr(param1+"|",'|',0);
      // 			int i = 0;
      // 			while (!tmpstr.IsEmpty())
      // 			{
      // 				CString key = SearchStr(tmpstr+",",',',0);
      // 				CString value = SearchStr(tmpstr+",",',',1);
      // 				m_pPhone->SetSyncData(key,value);
      // 				i++;
      // 				tmpstr = SearchStr(param1+"|",'|',i); 
      // 			}
      m_pPhone->SetSyncData(param1);
    }
    break;
  case OPER_GETSTATUS:
    m_pPhone->GetState();
    break;
  case OPER_UPDATEGROUPINFO:
    m_pPhone->UpdateGroupInfo(param1);
    break;
  // add by hzd 2016-11-7 增加获取录音url文件列表操作
  case OPER_GETRECFILES:
    GetRecFiles(param1);
    break;
  }
  return strRet;
}

void CControlCenter::NotifyStateChange(int state)
{//通知界面更新状态
  PostMessage(m_UIHwnd, WM_STATE_CHANGE, (WPARAM)state, 0);
}


void CControlCenter::DispatchEvent(DispatchEventType EvtType, CString param)
{//通知事件发送
  int size = param.GetLength();
  char *buf = new char[size + 1];
  memset(buf, 0, size + 1);
  memcpy(buf, param.GetBuffer(0), size);

  PostMessage(m_UIHwnd, WM_DISPATCH_EVENT, (WPARAM)EvtType, (LPARAM)buf);
}



void CControlCenter::DispatchEvent(DispatchEventType EvtType, char * param)
{//通知事件发送
  int size = 0;
  if (param == NULL)
  {
    size = 0;
  }
  else
    size = strlen(param);

  char *buf = new char[size + 1];
  memset(buf, 0, size + 1);
  memcpy(buf, param, size);


  PostMessage(m_UIHwnd, WM_DISPATCH_EVENT, (WPARAM)EvtType, (LPARAM)buf);
}

void CControlCenter::StartTpinTimer()
{//启动TPIN超时计时
  SendMessage(m_UIHwnd, WM_START_TPIN_TIMER, 0, 0);
  //	PostMessage(m_UIHwnd,WM_START_TPIN_TIMER,0,0);	 //有时可能PostMessage发送的信息会丢失
}

void CControlCenter::EndTpinTimer()
{//关闭TPIN计时
  SendMessage(m_UIHwnd, WM_END_TPIN_TIMER, 0, 0);
  //	PostMessage(m_UIHwnd,WM_END_TPIN_TIMER,0,0);	//有时可能PostMessage发送的信息会丢失
}




void CControlCenter::SetHwnd(HWND hwnd)
{//设置界面类的句柄
  m_UIHwnd = hwnd;
}

int CControlCenter::Start()
{//启动
  //here to connect to CTI server
  if (GENESYS == g_nCTISvrType)
  {
    g_bSysExit = false;
    WriteLog("Ready to start the softphone...!!", SYSTEM_LOG, RUN_LOG_LEVEL);
    m_pPhone = (CCTIInterface *)new CGenesysInterface();
    if (m_pPhone)
    {
      m_pPhone->SetCtrlCenterPtr(this);
      if (m_pPhone->Init())
      {
        if (m_pPhone->ConnectCTIServer(g_strCTISvrIp, g_strCTISvrPort))
        {
          NotifyStateChange(PHONE_STATE_INIT);
          m_bStartFlag = true;
        }
        else
        {
          NotifyStateChange(PHONE_STATE_DISABLE);
        }
      }
      else
      {
        NotifyStateChange(PHONE_STATE_DISABLE);
      }
    }
  }
  return 0;
}


void CControlCenter::Stop()
{//停止
  WriteLog("Ready to exit the softphone...!!", SYSTEM_LOG, RUN_LOG_LEVEL);
  if (m_pPhone)
  {
    if (m_pPhone->GetLoginOkFlag())
    {

      m_bStartFlag = false;
      m_pPhone->Logout();

    }
    m_pPhone->Exit();
    delete m_pPhone;
    m_pPhone = NULL;
    WriteLog("Exit the softphone OK!!", SYSTEM_LOG, RUN_LOG_LEVEL);
  }
}

