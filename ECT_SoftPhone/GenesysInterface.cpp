// GenesysInterface.cpp: implementation of the CGenesysInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ECT_SoftPhone.h"
#include "GenesysInterface.h"
#include "AgentFormDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

void ReConnectTServer();
void ClearParam();
short InitParam();
void PrepareForReConnectTServer();
UINT StartListen(LPVOID lParam);
UINT DelayEvent(LPVOID lParam);
UINT WaitExitEvent(LPVOID lParam);
UINT DelayAnswer(LPVOID lParam);
void EndMonitor();


HANDLE g_GenesysEventHandle;
int g_tserver;									//Genesys Server
void TServerEventsProc(TEvent *event);			//事件处理线程
HANDLE	g_evtUpdateHandle;
int		g_GroupCount = 0;
CString g_QueryGroupName;

HANDLE	g_evtWaitHandle;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenesysInterface::CGenesysInterface()
{
  g_evtUpdateHandle = ::CreateEvent(NULL, false, false, NULL);
  g_evtWaitHandle = ::CreateEvent(NULL, false, false, NULL);
}

CGenesysInterface::~CGenesysInterface()
{

}


int CGenesysInterface::Init()
{
  return OK;
}

int CGenesysInterface::Exit()
{
  ClearParam();
  return OK;
}



void ClearParam()
{//清除参数

  WriteLog("Ready to close the tserver!", SYSTEM_LOG, RUN_LOG_LEVEL);
  ::SetEvent(g_GenesysEventHandle);
  //	Sleep(200);
  g_bSysExit = true;
  Sleep(100);

  TCloseServer(g_tserver);
}

void PrepareForReConnectTServer()
{//准备重连
  g_bConnectTServerOK = false;
  if (g_bSysExit) return;
  ClearParam();
}


short InitParam()
{//参数初始化
  conn_startup();
  char Host[20];

  strcpy_s(Host, g_strCTISvrIp);
  if ((g_tserver = TOpenServerEx(Host, g_strCTISvrPort, TServerEventsProc, "tserver", NULL, SyncMode)) < 0)
  {
    g_bConnectTServerOK = false;
    CString tmpStr;
    tmpStr.Format("与Genesys的TServer(主机名:%s 端口:%ld)建立连接失败!\n\n点击\"确定\"按钮，重新连接操作将每隔%d秒进行一次，可以点击\"取消\"按钮而不进行连接。",
      g_strCTISvrIp.GetString(), g_strCTISvrPort, g_nReconnInterval);
    if (!g_bReconnect)
    {
      if (IDOK == MessageBox(NULL, tmpStr, "Genesys连接提示", MB_ICONWARNING | MB_OKCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1))
      {
        PrepareForReConnectTServer();
      }

    }

    return FAIL;
  }
  else
  {
    g_bConnectTServerOK = true;
  }

  g_GenesysEventHandle = ::CreateEvent(NULL, false, false, "Genesys_event");
  AfxBeginThread(WaitExitEvent, 0, THREAD_PRIORITY_ABOVE_NORMAL, 0, NULL, NULL);
  AfxBeginThread(StartListen, (LPVOID)g_tserver, THREAD_PRIORITY_ABOVE_NORMAL, 0, NULL, NULL);

  char ACD[10];
  strcpy_s(ACD, g_strAgentGroup);
  char RegDN[DN_LEN], RegAgtID[DN_LEN];

  strcpy_s(RegDN, g_strAgentExt);

  strcpy_s(RegAgtID, g_strAgentID);


  if (g_PBX == "ALCATEL")
  {
    TRegisterAddress(g_tserver, RegDN, ModeShare, RegisterDefault, AddressTypeDN, NULL);
    TRegisterAddress(g_tserver, RegAgtID, ModeShare, RegisterDefault, AddressTypeAgentID, NULL);
    if (g_nLoginType)
      TAgentLogin(g_tserver, ACD, RegDN, AgentTypeSupervisor, RegAgtID, NULL, AgentManualIn, NULL, NULL);
    else
      TAgentLogin(g_tserver, ACD, RegDN, AgentTypeAgent, RegAgtID, NULL, AgentManualIn, NULL, NULL);
  }
  else
  {
  }
  return OK;
}

UINT WaitExitEvent(LPVOID lParam)
{//等待退出事件
  while (true)
  {
    if (::WaitForSingleObject(g_GenesysEventHandle, 10) == WAIT_OBJECT_0)
    {
      g_bSysExit = true;
      WriteLog("The thread WaitExitEvent is closing...!!", SYSTEM_LOG, BASE_LOG_LEVEL);
      break;
    }
  }
  if (g_GenesysEventHandle)
  {
    CloseHandle(g_GenesysEventHandle);
    g_GenesysEventHandle = NULL;
  }
  return OK;
}

UINT StartListen(LPVOID lParam)
{//启动事件监听
  while (!g_bSysExit)
  {
    TDispatch((int)lParam);
    Sleep(5);
  }
  WriteLog("The thread StartListen is closing...!!", SYSTEM_LOG, BASE_LOG_LEVEL);

  g_bSysExit = false;
  return OK;
}

void CGenesysInterface::ReConnectTServer()
{//重连CTI服务器
  g_bReconnect = true;
  InitParam();
  if (g_bConnectTServerOK)
  {
    if (g_bWriteLog)
      //			WriteLog("Reconnect to TServer OK!\n");
        //		::KillTimer(m_pDialog->m_hWnd,TIMER_ID);
          return;
  }
}


int CGenesysInterface::ConnectCTIServer(CString HostIP, long Port)
{//连接CTI服务器
  //conn_startup();
  char Host[20];
  CString tmpStr;
  bool bFlag = false;
  // 	g_strCTISvrIp = HostIP;
  // 	g_strCTISvrPort = Port;

  g_bConnectTServerOK = false;
  strcpy_s(Host, HostIP);
  if ((g_tserver = TOpenServerEx(Host, Port, TServerEventsProc, "tserver", NULL, SyncMode)) < 0)
  {
    tmpStr.Format("与Genesys的TServer(主机名:%s 端口:%ld)建立连接失败!\n\n点击\"确定\"按钮，重新连接操作将每隔%d秒进行一次，可以点击\"取消\"按钮而不进行连接。",
      g_strCTISvrIp.GetString(), g_strCTISvrPort, g_nReconnInterval);
    if (!g_bReconnect)
    {
      tmpStr.Format("Can't connect to primary CTI server!(IP:%s Port:%d), call TOpenServerEx ret:%d", g_strCTISvrIp.GetString(), g_strCTISvrPort, g_tserver);
      WriteLog(tmpStr, SYSTEM_LOG, BASE_LOG_LEVEL);

      //  			if(IDOK==MessageBox(NULL,tmpStr,"Genesys连接提示",MB_ICONWARNING|MB_OKCANCEL|MB_ICONEXCLAMATION|MB_DEFBUTTON1))
      //  			{
      //  				PrepareForReConnectTServer();
      // 				CString strinfo;
      // 				strinfo.Format("Ready to reconnect to CTI server after %d seconds",g_nReconnInterval);
      // 				WriteLog(strinfo,SYSTEM_LOG,BASE_LOG_LEVEL);
      //  			}

      if (!g_strCTISvrIpBak.IsEmpty() && g_strCTISvrPortBak > 0)
      {
        strcpy_s(Host, g_strCTISvrIpBak);

        if ((g_tserver = TOpenServerEx(Host, g_strCTISvrPortBak, TServerEventsProc, "tserver", NULL, SyncMode)) < 0)
        {
          tmpStr.Format("Can't connect to backup CTI server!(IP:%s Port:%d), call TOpenServerEx ret:%d", g_strCTISvrIpBak.GetString(), g_strCTISvrPortBak, g_tserver);
          WriteLog(tmpStr, SYSTEM_LOG, BASE_LOG_LEVEL);
          return FAIL;
        }
        else
        {
          tmpStr.Format("Connect to backup CTI server(IP:%s Port:%d) successfully! call TOpenServerEx ret:%d", g_strCTISvrIpBak.GetString(), g_strCTISvrPortBak, g_tserver);
          WriteLog(tmpStr, SYSTEM_LOG, BASE_LOG_LEVEL);
          g_bConnectTServerOK = true;
          g_UserData = TKVListCreate();
        }
      }
    }
  }
  else
  {

    tmpStr.Format("Connect to CTI server(IP:%s Port:%d) successfully! call TOpenServerEx ret:%d", g_strCTISvrIp.GetString(), g_strCTISvrPort, g_tserver);
    WriteLog(tmpStr, SYSTEM_LOG, BASE_LOG_LEVEL);
    g_bConnectTServerOK = true;
    g_UserData = TKVListCreate();
  }
  g_GenesysEventHandle = ::CreateEvent(NULL, false, false, "Genesys_event");
  //	AfxBeginThread(WaitExitEvent,0,THREAD_PRIORITY_ABOVE_NORMAL,0,NULL,NULL);
  AfxBeginThread(StartListen, (LPVOID)g_tserver, THREAD_PRIORITY_ABOVE_NORMAL, 0, NULL, NULL);

  return OK;
}

