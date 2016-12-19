#if !defined(AFX_ECT_SOFTPHONECTL_H__4F3912A5_290F_438C_8EC3_52A21851AA65__INCLUDED_)
#define AFX_ECT_SOFTPHONECTL_H__4F3912A5_290F_438C_8EC3_52A21851AA65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ECT_SoftPhoneCtl.h : Declaration of the CECT_SoftPhoneCtrl ActiveX Control class.
#include "AgentFormDlg.h"

//add by caihua
#include <objsafe.h>

/////////////////////////////////////////////////////////////////////////////
// CECT_SoftPhoneCtrl : See ECT_SoftPhoneCtl.cpp for implementation.
class CAgentFormDlg;
class CECT_SoftPhoneCtrl : public COleControl
{
  DECLARE_DYNCREATE(CECT_SoftPhoneCtrl)

  // Constructor
public:
  CECT_SoftPhoneCtrl();
  CAgentFormDlg *m_pAgentDlg;
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CECT_SoftPhoneCtrl)
public:
  virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
  virtual void DoPropExchange(CPropExchange* pPX);
  virtual void OnResetState();
  //}}AFX_VIRTUAL

  // Implementation
protected:
  ~CECT_SoftPhoneCtrl();

  DECLARE_OLECREATE_EX(CECT_SoftPhoneCtrl)    // Class factory and guid
  DECLARE_OLETYPELIB(CECT_SoftPhoneCtrl)      // GetTypeInfo
  DECLARE_PROPPAGEIDS(CECT_SoftPhoneCtrl)     // Property page IDs
  DECLARE_OLECTLTYPE(CECT_SoftPhoneCtrl)		// Type name and misc status

  // Message maps
  //{{AFX_MSG(CECT_SoftPhoneCtrl)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnDestroy();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

  // Dispatch maps
  //{{AFX_DISPATCH(CECT_SoftPhoneCtrl)
  afx_msg short GetCTIServerType();
  afx_msg void  SetCTIServerType(short nNewValue);
  afx_msg BSTR  GetCTIServerIp();
  afx_msg void  SetCTIServerIp(LPCTSTR lpszNewValue);
  afx_msg long  GetCTIServerPort();
  afx_msg void  SetCTIServerPort(long nNewValue);
  afx_msg BSTR  GetPBX();
  afx_msg void  SetPBX(LPCTSTR lpszNewValue);
  afx_msg BOOL  GetWriteLogFlag();
  afx_msg void  SetWriteLogFlag(BOOL bNewValue);
  afx_msg short GetLogLevel();
  afx_msg void  SetLogLevel(short nNewValue);
  afx_msg short Login();
  afx_msg short SetCTIParam(LPCTSTR CTIServerIP, long CTIServerPort, long CTIServerType, LPCTSTR PBX);
  afx_msg short SetAgentParam(LPCTSTR AgentID, LPCTSTR Extension, LPCTSTR AgentGroup, long LoginType);
  afx_msg short Logout();
  afx_msg short SetIdle();
  afx_msg short SetBusy(LPCTSTR BusyReason);
  afx_msg short Answer();
  afx_msg short Hangup();
  afx_msg short Retrieve();
  afx_msg short Hold();
  afx_msg short MakeCall(LPCTSTR PhoneNum);
  afx_msg short Reconnect();
  afx_msg short ConsultAgent(LPCTSTR AgentID);
  afx_msg short Conference();
  afx_msg short Monitor(LPCTSTR AgentID);
  afx_msg short Transfer(LPCTSTR PhoneNum);
  afx_msg short TPIN(LPCTSTR PhoneNum, LPCTSTR Key, LPCTSTR Value);
  afx_msg long  GetStatus();
  afx_msg short SetUserData(LPCTSTR KV_Str);
  afx_msg short SetOneUserData(LPCTSTR Key, LPCTSTR Value);
  afx_msg BSTR  GetOneUserData(LPCTSTR Key);
  afx_msg short SetAllAgentsParam(LPCTSTR AllAgentStr);
  afx_msg short BlindTransfer(LPCTSTR PhoneNum);
  afx_msg short QueryAgentStatus(LPCTSTR AgentID);
  afx_msg short QueryCallStatus(LPCTSTR AgentID);
  afx_msg short Bargein(LPCTSTR AgentID);
  afx_msg short ForceBreak(LPCTSTR AgentID);
  afx_msg short ForceLogout(LPCTSTR AgentExtension);
  afx_msg short Run();
  afx_msg short SetCTIBackupParam(LPCTSTR CTIServerIPBackup, long CTIServerPortBackup);
  // add by hzd 2016-11-7 增加录音相关
  afx_msg short SetRECParam(LPCTSTR RECServerIP, long RECServerPort, LPCTSTR URLPath, LPCTSTR CCID, LPCTSTR UserName, LPCTSTR PassWord);
  afx_msg BSTR  GetRECFile(LPCTSTR CallUUID);
  // add by hzd 2016-11-7 增加录音相关
  //}}AFX_DISPATCH
  DECLARE_DISPATCH_MAP()

  afx_msg void AboutBox();

  //add by caihua
  //去掉安全警告 BEGIN
  DECLARE_INTERFACE_MAP()
  BEGIN_INTERFACE_PART(ObjectSafety, IObjectSafety)
    STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD __RPC_FAR *pdwSupportedOptions, DWORD __RPC_FAR *pdwEnabledOptions);
    STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions);
  END_INTERFACE_PART(ObjectSafety)


