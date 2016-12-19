; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CECT_SoftPhoneCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ect_softphone.h"
LastPage=0
CDK=Y

ClassCount=12
Class1=CAgentFormDlg
Class2=CBitmapDialog
Class3=CBusyReasonDlg
Class4=CColorStaticST
Class5=CConsultDlg
Class6=CDialDlg
Class7=CECT_SoftPhoneCtrl
Class8=CECT_SoftPhonePropPage
Class9=CImageButton
Class10=CListenDlg
Class11=CRoundButton
Class12=CTransferDlg

ResourceCount=9
Resource1=IDD_DIALOG_CONSULT
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX_ECT_SOFTPHONE
Resource4=IDD_PROPPAGE_ECT_SOFTPHONE
Resource5=IDD_DIALOG_TRANSFER
Resource6=IDD_DIALOG_DIAL
Resource7=IDD_DIALOG_LISTEN
Resource8=IDD_DIALOG_SETBUSYREASON
Resource9=IDD_AGENTFORM_DIALOG

[CLS:CAgentFormDlg]
Type=0
BaseClass=CBitmapDialog
HeaderFile=AgentFormDlg.h
ImplementationFile=AgentFormDlg.cpp
LastObject=CAgentFormDlg
Filter=D
VirtualFilter=dWC

[CLS:CBitmapDialog]
Type=0
BaseClass=CDialog
HeaderFile=BITMAPDIALOG.H
ImplementationFile=BITMAPDIALOG.CPP

[CLS:CBusyReasonDlg]
Type=0
BaseClass=CDialog
HeaderFile=BusyReasonDlg.h
ImplementationFile=BusyReasonDlg.cpp

[CLS:CColorStaticST]
Type=0
BaseClass=CStatic
HeaderFile=ColorStaticST.h
ImplementationFile=ColorStaticST.cpp

[CLS:CConsultDlg]
Type=0
BaseClass=CDialog
HeaderFile=ConsultDlg.h
ImplementationFile=ConsultDlg.cpp

[CLS:CDialDlg]
Type=0
BaseClass=CDialog
HeaderFile=DialDlg.h
ImplementationFile=DialDlg.cpp

[CLS:CECT_SoftPhoneCtrl]
Type=0
BaseClass=COleControl
HeaderFile=ECT_SoftPhoneCtl.h
ImplementationFile=ECT_SoftPhoneCtl.cpp
Filter=W
VirtualFilter=wWC
LastObject=CECT_SoftPhoneCtrl

[CLS:CECT_SoftPhonePropPage]
Type=0
BaseClass=COlePropertyPage
HeaderFile=ECT_SoftPhonePpg.h
ImplementationFile=ECT_SoftPhonePpg.cpp

[CLS:CImageButton]
Type=0
BaseClass=CButton
HeaderFile=ImageButton.h
ImplementationFile=ImageButton.cpp

[CLS:CListenDlg]
Type=0
BaseClass=CDialog
HeaderFile=ListenDlg.h
ImplementationFile=ListenDlg.cpp

[CLS:CRoundButton]
Type=0
BaseClass=CButton
HeaderFile=RoundButton.h
ImplementationFile=ROUNDBUTTON.CPP

[CLS:CTransferDlg]
Type=0
BaseClass=CDialog
HeaderFile=TransferDlg.h
ImplementationFile=TransferDlg.cpp

[DLG:IDD_AGENTFORM_DIALOG]
Type=1
Class=CAgentFormDlg
ControlCount=21
Control1=IDC_LOGIN,button,1342243840
Control2=IDC_CONSULT,button,1342243840
Control3=IDC_DIAL,button,1342243840
Control4=IDC_TRANSFER,button,1342243840
Control5=IDC_HOLD,button,1342243840
Control6=IDC_SETBUSY,button,1342243840
Control7=IDC_RECONNECT,button,1342243840
Control8=IDC_LISTEN,button,1342243840
Control9=IDC_ANSWER,button,1342243840
Control10=IDC_BARGEIN,button,1342243840
Control11=IDC_FORCEBREAK,button,1342243840
Control12=IDC_STATIC,static,1342308352
Control13=IDC_TEXT_AGENTID,static,1342308864
Control14=IDC_STATIC,static,1342308352
Control15=IDC_TEXT_EXTENSION,static,1342308864
Control16=IDC_STATIC,static,1342308352
Control17=IDC_TEXT_STATUS,static,1342308864
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_TIME,static,1342308864
Control21=IDC_DIALNUM,static,1342308864

[DLG:IDD_DIALOG_SETBUSYREASON]
Type=1
Class=CBusyReasonDlg
ControlCount=5
Control1=IDC_BUSYREASON,SysListView32,1350631425
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_REASON,edit,1350633600
Control5=IDC_OK,button,1342242816

[DLG:IDD_DIALOG_CONSULT]
Type=1
Class=CConsultDlg
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_NUM,edit,1350641792
Control4=IDC_CONSULTAGENT,button,1342242816
Control5=IDC_GROUP_LIST,SysListView32,1350631433
Control6=IDC_AGENT_LIST,SysListView32,1350631425

[DLG:IDD_DIALOG_DIAL]
Type=1
Class=CDialDlg
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_NUM,edit,1350639616
Control3=IDC_STATIC,static,1342308352
Control4=IDC_AGENT_LIST,SysListView32,1350631429
Control5=IDC_NUMDIAL,button,1342242816
Control6=IDC_GROUP_LIST,SysListView32,1350631429

[DLG:IDD_PROPPAGE_ECT_SOFTPHONE]
Type=1
Class=CECT_SoftPhonePropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_LISTEN]
Type=1
Class=CListenDlg
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_LISTEN,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NUM,edit,1350641792
Control5=IDC_GROUP_LIST,SysListView32,1350631425
Control6=IDC_AGENT_LIST,SysListView32,1350631425

[DLG:IDD_DIALOG_TRANSFER]
Type=1
Class=CTransferDlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_NUM,edit,1350641792
Control3=IDCANCEL,button,1342242816
Control4=IDC_TRANSAGENT,button,1342242816
Control5=IDC_TRANSGROUP,button,1073807360
Control6=IDC_GROUP_LIST,SysListView32,1350631433
Control7=IDC_AGENT_LIST,SysListView32,1350631425

[DLG:IDD_ABOUTBOX_ECT_SOFTPHONE]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDC_OK
CommandCount=1

