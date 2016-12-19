// ControlCenter.h: interface for the CControlCenter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLCENTER_H__075B7BE3_FCE1_4BD9_992D_E819C76551CA__INCLUDED_)
#define AFX_CONTROLCENTER_H__075B7BE3_FCE1_4BD9_992D_E819C76551CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GenesysInterface.h"
#include "CTIInterface.h"
#include "StateMachine.h"

class CECT_SoftPhoneCtrl;
class CGenesysInterface;
class CControlCenter  
{
public:
  void EndTpinTimer();
  void StartTpinTimer();
  void ConfigSoftPhone(CString AgtID,CString AgtExt,CString AgtGroup,AgentLoginType loginType);
  void ConfigCTIServer(CString svrIP,long svrPort,long svrType,CString pbx);
  // add by hzd 2016-11-7 增加配置录音服务器参数
  void ConfigRECServer(CString svrIP, long svrPort, CString urlPath, CString ccid, CString usrname, CString passWord);
  int  Start();
  void Stop();
  void SetHwnd(HWND hwnd);
  void NotifyStateChange(int state);  

  CString ExecuteOperation(int optype,CString param1="",CString param2="");
  int UpdateState(int state);
  int UpdateState(int state,CString connID);
  int QueryState();
  void DispatchEvent(DispatchEventType EvtType,CString param="");
  void DispatchEvent(DispatchEventType EvtType,char * param);

  CControlCenter();
  virtual ~CControlCenter();

protected:
  HWND m_UIHwnd;
  CCTIInterface* m_pPhone; 
  CStateMachine m_stateMachine;

private:
  bool m_bStartFlag;
};

#endif // !defined(AFX_CONTROLCENTER_H__075B7BE3_FCE1_4BD9_992D_E819C76551CA__INCLUDED_)
