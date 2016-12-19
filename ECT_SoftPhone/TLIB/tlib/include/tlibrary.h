/*
 * $Id: tlib_ext.h /main/23 24-Oct-2005.12:56:41 Pacific dmitryn $
 */ 
#ifndef _TLIB_H_INCLUDED
#define _TLIB_H_INCLUDED

#include "conn_fdset.h" /* need 'fd_set' for TSyncXXX functions */
#include "cmntypes.h"   /* TConnectionID is defined here        */
#include "cmnlog.h"
#include "kvlist.h"
#include "xkvlist.h"

#define TLIBRARY_VERSION 71000 /* 7.1.0 family, version 7.1.000+ */
#define T_PROTOCOL_VERSION "tserver protocol 4.2"

#ifdef __cplusplus
extern "C" {
#endif

const char *tlib_get_version_info(void);

typedef int TServer;
typedef char *TDirectoryNumber;
typedef char *TAgentID;
typedef char *TAgentPassword;
typedef unsigned long TCallID;
typedef unsigned long TFile;
typedef unsigned long TTime;
typedef unsigned int TReferenceID;
typedef int TPrivateMsgType;

typedef enum {
  AddressTypeUnknown,
  AddressTypeDN,
  AddressTypePosition,
  AddressTypeQueue,
  AddressTypeRouteDN,
  AddressTypeTrunk,
  AddressTypeVoiceChannel,
  AddressTypeDataChannel,
  AddressTypeAnnouncement,
  AddressTypeASAI,
  AddressTypeACDGroup,
  AddressTypeVSP,
  AddressTypeRouteQueue, /* RouteDN + Queue    */
  AddressTypeAgentID,    /* not a real address */
  AddressTypeOther = 99  /* other/unspecified  */
} 
TAddressType;

typedef enum {
  ServerRolePrimary,
  ServerRoleBackup
} 
TServerRole;

#define T_MASK_LENGTH 64
typedef unsigned char TMask[T_MASK_LENGTH];

#define TMaskSetAll(M)	 memset((M), 0xff, T_MASK_LENGTH)
#define TMaskClearAll(M) memset((M), 0x00, T_MASK_LENGTH)
#define TMaskSet(E, M)	 ((M)[(E)/8] |=  (1 << ((E)%8)))
#define TMaskClear(E, M) ((M)[(E)/8] &= ~(1 << ((E)%8)))
#define TMaskIsSet(E, M) ((M)[(E)/8] &   (1 << ((E)%8)))

#define ISCC_TRACKING_NUMBER "_ISCC_TRACKING_NUMBER_"  
#define ISCC_ORIGIN_LOCATION "_ISCC_ORIGIN_LOCATION_"  

/*---------------------------------------------------------------------------*/

enum TMessageType {
  RequestRegisterClient,        /*   0 */
  RequestQueryServer,
  RequestQueryAddress,
  RequestRegisterAddress,
  RequestUnregisterAddress,
  RequestRegisterAll,
  RequestUnregisterAll,
  RequestSetInputMask,
  RequestAgentLogin,
  RequestAgentLogout,
  RequestAgentReady,            /*  10 */
  RequestAgentNotReady,
  RequestSetDNDOn,
  RequestSetDNDOff,
  RequestMakeCall,
  RequestMakePredictiveCall,
  RequestAnswerCall,
  RequestReleaseCall,
  RequestHoldCall,
  RequestRetrieveCall,
  RequestInitiateConference,    /*  20 */
  RequestCompleteConference,
  RequestDeleteFromConference,
  RequestInitiateTransfer,
  RequestMuteTransfer,
  RequestSingleStepTransfer,
  RequestCompleteTransfer,
  RequestMergeCalls,
  RequestAlternateCall,
  RequestReconnectCall,
  RequestAttachUserData,        /*  30 */
  RequestUpdateUserData,
  RequestDeleteUserData,
  RequestDeletePair,
  RequestCallForwardSet,
  RequestCallForwardCancel,
  RequestRouteCall,
  RequestGiveMusicTreatment,
  RequestGiveSilenceTreatment,
  RequestGiveRingBackTreatment,
  RequestLoginMailBox,          /*  40 */
  RequestLogoutMailBox,
  RequestOpenVoiceFile,
  RequestCloseVoiceFile,
  RequestPlayVoiceFile,
  RequestCollectDigits,
  RequestSetMessageWaitingOn,
  RequestSetMessageWaitingOff,
  RequestDistributeUserEvent,
  RequestDistributeEvent,

  EventServerConnected,         /*  50 */
  EventServerDisconnected,
  EventError,
  EventRegistered,
  EventUnregistered,
  EventRegisteredAll,
  EventUnregisteredAll,
  EventQueued,
  EventDiverted,
  EventAbandoned,
  EventRinging,                 /*  60 */
  EventDialing,
  EventNetworkReached,
  EventDestinationBusy,
  EventEstablished,
  EventReleased,
  EventHeld,
  EventRetrieved,
  EventPartyChanged,
  EventPartyAdded,
  EventPartyDeleted,            /*  70 */
  EventRouteRequest,
  EventRouteUsed,
  EventAgentLogin,
  EventAgentLogout,
  EventAgentReady,
  EventAgentNotReady,
  EventDNDOn,
  EventDNDOff,
  EventMailBoxLogin,
  EventMailBoxLogout,           /*  80 */
  EventVoiceFileOpened,
  EventVoiceFileClosed,
  EventVoiceFileEndPlay,
  EventDigitsCollected,
  EventAttachedDataChanged,
  EventOffHook,
  EventOnHook,
  EventForwardSet,
  EventForwardCancel,
  EventMessageWaitingOn,        /*  90 */
  EventMessageWaitingOff,
  EventAddressInfo,
  EventServerInfo,
  EventLinkDisconnected,
  EventLinkConnected,
  EventUserEvent,

  RequestSendDTMF,              /*  97 */
  EventDTMFSent,

  EventResourceAllocated,       /*  99 */
  EventResourceFreed,

  EventRemoteConnectionSuccess, /* 101 */
  EventRemoteConnectionFailed,

  RequestRedirectCall,          /* 103 */
  RequestListenDisconnect,
  RequestListenReconnect,
  EventListenDisconnected,
  EventListenReconnected,
  RequestQueryCall,
  EventPartyInfo,
  RequestClearCall,

  RequestSetCallInfo,           /* 111 */
  EventCallInfoChanged,

  RequestApplyTreatment,        /* 113 */
  EventTreatmentApplied,
  EventTreatmentNotApplied,
  EventTreatmentEnd,

  EventHardwareError,           /* 117 */
  EventAgentAfterCallWork,
  EventTreatmentRequired,

  RequestSingleStepConference,  /* 120 */
  RequestQuerySwitch,
  EventSwitchInfo,

  RequestGetAccessNumber,       /* 123 */
  RequestCancelReqGetAccessNumber,
  EventAnswerAccessNumber,
  EventReqGetAccessNumberCanceled,

  RequestReserveAgent,          /* 127 */
  EventAgentReserved,
  RequestReserveAgentAndGetAccessNumber,

  RequestAgentSetIdleReason,    /* 130 */
  EventAgentIdleReasonSet,

  EventRestoreConnection,       /* 132 */
  EventPrimaryChanged,
  RequestLostBackupConnection,
  RequestSetDNInfo,

  RequestQueryLocation,         /* 136 */
  EventLocationInfo,

  EventACK,                     /* 138 */

  RequestMonitorNextCall,       /* 139 */
  RequestCancelMonitoring,
  EventMonitoringNextCall,
  EventMonitoringCancelled,

  RequestSetMuteOn,             /* 143 */
  RequestSetMuteOff,
  EventMuteOn,
  EventMuteOff,

  EventDNOutOfService,          /* 147 */
  EventDNBackInService,

  RequestPrivateService,        /* 149 */
  EventPrivateInfo,

  EventBridged, /* added by Epi 7/10/01, ER#23208 */
  EventQueueLogout,                   /* ER#53943 */

  EventReserved_1,              /* 153 */
  EventReserved_2,
  EventReserved_3,
  EventReserved_4,
  EventReserved_5,
  EventReserved_6,
  EventReserved_7,
/*
 * Call Monitoring events:
 */
  EventCallCreated,             /* 160 */
  EventCallDataChanged,
  EventCallDeleted,
  EventCallPartyAdded,
  EventCallPartyState,
  EventCallPartyMoved,
  EventCallPartyDeleted,
/*
 * Call Monitoring requests:
 */
  RequestStartCallMonitoring,   /* 167 */
  RequestStopCallMonitoring,
/*
 * Return Receipt service:
 */
  RequestSendReturnReceipt,     /* 169 */
  EventReturnReceipt,
/*
 * Network Attended Transfer / Conference (ER#94506):
 */
  RequestNetworkConsult,        /* 171 */
  RequestNetworkAlternate,
  RequestNetworkTransfer,
  RequestNetworkMerge,
  RequestNetworkReconnect,
  RequestNetworkSingleStepTransfer,
  RequestNetworkPrivateService,
  EventNetworkCallStatus,       /* 178 */
  EventNetworkPrivateInfo,

  MessageIDMAX
}; 
enum TAttribute {
  AttributeProtocolVersion,     /*   0 */
  AttributeErrorMessage,
  AttributeReferenceID,
  AttributeCallID,
  AttributeNodeID,
  AttributeNetworkCallID,
  AttributeNetworkNodeID,
  AttributeTransferredNetworkCallID,
  AttributeTransferredNetworkNodeID,
  AttributeConnID,
  AttributePreviousConnID,      /*  10 */
  AttributeTransferConnID,
  AttributeConferenceConnID,
  AttributeCallState,
  AttributeAgentID,
  AttributeAgentStateReasonUnused,
  AttributeAgentWorkMode,
  AttributeReason,
  AttributeDNIS,
  AttributeANI,
  AttributeThisDN,              /*  20 */
  AttributeThisQueue,
  AttributeThisTrunk,
  AttributeThisDNRole,
  AttributeOtherDN,
  AttributeOtherQueue,
  AttributeOtherTrunk,
  AttributeOtherDNRole,
  AttributeThirdPartyDN,
  AttributeThirdPartyQueue,
  AttributeThirdPartyTrunk,     /*  30 */
  AttributeThirdPartyDNRole,
  AttributeMusicPath,
  AttributeVoiceFileName,
  AttributeFileHandle,
  AttributeUserID,
  AttributePassword,
  AttributeVoiceSegment,
  AttributeVoiceIFlag,
  AttributeVoiceCFlag,
  AttributeNumberOfDigits,      /*  40 */
  AttributeTerminateDigits,
  AttributeTimeout,
  AttributeCollectedDigits,
  AttributeLastDigit,
  AttributeInputMask,
  AttributeErrorCode,
  AttributeAddressType,
  AttributeAddressMode,
  AttributeRegisterMode,
  AttributeControlMode,         /*  50 */
  AttributeUserData,
  AttributeDataKey,
  AttributeExtensions,
  AttributeCallType,
  AttributeCallingLineName, /* obsolete, do not use */
  AttributeAddressInfoType,
  AttributeAddressInfoStatus,
  AttributeUserEvent,
  AttributeCommunicationDN,
  AttributeRouteType,           /*  60 */
  AttributeServerVersion,
  AttributeServerRole,
  AttributeServerCapabilityMask,
  AttributeApplicationName,
  AttributeApplicationPassword,
  AttributeMergeType,
  AttributeForwardMode,
  AttributeDTMFDigits,
  AttributeLocation,

  AttributeRemoteLocation,      /*  70 */
  AttributeRemoteConnID,
  AttributeRemoteDN,

  AttributeMakeCallType,        /*  73 */
  AttributeCallInfoType,

  AttributeHomeLocation,        /*  75 */
  AttributeCustomerID,

  AttributeFirstTransferHomeLocation, /* 77 */
  AttributeFirstTransferOrigDN,
  AttributeLastTransferHomeLocation,
  AttributeLastTransferOrigDN,

  AttributeSetOperation,        /*  81 */
  AttributeNewConnID,

  AttributeTreatmentType,       /*  83 */
  AttributeTreatmentParms,

  AttributeCLID, /* obsolete, do not use */

  AttributeTimeinSecs,          /*  86 */
  AttributeTimeinuSecs,

  AttributeSwitchInfoType,      /*  88 */
  
  AttributeXRouteType,          /*  89 */
  AttributeAccessNumber,
  AttributeXReferenceID,  

  AttributePlace,               /*  92 */
  AttributePriority,

  AttributeAgentIdleReason,     /*  94 */

  AttributeRegistrationCode,    /*  95 */
  AttributeDNSyncInfo,

  AttributeMediaType, /* TMediaType enumeration */

  AttributeLocationInfoType,    /*  98 */
  AttributeOriginalConnID,
  AttributeConsultType,
  AttributeMonitorNextCallType,

  AttributeClientID,            /* 102 */
  AttributeProtocolID,
  AttributePreviousCallID,
  AttributePrivateMsgID,

  AttributeFirstTransferConnID, /* L/V\N FR#29197 */
  AttributeLastTransferConnID,

  AttributeSessionID, /* ER#42511  108 */
  AttributeHost,
  AttributePort,  /* for ER#43292  110 */

  AttributeDBID,                /* 111 */
  AttributeOtherDBID,
  AttributeThirdPartyDBID,

  AttributeCause,               /* 114 */
  AttributeDN,
  AttributeDialedNumber,
  AttributeOriginConnID,
  AttributeRefConnID,
  AttributeReliability,
  AttributeTimeStamp,           /* 120 */
  AttributeSwitchTime,

  AttributePartyID,             /* 122 */
  AttributePartyType,
  AttributePartyState,
  AttributeRefParty,
  AttributeCtrlParty,

  AttributeRemoteLoc,           /* 127 */
  AttributeRemoteParty,
  AttributeDevice,
  AttributeReserved_1,
  AttributeReserved_2,
  AttributeUpdateRevision,      /* 132 - reserved for ISCC, ER#65159 */

  AttributeReturnReceipt,       /* 133 */
  AttributeReturnReceiptDN,
  AttributeServerXCapabilities, /* 135 - ER#88935 */

  AttributeNetworkCallState,    /* 136 - ER#94506 */
  AttributeNetworkDestState,
  AttributeNetworkPartyRole,
  AttributeNetworkOrigDN,
  AttributeNetworkDestDN,

  AttributeCallUUID,            /* 141 - multi-site reporting in 7.1 */
  AttributeNewCallUUID,
  AttributeOrigCallUUID,
  AttributeRefCallUUID,
  AttributePartyUUID,
  AttributeISLinkList,

  AttributeServerStartTime,		/* 147 - event identification - added in 7.2 */
  AttributeEventSequenceNumber,

  AttributeIDMAX                /* 149 */
};

/*---------------------------------------------------------------------------*/

typedef struct TRemoteParty_tag {
  char *HomeLocation;
  TDirectoryNumber OrigDN;
} 
TRemoteParty;

typedef struct TCallHistoryInfo_tag {
  TRemoteParty FirstTransfer;
  TRemoteParty LastTransfer;
} 
TCallHistoryInfo;

typedef enum _TCallType {
  CallTypeUnknown,
  CallTypeInternal,
  CallTypeInbound,
  CallTypeOutbound,
  CallTypeConsult
} 
TCallType;

typedef enum _TCallState {
  CallStateOk,
  CallStateTransferred,
  CallStateConferenced,
  CallStateGeneralError,
  CallStateSystemError,
  CallStateRemoteRelease,
  CallStateBusy,
  CallStateNoAnswer,
  CallStateSitDetected,
  CallStateAnsweringMachineDetected,
  CallStateAllTrunksBusy,
  CallStateSitInvalidnum,
  CallStateSitVacant,
  CallStateSitIntercept,
  CallStateSitUnknown,
  CallStateSitNocircuit,
  CallStateSitReorder,
  CallStateFaxDetected,
  CallStateQueueFull,
  CallStateCleared,
  CallStateOverflowed,
  CallStateAbandoned,
  CallStateRedirected,
  CallStateForwarded,
  CallStateConsult,
  CallStatePickedup,
  CallStateDropped,
  CallStateDroppednoanswer,
  CallStateUnknown,
  CallStateCovered, /* 5/5/98 */
  CallStateConverseOn,
  CallStateBridged,

  CallStateDeafened = 49, /* added 9/15/99 by epi */
  CallStateHeld     = 50  /* (see common/gcti.h)  */
} 
TCallState;

typedef enum _TAgentWorkMode {
  AgentWorkModeUnknown  = 0,
  AgentManualIn         = 1,
  AgentAutoIn           = 2,      /* substate of Ready    */
  AgentLegalGuard =  AgentAutoIn, /* substate of NotReady */
  AgentAfterCallWork    = 3,
  AgentAuxWork          = 4,
  AgentNoCallDisconnect = 5,
  AgentWalkAway         = 6,
  AgentReturnBack       = 7
} 
TAgentWorkMode;

typedef enum _TDNRole {
  RoleUnknown,
  RoleOrigination,
  RoleDestination,
  RoleConferenceMember,
  RoleNewParty,
  RoleAddedBy,
  RoleDeletedBy,
  RoleTransferredBy,
  RoleDeletedParty,
  RoleConferencedBy,
  RoleObserver
} 
TDNRole;

/*---------------------------------------------------------------------------*/

typedef enum _AssociationInfoType {
  AssociatedToThisSession,
  AssociatedToAnotherSession,
  NotAssociated,
  AssociationNotAllowed
} 
AssociationInfoType;

enum _TAddressInfoType {
  AddressInfoAddressStatus,
  AddressInfoMessageWaitingStatus,
  AddressInfoAssociationStatus,
  AddressInfoCallForwardingStatus,
  AddressInfoAgentStatus,
  AddressInfoNumberOfAgentsInQueue,
  AddressInfoNumberOfAvailableAgentsInQueue,
  AddressInfoNumberOfCallsInQueue,
  AddressInfoAddressType,
  AddressInfoCallsQuery,
  AddressInfoSendAllCallsStatus,
  AddressInfoQueueLoginAudit,
  AddressInfoNumberOfIdleClassifiers,  /* obsolete, use TSwitchQuery instead */
  AddressInfoNumberOfClassifiersInUse, /* obsolete, use TSwitchQuery instead */
  AddressInfoNumberOfIdleTrunks,
  AddressInfoNumberOfTrunksInUse,
  AddressInfoDatabaseValue,
  AddressInfoDNStatus,
  AddressInfoQueueStatus,
  AddressInfoIDMAX
};
typedef enum _TAddressInfoType TAddressInfoType;

typedef enum _AddressStatusInfoType {
  AddressStatusIdle,
  AddressStatusOrigination,
  AddressStatusDialing,
  AddressStatusTalking,
  AddressStatusRinging,
  AddressStatusHeld,
  AddressStatusTreatment,
  AddressStatusLockedOut,
  AddressStatusMaintenance,
  AddressStatusAvailable,
  AddressStatusVacant
} 
AddressStatusInfoType;

typedef enum _MsgWaitingInfoType {
  MsgWaitingActivated,
  MsgWaitingDeactivated,
  ExecMsgWaitingActivated,
  ExecMsgWaitingDeactivated,
  MsgWaitingNotAllowed
} 
MsgWaitingInfoType;

enum _TForwardMode {
  ForwardModeNone,
  ForwardModeUnconditional,
  ForwardModeOnBusy,
  ForwardModeOnNoAnswer,
  ForwardModeOnBusyAndNoAnswer,
  ForwardModeSendAllCalls,
  ForwardModeIDMAX
};
typedef enum _TForwardMode TForwardMode;

typedef union _TAddressInfoStatus {
  AssociationInfoType AssociationStatus;
  AddressStatusInfoType AddressStatus;
  MsgWaitingInfoType MsgWaitingStatus;
  TForwardMode CallForwardingStatus;
  TAgentWorkMode AgentStatus;
  int NumberOfAgentsInQueue;
  int NumberOfAvailableAgentsInQueue;
  int NumberOfCallsInQueue;
  TAddressType AddressType;
  TForwardMode SendAllCallsStatus;
  int NumberOfIdleClassifiers;  /* obsolete */
  int NumberOfClassifiersInUse; /* obsolete */
  int NumberOfIdleTrunks;
  int NumberOfTrunksInUse;
  int NumberOfListElements; /* value passed in AttributeExtensions */
} 
TAddressInfoStatus;

/*---------------------------------------------------------------------------*/

enum _TTreatmentType {
  TreatmentUnknown,
  TreatmentIVR,
  TreatmentMusic,
  TreatmentRingBack,
  TreatmentSilence,
  TreatmentBusy,
  TreatmentCollectDigits,
  TreatmentPlayAnnouncement,
  TreatmentPlayAnnouncementAndDigits,
  TreatmentVerifyDigits,
  TreatmentRecordUserAnnouncement,
  TreatmentDeleteUserAnnouncement,
  TreatmentCancelCall,
  TreatmentPlayApplication,
  TreatmentSetDefaultRoute,
  TreatmentTextToSpeech,
  TreatmentTextToSpeechAndDigits,

  TreatmentFastBusy, /* added for DMS-100 */
  TreatmentRAN,      /* Sep 21, 1998      */
  TreatmentIDMAX
};
typedef enum _TTreatmentType TTreatmentType;

enum _TRouteType {
  RouteTypeUnknown,
  RouteTypeDefault,
  RouteTypeLabel,
  RouteTypeOverwriteDNIS,
  RouteTypeDDD,
  RouteTypeIDDD,
  RouteTypeDirect,
  RouteTypeReject,
  RouteTypeAnnouncement,
  RouteTypePostFeature,
  RouteTypeDirectAgent,
  RouteTypePriority,
  RouteTypeDirectPriority,

  RouteTypeAgentID, /* OtherDN = AgentID; added 8/10/99 */
  RouteTypeCallDisconnect, /* used for re-route ER47577 */

  RouteTypeIDMAX
};
typedef enum _TRouteType TRouteType;

typedef enum _TXRouteType {
  XRouteTypeDefault       = -1,
  XRouteTypeMIN           =  0,
  XRouteTypeRoute         =  0,
  XRouteTypeDirect        =  1,
  XRouteTypeReroute       =  2,
  XRouteTypeDirectUUI     =  3,
  XRouteTypeDirectANI     =  4,
  XRouteTypeDirectNoToken =  5,
  XRouteTypeDNISPooling   =  6,
  XRouteTypeDirectDigits  =  7,
  XRouteTypePullBack      =  8, /* ER#43524 */
  XRouteTypeExtProtocol   =  9, /* 06/14/02 */
  XRouteTypeRouteUUI      = 10, /* ER#92226 */
  XRouteTypeDirectNetworkCallID = 11, /* ER#22123396 */
  XRouteTypeMAX
} 
TXRouteType;

typedef struct TTimeStamp_tag {
  unsigned long seconds;
  unsigned long useconds;
} 
TTimeStamp;

typedef enum _TMediaType {
  TMediaVoice      =   0,  /* Voice (PSTN) call   */
  TMediaVoIP       =   1,  /* Voice over IP       */
  TMediaEMail      =   2,
  TMediaVMail      =   3,  /* Voice Mail          */
  TMediaSMail      =   4,  /* Scanned Mail        */
  TMediaChat       =   5,
  TMediaVideo      =   6,
  TMediaCobrowsing =   7,
  TMediaWhiteboard =   8,
  TMediaAppSharing =   9,  /* Application Sharing */
  TMediaWebForm    =  10,
  TMediaWorkItem   =  11,  /* work item (generic) */

  TMediaCustom0    = 100   /*<- all values above this one are */
}                          /* reserved for custom media types */
TMediaType;

typedef enum _TLocationInfoType {
  LocationInfoAllLocations,
  LocationInfoLocationData,
  LocationInfoMonitorLocation,
  LocationInfoCancelMonitorLocation,
  LocationInfoMonitorAllLocations,
  LocationInfoCancelMonitorAllLocations,
  LocationInfoCancellMonitorAllLocations   /* typo: 'Cancell' */
  = LocationInfoCancelMonitorAllLocations, /*   DO NOT USE    */
  LocationInfoLocationMonitorCanceled,
  LocationInfoAllLocationsMonitorCanceled
} 
TLocationInfoType;

enum _TMonitorNextCallType {
  MonitorOneCall,
  MonitorAllCalls,
  MonitorNextCallTypeIDMAX
};
typedef enum _TMonitorNextCallType TMonitorNextCallType;

/*---------------------------------------------------------------------------*/

typedef enum TPartyState_tag {
  PtState_NULL         =          0,
/* Generic Telephony States: */
  PtState_Initiated    =     0x0001,
  PtState_Queued       =     0x0009,
  PtState_Alerting     =     0x000A,
  PtState_Busy         =     0x000B,
  PtState_Connected    =     0x000C,
  PtState_CP_Detect    =     0x000D,
  PtState_Held         =     0x000E,
  PtState_Failed       =     0x000F,
/* Supplementary Telephony States: */
  PtState_NoListen     =     0x0010,
  PtState_NoTalk       =     0x0020,
  PtState_Bridged      =     0x0040,
  PtState_Audit        =     0x0080,
  PtState_SvcObserving =     0x00A0,
/* Routing/Treatment States: */
  PtState_TreatmentReq =     0x0100,
  PtState_Treatment    =     0x0200,
  PtState_Routing      =     0x0800,
/* State Modifiers: */
  PtStateMod_Dialing   =    0x10000,
  PtStateMod_Uncertain =    0x20000
} 
TPartyState; /* reported in "ps-%d" pair of EventAddressInfo/Extensions */

#define PtState_GTS_mask     0x000F
#define PtState_STS_mask     0x00F0
#define PtState_RTS_mask     0x0F00
#define PtState_report_mask  0xFFFF
#define PtState_DDP_mask 0xFF000000

/*---------------------------------------------------------------------------*/

typedef struct TEvent_tag {
  enum TMessageType	Event;
  TServer		Server;
  int			ReferenceID;

  char			*HomeLocation;
  char			*CustomerID;

  TConnectionID		ConnID;
  TConnectionID		PreviousConnID;
  TCallID		CallID;
  int			NodeID;
  TCallID		NetworkCallID;
  int			NetworkNodeID;

  TCallHistoryInfo	CallHistory;
  TCallType		CallType;
  TCallState		CallState;

  TAgentID		AgentID;
  TAgentWorkMode	WorkMode;

  long			ErrorCode;
  char			*ErrorMessage;

  TFile			FileHandle;
  char			*CollectedDigits;
  char			LastCollectedDigit;

  TDirectoryNumber	ThisDN;
  TDirectoryNumber	ThisQueue;
  unsigned long		ThisTrunk;
  TDNRole		ThisDNRole;
  TDirectoryNumber	OtherDN;
  TDirectoryNumber	OtherQueue;
  unsigned long		OtherTrunk;
  TDNRole		OtherDNRole;
  TDirectoryNumber	ThirdPartyDN;     
  TDirectoryNumber	ThirdPartyQueue;
  unsigned long		ThirdPartyTrunk;
  TDNRole		ThirdPartyDNRole;

  TDirectoryNumber	DNIS;
  TDirectoryNumber	ANI;
  char			*CallingLineName; /* obsolete */
  TDirectoryNumber	CLID;             /* obsolete */

  TAddressInfoType	InfoType;
  TAddressInfoStatus	InfoStatus;

  TTreatmentType	TreatmentType;
  TRouteType            RouteType;

  char			*ServerVersion;
  TServerRole		ServerRole;
  TMask			Capabilities;

  TKVList		*UserData;
  TKVList		*Reasons;
  TKVList		*Extensions;

  TTimeStamp		Time;
  void 			*RawData;

  TDirectoryNumber	AccessNumber;
  TXRouteType		XRouteType;
  TReferenceID		XReferenceID;
  TKVList               *TreatmentParameters;
  char                  *Place;
  int                   Timeout;
  TMediaType            MediaType; /* added 7/15/99 ER#9462 */

  TLocationInfoType	LocationInfo;
  TMonitorNextCallType  MonitorNextCallType;
/*
 * Used in RequestPrivateService/EventPrivateInfo only (added 11/6/2000):
 */
  TPrivateMsgType       PrivateEvent;
/*
 * Application data (set by TSetApplicationData), added 4/22/03 ER#33576:
 */
  void *ApplicationData;
  int TEventFormat; /* reserved for internal use */
} 
TEvent;

TEvent *TCopyEvent(TEvent *event);
void    TFreeEvent(TEvent *event);

/*
 * Getting attributes not included as separate fields into TEvent structure:
 */
const char   *TEventGetStringAttr(const TEvent *ev, enum TAttribute attr);
int           TEventGetIntAttr   (const TEvent *ev, enum TAttribute attr);
TConnectionID TEventGetConnID    (const TEvent *ev, enum TAttribute attr);
ulong64_t     TEventGetLongAttr  (const TEvent *ev, enum TAttribute attr);
TKVList*      TEventGetKVListAttr(const TEvent *ev, enum TAttribute attr);
/*
 * Extended server capabilities:
 */
typedef int TXCaps;

TXCaps TGetXCapsFromString(const char* extended_capatibilities, int cap_type, int subtype);
TXCaps TGetXCapsFromKVList (const TKVList* extensions, int cap_type, int subtype);
TXCaps TGetXCaps(const TEvent *eventServerInfo, int cap_type, int cap_subtype);
int    TXCapsSupported(TXCaps xcaps, int enum_val);
TMask* TGetCapsFromKVList (const TKVList* extensions,TMask* mask);

#define XCAPS_ANY_MESSAGE -1

/*---------------------------------------------------------------------------*/

typedef enum _TOpenMode {
  SyncMode,
  AsyncMode
} 
TOpenMode;

typedef void (*TDispatchFunction)(TEvent *event);

TServer TOpenServer(
	const char *server_name,
	TDispatchFunction dispatch_function,
	const char *application_name,
	const char *application_password,
	TOpenMode open_mode
);
TServer TOpenServerEx(
	const char *server_host_name,
	int server_port,
	TDispatchFunction dispatch_function,
	const char *application_name,
	const char *application_password,
	TOpenMode open_mode
);
TServer TOpenServerX(XKVList *conn_param,
	TDispatchFunction dispatch_function,
	const char *application_name,
	const char *application_password,
	TOpenMode open_mode
);
int TProtocolReconfig(TServer server,
                      XKVList *new_conn_param
);
int TSetApplicationData(TServer server, void *app_data);

int TCloseServer(TServer server);
int TDispatch   (TServer server);
int TScanServer (TServer server, int timeout_sec);

enum TScanServerMode {
  TSCAN_MODE_DEFAULT   = 0, /* default scan mode */
  TSCAN_MODE_SYNC      = 0, /* - for SyncMode    */
  TSCAN_MODE_ASYNC     = 6, /* - for AsyncMode   */

  TSCAN_MODE_WRITE     =     2, /* must be synchronized with */
  TSCAN_MODE_WRITE_ALL = 0x200, /* defines in connection.h   */
  TSCAN_MODE_CONNECT   = 0x610
};
int TScanServerEx(
	TServer server,
	int timeout_sec,
	enum TScanServerMode scan_mode
);

int TSetInputMask(
	TServer server,
	TMask mask
);
int TGetReferenceID(void);
int TSetReferenceID(int reference_id_for_next_req);
int TSetRefIDLimit (int new_limit);

/*---------------------------------------------------------------------------*/

typedef enum _TRegisterMode {
  ModeShare,
  ModePrivate,
  ModeMonitor
} 
TRegisterMode;

typedef enum _TControlMode {
  RegisterDefault,
  RegisterForce,
  RegisterLocal
} 
TControlMode;

int TRegisterAddress(
	TServer server,
	const TDirectoryNumber dn,
	TRegisterMode mode,
	TControlMode ctrmode,
	TAddressType type,
	TKVList *extensions
);
int TUnregisterAddress(
	TServer server,
	const TDirectoryNumber dn,
	TControlMode ctrmode,
	TKVList *extensions
);

/*---------------------------------------------------------------------------*/

enum _TMakeCallType {
  MakeCallRegular,
  MakeCallDirectAgent,
  MakeCallSupervisorAssist,
  MakeCallPriority,
  MakeCallDirectPriority,
  MakeCallTypeIDMAX
};
typedef enum _TMakeCallType TMakeCallType;

int TMakeCall(
	TServer server,
	const TDirectoryNumber dn,
	const TDirectoryNumber destination,
	const char *location,
	TMakeCallType call_type,
	TKVList *user_data,
	TKVList *reasons,
	TKVList *extensions
);
int TMakePredictiveCall(
	TServer server,
	const TDirectoryNumber dn,
	const TDirectoryNumber destination,
	int ring_timeout,
	TKVList *user_data,
	TKVList *reasons,
	TKVList *extensions
);

/*---------------------------------------------------------------------------*/

int TAnswerCall(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);
int TRedirectCall(
	TServer server,
	const TDirectoryNumber dn,
	const TDirectoryNumber destination,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);
int TReleaseCall(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);
int TClearCall(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);

int THoldCall(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);
int TRetrieveCall(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);
int TAlternateCall(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID held_conn_id,
	TConnectionID current_conn_id,
	TKVList *reasons,
	TKVList *extensions
);
int TReconnectCall(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID held_conn_id,
	TConnectionID current_conn_id,
	TKVList *reasons,
	TKVList *extensions
);

int TInitiateTransfer(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	const TDirectoryNumber destination,
	const char *location,
	TKVList *user_data,
	TKVList *reasons,
	TKVList *extensions
);
int TCompleteTransfer(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID held_conn_id,
	TConnectionID current_conn_id,
	TKVList *reasons,
	TKVList *extensions
);

int TMuteTransfer(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	const TDirectoryNumber destination,
	const char *location,
	TKVList *user_data,
	TKVList *reasons,
	TKVList *extensions
);
int TSingleStepTransfer(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	const TDirectoryNumber destination,
	const char *location,
	TKVList *user_data,
	TKVList *reasons,
	TKVList *extensions
);

int TInitiateConference(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	const TDirectoryNumber destination,
	const char *location,
	TKVList *user_data,
	TKVList *reasons,
	TKVList *extensions
);
int TCompleteConference(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID held_conn_id,
	TConnectionID current_conn_id,
	TKVList *reasons,
	TKVList *extensions
);

int TSingleStepConference(
        TServer server, 
        const TDirectoryNumber dn,
        TConnectionID conn_id, 
        const TDirectoryNumber destination,
        const char *location,
        TKVList *user_data, 
        TKVList *reasons,
        TKVList *extensions
);

int TDeleteFromConference(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	const TDirectoryNumber dn_to_drop,
	TKVList *reasons,
	TKVList *extensions
);

int TListenDisconnect(
	TServer server,
	const TDirectoryNumber dn,
	const TDirectoryNumber listener_dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);
int TListenReconnect(
	TServer server,
	const TDirectoryNumber dn,
	const TDirectoryNumber listener_dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);

enum _TMergeType {
  MergeForTransfer,
  MergeForConference,
  MergeTypeIDMAX
};
typedef enum _TMergeType TMergeType;

int TMergeCalls(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID held_conn_id,
	TConnectionID current_conn_id,
	TMergeType merge_type,
	TKVList *reasons,
	TKVList *extensions
);

/*---------------------------------------------------------------------------*/

typedef enum _TAgentType {
  AgentTypeAgent,
  AgentTypeSupervisor
} 
TAgentType;

int TAgentLogin(
	TServer server,
	const TDirectoryNumber queue,
	const TDirectoryNumber dn,
	TAgentType agent_type,
	const TAgentID agent_id,
	const TAgentPassword passwd,
	TAgentWorkMode workmode,
	TKVList *reasons,
	TKVList *extensions
);
int TAgentLogout(
	TServer server,
	const TDirectoryNumber queue,
	const TDirectoryNumber dn,
	TKVList *reasons,
	TKVList *extensions
);
int TAgentSetReady(
	TServer server,
	const TDirectoryNumber queue,
	const TDirectoryNumber dn,
	TAgentWorkMode workmode,
	TKVList *reasons,
	TKVList *extensions
);
int TAgentSetNotReady(
	TServer server,
	const TDirectoryNumber queue,
	const TDirectoryNumber dn,
	TAgentWorkMode workmode,
	TKVList *reasons,
	TKVList *extensions
);
int TAgentSetIdleReason( /* DEPRECATED */
	TServer server,
	const TDirectoryNumber queue,
	const TDirectoryNumber dn,
	const char *idle_reason,
	TKVList *reasons,
	TKVList *extensions
);

int TReserveAgent(
        TServer server,
        const TDirectoryNumber agent_dn,
	const TAgentID agent_id,
        const char *agent_place,
        int duration,
        int priority,
	TKVList *reasons,
	TKVList *extensions
);

/*---------------------------------------------------------------------------*/

int TSetDNDOn(
	TServer server,
	const TDirectoryNumber dn,
	TKVList *reasons,
	TKVList *extensions
);
int TSetDNDOff(
	TServer server,
	const TDirectoryNumber dn,
	TKVList *reasons,
	TKVList *extensions
);
int TCallSetForward(
	TServer server,
	const TDirectoryNumber dn,
	const TDirectoryNumber destination,
	TForwardMode forward_mode,
	TKVList *reasons,
	TKVList *extensions
);
int TCallCancelForward(
	TServer server,
	const TDirectoryNumber dn,
	TForwardMode forward_mode,
	TKVList *reasons,
	TKVList *extensions
);
int TSetMessageWaitingOn(
	TServer server,
	const TDirectoryNumber dn,
	TKVList *reasons,
	TKVList *extensions
);
int TSetMessageWaitingOff(
	TServer server,
	const TDirectoryNumber dn,
	TKVList *reasons,
	TKVList *extensions
);
int TSetMuteOn(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);
int TSetMuteOff(
    	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *reasons,
	TKVList *extensions
);

/*---------------------------------------------------------------------------*/

int TLoginMailBox(
	TServer server,
	const TDirectoryNumber dn,
	const char *mbox_number,
	const char *mbox_passwd,
	TKVList *reasons,
	TKVList *extensions
);
int TLogoutMailBox(
	TServer server,
	const TDirectoryNumber dn,
	TKVList *reasons,
	TKVList *extensions
);

int TOpenVoiceFile(
	TServer server,
	const TDirectoryNumber dn,
	const char *file_name,
	TKVList *reasons,
	TKVList *extensions
);
int TCloseVoiceFile(
	TServer server,
	const TDirectoryNumber dn,
	TFile file_handle,
	TKVList *reasons,
	TKVList *extensions
);

typedef enum _TInterruptFlag {
  Uninterruptable = 1,
  Interruptable   = 2
} 
TInterruptFlag;

typedef enum _TClearFlag {
  Clear    = 1,
  NotClear = 2
} 
TClearFlag;

int TPlayVoice(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TFile file_handle,
	const char *segments,
	TInterruptFlag iflag,
	TClearFlag cflag,
	TKVList *reasons,
	TKVList *extensions
);

int TCollectDigits(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	int num_digits,
	const char *term_digits,
	TClearFlag cflag,
	TTime timeout,
	TKVList *reasons,
	TKVList *extensions
);
int TSendDTMF(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	const char *digits,
	TKVList *reasons,
	TKVList *extensions
);

/*---------------------------------------------------------------------------*/

int TQueryServer(
	TServer server,
	TKVList *extensions
);
int TQueryAddress(
	TServer server,
	const TDirectoryNumber queue,
	const TDirectoryNumber dn,
	TAddressType addr_type,
	TAddressInfoType info_type,
	TKVList *extensions
);

enum _TCallInfoType {
  CallInfoPartiesQuery,
  CallInfoStatusQuery,
  CallInfoIDMAX
};
typedef enum _TCallInfoType TCallInfoType;

int TQueryCall(
	TServer server,
	const TDirectoryNumber dn, /* reserved for access control */
	TConnectionID conn_id,
	TCallInfoType info_type,
	TKVList *extensions
);

enum _TSwitchInfoType {
  SwitchInfoTypeUnused,
  SwitchInfoDateTime,
  SwitchInfoClassifierStat,
  SwitchInfoIDMAX
};
typedef enum _TSwitchInfoType TSwitchInfoType;

int TQuerySwitch(
	TServer server,
	TSwitchInfoType info_type,
	TKVList *extensions
);

/*---------------------------------------------------------------------------*/

int TAttachUserData(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *user_data
);
int TUpdateUserData(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	TKVList *user_data
);
int TDeleteUserData(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id,
	const char *key
);
int TDeleteAllUserData(
	TServer server,
	const TDirectoryNumber dn,
	TConnectionID conn_id
);

int TSendUserEvent(
	TServer server,
	const TDirectoryNumber dn,
	TEvent *event
);

/*---------------------------------------------------------------------------*/

int TMonitorNextCall(
	TServer server,
	const TDirectoryNumber dn,
	const TDirectoryNumber agent_dn,
	TMonitorNextCallType monitor_type,
	TKVList *reasons,
	TKVList *extensions
);
int TCancelMonitoring(
	TServer server,
	const TDirectoryNumber dn,
	const TDirectoryNumber agent_dn,
	TKVList *reasons,
	TKVList *extensions
);

/*-----------------------------------------------------------------------------
 * Network Attended Transfer / Conference (ER#94506)
 */
int TNetworkConsult(
	TServer server,
	const TDirectoryNumber ctrl_dn,
	TConnectionID conn_id,
	const char *home_location,
	const TDirectoryNumber destination,
	const char *dest_location,
	TKVList *reasons,
	TKVList *extensions
);
int TNetworkAlternate(
	TServer server,
	const TDirectoryNumber ctrl_dn,
	TConnectionID conn_id,
	const char *home_location,
	TKVList *reasons,
	TKVList *extensions
);
int TNetworkTransfer(
	TServer server,
	const TDirectoryNumber ctrl_dn,
	TConnectionID conn_id,
	const char *home_location,
	TKVList *reasons,
	TKVList *extensions
);
int TNetworkMerge(
	TServer server,
	const TDirectoryNumber ctrl_dn,
	TConnectionID conn_id,
	const char *home_location,
	TKVList *reasons,
	TKVList *extensions
);
int TNetworkReconnect(
	TServer server,
	const TDirectoryNumber ctrl_dn,
	TConnectionID conn_id,
	const char *home_location,
	TKVList *reasons,
	TKVList *extensions
);

typedef enum TNetworkCallState_tag {
  NetworkCallStateUnknown      = 0,
  NetworkCallStateConsulting   = 1,
  NetworkCallStateConsultHeld  = 2,
  NetworkCallStateTransferred  = 3,
  NetworkCallStateConferenced  = 4,
  NetworkCallStateReconnected  = 5,
  NetworkCallStateDisconnected = 6,
  NetworkCallStateNull         = 7
}
TNetworkCallState;

typedef enum TNetworkDestState_tag {
  NetworkDestStateUnknown     = 0,
  NetworkDestStateRouting     = 1,
  NetworkDestStateDelivering  = 2,
  NetworkDestStateNoParty     = 3,
  NetworkDestStateFailed = NetworkDestStateNoParty,
  NetworkDestStateOk          = 4
}
TNetworkDestState;

typedef enum TNetworkPartyRole_tag {
  RoleNtwUnknown   = 0,
  RoleNtwOrigParty = 1,
  RoleNtwDestParty = 2
}
TNetworkPartyRole;

int TNetworkSingleStepTransfer(
	TServer server,
	const TDirectoryNumber ctrl_dn,
	TConnectionID conn_id,
	const char *home_location,
	const TDirectoryNumber destination,
	const char *dest_location,
	TKVList *reasons,
	TKVList *extensions
);
int TNetworkPrivateService(
	TServer server,
        TPrivateMsgType serviceID,
	const TDirectoryNumber ctrl_dn,
	TConnectionID conn_id,
	const char *home_location,
	TKVList *reasons,
	TKVList *extensions
);

/*---------------------------------------------------------------------------*/

void TSetReconnectParams( /* OBSOLETE, please use TSetParamHA instead */
	int attempts, 
	int timeout
);

int TSetParamHA(  /* Set parameter for HA:      */
        int key,  /* - what (see THA_xxx below) */
        int value /* - parameter value          */
);
#define THA_CON_TIMEOUT  1 /* connect_timeout - default 3.6 sec */
#define THA_SWO_TIMEOUT  2 /* switchover_timeout        3.6 sec */
#define THA_BRC_INTERVAL 8 /* reconnect_interval         20 sec */
#define THA_BRC_ATTEMPTS 4 /* obsolete, no effect w/TLib 6.5.3+ */

/*---------------------------------------------------------------------------*/

enum TSockInfoReason {
  TSocketCreated,
  TSocketDeleted,
  TSocketChanged
};

typedef struct TSockInfo_tag {
  int socket;
  int sync_id;
  int reason;
  void *ptr;
} 
TSockInfo;

#ifdef FD_SET /* fd_set still may be not defined */
  int  TSyncSetSelectMask(int sync_id, fd_set *pfd);
  void TSyncClear        (int sync_id, fd_set *pfd);
  int  TSyncIsSet        (int sync_id, fd_set *pfd);
#endif
void TSetSocketChangeCallback(void (*client_callback)(TSockInfo *p));

TServer TGetServerBySocket(int socket);

/*---------------------------------------------------------------------------*/

typedef int (*TPrintFunction)(void *stream, char* format, ...);

TPrintFunction TMessageSetPrintFunction(TPrintFunction f);
int            TMessageSetPrintFlags   (int flags);

#define TPrintFlagEnableTrace   0x0001
#define TPrintFlagVerboseTrace  0x0002
#define TPrintFlagDisableUData  0x1000
#define TPrintFlagDisablePasswd 0x2000

const char *TGetMessageTypeName(enum TMessageType msg_type);
const char *TGetAgentWorkModeNames(TAgentWorkMode wmode);
const char *TGetAddressInfoTypeNames(TAddressInfoType aitype);
const char *TGetCallInfoTypeNames(TCallInfoType citype);
const char *TGetSwitchInfoTypeNames(TSwitchInfoType sitype);
const char *TGetForwardModeNames(TForwardMode fmode);
const char *TGetMakeCallTypeNames(TMakeCallType mctype);
const char *TGetRouteTypeNames(TRouteType rtype);
const char *TGetTreatmentTypeNames(TTreatmentType ttype);
const char *TGetMergeTypeNames(TMergeType mtype);
const char *TGetMonitorNextCallTypeNames(TMonitorNextCallType mtype);

int TLibSetupLog(void *stream, comlib_print_proc_t print_func);
/*
 * First parameter in 'print_func' is always 0 for debug/trace messages, and
 * non-zero for the following message:
 */
#define TLibERR_INVALID_MESSAGE_RECEIVED 4546
 /* STANDARD|Invalid %s[TLib] message received from %s[server], %s[text] */

#ifdef __cplusplus
}
#endif

#endif /* _TLIB_H_INCLUDED */

