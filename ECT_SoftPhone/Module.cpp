#include "stdafx.h"
#include "Module.h"
#include <sys/timeb.h>
#include "ControlCenter.h"
#include <afxinet.h>
#include ".\jsoncpp\include\json.h"

BOOL	g_bWriteLog = TRUE;//是否写日志
CString	g_LogPath = "C:\\SOFTPHONE_LOG";//日志路径
CFile	g_File;
LogLevel g_nLogLevel = DEBUG_LOG_LEVEL; //日志详细级别，1，2，3级， 详细程序渐增
BOOL  g_bCheckPassword = FALSE;//是否验证密码

bool g_bConnectTServerOK = false;	//CTI Server连接状态标志


CString g_strAgentID;                               //工号
CString g_strCallID;                                //CALLID FROM ivr
CString g_strBeMonitorAgentID;                      //被监控的工号
CString g_strMonitorAgentDN;	                      //监控者的分机
CString g_strAgentPwd;                              //密码
CString g_strAgentExt;                              //分机
CString g_strAgentGroup;                            //技能组
CallType g_nCallType;                               //呼叫类型             
CTime	g_CallBeginTime=CTime::GetCurrentTime();      //呼叫开始时间
CTime   g_CallEndTime=CTime::GetCurrentTime();      //呼叫结束时间
CTime	g_CurStatusBeginTime=CTime::GetCurrentTime(); //当前状态开始时间
CString g_strRouteSource;                           //路由发起点
CString g_strRouteDest;		                          //路由终结点
TimerOperType g_TimerType = TIMER_OPER_INIT;        //时间类型
CString g_strANI;                                   //主叫号码
CString g_strANITPIN;                               // TPIN原主叫号码
CString g_strDNIS;						                      //被叫号码
AgentLoginType     g_nLoginType=AGENT;              //签入类型
bool    g_bBargeinFlag = false;
bool    g_bTpinFlag = false;
bool	  g_bTransFlag = false;
bool	  g_bListenFlag = false;
int     g_nTransTpye = 0;         // 转接类型 0-未转接|1-转接中|2-转接取回
bool    g_bSetBusyFlag = false;   // 预约预约置忙标识
long	  g_nErrorCode = 0;
CString g_strErrorStr ;


long	g_nCTISvrType=0;                //CTI服务器类型 
CString	g_strCTISvrIp="127.0.0.1";	  //CTI服务器IP
long	g_strCTISvrPort=3000;	          //CTI服务器端口
CString	g_strCTISvrIpBak="127.0.0.1";	//备用CTI服务器IP
long	g_strCTISvrPortBak=3888;	      //备用CTI服务器端口