CString GetKV(TKVList *UserData, CString label)
{
  CString value = "";
  char Key[100];
  strcpy_s(Key, label);

  if (UserData)
  {
    value = TKVListGetStringValue(UserData, Key, NULL);
    if (value.IsEmpty())
    {
      int n = -1;
      n = TKVListGetIntValue(UserData, Key, NULL);
      if (-1 != n)
      {
        value.Format("%d", n);
      }
    }
  }
  return value;
}

// 从 TransferData 中获取VAR值
CString GeKeyFromUserData(CString UserData, CString label)
{
  if (!g_bConnectTServerOK) return "";

  CString Value = "";
  int i = 0;

  CString key = "";
  CString value = "";
  CString tmpstr = SearchStr(UserData + "|", '|', 0);
  if (UserData)
  {
    while (1)
    {
      if (!tmpstr.IsEmpty())
      {
        key = SearchStr(tmpstr + ",", ',', 0);
        value = SearchStr(tmpstr + ",", ',', 1);
        if (!key.Compare(label)) Value = value;
      }
      else break;
      i++;
      tmpstr = SearchStr(UserData + "|", '|', i);
    }
  }
  return Value;
}

static void TServerEventsProc(TEvent *event)
{//CTI事件接收
  CString tmpStr;
  static CString strCurRgtDN;
  CString agentInfoStatus = "-1";
  try
  {

    tmpStr.Format("Event receive from CTI, Event name: %s  thisDN:%s  otherDN:%s thirdDN:%s",
      TMessageTypeNames[event->Event], event->ThisDN, event->OtherDN, event->ThirdPartyDN);
    WriteLog(tmpStr, INFO_LOG, DEBUG_LOG_LEVEL);
    CString dnstr = event->ThisDN;
    if (dnstr != g_strAgentExt)
    {
      switch (event->Event)
      {
      case EventRegistered:
        break;
      case EventUnregistered:
        break;
      case EventAddressInfo:
        {
          tmpStr.Format("thisDN:%s,AgentID:%s,AgentStatus:%d,CallType:%d",
            event->ThisDN, event->AgentID, event->InfoStatus.AgentStatus, event->CallType);
          WriteLog(tmpStr, INFO_LOG, DEBUG_LOG_LEVEL);
          CString agtdn = dnstr;
          CString agtid = event->AgentID;
          if (!agtdn.IsEmpty() && !agtid.IsEmpty())
          {
            CAgentGroup ag = g_AgentGroupList.GetGroup(g_QueryGroupName);
            int status = event->InfoStatus.AgentStatus;
            switch (status)
            {
            case 0:
              ag.UpdateCallStatus(agtid, agtdn, status);
              tmpStr.Format("%s|%s|%d", agtid.GetString(), agtdn.GetString(), PHONE_STATE_INIT);
              g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_QUERYCALL, tmpStr);
              break;
            case 1:
              ag.UpdateCallStatus(agtid, agtdn, status);
              tmpStr.Format("%s|%s|%d", agtid.GetString(), agtdn.GetString(), PHONE_STATE_TALKING);
              g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_QUERYCALL, tmpStr);
              break;
            case 2:
              ag.UpdateAgentStatus(agtid, agtdn, status);
              tmpStr.Format("%s|%s|%d", agtid.GetString(), agtdn.GetString(), PHONE_STATE_IDLE);
              g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_QUERYAGENT, tmpStr);
              break;
            case 3:
              ag.UpdateAgentStatus(agtid, agtdn, status);
              tmpStr.Format("%s|%s|%d", agtid.GetString(), agtdn.GetString(), PHONE_STATE_BUSY);
              g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_QUERYAGENT, tmpStr);
              break;
            case 4:
              ag.UpdateAgentStatus(agtid, agtdn, status);
              tmpStr.Format("%s|%s|%d", agtid.GetString(), agtdn.GetString(), PHONE_STATE_AFTERTALK);
              g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_QUERYAGENT, tmpStr);
              break;
            }
            g_AgentGroupList.SetGroup(ag);
            g_GroupCount--;
          }
          else
          {
            tmpStr.Format("%s|%s|%d", dnstr.GetString(), "", PHONE_STATE_DISABLE);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_QUERYAGENT, tmpStr);
            CAgentGroup ag = g_AgentGroupList.GetGroup(g_QueryGroupName);
            ag.UpdateAgentStatus(dnstr, "", 0);
            ag.UpdateCallStatus(dnstr, "", 0);
            g_AgentGroupList.SetGroup(ag);
            g_GroupCount--;
            g_GroupCount--;
          }
          if (0 == g_GroupCount)
          {
            ::SetEvent(g_evtUpdateHandle);
          }

        }
        break;
      case EventError:
        tmpStr.Format("Receive error from CTI server, DN:%s, Error code:[%d] Msg:%s",
          event->ThisDN, event->ErrorCode, event->ErrorMessage);

        WriteLog(tmpStr, ERROR_LOG, BASE_LOG_LEVEL);
        break;
      case EventLinkConnected:

        g_pCtrlCenter->UpdateState(PHONE_STATE_INIT);
        WriteLog("Connect to CTI Server ok!", SYSTEM_LOG, BASE_LOG_LEVEL);
        break;
      case EventServerConnected:
        g_pCtrlCenter->UpdateState(PHONE_STATE_INIT);
        g_strConnID = "";
        g_strConsultConnID = "";
        WriteLog("Connect to CTI Server ok!", SYSTEM_LOG, BASE_LOG_LEVEL);
        break;

      case EventServerDisconnected:
        g_pCtrlCenter->UpdateState(PHONE_STATE_DISABLE);
        WriteLog("Disconnect from CTI Server!", SYSTEM_LOG, BASE_LOG_LEVEL);
        break;
      }
    }
    else
    {

      switch (event->Event)
      {
      case EventError:
        tmpStr.Format("Receive error from CTI server, DN:%s, Error code:[%d] Msg:%s",
          event->ThisDN, event->ErrorCode, event->ErrorMessage);

        WriteLog(tmpStr, ERROR_LOG, BASE_LOG_LEVEL);
        if (g_bTpinFlag)
        {
          g_bTpinFlag = false;
        }
        g_nErrorCode = event->ErrorCode;
        g_strErrorStr = event->ErrorMessage;
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ERROR);
        break;


      case EventServerInfo:

        break;

      case EventAddressInfo:
        {

        }
        break;

      case EventPartyInfo:

        break;

      case EventMonitoringNextCall:
        tmpStr.Format("MonitoringNextCall event! thisDN:%s otherDN:%s ANI:%s ConnID:%s  CallType:%d",
          event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        g_strMonitorAgentDN = event->OtherDN;
        if (g_nLoginType == SUPERVISOR)
        {
          g_pCtrlCenter->UpdateState(PHONE_STATE_LISTEN);
          g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_MONITORCALL);
        }
        else if (PHONE_STATE_HOLD == g_pCtrlCenter->QueryState())
        {
          ::SetEvent(g_evtWaitHandle);
          g_strMonitorAgentDN = event->OtherDN;
        }
        else if (PHONE_STATE_CONSULT == g_pCtrlCenter->QueryState())
        {
          ::SetEvent(g_evtWaitHandle);
          g_strMonitorAgentDN = event->OtherDN;
        }
        else if (PHONE_STATE_CONFERENCE == g_pCtrlCenter->QueryState())
        {
          //在会议状态下监听是不能成功的，但必须放弃此事件
        }
        else
        {
          ::SetEvent(g_evtWaitHandle);
          g_strMonitorAgentDN = event->OtherDN;
          g_pCtrlCenter->UpdateState(PHONE_STATE_BELISTEN);
        }
        break;

      case EventMonitoringCancelled:
        tmpStr.Format("MonitoringCancelled event! thisDN:%s otherDN:%s ANI:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        if (g_nLoginType == SUPERVISOR)
        {
          g_pCtrlCenter->UpdateState(PHONE_STATE_IDLE);
          g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_AGENTIDLE);
        }
        break;

      case EventMuteOff:

        break;

      case EventMuteOn:

        break;
      case EventAttachedDataChanged:
        TKVListFree(g_UserData);
        g_UserData = TKVListCreate();
        g_UserData = TKVListDup(event->UserData);

        WriteLog("AttachedDataChanged event!", INFO_LOG, RUN_LOG_LEVEL);
        tmpStr.Format("KV string:%s", TKVListToString(g_UserData));
        WriteLog(tmpStr, INFO_LOG, DEBUG_LOG_LEVEL);
        break;

      case EventRinging:
        TKVListFree(g_UserData);
        g_UserData = TKVListCreate();
        g_UserData = TKVListDup(event->UserData);
        tmpStr = event->ANI;
        if (tmpStr.IsEmpty()) g_strANITPIN = event->OtherDN;
        else g_strANITPIN = event->ANI;

        if (g_bBargeinFlag)
        {
          //do nothing
          WriteLog("Bargein Ring event received!", INFO_LOG, RUN_LOG_LEVEL);
        }
        else if (g_bTpinFlag)
        {
          WriteLog("Tpin callback ring.....! wait for one second and auto answer it!", INFO_LOG, RUN_LOG_LEVEL);
          AfxBeginThread(DelayAnswer, 0, THREAD_PRIORITY_ABOVE_NORMAL, 0, NULL, NULL);
          //	g_pCtrlCenter->ExecuteOperation(OPER_ANSWER);
        }
        else if (g_bListenFlag)
        {
          WriteLog("Listen Ring event received! (1)", INFO_LOG, RUN_LOG_LEVEL);
          g_bListenFlag = true;
          // modify by hzd
          g_pCtrlCenter->UpdateState(PHONE_STATE_LISTEN);
        }
        else if (PHONE_STATE_LISTEN == g_pCtrlCenter->QueryState())
        {
          WriteLog("Listen Ring event received! (2)", INFO_LOG, RUN_LOG_LEVEL);
        }
        else
        {
          g_nCallType = (CallType)event->CallType;
          g_strConnID = connid_to_str(event->ConnID);
          g_strMonitorAgentDN = "";
          tmpStr = event->ANI;
          if (tmpStr.IsEmpty())
            g_strANI = event->OtherDN;
          else
            g_strANI = event->ANI;

          g_strDNIS = event->DNIS;


          tmpStr.Format("Ring event! thisDN:%s otherDN:%s ANI:%s ConnID:%s CallType:%d",
            event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
          WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);

          g_pCtrlCenter->UpdateState(PHONE_STATE_RING);
          g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_NEWCALL);

        }

        break;

      case EventDialing:
        g_pCtrlCenter->UpdateState(PHONE_STATE_DIALING);
        g_strDNIS = event->DNIS;
        if (CALL_TYPE_CONSULT != event->CallType)
        {
          g_nCallType = (CallType)event->CallType;
          g_strConnID = connid_to_str(event->ConnID);
        }
        else
        {
          g_nCallType = (CallType)event->CallType;
          g_strConsultConnID = connid_to_str(event->ConnID);
          g_strOriConnID = g_strConnID;
        }

        tmpStr.Format("Dialing event! thisDN:%s otherDN:%s DNIS:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->DNIS, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);

        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_DIALING);
        break;

      case EventAbandoned:
        tmpStr.Format("Abandoned event! thisDN:%s otherDN:%s ANI:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);

        g_pCtrlCenter->UpdateState(PHONE_STATE_IDLE);
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ABANDON);
        break;

      case EventDTMFSent:
        break;

      case EventEstablished:
        TKVListFree(g_UserData);
        g_UserData = TKVListCreate();
        g_UserData = TKVListDup(event->UserData);


        tmpStr.Format("Established event! thisDN:%s otherDN:%s ANI:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);


        g_nCallType = (CallType)event->CallType;
        switch (event->CallType)
        {
        case CALL_TYPE_INBOUND:
          tmpStr = event->ANI;
          if (tmpStr.IsEmpty())
            g_strANI = event->OtherDN;
          else
            g_strANI = event->ANI;

          if (g_bBargeinFlag)
          {
            g_pCtrlCenter->UpdateState(PHONE_STATE_CONFERENCE);
            tmpStr.Format("Bargein Successfully! thisDN:%s otherDN:%s ANI:%s ConnID:%s CallType:%d",
              event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
            WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_CONFERENCE, event->OtherDN);
            g_bBargeinFlag = false;
            g_TimerType = TIMER_OPER_START;
          }
          else if (g_bTpinFlag)
          {
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_AFTERTPIN);
            g_bTpinFlag = false;
            g_pCtrlCenter->EndTpinTimer();
            WriteLog("Tpin end ok! It's now talking!", INFO_LOG, RUN_LOG_LEVEL);

          }
          else if ((g_bListenFlag == true) || (PHONE_STATE_LISTEN == g_pCtrlCenter->QueryState()))
          {
            WriteLog("Continue to listen!", INFO_LOG, RUN_LOG_LEVEL);
            g_CallBeginTime = CTime::GetCurrentTime();
            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_START;
          }
          else if (PHONE_STATE_BELISTEN == g_pCtrlCenter->QueryState())
          {
            WriteLog("Continue to belisten!", INFO_LOG, RUN_LOG_LEVEL);
          }
          else
          {
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
            g_CallBeginTime = CTime::GetCurrentTime();
            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_START;
          }

          break;
        case CALL_TYPE_OUTBOUND:
          tmpStr = event->DNIS;
          if (tmpStr.IsEmpty())
            g_strANI = event->OtherDN;
          else
            g_strANI = event->DNIS;
          if (g_bTpinFlag)
          {
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_AFTERTPIN);
            g_bTpinFlag = false;
            g_pCtrlCenter->EndTpinTimer();
            WriteLog("Tpin end ok! It's now talking!", INFO_LOG, RUN_LOG_LEVEL);

          }
          else
          {
            g_CallBeginTime = CTime::GetCurrentTime();
            g_CallEndTime = CTime::GetCurrentTime();
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
            g_TimerType = TIMER_OPER_START;
          }

          break;
        case CALL_TYPE_CONSULT:
          g_strANI = event->OtherDN;
          if (connid_to_str(event->ConnID) == g_strConnID)
          {
            g_CallBeginTime = CTime::GetCurrentTime();
            g_CallEndTime = CTime::GetCurrentTime();
            g_pCtrlCenter->UpdateState(PHONE_STATE_ANSWER_CONSULT);
            g_TimerType = TIMER_OPER_START;
          }
          else
          {
            g_strConsultConnID = connid_to_str(event->ConnID);
            g_pCtrlCenter->UpdateState(PHONE_STATE_CONSULT);
          }
          break;
        case CALL_TYPE_INTERNAL:
          g_strANI = event->OtherDN;
          // modify by hzd 2016-11-16
          if ((g_bListenFlag == true) || (PHONE_STATE_LISTEN == g_pCtrlCenter->QueryState()))
          {
            WriteLog("Continue to listen!", INFO_LOG, RUN_LOG_LEVEL);
            g_CallBeginTime = CTime::GetCurrentTime();
            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_START;
            g_pCtrlCenter->UpdateState(PHONE_STATE_LISTEN);
          }
          else if (PHONE_STATE_BELISTEN == g_pCtrlCenter->QueryState())
          {
            WriteLog("Continue to belisten!", INFO_LOG, RUN_LOG_LEVEL);
          }
          else
          {
            g_CallBeginTime = CTime::GetCurrentTime();
            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_START;
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
          }
          break;
        case CALL_TYPE_UNKNOWN:
          //nothing to do
          break;
        }
        /*
        RecordID();//add by 09 08 03
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_RECORD);//add by 09 08 03
        */
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ESTABLISHED);
        break;

      case  EventReleased:
        TKVListFree(g_UserData);
        g_UserData = TKVListCreate();
        g_UserData = TKVListDup(event->UserData);
        //需要修改获取VAR1
        //g_strCallID = GetKV(g_UserData, "TransferData");
        g_strCallID = GeKeyFromUserData(GetKV(g_UserData, "TransferData"), "VAR1");
        g_strRouteSource = GetKV(g_UserData, "RTargetRequested");
        g_strRouteDest = GetKV(g_UserData, "RTargetObjectSelected");

        //挂机记录录音结束时间 add by hzd 2016-11-10
        g_timeRecEnd = CTime::GetCurrentTime();
        tmpStr.Format("Call hangup ok! thisDN:%s otherDN:%s ANI:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        //TPIN 实现方式变为 会议方式，不需要处理
        //if (g_bTpinFlag)
        //{
        //g_bTpinFlag = false;
        //g_pCtrlCenter->UpdateState(PHONE_STATE_TPIN);
        //g_pCtrlCenter->ExecuteOperation(OPER_SETBUSY, "置忙");
        //WriteLog("Tpin end ok! It's now talking!", INFO_LOG, RUN_LOG_LEVEL);
        //}

        switch (event->CallType)
        {
        case CALL_TYPE_INBOUND:
          if (PHONE_STATE_TPIN == g_pCtrlCenter->QueryState())
          {
            WriteLog("Tpin ready to count time......", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->StartTpinTimer();
          }
          else if ((true == g_bListenFlag) || (PHONE_STATE_LISTEN == g_pCtrlCenter->QueryState()))
          {
            g_bListenFlag = false;
            EndMonitor();  //add by wyh 2009-4-21

            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_STOP;
            g_pCtrlCenter->UpdateState(PHONE_STATE_AFTERTALK);
            WriteLog("Agent is ACW state after the Inbound call.", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_SERVICEEND);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ACW);
          }
          else if (PHONE_STATE_BELISTEN == g_pCtrlCenter->QueryState())
          {
            //kickout monitor
            EndMonitor();  //add by wyh 2009-4-21

            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_STOP;
            g_pCtrlCenter->UpdateState(PHONE_STATE_AFTERTALK);
            WriteLog("Agent is ACW state after the Inbound call.", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_SERVICEEND);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ACW);
          }
          else if (PHONE_STATE_RING == g_pCtrlCenter->QueryState())
          {
            g_strBusyReason = "置忙";
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ABANDON);
            WriteLog("Call is abandon.", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->UpdateState(PHONE_STATE_BUSY);
          }
          else if (PHONE_STATE_BUSY == g_pCtrlCenter->QueryState())
          {
          }
          else
          {
            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_STOP;
            g_pCtrlCenter->UpdateState(PHONE_STATE_AFTERTALK);
            WriteLog("Agent is ACW state after the Inbound call.", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_SERVICEEND);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ACW);
            g_bTransFlag = false;

          }

          break;
        case CALL_TYPE_OUTBOUND:
          if (PHONE_STATE_TPIN == g_pCtrlCenter->QueryState())
          {
            WriteLog("Tpin ready to count time......", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->StartTpinTimer();
          }
          else
          {
            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_STOP;
            g_pCtrlCenter->UpdateState(PHONE_STATE_IDLE);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_SERVICEEND);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ACW);
            WriteLog("Agent is IDLE state after the Outbound call.", INFO_LOG, RUN_LOG_LEVEL);
          }

          break;
        case CALL_TYPE_CONSULT:
          if (PHONE_STATE_ANSWER_CONSULT == g_pCtrlCenter->QueryState())
          {
            g_pCtrlCenter->UpdateState(PHONE_STATE_IDLE);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_AGENTIDLE);
            g_TimerType = TIMER_OPER_STOP;
            WriteLog("Agent is IDLE state after the consult call.", INFO_LOG, RUN_LOG_LEVEL);
          }
          else if ((PHONE_STATE_CONSULT == g_pCtrlCenter->QueryState()) && (2 == g_nTransTpye))
          { // 转接/咨询取回 modify by hzd 2016-11-18
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
            WriteLog("Agent is Talking state after the consult call reconnect.", INFO_LOG, RUN_LOG_LEVEL);
          }
          else if ((PHONE_STATE_CONSULT == g_pCtrlCenter->QueryState()) && (1 == g_nTransTpye))
          { // 转接/咨询后处理 add by hzd 2016-12-1            
            g_pCtrlCenter->UpdateState(PHONE_STATE_AFTERTALK);
            WriteLog("Agent is AfterTalk state after the consult call.", INFO_LOG, RUN_LOG_LEVEL);
          }

          break;
        case CALL_TYPE_INTERNAL:
          // modify by hzd 2016-11-17
          if ((true == g_bListenFlag) || (PHONE_STATE_LISTEN == g_pCtrlCenter->QueryState()))
          {
            g_bListenFlag = false;
            EndMonitor();

            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_STOP;
            g_pCtrlCenter->UpdateState(PHONE_STATE_AFTERTALK);
            WriteLog("Agent is ACW state after the Internal call.", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_SERVICEEND);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ACW);
          }
          else
          {
            g_CallEndTime = CTime::GetCurrentTime();
            g_TimerType = TIMER_OPER_STOP;
            g_pCtrlCenter->UpdateState(PHONE_STATE_AFTERTALK);
            WriteLog("Agent is ACW state after the Internal call.", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_SERVICEEND);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ACW);
          }
          break;
        case CALL_TYPE_UNKNOWN:
          g_pCtrlCenter->UpdateState(PHONE_STATE_IDLE);
          break;
        }

        if (!g_bBargeinFlag && !g_bTpinFlag)
        {
          g_strConnID = "";
          g_strConsultConnID = "";
          g_bBargeinFlag = false;
          g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_HANGUP);
        }

        // 预约置忙处理
        if (true == g_bSetBusyFlag)
        {
          g_strBusyReason = "置忙";
          WriteLog("Agent is Busy State after this call.", INFO_LOG, RUN_LOG_LEVEL);
          g_pCtrlCenter->ExecuteOperation(OPER_SETBUSY, g_strBusyReason);
          g_pCtrlCenter->UpdateState(PHONE_STATE_BUSY);
          
        }
        break;

      case EventPartyChanged:
        TKVListFree(g_UserData);
        g_UserData = TKVListCreate();
        g_UserData = TKVListDup(event->UserData);


        g_strConnID = connid_to_str(event->ConnID);
        tmpStr = event->OtherDN;
        g_nCallType = (CallType)event->CallType;
        if (!tmpStr.IsEmpty())
        {
          g_strANI = event->OtherDN; //edit by wyh 2009-3-2
          g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
          //update user info,dispatch event
          g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_CALLTYPECHANGED);
        }
        else
        {
          g_pCtrlCenter->UpdateState(PHONE_STATE_CONFERENCE);
          g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_CONFERENCE, event->ThirdPartyDN);
        }


        tmpStr.Format("PartyChanged event! thisDN:%s otherDN:%s ThirdDN:%s ANI:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->ThirdPartyDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        break;

      case EventPartyAdded:
        {
          bool bIsMonitorFlag = false;
          CString tmpcid = connid_to_str(event->ConnID);
          if (g_strConnID == tmpcid)
          {
            bIsMonitorFlag = true;
          }
          g_strConnID = tmpcid;
          g_nCallType = (CallType)event->CallType;
          tmpStr.Format("PartyAdded event! thisDN:%s otherDN:%s ThirdDN:%s ANI:%s ConnID:%s CallType:%d",
            event->ThisDN, event->OtherDN, event->ThirdPartyDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
          WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);

          if (PHONE_STATE_HOLD == g_pCtrlCenter->QueryState())
          {
            WriteLog("Monitor agent after holding call!", INFO_LOG, RUN_LOG_LEVEL);
          }
          //add by hzd 2016-10-26 
          else if (g_bTpinFlag) 
          {
            g_bTpinFlag = true;
            g_pCtrlCenter->UpdateState(PHONE_STATE_TPIN);
            g_strANI = g_strANITPIN;
            WriteLog("Tpin ready to count time......", INFO_LOG, RUN_LOG_LEVEL);
            g_pCtrlCenter->StartTpinTimer();
          }
          //add by hzd 2016-10-26
          else{
            char *buf = new char[10];
            memset(buf, 0, 10);
            memcpy(buf, event->OtherDN, strlen(event->OtherDN));
            AfxBeginThread(DelayEvent, (LPVOID)buf, THREAD_PRIORITY_ABOVE_NORMAL, 0, NULL, NULL);
          }
        }
        break;
      case EventPartyDeleted:
        g_strConnID = connid_to_str(event->ConnID);
        if (g_bTpinFlag) g_strANI = g_strANITPIN;
        else g_strANI = event->ANI;

        tmpStr.Format("PartyDeleted event! thisDN:%s otherDN:%s ThirdDN:%s ANI:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->ThirdPartyDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        if (g_nLoginType == SUPERVISOR)
        {
          if (PHONE_STATE_LISTEN == g_pCtrlCenter->QueryState())
          {
            WriteLog("Cancel monitor when user hangup!", INFO_LOG, RUN_LOG_LEVEL);
            char dn[DN_LEN], mdn[DN_LEN];
            strcpy_s(dn, g_strAgentExt);
            strcpy_s(mdn, g_strMonitorAgentDN);
            int nRet = 0;

            if (0 >= (nRet = TCancelMonitoring(
              g_tserver,
              mdn,
              dn,
              NULL,
              NULL)))
            {
              ;
            }

            if (0 >= (nRet = TReleaseCall(
              g_tserver,
              dn,
              str_to_connid(""),
              NULL,
              NULL)))
            {
              ;
            }
          }
          else
          {
            g_strBeMonitorAgentID = "";
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_CONFERENCEEND, event->ThirdPartyDN);
          }
        }
        else if (g_nLoginType == AGENT && PHONE_STATE_BELISTEN != g_pCtrlCenter->QueryState())
        {
          if ((PHONE_STATE_TPIN ==  g_pCtrlCenter->QueryState()) && (TRUE == g_bTpinFlag))
          {
            g_bTpinFlag = false;
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_AFTERTPIN);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_CONFERENCEEND, event->ThirdPartyDN);	
            g_pCtrlCenter->EndTpinTimer();
            WriteLog("Tpin end ok! It's talking now!", INFO_LOG, RUN_LOG_LEVEL);
          }
          else
          { // 会议模式下,一方退出会议后处理 add by hzd 2016-12-1
            g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_ESTABLISHED);
            g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_CONFERENCEEND, event->ThirdPartyDN);	
            WriteLog("Conference end ok! It's talking now!", INFO_LOG, RUN_LOG_LEVEL);
          }
        }
        break;

      case EventDestinationBusy:

        break;

      case EventHeld:
        g_pCtrlCenter->UpdateState(PHONE_STATE_HOLD);
        tmpStr.Format("Held event! thisDN:%s otherDN:%s ANI:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_HELD);
        break;

      case EventRetrieved:
        g_strANI = event->OtherDN;
        g_pCtrlCenter->UpdateState(PHONE_STATE_TALKING);
        tmpStr.Format("Retrieved event! thisDN:%s otherDN:%s ANI:%s ConnID:%s CallType:%d",
          event->ThisDN, event->OtherDN, event->ANI, connid_to_str(event->ConnID), event->CallType);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_RETRIEVED);

        break;

      case EventAgentReady:
        g_TimerType = TIMER_OPER_INIT;
        g_pCtrlCenter->UpdateState(PHONE_STATE_IDLE);
        TKVListFree(g_UserData);
        g_UserData = TKVListCreate();
        WriteLog("Agent ready!", INFO_LOG, RUN_LOG_LEVEL);
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_AGENTIDLE);
        break;

      case EventAgentNotReady:
        if (PHONE_STATE_IDLE == g_pCtrlCenter->QueryState())
        {
          g_pCtrlCenter->UpdateState(PHONE_STATE_BUSY);
          WriteLog("Agent not ready!", INFO_LOG, RUN_LOG_LEVEL);
          g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_AGENTBUSY);
        }
        else if (PHONE_STATE_LISTEN == g_pCtrlCenter->QueryState())
        {
          //nothing to do
        }

        break;

      case EventRegistered:
        //			g_pCtrlCenter->UpdateState(PHONE_STATE_IDLE);
        tmpStr.Format("Register ok! DN:%s", event->ThisDN);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        break;

      case EventAgentLogin:
        g_pCtrlCenter->UpdateState(PHONE_STATE_LOGIN);
        tmpStr.Format("Login ok! AgentID:%s DN:%s", event->AgentID, event->ThisDN);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_LOGIN);

        break;

      case EventAgentLogout:
        tmpStr.Format("Logout ok! AgentID:%s DN:%s", event->AgentID, event->ThisDN);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        g_pCtrlCenter->UpdateState(PHONE_STATE_LOGOUT);
        g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_LOGOUT);
        break;

      case EventUnregistered:
        tmpStr.Format("Unregister ok! DN:%s", event->ThisDN);
        WriteLog(tmpStr, INFO_LOG, RUN_LOG_LEVEL);
        g_pCtrlCenter->UpdateState(PHONE_STATE_LOGOUT);
        break;
      }
    }
  }
  catch (COleException *e)
  {
    WriteLog("catch COleException e!\n", ERROR_LOG, RUN_LOG_LEVEL);
    e->Delete();
  }
}