public:
  // Event maps
  //{{AFX_EVENT(CECT_SoftPhoneCtrl)
  void FireLoginEvent(LPCTSTR AgentID, LPCTSTR AgentExtension)
  {FireEvent(eventidLoginEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR), AgentID, AgentExtension);}
  void FireLogoutEvent(LPCTSTR AgentID, LPCTSTR AgentExtension)
  {FireEvent(eventidLogoutEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR), AgentID, AgentExtension);}
  void FireAgentReadyEvent(LPCTSTR AgentID, LPCTSTR AgentExtension)
  {FireEvent(eventidAgentReadyEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR), AgentID, AgentExtension);}
  void FireAgentBusyEvent(LPCTSTR AgentID, LPCTSTR AgentExtension, LPCTSTR BusyReason)
  {FireEvent(eventidAgentBusyEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_BSTR), AgentID, AgentExtension, BusyReason);}
  void FireNewCallEvent(LPCTSTR PhoneNum, long CallType)
  {FireEvent(eventidNewCallEvent,EVENT_PARAM(VTS_BSTR  VTS_I4), PhoneNum, CallType);}
  void FireHoldEvent()
  {FireEvent(eventidHoldEvent,EVENT_PARAM(VTS_NONE));}
  void FireRetrieveEvent()
  {FireEvent(eventidRetrieveEvent,EVENT_PARAM(VTS_NONE));}
  void FireHangupEvent()
  {FireEvent(eventidHangupEvent,EVENT_PARAM(VTS_NONE));}
  void FireEstablishedEvent(LPCTSTR PhoneNum, long CallType)
  {FireEvent(eventidEstablishedEvent,EVENT_PARAM(VTS_BSTR  VTS_I4), PhoneNum, CallType);}
  void FireACWEvent(LPCTSTR PhoneNum)
  {FireEvent(eventidACWEvent,EVENT_PARAM(VTS_BSTR), PhoneNum);}
  void FireAfterTPINEvent(LPCTSTR PhoneNum)
  {FireEvent(eventidAfterTPINEvent,EVENT_PARAM(VTS_BSTR), PhoneNum);}
  void FireCallAbandonEvent()
  {FireEvent(eventidCallAbandonEvent,EVENT_PARAM(VTS_NONE));}
  void FireMonitorCallEvent(LPCTSTR BeMonitorAgentID, LPCTSTR AgentID, LPCTSTR AgentExtension, LPCTSTR CallID, long CallType)
  {FireEvent(eventidMonitorCallEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_I4), BeMonitorAgentID, AgentID, AgentExtension, CallID, CallType);}
  void FireServiceEfficiencyEvent(LPCTSTR AgentID, LPCTSTR AgentGroup, LPCTSTR CallID, LPCTSTR ANI, LPCTSTR DNIS, LPCTSTR BeginTime, LPCTSTR EndTime, long CallLength, LPCTSTR RouteSource, LPCTSTR RouteDestination)
  {FireEvent(eventidServiceEfficiencyEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_BSTR  VTS_I4  VTS_BSTR  VTS_BSTR), AgentID, AgentGroup, CallID, ANI, DNIS, BeginTime, EndTime, CallLength, RouteSource, RouteDestination);}
  void FireCheckPasswordEvent(LPCTSTR reason)
  {FireEvent(eventidCheckPasswordEvent,EVENT_PARAM(VTS_BSTR), reason);}
  void FireErrorEvent(long ErrorCode, LPCTSTR ErrorString)
  {FireEvent(eventidErrorEvent,EVENT_PARAM(VTS_I4  VTS_BSTR), ErrorCode, ErrorString);}
  void FireQueryAgentEvent(LPCTSTR AgentID, LPCTSTR AgentExtension, long AgentStatus)
  {FireEvent(eventidQueryAgentEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_I4), AgentID, AgentExtension, AgentStatus);}
  void FireQueryCallEvent(LPCTSTR AgentID, LPCTSTR AgentExtension, long CallStatus)
  {FireEvent(eventidQueryCallEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_I4), AgentID, AgentExtension, CallStatus);}
  void FireAgentStatusChangeEvent(long state)
  {FireEvent(eventidAgentStatusChangeEvent,EVENT_PARAM(VTS_I4), state);}
  void FireConferenceEvent(LPCTSTR PhoneNum, LPCTSTR OtherExtension, long CallType)
  {FireEvent(eventidConferenceEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR  VTS_I4), PhoneNum, OtherExtension, CallType);}
  void FireConferenceEndEvent(LPCTSTR PhoneNum, LPCTSTR OtherExtension)
  {FireEvent(eventidConferenceEndEvent,EVENT_PARAM(VTS_BSTR  VTS_BSTR), PhoneNum, OtherExtension);}
  void FireCallTypeChangedEvent(LPCTSTR PhoneNum, long CallType)
  {FireEvent(eventidCallTypeChangedEvent,EVENT_PARAM(VTS_BSTR  VTS_I4), PhoneNum, CallType);}
  void FireDialingEvent(LPCTSTR PhoneNum, long CallType)
  {FireEvent(eventidDialingEvent,EVENT_PARAM(VTS_BSTR  VTS_I4), PhoneNum, CallType);}
  void FireRecordEvent(LPCTSTR ip, long port, LPCTSTR recordID)
  {FireEvent(eventidRecordEvent,EVENT_PARAM(VTS_BSTR  VTS_I4  VTS_BSTR), ip, port, recordID);}
  //}}AFX_EVENT
  DECLARE_EVENT_MAP()

  // Dispatch and event IDs