// add by hzd 2016-11-7
bool    g_strRecParaSetFlag = false;  //录音参数设置标识
CString g_strRecSvrIp = "127.0.0.1";  //录音服务器IP
long    g_strRecSvrPort = 8080;       //录音服务器端口
CString g_strRecUrlPath = "/api/va2/ops/contact-centers/"; //录音文件url路径
CString g_strRecCCID = "";            //录音数据库服务器认证标识
CString g_strRecUsrName = "";         //录音数据库服务器认证用户名
CString g_strRecPassWord = "";        //录音数据库服务器认证密码
CString g_strRecUrlFiles = "";        //录音url文件列表
CTime   g_timeRecEnd = CTime::GetCurrentTime(); //挂机录音结束时间
unsigned char * base64 = (unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
// add by hzd 2016-11-7

CString g_strConnID;                  //通话CONNID
CString g_strConsultConnID;           //咨询CONNID
CString g_strOriConnID;               // 转接或咨询时的原ConnID add by hzd 2016-11-18
TKVList *g_UserData=NULL;             //随路数据

CString g_PBX="ALCATEL";   //交换机类型
CString g_strBusyReason="置忙";   //置忙原因
CString g_strPasswordReason;   //验密原因
CString g_strBusyReasonList;//置忙原因列表
CString g_strAllAgents;

CControlCenter* g_pCtrlCenter;
CAgentGroupList g_AgentGroupList;

bool g_bReconnect=false;  //重连服务器

int  g_nReconnInterval=40;//重连间隔时间 单位：秒
bool g_bSysExit=false;  //系统退出标识

CString g_RecordIP = "192.168.1.31";//录音服务器的IP
UINT    g_RecordPort = 6666;//录音服务器的端口
CString g_RecordID;//录音流水号
char TMessageTypeNames[][64] = {
  "RequestRegisterClient",
  "RequestQueryServer",
  "RequestQueryAddress",
  "RequestRegisterAddress",
  "RequestUnregisterAddress",
  "RequestRegisterAll",
  "RequestUnregisterAll",
  "RequestSetInputMask",
  "RequestAgentLogin",
  "RequestAgentLogout",
  "RequestAgentReady",
  "RequestAgentNotReady",
  "RequestSetDNDOn",
  "RequestSetDNDOff",
  "RequestMakeCall",
  "RequestMakePredictiveCall",
  "RequestAnswerCall",
  "RequestReleaseCall",
  "RequestHoldCall",
  "RequestRetrieveCall",
  "RequestInitiateConference",
  "RequestCompleteConference",
  "RequestDeleteFromConference",
  "RequestInitiateTransfer",
  "RequestMuteTransfer",
  "RequestSingleStepTransfer",
  "RequestCompleteTransfer",
  "RequestMergeCalls",
  "RequestAlternateCall",
  "RequestReconnectCall",
  "RequestAttachUserData",
  "RequestUpdateUserData",
  "RequestDeleteUserData",
  "RequestDeletePair",
  "RequestCallForwardSet",
  "RequestCallForwardCancel",
  "RequestRouteCall",
  "RequestGiveMusicTreatment",
  "RequestGiveSilenceTreatment",
  "RequestGiveRingBackTreatment",
  "RequestLoginMailBox",
  "RequestLogoutMailBox",
  "RequestOpenVoiceFile",
  "RequestCloseVoiceFile",
  "RequestPlayVoiceFile",
  "RequestCollectDigits",
  "RequestSetMessageWaitingOn",
  "RequestSetMessageWaitingOff",
  "RequestDistributeUserEvent",
  "RequestDistributeEvent",

  "EventServerConnected",
  "EventServerDisconnected",
  "EventError",
  "EventRegistered",
  "EventUnregistered",
  "EventRegisteredAll",
  "EventUnregisteredAll",
  "EventQueued",
  "EventDiverted",
  "EventAbandoned",
  "EventRinging",
  "EventDialing",
  "EventNetworkReached",
  "EventDestinationBusy",
  "EventEstablished",
  "EventReleased",
  "EventHeld",
  "EventRetrieved",
  "EventPartyChanged",
  "EventPartyAdded",
  "EventPartyDeleted",
  "EventRouteRequest",
  "EventRouteUsed",
  "EventAgentLogin",
  "EventAgentLogout",
  "EventAgentReady",
  "EventAgentNotReady",
  "EventDNDOn",
  "EventDNDOff",
  "EventMailBoxLogin",
  "EventMailBoxLogout",
  "EventVoiceFileOpened",
  "EventVoiceFileClosed",
  "EventVoiceFileEndPlay",
  "EventDigitsCollected",
  "EventAttachedDataChanged",
  "EventOffHook",
  "EventOnHook",
  "EventForwardSet",
  "EventForwardCancel",
  "EventMessageWaitingOn",
  "EventMessageWaitingOff",
  "EventAddressInfo",
  "EventServerInfo",
  "EventLinkDisconnected",
  "EventLinkConnected",
  "EventUserEvent",

  "RequestSendDTMF",
  "EventDTMFSent",

  "EventResourceAllocated",
  "EventResourceFreed",

  "EventRemoteConnectionSuccess",
  "EventRemoteConnectionFailed",

  "RequestRedirectCall",
  "RequestListenDisconnect",
  "RequestListenReconnect",
  "EventListenDisconnected",
  "EventListenReconnected",
  "RequestQueryCall",
  "EventPartyInfo",
  "RequestClearCall",
  "RequestSetCallInfo",
  "EventCallInfoChanged",
  "RequestApplyTreatment",
  "EventTreatmentApplied",
  "EventTreatmentNotApplied",
  "EventTreatmentEnd",
  "EventHardwareError",
  "EventAgentAfterCallWork",
  "EventTreatmentRequired",
  "RequestSingleStepConference",
  "RequestQuerySwitch",
  "EventSwitchInfo",

  "RequestGetAccessNumber",
  "RequestCancelReqGetAccessNumber",
  "EventAnswerAccessNumber",
  "EventReqGetAccessNumberCanceled",

  "RequestReserveAgent",
  "EventAgentReserved",
  "RequestReserveAgentAndGetAccessNumber",

  "RequestAgentSetIdleReason",
  "EventAgentIdleReasonSet",

  "EventRestoreConnection",
  "EventPrimaryChanged",
  "RequestLostBackupConnection",
  "RequestSetDNInfo",

  "RequestQueryLocation",
  "EventLocationInfo",

  "EventACK",

  "RequestMonitorNextCall",
  "RequestCancelMonitoring",
  "EventMonitoringNextCall",
  "EventMonitoringCancelled",

  "RequestSetMuteOn",
  "RequestSetMuteOff",
  "EventMuteOn",
  "EventMuteOff",

  "EventDNOutOfService",
  "EventDNBackInService",

  "MessageIDMAX"

};


CString SearchStr(CString SourStr,char InterChar,int Position)
{
  CString TempStr,Tp;
  int Well_pos;
  int i;

  TempStr=SourStr;
  Tp="";
  i=0;

  do
  {
    Well_pos=TempStr.Find(InterChar);

    if(Well_pos!=-1)
    {
      Tp=TempStr.Mid(0,Well_pos); 
      TempStr=TempStr.Mid(Well_pos+1); 

      if(Position==i)
        break;

      i=i+1;
      Tp="";
    }
  }  
  while(Well_pos!=-1);

  return Tp;
}

bool OpenLog(CString filename)
{//打开日志文件
  try
  {
    CString fname = g_File.GetFilePath();
    if (fname!=filename)
    {
      // g_File 已声明为对象
      //if (g_File!=NULL)
      //{
      //	g_File.Close();
      //}
      ::CreateDirectory(g_LogPath,NULL); 
      CTime curTime = CTime::GetCurrentTime();
      CFile pFile;
      CString strPath;
      strPath.Format("%s\\ECT_SOFTPHONE_%s.log",g_LogPath.GetString(),curTime.Format("%Y%m%d"));

      g_File.Open(strPath,CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone | CFile::modeNoTruncate);
    }
    return true;
  }
  catch (CException* e)
  {
    delete e;
  }

  return false;
}


void WriteLog(CString logstr,int type,int Level)
{ //日志记录

  //type:INFO:   ERR:  DEBUG: SYSTEM: WARNNING:

  //要求：
  //LOG放的C 盘根下创建C:\SOFTPHONE_LOG目录，文件名：ECT_SOFTPHONE_20081119.LOG
  //日志格式如下：
  //[2008-09-12 18:23:46]--INFO:日志信息写的这里\n

  if(!g_bWriteLog) return;

  CString strPath = g_LogPath;
  try
  {
    CString retStr,tmpLog,typeStr;
    CTime curTime = CTime::GetCurrentTime();
    retStr += curTime.Format("%Y-%m-%d %H:%M:%S");		
    strPath.Format("%s\\ECT_SOFTPHONE_%s.log",g_LogPath.GetString(),curTime.Format("%Y%m%d").GetString());

    OpenLog(strPath);

    DWORD lengths = DWORD(g_File.GetLength());
    if(Level <= g_nLogLevel)
    {
      if(lengths <= 20 * 1024 * 1024)
      {
        switch(type)
        {
        case SYSTEM_LOG:
          typeStr = "SYSTEM:";
          break;
        case INFO_LOG:
          typeStr = "INFO:";
          break;
        case ERROR_LOG:
          typeStr = "ERROR:";
          break;
        case WARNING_LOG:
          typeStr = "WARNING:";
          break;
        }
        g_File.SeekToEnd();
        tmpLog.Format("[%s]--%s%s\r\n",retStr.GetString(),typeStr.GetString(),logstr.GetString());
        g_File.Write(tmpLog.GetBuffer(tmpLog.GetLength()),tmpLog.GetLength());
      }
      else
      {
        g_File.Close();
        ::DeleteFile(strPath);
      }
    }	 	 
    else
      return;
  }
  catch(CFileException *e)
  {
    if(e->m_cause == CFileException::genericException)
      AfxMessageBox("创建异常,不能创建日志!");
    e->Delete();    
  }
  return;


}

void RecordID()
{
  /*
  SOCKET m_socket = socket(AF_INET,SOCK_STREAM,0);//add by 09 08 03

  struct sockaddr_in serveraddr; 

  serveraddr.sin_family       = AF_INET;
  serveraddr.sin_port         = htons(g_RecordPort);
  serveraddr.sin_addr.s_addr  = inet_addr(g_RecordIP);
  int suc = connect(m_socket,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

  if(suc == 0)
  {
  char buf[200];
  CString	recordStr = "0026ReqINum," + g_strAgentExt + "," + g_strAgentID +",0,0,in";
  char sData[200];  
  memset(sData,0,sizeof(sData));
  strcpy_s(sData,recordStr);
  send(m_socket,sData,sizeof(sData),0);
  memset(buf,0,sizeof(buf));
  recv(m_socket,buf,200,0);
  CString tmpstr = buf;
  g_RecordID = tmpstr.Left(4);

  }
  //AfxMessageBox(g_RecordID);
  closesocket(m_socket);
  */
}

// 获取录音url文件列表 add by hzd 2016-11-7
void GetRecFiles(CString CallUUID)
{
  CString temp;
  CString jsongst;
  CTime   curTime;
  // 录音结束后时长
  CTimeSpan spanTime;
  // 录音结束时长 单位:秒
  int nspan;

  curTime = CTime::GetCurrentTime();
  spanTime = curTime - g_timeRecEnd;
  nspan = spanTime.GetSeconds() + spanTime.GetMinutes()*60 +spanTime.GetHours()*3600;
  if (GET_REC_INFO_WAIT_TIME > nspan)
  {
    AfxMessageBox(_T("录音文件还没有生成,请稍后再试!!"));
    return;
  }
  if(g_pCtrlCenter->QueryState() == PHONE_STATE_TALKING)
  {
    AfxMessageBox(_T("座席还在工作中,无法使用该功能!"));
    return;
  }
  temp = HttpGetResponse(CallUUID);
  g_strRecUrlFiles = GetFileList(temp);
  if (g_strRecUrlFiles.IsEmpty())
  {
    AfxMessageBox("获取录音URL列表为空!");
  }
}

// 获取GIR系统录音文件信息JSON add by hzd 2016-11-7
CString HttpGetResponse(CString CallUUID)
{
  CString Response = "";
  CString ServerPort;
  CInternetSession Session;
  CHttpConnection* pConnection = NULL;
  CString strObjectName;
  CHttpFile* pFile = NULL;
  DWORD dwServiceType, dwret;
  unsigned short nPort;
  LPCTSTR LPstrAuthorization;

  CString UsrnamePassword = g_strRecUsrName + ":" + g_strRecPassWord;
  CString base64UP = base64encode(UsrnamePassword, UsrnamePassword.GetLength());
  CString strAuthorization = "Authorization: Basic " + base64UP;
  LPstrAuthorization = strAuthorization.GetBuffer();

  ServerPort.Format(_T("%ld"), g_strRecSvrPort);
  CString url = "http://" + g_strRecSvrIp + ":" + ServerPort + g_strRecUrlPath + g_strRecCCID + "/recordings/" + CallUUID;

  if (!AfxParseURL(url, dwServiceType, g_strRecSvrIp, strObjectName, nPort))
  {
    AfxMessageBox("URL Error!");
    return Response;
  }  

  // 设置超时 单位 毫秒
  Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);
  Session.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 5000);
  Session.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 5000);
  Session.SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT, 5000);
  Session.SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, 5000);
  Session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

  try
  {
    // 连接至服务器
    pConnection = Session.GetHttpConnection(g_strRecSvrIp, nPort);

    // 打开http请求
    pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObjectName, url, 1, 0, 0, INTERNET_FLAG_NO_COOKIES);

    // 添加http头
    //pFile->AddRequestHeaders(strAuthorization, HTTP_ADDREQ_FLAG_REPLACE);
    //pFile->AddRequestHeaders(strAuthorization, HTTP_ADDREQ_FLAG_REPLACE);
    pFile->AddRequestHeaders(strAuthorization, HTTP_ADDREQ_FLAG_ADD);
    //pFile->AddRequestHeaders(strAuthorization, HTTP_ADDREQ_FLAG_ADD_IF_NEW);
    //pFile->AddRequestHeaders(strAuthorization, HTTP_ADDREQ_FLAG_COALESCE);

    // 发送http请求
    pFile->SendRequest();

    // 获取http请求状态
    pFile->QueryInfoStatusCode(dwret);
    // 获取http返回信息
    if (HTTP_STATUS_OK == dwret) pFile->ReadString(Response);
    else
    {
      CString tmpstr;
      tmpstr.Format("Http Request info return:[%d]", dwret);
      WriteLog(tmpstr, ERROR_LOG, RUN_LOG_LEVEL);
    }
  }
  catch (CException* e)
  {
    throw e;
  }

  // 关闭文件
  if (NULL != pFile)
  {
    pFile->Close();
    delete pFile;
    pFile = 0;
  }

  // 断开连接
  if (NULL != pConnection)
  {
    pConnection->Close();
    delete pConnection;
    pConnection = 0;
  }

  // 关闭会话
  Session.Close();

  return Response;
}