int CGenesysInterface::Login(CString AgentID, CString Extension, CString AgentGroup, int LoginType)
{//签入
  if (!g_bConnectTServerOK)
    return FAIL;
  char ACD[DN_LEN];
  char RegDN[DN_LEN], RegAgtID[DN_LEN];
  g_strAgentGroup = AgentGroup;
  g_strAgentID = AgentID;
  g_strAgentExt = Extension;
  strcpy_s(ACD, g_strAgentGroup);
  strcpy_s(RegDN, g_strAgentExt);
  strcpy_s(RegAgtID, g_strAgentID);
  if (g_PBX == "ALCATEL")
  {

    TRegisterAddress(g_tserver, RegDN, ModeShare, RegisterDefault, AddressTypeDN, NULL);
    if (g_nLoginType)
    {
      TAgentLogin(g_tserver, ACD, RegDN, AgentTypeSupervisor, RegAgtID, NULL, AgentAutoIn, NULL, NULL);
    }
    else
      TAgentLogin(g_tserver, ACD, RegDN, AgentTypeAgent, RegAgtID, NULL, AgentManualIn, NULL, NULL);
  }
  else
  {
    TRegisterAddress(g_tserver, RegDN, ModeShare, RegisterDefault, AddressTypeDN, NULL);
    if (g_nLoginType)
      TAgentLogin(g_tserver, ACD, RegDN, AgentTypeSupervisor, RegAgtID, NULL, AgentAutoIn, NULL, NULL);
    else
      TAgentLogin(g_tserver, ACD, RegDN, AgentTypeAgent, RegAgtID, NULL, AgentManualIn, NULL, NULL);
  }
  return OK;
}

