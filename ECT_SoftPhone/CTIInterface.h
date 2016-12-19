// CTIInterface.h: interface for the CCTIInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTIINTERFACE_H__C11F1AD2_5946_44C8_9898_96C080E45DD2__INCLUDED_)
#define AFX_CTIINTERFACE_H__C11F1AD2_5946_44C8_9898_96C080E45DD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CControlCenter;
class CCTIInterface  
{
public:
  CCTIInterface();
  virtual ~CCTIInterface();
private:
  CString m_AgentExt;
  CString m_AgentID;
  CString m_AgentGroup;
  CString m_PeriphID;
  int		m_State;
  CControlCenter  *m_pCC;
  bool	m_bConnectCTIOk;
  bool m_bLonginOK;

public:
  void SetCtrlCenterPtr(CControlCenter *pCC){m_pCC=pCC;};

  virtual bool IsCanBargein(CString ObjAgentID);//是否强插

  virtual int GetState(){return m_State;};
  virtual void SetState(int state);

  virtual int ConnectCTIServer(CString HostIP,long Port) = 0;//连接CTI

  virtual int Init() = 0;//初始化
  virtual int Exit() = 0;//退出

  //座席功能
  virtual int Login(CString AgentID,CString Extension,CString AgentGroup,int LoginType) = 0;//签入
  virtual int Logout() = 0;//签出
  virtual int SetIdle() = 0;//置闲
  virtual int SetBusy(CString busyReason) = 0;//置忙
  virtual int Answer() = 0;//摘机
  virtual int Hold() = 0;//保持
  virtual int Retrieve() = 0;//恢复
  virtual int Reconnect() = 0;//取回
  virtual int Hangup() = 0;//挂机
  virtual int DialNum(CString telnum) = 0;//外拨
  virtual int Consult(CString telnum) = 0;//咨询
  virtual int Transfer(CString telnum) = 0;//转接
  virtual int ConferenceTPin(CString telnum) = 0; //TPIN

  virtual int SingleStepTransfer(CString telnum) = 0;//单步会议

  virtual int Conference() = 0;//会议

  virtual int SetSyncData(CString label, CString value) = 0;//设置随路数据
  virtual int SetSyncData(CString kv) = 0;//设置多个随路数据
  virtual CString GetSyncData(CString label) = 0;//得到随路数据


  //班长席功能
  virtual int Listen(CString AgentDN) = 0;//监听
  virtual int ForceBreak(CString AgentDN) = 0;//强拆
  virtual int BargeIn(CString AgentDN) = 0;//强插

  virtual int ForceLogout(CString AgentDN);//强制签出



  virtual bool GetLoginOkFlag();//座席LOGIN的成功状态	
  virtual void SetLoginOkFlag(bool value);

  virtual bool GetSupervisorFlag();//座席是不是Supervisor身份	

  virtual int UpdateGroupInfo(CString groupname)=0;

  virtual int QueryAgentStatus(CString AgentID)=0;
  virtual int QueryCallStatus(CString AgentID)=0;

  //事件
  virtual int OnEvent(CString key,CString info) = 0;
  virtual int OnAgentStateChange(int state) = 0;

};

#endif // !defined(AFX_CTIINTERFACE_H__C11F1AD2_5946_44C8_9898_96C080E45DD2__INCLUDED_)
