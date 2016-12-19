// ECT_SoftPhoneCtl.cpp : Implementation of the CECT_SoftPhoneCtrl ActiveX Control class.

#include "stdafx.h"
#include "ECT_SoftPhone.h"
#include "ECT_SoftPhoneCtl.h"
#include "ECT_SoftPhonePpg.h"
#include "AgentFormDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CECT_SoftPhoneCtrl, COleControl)


  //add by caihua
  //去掉安全警告 BEGIN
  BEGIN_INTERFACE_MAP(CECT_SoftPhoneCtrl, COleControl)
    INTERFACE_PART(CECT_SoftPhoneCtrl, IID_IObjectSafety, ObjectSafety)
  END_INTERFACE_MAP()
  // Implementation of IObjectSafety
  STDMETHODIMP CECT_SoftPhoneCtrl::XObjectSafety::GetInterfaceSafetyOptions(
    REFIID riid,
    DWORD __RPC_FAR *pdwSupportedOptions,
    DWORD __RPC_FAR *pdwEnabledOptions)
  {
    METHOD_PROLOGUE_EX(CECT_SoftPhoneCtrl, ObjectSafety)
      if (!pdwSupportedOptions || !pdwEnabledOptions)
      {
        return E_POINTER;
      }
      *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
      *pdwEnabledOptions = 0;
      if (NULL == pThis->GetInterface(&riid))
      {
        //WriteLog("Requested interface is not supported.\n", INFO_LOG, RUN_LOG_LEVEL);
        return E_NOINTERFACE;
      }
      // What interface is being checked out anyhow?
      OLECHAR szGUID[39];
      int i = StringFromGUID2(riid, szGUID, 39);
      if (riid == IID_IDispatch)
      {
        // Client wants to know if object is safe for scripting
        *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
        return S_OK;
      }
      else if (riid == IID_IPersistPropertyBag
        || riid == IID_IPersistStreamInit
        || riid == IID_IPersistStorage
        || riid == IID_IPersistMemory)
      {
        // Those are the persistence interfaces COleControl derived controls support
        // as indicated in AFXCTL.H
        // Client wants to know if object is safe for initializing from persistent data
        *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
        return S_OK;
      }
      else
      {
        // Find out what interface this is, and decide what options to enable
        //WriteLog("We didn't account for the safety of this interface, and it's one we support...\n", INFO_LOG, RUN_LOG_LEVEL);
        return E_NOINTERFACE;
      }
  }
  STDMETHODIMP CECT_SoftPhoneCtrl::XObjectSafety::SetInterfaceSafetyOptions(
    REFIID riid,
    DWORD dwOptionSetMask,
    DWORD dwEnabledOptions)
  {
    METHOD_PROLOGUE_EX(CECT_SoftPhoneCtrl, ObjectSafety)
      OLECHAR szGUID[39];
    // What is this interface anyway?
    // We can do a quick lookup in the registry under HKEY_CLASSES_ROOT\Interface
    int i = StringFromGUID2(riid, szGUID, 39);
    if (0 == dwOptionSetMask && 0 == dwEnabledOptions)
    {
      // the control certainly supports NO requests through the specified interface
      // so it"s safe to return S_OK even if the interface isn"t supported.
      return S_OK;
    }
    // Do we support the specified interface?
    if (NULL == pThis->GetInterface(&riid))
    {
      char szTmp[500];
      sprintf_s(szTmp, "%ls is not support.\n", szGUID);
      //WriteLog(szTmp, INFO_LOG, RUN_LOG_LEVEL);
      return E_FAIL;
    }
    if (riid == IID_IDispatch)
    {
      //WriteLog("Client asking if it's safe to call through IDispatch.\n", INFO_LOG, RUN_LOG_LEVEL);
      //WriteLog("In other words, is the control safe for scripting?\n", INFO_LOG, RUN_LOG_LEVEL);
      if (INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_CALLER == dwEnabledOptions)
      {
        return S_OK;
      }
      else
      {
        return E_FAIL;
      }
    }
    else if (riid == IID_IPersistPropertyBag
      || riid == IID_IPersistStreamInit
      || riid == IID_IPersistStorage
      || riid == IID_IPersistMemory)
    {
      //AfxMessageBox("Client asking if it's safe to call through IPersist*.\n");
      //WriteLog("Client asking if it's safe to call through IPersist*.\n", INFO_LOG, RUN_LOG_LEVEL);
      //AfxMessageBox("In other words, is the control safe for initializing from persistent data?\n");
      //WriteLog("In other words, is the control safe for initializing from persistent data?\n", INFO_LOG, RUN_LOG_LEVEL);
      if (INTERFACESAFE_FOR_UNTRUSTED_DATA == dwOptionSetMask && INTERFACESAFE_FOR_UNTRUSTED_DATA == dwEnabledOptions)
      {
        return NOERROR;
      }
      else
      {
        return E_FAIL;
      }
    }
    else
    {
      char szTmp[500];
      sprintf_s(szTmp, "We didn't account for the safety of %ls, and it's one we support...\n", szGUID);
      //WriteLog(szTmp,INFO_LOG,RUN_LOG_LEVEL);
      AfxMessageBox(szTmp);

      return E_FAIL;
    }
  }
  STDMETHODIMP_(ULONG) CECT_SoftPhoneCtrl::XObjectSafety::AddRef()
  {
    METHOD_PROLOGUE_EX_(CECT_SoftPhoneCtrl, ObjectSafety)
      return (ULONG)pThis->ExternalAddRef();
  }
  STDMETHODIMP_(ULONG) CECT_SoftPhoneCtrl::XObjectSafety::Release()
  {
    METHOD_PROLOGUE_EX_(CECT_SoftPhoneCtrl, ObjectSafety)
      return (ULONG)pThis->ExternalRelease();
  }
  STDMETHODIMP CECT_SoftPhoneCtrl::XObjectSafety::QueryInterface(
    REFIID iid, LPVOID* ppvObj)
  {
    METHOD_PROLOGUE_EX_(CECT_SoftPhoneCtrl, ObjectSafety)
      return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
  }
  //去掉安全警告 END


  /////////////////////////////////////////////////////////////////////////////
  // Message map

  BEGIN_MESSAGE_MAP(CECT_SoftPhoneCtrl, COleControl)
    //{{AFX_MSG_MAP(CECT_SoftPhoneCtrl)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
    ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
  END_MESSAGE_MAP()


  /////////////////////////////////////////////////////////////////////////////
  // Dispatch map

  BEGIN_DISPATCH_MAP(CECT_SoftPhoneCtrl, COleControl)
    //{{AFX_DISPATCH_MAP(CECT_SoftPhoneCtrl)
    DISP_PROPERTY_EX(CECT_SoftPhoneCtrl, "CTIServerType", GetCTIServerType, SetCTIServerType, VT_I4)
    DISP_PROPERTY_EX(CECT_SoftPhoneCtrl, "CTIServerIp", GetCTIServerIp, SetCTIServerIp, VT_BSTR)
    DISP_PROPERTY_EX(CECT_SoftPhoneCtrl, "CTIServerPort", GetCTIServerPort, SetCTIServerPort, VT_I4)
    DISP_PROPERTY_EX(CECT_SoftPhoneCtrl, "PBX", GetPBX, SetPBX, VT_BSTR)
    DISP_PROPERTY_EX(CECT_SoftPhoneCtrl, "WriteLogFlag", GetWriteLogFlag, SetWriteLogFlag, VT_BOOL)
    DISP_PROPERTY_EX(CECT_SoftPhoneCtrl, "LogLevel", GetLogLevel, SetLogLevel, VT_I4)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Login", Login, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetCTIParam", SetCTIParam, VT_I2, VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetAgentParam", SetAgentParam, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Logout", Logout, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetIdle", SetIdle, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetBusy", SetBusy, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Answer", Answer, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Hangup", Hangup, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Retrieve", Retrieve, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Hold", Hold, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "MakeCall", MakeCall, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Reconnect", Reconnect, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "ConsultAgent", ConsultAgent, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Conference", Conference, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Monitor", Monitor, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Transfer", Transfer, VT_I2, VTS_BSTR)
    // TPIN 调用参数发生变化 3个参数 TPIN 的路由点 随路数据 key 随路数据 value
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "TPIN", TPIN, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "GetStatus", GetStatus, VT_I4, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetUserData", SetUserData, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetOneUserData", SetOneUserData, VT_I2, VTS_BSTR VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "GetOneUserData", GetOneUserData, VT_BSTR, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetAllAgentsParam", SetAllAgentsParam, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "BlindTransfer", BlindTransfer, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "QueryAgentStatus", QueryAgentStatus, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "QueryCallStatus", QueryCallStatus, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Bargein", Bargein, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "ForceBreak", ForceBreak, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "ForceLogout", ForceLogout, VT_I2, VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "Run", Run, VT_I2, VTS_NONE)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetCTIBackupParam", SetCTIBackupParam, VT_I2, VTS_BSTR VTS_I4)
    // add by hzd 2016-11-7 增加录音相关
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "SetRECParam", SetRECParam, VT_I2, VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
    DISP_FUNCTION(CECT_SoftPhoneCtrl, "GetRECFile", GetRECFile, VT_BSTR, VTS_BSTR)
    // add by hzd 2016-11-7 增加录音相关
    //}}AFX_DISPATCH_MAP
    DISP_FUNCTION_ID(CECT_SoftPhoneCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
  END_DISPATCH_MAP()


  /////////////////////////////////////////////////////////////////////////////
  // Event map

  BEGIN_EVENT_MAP(CECT_SoftPhoneCtrl, COleControl)
    //{{AFX_EVENT_MAP(CECT_SoftPhoneCtrl)
    EVENT_CUSTOM("LoginEvent", FireLoginEvent,  VTS_BSTR  VTS_BSTR)
    EVENT_CUSTOM("LogoutEvent", FireLogoutEvent, VTS_BSTR  VTS_BSTR)
    EVENT_CUSTOM("AgentReadyEvent", FireAgentReadyEvent, VTS_BSTR  VTS_BSTR)
    EVENT_CUSTOM("AgentBusyEvent", FireAgentBusyEvent, VTS_BSTR  VTS_BSTR  VTS_BSTR)
    EVENT_CUSTOM("NewCallEvent", FireNewCallEvent, VTS_BSTR  VTS_I4)
    EVENT_CUSTOM("HoldEvent", FireHoldEvent, VTS_NONE)
    EVENT_CUSTOM("RetrieveEvent", FireRetrieveEvent, VTS_NONE)
    EVENT_CUSTOM("HangupEvent", FireHangupEvent, VTS_NONE)
    EVENT_CUSTOM("EstablishedEvent", FireEstablishedEvent, VTS_BSTR VTS_I4)
    EVENT_CUSTOM("ACWEvent", FireACWEvent, VTS_BSTR)
    EVENT_CUSTOM("AfterTPINEvent", FireAfterTPINEvent, VTS_BSTR)
    EVENT_CUSTOM("CallAbandonEvent", FireCallAbandonEvent, VTS_NONE)
    EVENT_CUSTOM("MonitorCallEvent", FireMonitorCallEvent, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
    EVENT_CUSTOM("ServiceEfficiencyEvent", FireServiceEfficiencyEvent, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR)
    EVENT_CUSTOM("CheckPasswordEvent", FireCheckPasswordEvent, VTS_BSTR)
    EVENT_CUSTOM("ErrorEvent", FireErrorEvent, VTS_I4  VTS_BSTR)
    EVENT_CUSTOM("QueryAgentEvent", FireQueryAgentEvent, VTS_BSTR VTS_BSTR VTS_I4)
    EVENT_CUSTOM("QueryCallEvent", FireQueryCallEvent, VTS_BSTR VTS_BSTR VTS_I4)
    EVENT_CUSTOM("AgentStatusChangeEvent", FireAgentStatusChangeEvent, VTS_I4)
    EVENT_CUSTOM("ConferenceEvent", FireConferenceEvent,VTS_BSTR VTS_BSTR VTS_I4)
    EVENT_CUSTOM("ConferenceEndEvent", FireConferenceEndEvent,VTS_BSTR VTS_BSTR)
    EVENT_CUSTOM("CallTypeChangedEvent", FireCallTypeChangedEvent,VTS_BSTR VTS_I4)
    EVENT_CUSTOM("DialingEvent", FireDialingEvent, VTS_BSTR  VTS_I4)
    EVENT_CUSTOM("RecordEvent", FireRecordEvent, VTS_BSTR  VTS_I4  VTS_BSTR)
    //}}AFX_EVENT_MAP
  END_EVENT_MAP()


  /////////////////////////////////////////////////////////////////////////////
  // Property pages

  // TODO: Add more property pages as needed.  Remember to increase the count!
  BEGIN_PROPPAGEIDS(CECT_SoftPhoneCtrl, 1)
    PROPPAGEID(CECT_SoftPhonePropPage::guid)
  END_PROPPAGEIDS(CECT_SoftPhoneCtrl)


  /////////////////////////////////////////////////////////////////////////////
  // Initialize class factory and guid

  IMPLEMENT_OLECREATE_EX(CECT_SoftPhoneCtrl, "ECTSOFTPHONE.ECTSoftPhoneCtrl.1",
    0x77dd447b, 0x336, 0x4ef5, 0x9b, 0xb2, 0xef, 0xd1, 0x71, 0x23, 0xb3, 0xa3)


    /////////////////////////////////////////////////////////////////////////////
    // Type library ID and version

    IMPLEMENT_OLETYPELIB(CECT_SoftPhoneCtrl, _tlid, _wVerMajor, _wVerMinor)


    /////////////////////////////////////////////////////////////////////////////
    // Interface IDs

    const IID BASED_CODE IID_DECT_SoftPhone =
  { 0x85d170cc, 0x1fe9, 0x41f3, { 0x9e, 0xec, 0xce, 0xbf, 0x44, 0x43, 0xa5, 0xc9 } };
  const IID BASED_CODE IID_DECT_SoftPhoneEvents =
  { 0xb9bfcee8, 0x98e, 0x4283, { 0x8f, 0x7d, 0xe3, 0x85, 0x9e, 0xee, 0x4, 0x26 } };


  /////////////////////////////////////////////////////////////////////////////
  // Control type information

  static const DWORD BASED_CODE _dwECT_SoftPhoneOleMisc =
    OLEMISC_ACTIVATEWHENVISIBLE |
    OLEMISC_SETCLIENTSITEFIRST |
    OLEMISC_INSIDEOUT |
    OLEMISC_CANTLINKINSIDE |
    OLEMISC_RECOMPOSEONRESIZE;

  IMPLEMENT_OLECTLTYPE(CECT_SoftPhoneCtrl, IDS_ECT_SOFTPHONE, _dwECT_SoftPhoneOleMisc)


    /////////////////////////////////////////////////////////////////////////////
    // CECT_SoftPhoneCtrl::CECT_SoftPhoneCtrlFactory::UpdateRegistry -
    // Adds or removes system registry entries for CECT_SoftPhoneCtrl

    BOOL CECT_SoftPhoneCtrl::CECT_SoftPhoneCtrlFactory::UpdateRegistry(BOOL bRegister)
  {
    // TODO: Verify that your control follows apartment-model threading rules.
    // Refer to MFC TechNote 64 for more information.
    // If your control does not conform to the apartment-model rules, then
    // you must modify the code below, changing the 6th parameter from
    // afxRegApartmentThreading to 0.

    if (bRegister)
      return AfxOleRegisterControlClass(
      AfxGetInstanceHandle(),
      m_clsid,
      m_lpszProgID,
      IDS_ECT_SOFTPHONE,
      IDB_ECT_SOFTPHONE,
      afxRegApartmentThreading,
      _dwECT_SoftPhoneOleMisc,
      _tlid,
      _wVerMajor,
      _wVerMinor);
    else
      return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
  }


  /////////////////////////////////////////////////////////////////////////////
  // CECT_SoftPhoneCtrl::CECT_SoftPhoneCtrl - Constructor

  CECT_SoftPhoneCtrl::CECT_SoftPhoneCtrl()
  {
    InitializeIIDs(&IID_DECT_SoftPhone, &IID_DECT_SoftPhoneEvents);

    // TODO: Initialize your control's instance data here.
    m_pAgentDlg = NULL;
  }


  /////////////////////////////////////////////////////////////////////////////
  // CECT_SoftPhoneCtrl::~CECT_SoftPhoneCtrl - Destructor

  CECT_SoftPhoneCtrl::~CECT_SoftPhoneCtrl()
  {
    if(m_pAgentDlg)
    {
      WriteLog("Ready to unconstruct the softphonectrl!",SYSTEM_LOG,RUN_LOG_LEVEL);
      delete m_pAgentDlg;
      m_pAgentDlg = NULL;
    }
  }


  void CECT_SoftPhoneCtrl::OnDestroy() 
  {
    COleControl::OnDestroy();
    if(m_pAgentDlg)
    {
      WriteLog("Ready to destroy softphonectrl!",SYSTEM_LOG,RUN_LOG_LEVEL);
      m_pAgentDlg->PostMessage(WM_DESTROY);
      Sleep(100);
      delete m_pAgentDlg;
      m_pAgentDlg = NULL;
    }

  }
  /////////////////////////////////////////////////////////////////////////////
  // CECT_SoftPhoneCtrl::OnDraw - Drawing function

  void CECT_SoftPhoneCtrl::OnDraw(
    CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
  {
    // TODO: Replace the following code with your own drawing code.
    m_pAgentDlg->ShowWindow(SW_SHOW);
  }


  /////////////////////////////////////////////////////////////////////////////
  // CECT_SoftPhoneCtrl::DoPropExchange - Persistence support

  void CECT_SoftPhoneCtrl::DoPropExchange(CPropExchange* pPX)
  {
    ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
    COleControl::DoPropExchange(pPX);


    PX_String(pPX,_T("CTIServerIp"),g_strCTISvrIp,_T("192.168.30.16"));
    PX_Long(pPX,_T("CTIServerPort"), g_strCTISvrPort,3000); 
    PX_String(pPX,_T("PBX"), g_PBX,_T("ALCATEL")); 
    PX_Long(pPX, _T("CTIServerType"), g_nCTISvrType,GENESYS);
    PX_String(pPX,_T("BusyReason"),g_strBusyReasonList,"1,会议|2,小休|3,吃饭"); 
    PX_Bool(pPX,_T("OpenLog"),g_bWriteLog,TRUE);
    PX_Bool(pPX,_T("CheckPassword"),g_bCheckPassword,FALSE);
    PX_Long(pPX,_T("LogLevel"),(long &)g_nLogLevel,2);
  }


  /////////////////////////////////////////////////////////////////////////////
  // CECT_SoftPhoneCtrl::OnResetState - Reset control to default state

  void CECT_SoftPhoneCtrl::OnResetState()
  {
    COleControl::OnResetState();  // Resets defaults found in DoPropExchange

    // TODO: Reset any other control state here.
  }


  /////////////////////////////////////////////////////////////////////////////
  // CECT_SoftPhoneCtrl::AboutBox - Display an "About" box to the user

  void CECT_SoftPhoneCtrl::AboutBox()
  {
    CDialog dlgAbout(IDD_ABOUTBOX_ECT_SOFTPHONE);
    dlgAbout.DoModal();
  }


  /////////////////////////////////////////////////////////////////////////////
  // CECT_SoftPhoneCtrl message handlers

  int CECT_SoftPhoneCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
  {
    if (COleControl::OnCreate(lpCreateStruct) == -1)
      return -1;
    if (NULL == m_pAgentDlg)
    {
      m_pAgentDlg = new CAgentFormDlg;
      m_pAgentDlg->Create(IDD_AGENTFORM_DIALOG, this);
      m_pAgentDlg->SetPhoneCtrlPtr(this);
    }

    return 0;
  }

  short CECT_SoftPhoneCtrl::GetCTIServerType() 
  {
    return (short)g_nCTISvrType;
  }

  void CECT_SoftPhoneCtrl::SetCTIServerType(short nNewValue) 
  {
    SetModifiedFlag();
  }

  BSTR CECT_SoftPhoneCtrl::GetCTIServerIp() 
  {
    CString strResult;
    strResult = g_strCTISvrIp;
    return strResult.AllocSysString();
  }

  void CECT_SoftPhoneCtrl::SetCTIServerIp(LPCTSTR lpszNewValue) 
  {
    g_strCTISvrIp = lpszNewValue;
    SetModifiedFlag();
  }

  long CECT_SoftPhoneCtrl::GetCTIServerPort() 
  {
    return g_strCTISvrPort;
  }

  void CECT_SoftPhoneCtrl::SetCTIServerPort(long lpszNewValue) 
  {
    g_strCTISvrPort = lpszNewValue;
    SetModifiedFlag();
  }

  BSTR CECT_SoftPhoneCtrl::GetPBX() 
  {
    CString strResult;
    strResult = g_PBX;

    return strResult.AllocSysString();
  }

  void CECT_SoftPhoneCtrl::SetPBX(LPCTSTR lpszNewValue) 
  {
    WriteLog("API [SetPBX] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    g_PBX = lpszNewValue;
    SetModifiedFlag();
  }

  short CECT_SoftPhoneCtrl::Login() 
  {
    WriteLog("API [Login] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_LOGIN);
    return 0;
  }

  short CECT_SoftPhoneCtrl::SetCTIParam(LPCTSTR CTIServerIP, long CTIServerPort, long CTIServerType, LPCTSTR PBX) 
  {
    CString tmpstr;
    tmpstr.Format("API [ SetCTIParam(%s,%d,%d,%s)] is called!!",CTIServerIP ,CTIServerPort ,CTIServerType ,PBX);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ConfigCTIServer(CTIServerIP,CTIServerPort,CTIServerType,PBX);

    return 0;
  }

  short CECT_SoftPhoneCtrl::SetAgentParam(LPCTSTR AgentID, LPCTSTR Extension, LPCTSTR AgentGroup, long LoginType) 
  {
    int type = LoginType;
    //if (type != AGENT || type !=SUPERVISOR)
    if (type !=SUPERVISOR)
    {
      type = AGENT;
    }
    if (0==strcmp(AgentID ,"") || 0==strcmp(Extension ,"") || 0==strcmp(AgentGroup ,""))
    {
      return FAILURE;
    }

    CString tmpstr;
    tmpstr.Format("API [ SetAgentParam(%s,%s,%s,%d)] is called!!", AgentID, Extension, AgentGroup,LoginType);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ConfigSoftPhone(AgentID,  Extension,  AgentGroup,  (AgentLoginType)LoginType);

    return 0;
  }

  short CECT_SoftPhoneCtrl::SetAllAgentsParam(LPCTSTR AllAgentStr) 
  {
    if (0==strcmp(AllAgentStr ,""))
    {
      return FAILURE;
    }
    CString tmpstr;
    tmpstr.Format("API [ SetAllAgentsParam(%s)] is called!!", AllAgentStr);
    //	WriteLog(tmpstr,SYSTEM_LOG,DEBUG_LOG_LEVEL);

    g_AgentGroupList.ParseInfo(AllAgentStr);
    return 0;
  }

  short CECT_SoftPhoneCtrl::Logout() 
  {
    WriteLog("API [Logout] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_LOGOUT);
    return 0;
  }

  short CECT_SoftPhoneCtrl::SetIdle() 
  {
    WriteLog("API [SetIdle] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_SETIDLE);
    return 0;
  }

  short CECT_SoftPhoneCtrl::SetBusy(LPCTSTR BusyReason) 
  {
    CString tmpReason = BusyReason;
    if (0==strcmp(tmpReason ,""))
    {
      tmpReason = "置忙";
    }

    CString tmpstr;
    tmpstr.Format("API [ SetBusy(%s)] is called!!", BusyReason);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_SETBUSY,BusyReason);
    return 0;
  }

  short CECT_SoftPhoneCtrl::Answer() 
  {
    WriteLog("API [Answer] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_ANSWER);
    return 0;
  }

  short CECT_SoftPhoneCtrl::Hangup() 
  {
    WriteLog("API [Hangup] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_RELEASE);
    return 0;
  }

  short CECT_SoftPhoneCtrl::Retrieve() 
  {
    WriteLog("API [Retrieve] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_RETRIEVE);
    return 0;
  }

  short CECT_SoftPhoneCtrl::Hold() 
  {
    WriteLog("API [Hold] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_HOLD);
    return 0;
  }

  short CECT_SoftPhoneCtrl::MakeCall(LPCTSTR PhoneNum) 
  {
    if (0==strcmp(PhoneNum ,""))
    {
      return FAILURE;
    }

    CString tmpstr;
    tmpstr.Format("API [ MakeCall(%s)] is called!!", PhoneNum);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_DIAL,PhoneNum);
    return 0;
  }

  short CECT_SoftPhoneCtrl::Reconnect() 
  {
    WriteLog("API [Reconnect] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_RECONNECT);
    return 0;
  }

  short CECT_SoftPhoneCtrl::ConsultAgent(LPCTSTR AgentID) 
  {
    if (0==strcmp(AgentID ,""))
    {
      return FAILURE;
    }

    CString tmpstr;
    tmpstr.Format("API [ ConsultAgent(%s)] is called!!", AgentID);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_CONSULT,AgentID);
    return 0;
  }

  short CECT_SoftPhoneCtrl::Conference() 
  {
    WriteLog("API [Conference] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_CONFERENCE);
    return 0;
  }

  short CECT_SoftPhoneCtrl::Monitor(LPCTSTR AgentID) 
  {
    if (0==strcmp(AgentID ,""))
    {
      return FAILURE;
    }

    CString tmpstr;
    tmpstr.Format("API [ Monitor(%s)] is called!!", AgentID);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_LISTEN,AgentID);
    return 0;
  } 

  short CECT_SoftPhoneCtrl::Transfer(LPCTSTR PhoneNum) 
  {
    CString tmpstr;
    tmpstr.Format("API [ Transfer(%s)] is called!!", PhoneNum);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_TRANSFER,PhoneNum);
    return 0;
  }

  short CECT_SoftPhoneCtrl::BlindTransfer(LPCTSTR PhoneNum) 
  {
    if (0==strcmp(PhoneNum ,""))
    {
      return FAILURE;
    }

    CString tmpstr;
    tmpstr.Format("API [ BlindTransfer(%s)] is called!!", PhoneNum);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_SINGLE_STEP_TRANSFER,PhoneNum);
    return 0;
  }

  short CECT_SoftPhoneCtrl::QueryAgentStatus(LPCTSTR AgentID) 
  {
    if (0==strcmp(AgentID ,""))
    {
      return FAILURE;
    }

    CString tmpstr;
    tmpstr.Format("API [ QueryAgentStatus(%s)] is called!!", AgentID);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_QUERYAGENT,AgentID);
    return 0;
  }

  short CECT_SoftPhoneCtrl::QueryCallStatus(LPCTSTR AgentID) 
  {
    if (0==strcmp(AgentID ,""))
    {
      return FAILURE;
    }

    CString tmpstr;
    tmpstr.Format("API [ QueryCallStatus(%s)] is called!!",AgentID );
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_QUERYCALL,AgentID);
    return 0;
  }

  short CECT_SoftPhoneCtrl::TPIN(LPCTSTR PhoneNum, LPCTSTR Key, LPCTSTR Value) 
  {
    if (0==strcmp(PhoneNum ,""))
    {
      return FAILURE;
    }

    CString tmpstr;
    tmpstr.Format("API [ TPIN(%s,%s,%s)] is called!!", PhoneNum,Key,Value);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_SETONEUSERDATA,Key,Value);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_TPIN,PhoneNum);

    return 0;
  }

  long CECT_SoftPhoneCtrl::GetStatus() 
  {
    WriteLog("API [GetStatus] is called!!",SYSTEM_LOG,RUN_LOG_LEVEL);
    return m_pAgentDlg->m_CtrlCenter.QueryState();
  }

  short CECT_SoftPhoneCtrl::SetUserData(LPCTSTR KV_Str) 
  {
    if (0==strcmp(KV_Str ,""))
    {
      return FAILURE;
    }
    CString tmpstr;
    tmpstr.Format("API [ SetUserData(%s)] is called!!", KV_Str);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);

    //m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_SETUSERDATA,KV_Str);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_SETONEUSERDATA,KV_Str);

    return 0;
  }

  short CECT_SoftPhoneCtrl::SetOneUserData(LPCTSTR Key, LPCTSTR Value) 
  {
    if (0==strcmp(Key ,""))
    {
      return FAILURE;
    }
    CString tmpstr; 
    tmpstr.Format("API [SetOneUserData (%s,%s)] is called!!",Key ,Value);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    CString strResult;
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_SETONEUSERDATA,Key,Value);
    return 0;
  }

  BSTR CECT_SoftPhoneCtrl::GetOneUserData(LPCTSTR Key) 
  {
    CString strResult;
    if (0==strcmp(Key ,""))
    {
      return strResult.AllocSysString();
    }

    strResult = m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_GETONEUSERDATA,Key);
    CString tmpstr;
    tmpstr.Format("API [ GetOneUserData(%s)] is called!! Value:\"%s\"", Key,strResult.GetString());
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    return strResult.AllocSysString();
  }

  BOOL CECT_SoftPhoneCtrl::GetWriteLogFlag() 
  {
    return g_bWriteLog;
  }

  void CECT_SoftPhoneCtrl::SetWriteLogFlag(BOOL bNewValue) 
  {
    g_bWriteLog = bNewValue;
    SetModifiedFlag();
  }

  short CECT_SoftPhoneCtrl::GetLogLevel() 
  {
    return g_nLogLevel;
  }

  void CECT_SoftPhoneCtrl::SetLogLevel(short nNewValue) 
  {
    g_nLogLevel = (LogLevel)nNewValue;

    SetModifiedFlag();
  }

  short CECT_SoftPhoneCtrl::Bargein(LPCTSTR AgentID) 
  {
    if (0==strcmp(AgentID,""))
    {
      return FAILURE;
    }	
    CString tmpstr;
    tmpstr.Format("API [ Bargein(%s)] is called!!",AgentID);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);

    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_BARGEIN,AgentID);
    return 0;
  }

  short CECT_SoftPhoneCtrl::ForceBreak(LPCTSTR AgentID) 
  {
    if (0==strcmp(AgentID,""))
    {
      return FAILURE;
    }
    CString tmpstr;
    tmpstr.Format("API [ForceBreak(%s)] is called!!",AgentID);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_FORCEBREAK,AgentID);
    return 0;
  }

  short CECT_SoftPhoneCtrl::ForceLogout(LPCTSTR AgentExtension) 
  {
    if (0==strcmp(AgentExtension,""))
    {
      return FAILURE;
    }
    CString tmpstr;
    tmpstr.Format("API [ForceLogout(%s)] is called!!",AgentExtension);	
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_FORCELOGOUT,AgentExtension);
    return SUCCESS;
  }

  short CECT_SoftPhoneCtrl::Run() 
  {
    WriteLog("API [Run] is called!",SYSTEM_LOG,RUN_LOG_LEVEL);
    if (NULL == m_pAgentDlg)
    {
      m_pAgentDlg = new CAgentFormDlg;
      m_pAgentDlg->Create(IDD_AGENTFORM_DIALOG, this);
      m_pAgentDlg->SetPhoneCtrlPtr(this);
    }
    m_pAgentDlg->m_CtrlCenter.Start();
    return 0;
  }

  short CECT_SoftPhoneCtrl::SetCTIBackupParam(LPCTSTR CTIServerIPBackup, long CTIServerPortBackup) 
  {
    g_strCTISvrIpBak = CTIServerIPBackup;
    g_strCTISvrPortBak = CTIServerPortBackup;
    CString tmpstr;
    tmpstr.Format("API [SetCTIBackupParam(%s,%d)] is called!!",CTIServerIPBackup,CTIServerPortBackup);	
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    return 0;
  }

  // add by hzd 2016-11-7 增加录音相关
  short CECT_SoftPhoneCtrl::SetRECParam(LPCTSTR RECServerIP, long RECServerPort, LPCTSTR URLPath, LPCTSTR CCID, LPCTSTR UserName, LPCTSTR PassWord)
  {
    CString tmpstr;
    tmpstr.Format("API [ SetRECParam(%s,%d,%s,%s,%s,%s)] is called!!", RECServerIP, RECServerPort, URLPath, CCID, UserName, PassWord);
    WriteLog(tmpstr,SYSTEM_LOG,RUN_LOG_LEVEL);
    m_pAgentDlg->m_CtrlCenter.ConfigRECServer(RECServerIP, RECServerPort, URLPath, CCID, UserName, PassWord);

    return 0;
  }

  // add by hzd 2016-11-7 增加录音相关
  BSTR CECT_SoftPhoneCtrl::GetRECFile(LPCTSTR CallUUID) 
  {
    CString strResult;
    if (0==strcmp(CallUUID,""))
    {
      return strResult.AllocSysString();
    }

    strResult = m_pAgentDlg->m_CtrlCenter.ExecuteOperation(OPER_GETRECFILES, CallUUID);
    CString tmpstr;
    tmpstr.Format("API [GetRECFile(%s)] is called!!", CallUUID);
    WriteLog(tmpstr, SYSTEM_LOG, RUN_LOG_LEVEL);
    return g_strRecUrlFiles.AllocSysString();
  }