public:
  enum {
    //{{AFX_DISP_ID(CECT_SoftPhoneCtrl)
    dispidCTIServerType = 1L,
    dispidCTIServerIp = 2L,
    dispidCTIServerPort = 3L,
    dispidPBX = 4L,
    dispidWriteLogFlag = 5L,
    dispidLogLevel = 6L,
    dispidLogin = 7L,
    dispidSetCTIParam = 8L,
    dispidSetAgentParam = 9L,
    dispidLogout = 10L,
    dispidSetIdle = 11L,
    dispidSetBusy = 12L,
    dispidAnswer = 13L,
    dispidHangup = 14L,
    dispidRetrieve = 15L,
    dispidHold = 16L,
    dispidMakeCall = 17L,
    dispidReconnect = 18L,
    dispidConsultAgent = 19L,
    dispidConference = 20L,
    dispidMonitor = 21L,
    dispidTransfer = 22L,
    dispidTPIN = 23L,
    dispidGetStatus = 24L,
    dispidSetUserData = 25L,
    dispidSetOneUserData = 26L,
    dispidGetOneUserData = 27L,
    dispidSetAllAgentsParam = 28L,
    dispidBlindTransfer = 29L,
    dispidQueryAgentStatus = 30L,
    dispidQueryCallStatus = 31L,
    dispidBargein = 32L,
    dispidForceBreak = 33L,
    dispidForceLogout = 34L,
    dispidRun = 35L,
    dispidSetCTIBackupParam = 36L,
    // add by hzd 2016-11-7 增加录音相关
    dispidSetRECParam = 37L,
    dispidGetRECFile = 38L,
    // add by hzd 2016-11-7 增加录音相关
    eventidLoginEvent = 1L,
    eventidLogoutEvent = 2L,
    eventidAgentReadyEvent = 3L,
    eventidAgentBusyEvent = 4L,
    eventidNewCallEvent = 5L,
    eventidHoldEvent = 6L,
    eventidRetrieveEvent = 7L,
    eventidHangupEvent = 8L,
    eventidEstablishedEvent = 9L,
    eventidACWEvent = 10L,
    eventidAfterTPINEvent = 11L,
    eventidCallAbandonEvent = 12L,
    eventidMonitorCallEvent = 13L,
    eventidServiceEfficiencyEvent = 14L,
    eventidCheckPasswordEvent = 15L,
    eventidErrorEvent = 16L,
    eventidQueryAgentEvent = 17L,
    eventidQueryCallEvent = 18L,
    eventidAgentStatusChangeEvent = 19L,
    eventidConferenceEvent = 20L,
    eventidConferenceEndEvent = 21L,
    eventidCallTypeChangedEvent = 22L,
    eventidDialingEvent = 23L,
    eventidRecordEvent = 24L,
    //}}AFX_DISP_ID
  };
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECT_SOFTPHONECTL_H__4F3912A5_290F_438C_8EC3_52A21851AA65__INCLUDED)