// 获取录音文件列表JSON add by hzd 2016-11-7
CString GetFileList(CString info)
{
  CString FileList = "";
  Json::Reader reader;
  Json::Value root;
  Json::Value infoOut;
  Json::FastWriter infoOutPut;
  std::string jsonstr;
  CString output;

  jsonstr = info.GetBuffer();
  if (reader.parse(jsonstr, root))
  {
    Json::Value recording = root["recording"];
    Json::Value mediaFiles = recording["mediaFiles"];
    if (!mediaFiles.isNull() && mediaFiles.isArray())
    {
      for (int i = 0; i < int(mediaFiles.size()); i++)
      {

        Json::Value originalMediaDescriptor = mediaFiles[i]["originalMediaDescriptor"];
        Json::Value path = originalMediaDescriptor["path"];
        infoOut["RecFile"].append(path);        
      }
    }    
    FileList = infoOutPut.write(infoOut).c_str();
  }
  return FileList;
}

// base64转码 add by hzd 2016-11-7
CString base64encode(CString src, int srclen)
{
  int n, buflen, i, j;
  static unsigned char *dst;
  CString buf = src;
  buflen = n = srclen;
  dst = (unsigned char*)malloc(buflen / 3 * 4 + 3);
  memset(dst, 0, buflen / 3 * 4 + 3);
  for (i = 0, j = 0; i <= buflen - 3; i += 3, j += 4)
  {
    dst[j] = (buf[i] & 0xFC) >> 2;
    dst[j + 1] = ((buf[i] & 0x03) << 4) + ((buf[i + 1] & 0xF0) >> 4);
    dst[j + 2] = ((buf[i + 1] & 0x0F) << 2) + ((buf[i + 2] & 0xC0) >> 6);
    dst[j + 3] = buf[i + 2] & 0x3F;
  }
  if (n % 3 == 1)
  {
    dst[j] = (buf[i] & 0xFC) >> 2;
    dst[j + 1] = ((buf[i] & 0x03) << 4);
    dst[j + 2] = 64;
    dst[j + 3] = 64;
    j += 4;
  }
  else if (n % 3 == 2)
  {
    dst[j] = (buf[i] & 0xFC) >> 2;
    dst[j + 1] = ((buf[i] & 0x03) << 4) + ((buf[i + 1] & 0xF0) >> 4);
    dst[j + 2] = ((buf[i + 1] & 0x0F) << 2);
    dst[j + 3] = 64;
    j += 4;
  }
  for (i = 0; i < j; i++) /* map 6 bit value to base64 ASCII character */
    dst[i] = base64[(int)dst[i]];
  dst[j] = 0;
  return CString(dst);
}