int CGenesysInterface::Logout()
{//签出
  if (!g_bConnectTServerOK)
    return FAIL;

  char RegDN[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(RegDN, g_strAgentExt);

  int nRet = 0;
  if (0 >= (nRet = TAgentLogout(
    g_tserver,
    NULL,
    RegDN,
    NULL,
    NULL)))
  {
    strErrMsg = "Error in  Logout!";
  }

  TUnregisterAddress(g_tserver, RegDN, RegisterDefault, NULL);

  return OK;
}


int CGenesysInterface::SetIdle()
{//置闲
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN], ACD[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(ACD, g_strAgentGroup);
  int nRet = 0;
  if (0 >= (nRet = TAgentSetReady(
    g_tserver,
    ACD,
    dn,
    AgentManualIn,
    NULL,
    NULL)))
  {
    strErrMsg = "Error in  SetReady!";
  }
  return OK;
}

int ChangeReasonToCode(CString busyReason)
{
  int nBusyCode = 0;
  if (busyReason.Compare("置忙") == 0)
    nBusyCode = 1;
  else if (busyReason.Compare("小休") == 0)
    nBusyCode = 1;
  else if (busyReason.Compare("会议") == 0)
    nBusyCode = 2;
  else if (busyReason.Compare("培训") == 0)
    nBusyCode = 3;
  return nBusyCode;
}

int CGenesysInterface::SetBusy(CString busyReason)
{//置忙
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN], ACD[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(ACD, g_strAgentGroup);
  int nRet = 0;
  TKVList *reasons = TKVListCreate();
  TKVListAddInt(reasons, "GCTI_NOT_READY_ACTIVATION", ChangeReasonToCode(busyReason));

  if (0 >= (nRet = TAgentSetNotReady(
    g_tserver,
    ACD,
    dn,
    AgentWalkAway,
    reasons,
    NULL)))
  {
    strErrMsg = "Error in  SetBusy!";
  }
  TKVListFree(reasons);
  return OK;
}


int CGenesysInterface::Answer()
{//摘机
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);

  CString tmpstr;
  tmpstr.Format("ready to answer,connid is %s", g_strConnID.GetString());
  WriteLog(tmpstr, INFO_LOG, DEBUG_LOG_LEVEL);
  int nRet = 0;
  if (0 >= (nRet = TAnswerCall(
    g_tserver,
    dn,
    str_to_connid(g_strConnID),
    NULL,
    NULL)))
  {
    strErrMsg = "Error in  Answer!";
  }

  return OK;
}

