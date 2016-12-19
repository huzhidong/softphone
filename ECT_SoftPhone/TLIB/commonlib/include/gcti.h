/*
** Genesys Common  API
** $Id: gcti.h /main/9 14-Oct-2003.14:15:25 PST tikin $
*/

#if !defined(_GCTI_H) || defined(COMPILE4NAMES)
#define _GCTI_H

#undef enum_start_ /* allow multiple inclusion */
#undef enum_end_   /* ( with different flags ) */
#undef i_
#undef i_end_
#undef i_reserved_

#ifdef COMPILE4NAMES
# define enum_start_(NAME)          char *NAME[] = {
# define i_(ITEM, VALUE, TEXT)        TEXT,
# ifdef C4N_INCLUDE_ALL
#   define i_reserved_(VALUE, TEXT)   TEXT,
# else
#   define i_reserved_(VALUE, TEXT)   "",
# endif
# define i_end_(ITEM, VALUE, TEXT)    TEXT
# define enum_end_(NAME)            };
#else
# define enum_start_(NAME)          typedef enum {
# define i_(ITEM, VALUE, TEXT)        ITEM = VALUE,
# define i_reserved_(VALUE, TEXT)
# define i_end_(ITEM, VALUE, TEXT)    ITEM = VALUE
# define enum_end_(NAME)            } NAME;
#endif
#undef COMPILE4NAMES
#undef C4N_INCLUDE_ALL

enum_start_(GctiCallState_names)         /* Final state-\/- used in Tserver */
  i_(GctiCStOk,             0, "Ok")                 /* .T */
  i_reserved_(              1, "Transferred")        /* .T */
  i_reserved_(              2, "Conferenced")        /* .T */
  i_(GctiCStGeneralError,   3, "General Error")      /* .T */
  i_(GctiCStSystemError,    4, "System Error")       /* FT */
  i_(GctiCStRemoteRelease,  5, "RemoteRelease")      /* *T */

  i_(GctiCStBusy,           6, "Busy")               /* FT */
  i_(GctiCStNoAnswer,       7, "No Answer")          /* FT */
  i_(GctiCStSitDetected,    8, "SIT Detected")       /* FT */
  i_(GctiCStAnswMachine,    9, "Answering Machine")  /* FT */
  i_(GctiCStAllTrunksBusy, 10, "All Trunks Busy")    /* FT */
  i_(GctiCStSitInvalidNum, 11, "SIT Invalid Num")    /* FT */
  i_(GctiCStSitVacant,     12, "SIT Vacant")         /* FT */
  i_(GctiCStSitIntercept,  13, "SIT Oper Intercept") /* FT */
  i_(GctiCStSitUnknown,    14, "SIT Unknown")        /* FT */
  i_(GctiCStSitNocircuit,  15, "SIT No Circuit")     /* FT */
  i_(GctiCStSitReorder,    16, "SIT Reorder")        /* FT */
  i_(GctiCStFaxDetected,   17, "Fax Detected")       /* FT */

  i_reserved_(             18, "Queue Full")         /* .T */
  i_reserved_(             19, "Cleared")            /* .T */
  i_reserved_(             20, "Overflowed")         /* .T */
  i_(GctiCStAbandoned,     21, "Abandoned")          /* FT */
  i_reserved_(             22, "Redirected")         /* .T */
  i_reserved_(             23, "Forwarded")          /* .T */
  i_reserved_(             24, "Consult")            /* .T */
  i_reserved_(             25, "Pickedup")           /* .T */
  i_(GctiCStDropped,       26, "Dropped")            /* FT */
  i_(GctiCStDroppedNoAns,  27, "Dropped No Answer")  /* ?T */

  i_(GctiCStUnknown,       28, "Unknown")            /* FT */
  i_reserved_(             29, "Covered")            /* .T */
  i_reserved_(             30, "Converse-On")        /* .T */
  i_reserved_(             31, "Bridged")            /* .T */

  i_(GctiCStSilence,          32, "Silence")
  i_(GctiCStAnswer,           33, "Answer")
  i_(GctiCStNuTone,           34, "NuTone")
  i_(GctiCStNoDialTone,       35, "NoDialTone")
  i_(GctiCStNoProgress,       36, "NoProgress")
  i_(GctiCStNoRingBack,       37, "NoRingBack")
  i_(GctiCStNoEstablished,    38, "NoEstablishe")
  i_(GctiCStPagerDetected,    39, "Pager Detected")

  i_(GctiCStWrongParty,       40, "Wrong Party")
  i_(GctiCStDialErr,          41, "Dial Error")
  i_(GctiCStDropErr,          42, "Call Drop Error")
  i_(GctiCStSwitchErr,        43, "Switch Error")
  i_(GctiCStNoFreePortErr,    44, "No Free Port Error")
  i_(GctiCStTransferErr,      45, "Transfer Error")
  i_(GctiCStStale,            46, "Stale")
  i_(GctiCStAgentCallBackErr, 47, "Agent CallBack Error")
  i_(GctiCStGroupCallBackErr, 48, "Group CallBack Error")

  i_reserved_(                49, "Deafened")        /* .T */
  i_reserved_(                50, "Held")            /* .T */

  i_(GctiCStDoNotCall,        51, "Do Not Call")   /* OCS & StatServer 6.0 */
  i_(GctiCStCancel,           52, "Cancel Record") /* FR#14587 10-Apr-2000 */

  i_(GctiCStWrongNumber,      53, "Wrong Number")  /* FR#65313 08-Sep-2003 */

  i_end_(GctiCSt_MAX,         54, "-MAX-")
