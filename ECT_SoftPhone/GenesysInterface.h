// GenesysInterface.h: interface for the CGenesysInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENESYSINTERFACE_H__4DE8FC64_BEF7_44B4_9988_3A06A77067E9__INCLUDED_)
#define AFX_GENESYSINTERFACE_H__4DE8FC64_BEF7_44B4_9988_3A06A77067E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CTIInterface.h"
//#include "AgentFormDlg.h"

class CGenesysInterface : public CCTIInterface
{
public:
  CGenesysInterface();
  virtual ~CGenesysInterface();
public:

  int Init();
  int Exit();
  int ConnectCTIServer(CString HostIP,long Port);
  void ReConnectTServer();

  //座席功能
  int Login(CString AgentID,CString Extension,CString AgentGroup,int LoginType=AGENT);//签入
  int Logout();//签出
  int SetIdle();//置闲
  int SetBusy(CString busyReason);//置忙
  int Answer();//摘机
  int Hold();//保持
  int Retrieve();//恢复
  int Reconnect();//取回
  int Hangup();//挂机
  int DialNum(CString telnum);//外拨
  int Consult(CString telnum);//咨询
  int Transfer(CString telnum);//转接
  int ConferenceTPin(CString telnum);//TPIN

  int SingleStepTransfer(CString telnum);

  int Conference();//会议
  int SetSyncData(CString label, CString value);//设置随路数据
  int SetSyncData(CString kv);//设置多个随路数据
  CString GetSyncData(CString label);//得到随路数据

  //班长席功能
  int Listen(CString AgentDN);//监听
  int ForceBreak(CString AgentDN);//强拆
  int BargeIn(CString AgentDN);//强插
  int ForceLogout(CString AgentDN);//强制签出

  //事件
  int OnEvent(CString key,CString info);
  int OnAgentStateChange(int state);

  int UpdateGroupInfo(CString groupname);
  int QueryAgentStatus(CString AgentID);
  int QueryAgentStatusByDN(CString telnum);   //通过电话号码查询坐席信息
  int QueryCallStatus(CString AgentID);

private:
  bool ISConnEmpty(TConnectionID conn);
  void KickoutMonitor();
};

#endif // !defined(AFX_GENESYSINTERFACE_H__4DE8FC64_BEF7_44B4_9988_3A06A77067E9__INCLUDED_)