int CGenesysInterface::Hold()
{//保持
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  int nRet = 0;
  if (PHONE_STATE_BELISTEN == g_pCtrlCenter->QueryState())
  {
    KickoutMonitor();
  }

  if (0 >= (nRet = THoldCall(
    g_tserver,
    dn,
    str_to_connid(g_strConnID),
    NULL,
    NULL)))
  {
    strErrMsg = "Error in  Hold!";
  }
  return OK;
}

void CGenesysInterface::KickoutMonitor()
{
  if (!g_bConnectTServerOK)
    return;
  EndMonitor();
}

int CGenesysInterface::ForceLogout(CString AgentDN)
{//强制签出
  if (!g_bConnectTServerOK && AgentDN.IsEmpty())
    return FAIL;

  char RegDN[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(RegDN, AgentDN);
  TRegisterAddress(g_tserver, RegDN, ModeShare, RegisterDefault, AddressTypeDN, NULL);


  int nRet = 0;
  if (0 >= (nRet = TAgentLogout(
    g_tserver,
    NULL,
    RegDN,
    NULL,
    NULL)))
  {
    strErrMsg = "Error in  ForceLogout!";
  }


  TUnregisterAddress(g_tserver, RegDN, RegisterDefault, NULL);
  return OK;
}

int CGenesysInterface::Retrieve()
{//恢复
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  int nRet = 0;
  if (0 >= (nRet = TRetrieveCall(
    g_tserver,
    dn,
    str_to_connid(g_strConnID),
    NULL,
    NULL)))
  {
    strErrMsg = "Error in  Hold!";
  }
  return OK;
}

int CGenesysInterface::Hangup()
{//挂机
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN], mdn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(mdn, g_strMonitorAgentDN);

  int nRet = 0;
  CString tmpstr;

  CString connid = g_strConnID;

  int state = g_pCtrlCenter->QueryState();

  if (PHONE_STATE_CONFERENCE == g_pCtrlCenter->QueryState() || PHONE_STATE_ANSWER_CONSULT == g_pCtrlCenter->QueryState())
  {
    if (0 >= (nRet = TDeleteFromConference(
      g_tserver,
      dn,
      str_to_connid(connid),
      dn,
      NULL,
      NULL)))
    {
      strErrMsg = "Error in  Release!";
    }
  }
  else if (PHONE_STATE_DIALING == g_pCtrlCenter->QueryState() && !g_strConsultConnID.IsEmpty())
  {
    if (0 >= (nRet = TReleaseCall(
      g_tserver,
      dn,
      str_to_connid(g_strConsultConnID),
      NULL,
      NULL)))
    {
      strErrMsg = "Error in  Release!";
    }
  }
  else if (PHONE_STATE_LISTEN == g_pCtrlCenter->QueryState())
  {
    // 监听状态下,发送挂机消息不生效
    if (0 >= (nRet = TCancelMonitoring(
      g_tserver,
      dn,
      mdn,
      NULL,
      NULL)))
    {
      strErrMsg = "Error in  TCancelMonitoring!";
    }
  }
  // add by hzd 2016-11-18
  else if (2 == g_nTransTpye)
  {
    if (0 >= (nRet = TReleaseCall(
      g_tserver,
      dn,
      str_to_connid(g_strOriConnID),
      NULL,
      NULL)))
    {
      strErrMsg = "Error in  Release!";
    }
    g_nTransTpye = 0;
    g_strOriConnID = "";
  }
  else{    
    if (0 >= (nRet = TReleaseCall(
      g_tserver,
      dn,
      str_to_connid(connid),
      NULL,
      NULL)))
    {
      strErrMsg = "Error in  Release!";
    }
  }

  tmpstr.Format("ready to hangup,connid is %s", connid.GetString());
  WriteLog(tmpstr, INFO_LOG, DEBUG_LOG_LEVEL);

  return OK;
}