enum_end_(GctiCallState)

enum_start_(GctiRecordType_names)
  i_(GctiRecTyNoRecordType,        0, "NoRecordType")
  i_(GctiRecTyUnknown,             1, "Unknown")
  i_(GctiRecTyGeneral,             2, "General")
  i_(GctiRecTyCampaignRescheduled, 3, "CampaignRescheduled")
  i_(GctiRecTyPersonalRescheduled, 4, "PersonalRescheduled")
  i_(GctiRecTyPersonalCallBack,    5, "PersonalCallBack")
  i_(GctiRecTyCampaignCallBack,    6, "CampaignCallBack")
  i_(GctiRecTyNoCall,              7, "NoCall")
  i_end_(GctiRecTy_MAX,            8, "-MAX-")
enum_end_(GctiRecordType)

enum_start_(GctiRecordStatus_names)
  i_(GctiRecStNoRecordStatus,      0, "NoRecordStatus")
  i_(GctiRecStReady,               1, "Ready")
  i_(GctiRecStRetrieved,           2, "Retrieved")
  i_(GctiRecStUpdated,             3, "Updated")
  i_(GctiRecStStale,               4, "Stale")
  i_(GctiRecStCancelled,           5, "Cancelled")
  i_(GctiRecStAgentError,          6, "AgentError")
  i_(GctiRecStChainUpdated,        7, "ChainUpdated")
  i_(GctiRecStMissedCallBack,      8, "MissedCallBack")
  i_(GctiRecStChainReady,          9, "ChainReady")
  i_end_(GctiRecSt_MAX,           10, "-MAX-")
enum_end_(GctiRecordStatus)

enum_start_(GctiContactType_names)
   i_(GctiCtTyNoContactType,       0, "NoContactType")
   i_(GctiCtTyHomePhone,           1, "HomePhone")
   i_(GctiCtTyDirectBusinessPhone, 2, "DirectBusinessPhone")
   i_(GctiCtTyBusinessWithExt,     3, "BusinessWithExt")
   i_(GctiCtTyMobile,              4, "Mobile")
   i_(GctiCtTyVacationPhone,       5, "VacationPhone")
   i_(GctiCtTyPager,               6, "Pager")
   i_(GctiCtTyModem,               7, "Modem")
   i_(GctiCtTyVoiceMail,           8, "VoiceMail")
   i_(GctiCtTyPinPager,            9, "PinPager")
   i_(GctiCtTyEMail,              10, "E-Mail")
   i_end_(GctiCtTy_MAX,           11, "-MAX-")
enum_end_(GctiContactType)

/*
 * Enums required for Voice Callback Project (ER#49113):
 */
enum_start_(GctiVoiceCallbackType_names) /* Type of Callback Request */
  i_(GctiVCTUnknown,   0, "Unknown")
  i_(GctiVCTASAP,      1, "Request for ASAP Callback")
  i_(GctiVCTScheduled, 2, "Request for Scheduled Callback")
  i_end_(GctiVCT_MAX,  3, "-MAX-")
enum_end_(GctiVoiceCallbackType)

enum_start_(GctiVoiceCallbackStage_names) /* Stage of processing */
  i_(GctiVCSUnknown,   0, "Unknown")
  i_(GctiVCSQueued,    1, "In queue, awaiting for distribution")
  i_(GctiVCSNotQueued, 2, "Not in queue")
  i_end_(GctiVCS_MAX,  3, "-MAX-")
enum_end_(GctiVoiceCallbackStage)

enum_start_(GctiVoiceCallbackOrigin_names) /* Origin of Callback Request */
  i_(GctiVCOUnknown,   0, "Unknown")
  i_(GctiVCOIVR,       1, "IVR")
  i_(GctiVCOWeb,       2, "Web Service")
  i_(GctiVCODesktop,   3, "Agent's Desktop")
  i_end_(GctiVCO_MAX,  4, "-MAX-")
enum_end_(GctiVoiceCallbackOrigin)

#endif