int CGenesysInterface::DialNum(CString telnum)
{//拨号
  if (!g_bConnectTServerOK)
    return FAIL;
  char dest[100], dn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dest, telnum);
  strcpy_s(dn, g_strAgentExt);
  int nRet = 0;


  if (0 >= (nRet = TMakeCall(
    g_tserver,
    dn,
    dest,
    NULL,
    MakeCallRegular,
    NULL,
    NULL,
    NULL
    )))
  {
    strErrMsg = "Error in Dial!";
  }
  return OK;
}


int CGenesysInterface::Reconnect()
{//取回
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  int nRet = 0;

  g_bTransFlag = false;
  if (1 == g_nTransTpye)
  {
    g_strConnID = g_strOriConnID;
    if (0 >= (nRet = TReconnectCall(
      g_tserver,
      dn,
      str_to_connid(g_strConnID),
      str_to_connid(g_strConsultConnID),
      NULL,
      NULL
      )))
    {
      strErrMsg = "Error in reconnect!";
    }
    g_nTransTpye = 2;
  }

  return OK;
}


int CGenesysInterface::Conference()
{//会议
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  int nRet = 0;

  if (0 >= (nRet = TCompleteConference(g_tserver,
    dn,
    str_to_connid(g_strConnID),
    str_to_connid(g_strConsultConnID),
    NULL,
    NULL)))
  {
    strErrMsg = "Error in Conference!";
  }
  return OK;
}

int CGenesysInterface::Transfer(CString telnum)
{//转接
  if (!g_bConnectTServerOK) return FAIL;
  char dn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  int nRet = 0;
  if (2 == g_nTransTpye) g_strConnID = g_strOriConnID;
  g_nTransTpye = 1;

  if (telnum.IsEmpty())
  {
    if (0 >= (nRet = TCompleteTransfer(g_tserver,
      dn,
      str_to_connid(g_strConnID),
      str_to_connid(g_strConsultConnID),
      NULL,
      NULL)))
    {
      strErrMsg = "Error in transfer!";
    }
  }
  else
  {
    g_bTransFlag = true;
    Consult(telnum);
  }

  return OK;
}

int CGenesysInterface::SingleStepTransfer(CString telnum)
{//单步转接
  if (!g_bConnectTServerOK)
    return FAIL;
  char dn[DN_LEN], dest[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(dest, telnum);
  int nRet = 0;

  if (PHONE_STATE_BELISTEN == g_pCtrlCenter->QueryState())
  {
    KickoutMonitor();
  }

  if (0 >= (nRet = TSingleStepTransfer(g_tserver,
    dn,
    str_to_connid(g_strConnID),
    dest,
    NULL,
    NULL,
    NULL,
    NULL)))
  {
    strErrMsg = "Error in SingleStepTransfer!";
  }
  return OK;
}

int CGenesysInterface::ConferenceTPin(CString telnum)
{//TPIN
  if (!g_bConnectTServerOK)
    return FAIL;

  g_bTpinFlag = true;
  // 调用SingleStepConference 
  //SingleStepTransfer(telnum);
  if (!g_bConnectTServerOK) return FAIL;
  char dn[DN_LEN], dest[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(dest, telnum);

  //if (PHONE_STATE_BELISTEN == g_pCtrlCenter->QueryState()) KickoutMonitor();

  TKVList *ext = TKVListCreate();
  TKVListAddInt(ext, "GCTI_PARTICIPATION_TYPE", 1);
  int nRet = 0;
  if (0 >= (nRet = TSingleStepConference(
    g_tserver,
    dn,
    str_to_connid(g_strConnID),
    dest,
    NULL,
    NULL,
    NULL,
    ext)))
  {
    strErrMsg = "Error in  Consult!";
  }
  if (0 >= (nRet = TListenDisconnect(
    g_tserver,
    dn,
    dn,
    str_to_connid(g_strConnID),
    NULL,
    NULL
    )))
  {
    strErrMsg = "Error in  Consult!";
  }
  TKVListFree(ext);
  return OK;
}

int CGenesysInterface::Consult(CString telnum)
{//咨询
  if (!g_bConnectTServerOK) return FAIL;
  char dn[DN_LEN], dest[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(dest, telnum);

  if (2 == g_nTransTpye) g_strConnID = g_strOriConnID;
  g_nTransTpye = 1;

  if (PHONE_STATE_BELISTEN == g_pCtrlCenter->QueryState())
  {
    KickoutMonitor();
  }

  int nRet = 0;
  if (0 >= (nRet = TInitiateConference(
    g_tserver,
    dn,
    str_to_connid(g_strConnID),
    dest,
    NULL,
    NULL,
    NULL,
    NULL)))
  {
    strErrMsg = "Error in  Consult!";
  }
  return OK;
}

int CGenesysInterface::SetSyncData(CString label, CString value)
{//设置随路数据
  if (!g_bConnectTServerOK)
    return FAIL;

  CString strGetData = "";
  int intNum = 0;
  while (strGetData != value && intNum < RETRY_TIMES)
  {
    ::Sleep(100);
    intNum = intNum + 1;

    CString strKey = label;
    CString strValue = value;
    char key[300], value[3000], dn[DN_LEN];
    int nRet;
    memset(key, 0x00, sizeof(key));
    memset(value, 0x00, sizeof(value));
    memset(dn, 0x00, sizeof(dn));
    strcpy_s(key, strKey);
    strcpy_s(value, strValue);
    strcpy_s(dn, g_strAgentExt);
    TKVList *ud = TKVListCreate();
    if (0 < (nRet = TKVListAddString(ud, key, value)))
    {
      if (!ISConnEmpty(str_to_connid(g_strConnID)))
        nRet = TUpdateUserData(g_tserver, dn, str_to_connid(g_strConnID), ud);
    }
    TKVListFree(ud);

    strGetData = GetSyncData(label);
  }
  if (strGetData != value)
    return FAIL;

  return OK;
}

int CGenesysInterface::SetSyncData(CString kv)
{//设置多个随路数据
  if (!g_bConnectTServerOK)
    return FAIL;

  CString tmpstr = SearchStr(kv + "|", '|', 0);
  int i = 0;
  char dn[DN_LEN];
  strcpy_s(dn, g_strAgentExt);
  TKVList *ud = TKVListCreate();
  while (!tmpstr.IsEmpty())
  {
    CString key = SearchStr(tmpstr + ",", ',', 0);
    CString value = SearchStr(tmpstr + ",", ',', 1);

    if (0 < TKVListAddString(ud, key, value))
    {

    }

    i++;
    tmpstr = SearchStr(kv + "|", '|', i);
  }

  if (!ISConnEmpty(str_to_connid(g_strConnID)))
    TUpdateUserData(g_tserver, dn, str_to_connid(g_strConnID), ud);
  TKVListFree(ud);

  return OK;
}

int CGenesysInterface::QueryAgentStatus(CString AgentID)
{//查询坐询状态，IDLE或BUSY
  if (!g_bConnectTServerOK)
    return FAIL;
  char agtid[10];
  strcpy_s(agtid, AgentID);
  TQueryAddress(g_tserver, NULL, agtid, AddressTypeDN, AddressInfoAgentStatus, NULL);
  return OK;
}

int CGenesysInterface::QueryAgentStatusByDN(CString Telnum)
{//  查询坐席信息
  if(!g_bConnectTServerOK) return FAIL;
  char telnum[DN_LEN];
  strcpy_s(telnum, Telnum);
  TQueryAddress(g_tserver, telnum,NULL,AddressTypeDN, AddressInfoAgentStatus, NULL);
  return OK;
}

int CGenesysInterface::QueryCallStatus(CString AgentID)
{//查询座席分机上是否有通话
  if (!g_bConnectTServerOK)
    return FAIL;
  char agtid[10];
  strcpy_s(agtid, AgentID);
  TQueryAddress(g_tserver, NULL, agtid, AddressTypeDN, AddressInfoDNStatus, NULL);
  return OK;
}

CString CGenesysInterface::GetSyncData(CString label)
{//读随路数据
  if (!g_bConnectTServerOK)
    return "";

  CString value = "";
  CString RetValue = "";
  CString strLabel;
  char Key[100];
  // T-Server下无法获取CallUUID,只能通过'GSIP_REC_FN'来截取CallUUID
  if (!label.Compare("CallUUID")) strLabel = "GSIP_REC_FN";
  else strLabel = label;
  strcpy_s(Key, strLabel);

  if (!ISConnEmpty(str_to_connid(g_strConnID)) && g_UserData)
  {
    value = TKVListGetStringValue(g_UserData, Key, NULL);
    // 		if(value.IsEmpty())
    // 		{
    // 			int n=-1;
    // 			n=TKVListGetIntValue(g_UserData, Key, NULL);
    // 			if(-1!=n)
    // 			{
    // 				value.Format("%d",n);
    // 			}
    // 		}
  }

  //获取到GSIP_REC_FN后,截取前32位为CallUUID modify by hzd 2016-11-14
  if (!strLabel.Compare("GSIP_REC_FN")) RetValue = value.Left(value.Find("_", 0));
  else RetValue = value;

  return RetValue;
}

int CGenesysInterface::Listen(CString AgentDN)
{//监听

  if (!g_bConnectTServerOK)
    return FAIL;
  if (SUPERVISOR != g_nLoginType)
    return FAIL;
  char dn[DN_LEN], dest[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(dest, AgentDN);
  g_strBeMonitorAgentID = AgentDN;

  g_bBargeinFlag = false;
  g_bListenFlag = true;
  int nRet = 0;

  //if (0 >= (nRet = TMonitorNextCall(
  //  g_tserver,
  //  dn,
  //  dest,
  //  MonitorAllCalls,
  //  NULL,
  //  NULL)))
  //{
  //  strErrMsg = "Error in  TMonitorNextCall!";
  //}
  QueryAgentStatusByDN(dest);
  TKVList *ext = TKVListCreate();
  TKVListAddInt(ext, "GCTI_PARTICIPATION_TYPE", 1);
  if (0 >= (nRet = TSingleStepConference(
    g_tserver, 
    dn, 
    str_to_connid(g_strConnID),
    dest,
    NULL,
    NULL,
    NULL,
    ext)))
  {
    strErrMsg = "Error in TSingleStepConference!";
  }
  nRet = 0;
  if (0 >= (nRet = TSetMuteOn(
    g_tserver,
    dn,
    str_to_connid(g_strConnID),
    NULL,
    NULL)))
  {
    strErrMsg = "Error in TSetMuteOn!";
  }

  return OK;
}

int CGenesysInterface::BargeIn(CString AgentDN)
{//强插
  if (!g_bConnectTServerOK)
    return FAIL;
  if (SUPERVISOR != g_nLoginType)
    return FAIL;

  char dn[DN_LEN], dest[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(dest, AgentDN);

  this->Hangup();

  g_bBargeinFlag = true;
  g_bListenFlag = false;

  TKVList *ext = TKVListCreate();
  TKVListAddInt(ext, "GCTI_PARTICIPATION_TYPE", 1);
  int nRet = 0;
  if (0 >= (nRet = TSingleStepConference(
    g_tserver,
    dn,
    str_to_connid("0000000000000000"),
    dest,
    NULL,
    NULL,
    NULL,
    ext)))
  {
    strErrMsg = "Error in  Bargein!";
  }

  TKVListFree(ext);

  return OK;
}

int CGenesysInterface::ForceBreak(CString AgentDN)
{//强拆
  if (!g_bConnectTServerOK)
    return FAIL;
  if (SUPERVISOR != g_nLoginType)
    return FAIL;

  char dn[DN_LEN], dest[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(dest, AgentDN);

  int nRet = 0;
  if (0 >= (nRet = TDeleteFromConference(
    g_tserver,
    dn,
    str_to_connid(g_strConnID),
    dest,
    NULL,
    NULL)))
  {
    strErrMsg = "Error in  ForceBreak!";
  }
  return OK;
}

int CGenesysInterface::OnEvent(CString key, CString info)
{//事件
  return OK;
}

int CGenesysInterface::OnAgentStateChange(int state)
{//状态变化
  return OK;
}

bool CGenesysInterface::ISConnEmpty(TConnectionID conn)
{//判断CONNID是否为空
  CString strConn = connid_to_str(conn);
  if (strConn == "0000000000000000")
    return true;
  return false;
}

int CGenesysInterface::UpdateGroupInfo(CString groupname)
{//更新座席组状态信息
  //getgroup
  if (!g_bConnectTServerOK)
    return FAIL;

  CAgentGroup ag = g_AgentGroupList.GetGroup(groupname);
  g_QueryGroupName = groupname;
  for (int i = 0; i < ag.agtList.GetSize(); i++)
  {
    CAgentInfo agtinfo = ag.agtList.GetAt(i);
    if (agtinfo.AgentID != g_strAgentID && !agtinfo.AgentID.IsEmpty())
    {
      char agtid[10];
      strcpy_s(agtid, agtinfo.AgentID);
      TQueryAddress(g_tserver, NULL, agtid, AddressTypeDN, AddressInfoAgentStatus, NULL);
      TQueryAddress(g_tserver, NULL, agtid, AddressTypeDN, AddressInfoDNStatus, NULL);
      g_GroupCount++;
      g_GroupCount++;
    }
  }

  if (0 == g_GroupCount)
    return OK;

  //wait for event
  if (WAIT_OBJECT_0 == ::WaitForSingleObject(g_evtUpdateHandle, UPDATE_GROUP_OVERTIME))
  {
    //return in time
    WriteLog("Query Agent group info successfully!", INFO_LOG, RUN_LOG_LEVEL);
  }
  else
  {
    //overtime
    WriteLog("Query Agent group info overtime!", INFO_LOG, RUN_LOG_LEVEL);
  }

  g_GroupCount = 0;

  return OK;
}

void EndMonitor()
{
  char dn[DN_LEN], mdn[DN_LEN];
  CString strErrMsg = "";
  strcpy_s(dn, g_strAgentExt);
  strcpy_s(mdn, g_strMonitorAgentDN);
  int nRet = 0;
  if (PHONE_STATE_BELISTEN == g_pCtrlCenter->QueryState())
  {

    TRegisterAddress(g_tserver, mdn, ModeShare, RegisterDefault, AddressTypeDN, NULL);

    if (0 >= (nRet = TCancelMonitoring(
      g_tserver,
      mdn,
      dn,
      NULL,
      NULL)))
    {
      strErrMsg = "Error in cancel monitor!";
    }

    if (0 >= (nRet = TReleaseCall(
      g_tserver,
      mdn,
      str_to_connid(""),
      NULL,
      NULL)))
    {
      strErrMsg = "Error in  Release!";
    }
    TUnregisterAddress(g_tserver, mdn, RegisterDefault, NULL);
    CString tmpstr;
    tmpstr.Format("Stop monitor DN:%s ok!", g_strMonitorAgentDN.GetString());
    WriteLog(tmpstr, INFO_LOG, RUN_LOG_LEVEL);
    g_strMonitorAgentDN = "";
  }
}


UINT DelayEvent(LPVOID lParam)
{//延迟事件
  char *buf = (char *)lParam;
  while (true)
  {
    if (WAIT_OBJECT_0 == ::WaitForSingleObject(g_evtWaitHandle, DELAY_EVENT_OVERTIME))
    {
      WriteLog("EventPartyAdded is omited!", INFO_LOG, RUN_LOG_LEVEL);
      g_pCtrlCenter->UpdateState(PHONE_STATE_BELISTEN);
      ::ResetEvent(g_evtWaitHandle);
      break;
    }
    else
    {
      CString tmpstr;
      tmpstr.Format("EventPartyAdded work. it's in bargein conference! Ext:%s!", buf);
      WriteLog(tmpstr, INFO_LOG, RUN_LOG_LEVEL);
      g_pCtrlCenter->DispatchEvent(DISPATCH_EVENT_CONFERENCE, buf);
      g_pCtrlCenter->UpdateState(PHONE_STATE_CONFERENCE);
      break;
    }
  }
  delete buf;
  return OK;
}

UINT DelayAnswer(LPVOID lParam)
{//延迟摘机
  Sleep(1800);
  g_pCtrlCenter->ExecuteOperation(OPER_ANSWER);
  return OK;
}