/*
 * $Id: tliberr.h /main/56 4-Oct-2004.16:09:46 PST epi $
 */

#ifndef _TLIBRERR_H_
#define _TLIBRERR_H_

#define TERR_NOMORE_LICENSE	40 /* No more licenses available  */
#define TERR_NOT_REGISTERED     41 /* Client hadn't register DN   */
#define TERR_RESOURCE_SEIZED    42 /* Resource is already seized  */
#define TERR_IN_SAME_STATE      43 /* Object is already in requested state */

#define TERR_UNKNOWN_ERROR	50 /* Unrecognized error          */
#define TERR_UNSUP_OPER		51 /* Unsupported operation       */
#define TERR_INTERNAL		52 /* Internal error              */
#define TERR_INVALID_ATTR	53 /* Invalid attribute value     */
#define TERR_NO_SWITCH		54 /* No connection to the switch */
#define TERR_PROTO_VERS		55 /* Incorrect protocol version  */
#define TERR_INV_CONNID		56 /* Invalid ConnectionID        */
#define TERR_TIMEOUT            57 /* Timeout expired             */
#define TERR_OUT_OF_SERVICE     58 /* Out of service              */
#define TERR_NOT_CONFIGURED     59 /* DN is not configured in CME */

/*
 * MeridianLink specific error codes
 */
#define TERR_INV_CALL_TN	60 /* Invalid Calling Tn */
#define TERR_INV_CALL_DN	61 /* Invalid Calling Dn */
#define TERR_INCM_CALL_DN	70 /* Incomplete Calling Dn */
#define TERR_INV_CALD_DN	71 /* Invalid Called Dn */
#define TERR_INCM_CALD_DN	72 /* Incomplete Called Dn */
#define TERR_INCM_CALD_TN	73 /* Incomplete Called Tn */
#define TERR_INV_ORIG_MANN	74 /* Invalid Origination Manner */
#define TERR_INV_DEST_MANN	75 /* Invalid Destination Manner */
#define TERR_INV_ORIG_UTYPE	76 /* Invalid Origination User Type */
#define TERR_INVLD_CSTM_NUM	77 /* Invalid Customer Number */
#define TERR_SYS_OR_DB_ERR	78 /* System Or Db Error */
#define TERR_ORIG_PTY_BSY	79 /* Origination Party Busy */
#define TERR_ORIG_RSR_BLK	80  /* Origination Resource Blocking */
#define TERR_ORIG_SET_MTN	81  /* Origination Set Mainten Busy */
#define TERR_ON_HOOK		82  /* Is On Hook */
#define TERR_ORIG_DN_BUSY	83  /* Origination Dn Busy */
#define TERR_ORIG_RING		84  /* Origination Ringing */
#define TERR_UNABL_DISC_ORIG	85  /* Unable To Disconnect Origination */
#define TERR_ORIG_ACCS_BLK	86  /* Origination Access Blocking */
#define TERR_ORIG_IN_PHOLD	87  /* Origination On Permanent Hold */
#define TERR_ORIG_SYS_ERR	88  /* Origination System Error */
#define TERR_ORIG_END		89  /* Origination End */
#define TERR_ORIG_PTY_IN_ACD	90  /* Origination Party In Acd */
#define TERR_TERM_PTY_BUSY	91  /* Terminating Party Busy */
#define TERR_DEST_RSR_BLK	92  /* Destination Resource Blocking */
#define TERR_DEST_INV_STATE	93  /* Destination Invalid State */
#define TERR_DEST_ACCS_BLK	94  /* Destination Access Blocking */
#define TERR_DEST_SYS_ERR	95  /* Destination System Error */
#define TERR_CANT_COML_TRN	96  /* Cannot Complete Conference */
#define TERR_CANT_INIT_TRN	97  /* Cannot Initiate Transfer */
#define TERR_CANT_CMPL_TRN	98  /* Cannot Complete Transfer */
#define TERR_CANT_RTR_ORG	99  /* Cannot Retrieve Original Call */

/*
 * Cause errors
 */
#define TERR_UNKNOWN		100 /* Unknown cause */
#define TERR_BAD_ASSOC_ID	101 /* Bad associon ID */
#define TERR_MSG_TYPE		102 /* Bad message type */
#define TERR_UNEXP_ELEMENT	103 /* Unexpected information element */
#define TERR_MSG_NOT_PART	104 /* Message not part of registered service */
#define TERR_ELEM_MISSING	105 /* Information element missing */
#define TERR_BAD_AFF_ASSOC	106 /* Bad affected association ID */
#define TERR_BAD_MSG_LENGTH	107 /* Bad message length */
#define TERR_BAD_SEQ_NUMBER	108 /* Bad sequence number */
#define TERR_LINK_DOWN		109 /* Link down or bad link specified */
#define TERR_REQ_IN_PROGRESS	110 /* Request already in progress */
#define TERR_TOO_MANY_REQ	111 /* Too many outstanding requests */
#define TERR_MSG_OUT_OF_SEQ	112 /* Message out of sequence (e.g. application
				       tries to open a voice file before 
				       sending a message to logon mailbox) */

#define TERR_ASSOC_TAB_FULL	113 /* Association table is full */
#define TERR_APPL_TAB_FULL	114 /* Application table is full */
#define TERR_APPL_EXISTS	115 /* Application already exists */
#define TERR_BAD_MACH_NAME	116 /* Bad Meridian 1 machine name */
#define TERR_BAD_HOST_NAME	117 /* Bad host machine name */
#define TERR_SERV_UNAVAIL	118 /* Requested service unavailable */
#define TERR_BAD_PASSWD		119 /* Bad password */
#define TERR_POLL_TIMEOUT	120 /* Polling timeout */
#define TERR_BAD_MAIL_NAME	121 /* Bad Meridian Mail Name */

#define TERR_CANT_REG_DNS	122 /* Cannot register all DN's */
#define TERR_DN_NOT_EXIST	123 /* DN for association does not exist */
#define TERR_DN_TAB_FULL	124 /* DN table is full */
#define TERR_DN_ALRDY_REG	125 /* DN already registered */
#define TERR_CUST_REG		126 /* Customer number must be registered
				       to register a DN(s) */
#define TERR_CANT_REMOVE_DN	127 /* Cannot remove DN */
#define TERR_BAD_DN_TYPE	128 /* Bad DN type for DN registration */

#define TERR_PROC_NOT_EXIST	129 /* Link process does not exist */
#define TERR_LINK_ID_EXIST	130 /* Link ID already exists */
#define TERR_MACH_NAME_EXIST	131 /* Meridian 1 machine name or Host ID
				       already exists */
#define TERR_BAD_LINK_ID	132 /* Bad link ID */
#define TERR_LINK_ALRDY_EST	133 /* Link already established */
#define TERR_LINK_ALRDY_DIS	134 /* Link already disabled */
#define TERR_OPEN_CONF_FILE	135 /* Error in opening configuration file */
#define TERR_LINK_CONF_FAIL	136 /* Link configuration failed */
#define TERR_LINK_ENBL_FAIL	137 /* Enable link command failed */
#define TERR_LINK_DIS_FAIL	138 /* Disable link command failed */
#define TERR_LNK_CMD_NOT_SUP	139 /* Link command not supported */
#define TERR_LNK_STS_REQ	140 /* Link statistics request failed */
#define TERR_LNK_CONF_LARGE	141 /* Link configuration information is
				       too large */
#define TERR_LNK_CMD_FAILED	142 /* Link command failed due to
				       reconfiguration of associated link */
#define TERR_TRACE_ALRDY_EN	143 /* Trace already enabled */
#define TERR_TRACE_ALRDY_DIS	144 /* Trace already disabled */
#define TERR_SFW_NOT_EQIPD	145 /* Link to Meridian 1 failed because
				       required software option not equipped */
#define TERR_ID_MISMATCH	146 /* Link to Meridian 1 failed due
				       to Meridian 1 ID mismatch */
#define TERR_NO_LINK_RESPND	147 /* No link responding */

#define TERR_FCL_ALRDY_ENB	148 /* Facility already enabled */
#define TERR_FCL_ALRDY_DIS	149 /* Facility already disabled */
#define TERR_MSG_ALRDY_SET	150 /* Message(s) already set */
#define TERR_MSG_ALRDY_CLR	151 /* Message(s) already cleared */
#define TERR_UNABL_REC_FILE	152 /* Unable to open/write/ close */
                                    /* recording file */
#define TERR_BAD_AFFCT_MSG	153 /* Bad affected message */
#define TERR_CANT_CLR_ALL	154 /* Cannot clear all (filter, monitor, */
				    /* or record) */

#define TERR_ACCNT_INACT	155 /* Account inactive (time-out expired) */
#define TERR_ADMIN_SHUTDOWN	156 /* Meridian Mail shutdown by administrator */
#define TERR_SYSTEM_ERR		157 /* Meridian Mail system error */
#define TERR_VCHAN_NOT_ANS	158 /* Incoming Voice Channel not answered
				       in 15 seconds */
#define TERR_MANY_BAD_LOGIN	159 /* Too many bad login attempts */

#define TERR_FLOW_CTL_1		160 /* Flow control - level 1 */
#define TERR_FLOW_CTL_2		161 /* Flow control - level 2 */
#define TERR_FLOW_CTL_3		162 /* Flow control - level 3 */
#define TERR_FLOW_CTL_CLR	163 /* Flow control condition cleared */

#define TERR_BAD_SYSTEM_CMD	164 /* Bad system command */

#define TERR_ACCESS_RESTICT	165 /* Access restricted */
#define TERR_RES_UNAVAIL	166 /* Resource unavailable */
#define TERR_INV_CUST_NUM	167 /* Invalid customer number */
#define TERR_INV_ORIG_ADDR	168 /* Invalid origination address */
#define TERR_INV_DEST_REQ	169 /* Invalid destination request */
#define TERR_INV_MANNER		170 /* Invalid manner */
#define TERR_UNSUCC_RETRV	171 /* Unsuccessful retrieve original */
#define TERR_UNSUCC_TRANSFER	172 /* Unsuccessful transfer */
#define TERR_UNSUCC_CONFER	173 /* Unsuccessful conference */
#define TERR_UNSUCC_ANSWER	174 /* Unsuccessful answer request */
#define TERR_UNSUCC_RELEASE	175 /* Unsuccessful release request */
#define TERR_UNSUCC_REFER	176 /* Refer to Connection Status IE for
				       information */

#define TERR_TARG_DN_INV	177 /* Target DN Invalid */
#define TERR_TARG_DN_NOT_AST	178 /* Target DN not AST */
#define TERR_FTR_NOT_INVOK	179 /* Feature could not be invoked */
#define TERR_FTR_NOT_CFG	180 /* Feature not configured to set */
#define TERR_FTR_OUT_OF_RNG	181 /* Requested feature out of valid range */
#define TERR_TARG_NOT_AGENT	182 /* Target set not ACD agent */
#define TERR_TARG_VIRT_AGENT	183 /* Target set is a Virtual Agent */
#define TERR_MAINT_BUSY		184 /* Set is maintenance busy */
#define TERR_SET_WRONG_STATE	185 /* Set is in wrong state for invocation */
#define TERR_SET_TARG_STATE	186 /* Set is in target state */
#define TERR_ACD_LOGOFF		187 /* No NRDY/RDY while ACD set is logged out */

#define TERR_CUST_NRDY		188 /* Package C customer can't use NRDY
				       with IDN call */
#define TERR_FTR_IE_INV		189 /* Feature IE is missing or invalid */
#define TERR_DN_IE_INV		190 /* DN IE is missing or invalid */
#define TERR_AGENT_ID_IE_INV	191 /* Agent ID IE is missing or invalid */
#define TERR_AGENT_ID_INV	192 /* Agent ID is invalid */
#define TERR_CFW_DN_IE_INV	193 /* CFW DN IE is invalid */
#define TERR_CFW_TOO_LONG	194 /* The Call Forward DN is too long */
#define TERR_CFW_DN_INV		195 /* The call Forward DN is invalid */
#define TERR_INVOKE_CFW		196 /* User is invoking Call Forward */
#define TERR_MSB_NOT_SUPP	197 /* MSB/MSI not supported for 500/2500 sets */
#define TERR_5ACD_STATUS	198 /* 500/2500 ACD agent already changed
				       status */
#define TERR_5ACD_RUNG		199 /* 500/2500 ACD agent set is being rung */
#define TERR_MANUAL_LOGIN	200 /* User is manually loggin in 500/2500
				       ACD set */
#define TERR_OPT209_NOT_EQTP	201 /* Meridian Link Server Option 209
				       is not equipped */

#define TERR_RES_ACQ_ANOTHER	202 /* The resource is already acquired
				       by another application */
#define TERR_RES_ALRDY_ACQ	203 /* The resource is already acquired
				       by this application */
#define TERR_RES_NOT_RELEASD	204 /* The resource is not released */
#define TERR_CANT_ACQ_ALL	205 /* The application can't acquire all
				       the resource */
#define TERR_RES_TYPE_UNKNWN	206 /* The resource type is unknown */
#define TERR_AML_DOWN		207 /* The AML is down */
#define TERR_RES_TAB_FULL	208 /* The resource table is full */
#define TERR_CDN_NOT_CNG	209 /* The CDN is not configured or to operate
				       on controlled mode */
#define TERR_POLLTMR_OF_RNG	210 /* The Poll timer is out of range */
#define TERR_RES_ID_LNG_LONG	211 /* The resource ID length is too long */
#define TERR_ADMIN_DEV_DIS	212 /* Device disabled by administration */
#define TERR_NO_RSP_OPER_REQ	213 /* No response to operation request */
#define TERR_LOGON_TR_EXCEED	214 /* Logon tries exceeded */
#define TERR_NOT_EQTP_FTR	215 /* This release of the Meridian 1 software
				       is not equipped to operate this  feature */
#define TERR_RES_NOT_ACQ	216 /* The resource is not acquired by the
				       application */      
#define TERR_REG_NOT_SET	217 /* Registration not set up for request */
#define TERR_INTERNAL_ERR	218 /* Internal error */
#define TERR_BAD_RES_ID		219 /* Bad resource ID */
#define TERR_NO_RES_AVAIL	220 /* No internal resource available */
#define TERR_SRV_NOT_AVAIL	221 /* Service not available on device */
#define TERR_DEV_NOT_AVAIL	222 /* Device not available */

#define TERR_BAD_PARAM		223 /* Bad parameter passed to function */
#define TERR_NO_RESULT_AVAIL	224 /* No result available yet  */
#define TERR_NO_RESULT_TMOUT	225 /* No result - command timed out */
#define TERR_OUT_OF_MEM		226 /* Out of memory (local) */
#define TERR_INV_APPL_CLASS	227 /* Invalid application class */
#define TERR_INV_CMD_BFR_ACQ	228 /* Command invalid before `Acquire' */
#define TERR_MUST_REGISTER	229 /* Must register first */
#define TERR_MUST_DEREGIST	230 /* Must deregister first */
#define TERR_DN_BUSY		231 /* DN is busy */
#define TERR_DN_NO_ANSWER	232 /* No answer at DN */
#define TERR_CALL_REJECTED	233 /* Call has been rejected */
#define TERR_CONN_ATMPT_FAIL	234 /* Call connection attempt has failed */
#define TERR_CALL_COLLISION	235 /* Call resulted in collision */
#define TERR_TIMEOUT_PRF_OP	236 /* Timeout performing operation */
#define TERR_DISCON_CALL	237 /* Call has disconnected */

#define TERR_NO_QUEUE_SPACE	238 /* Msg send failed:  no queue space */
#define TERR_INV_PROC_TYPE	239 /* Invalid process type */
#define TERR_SERR_ACCS_APIQ	240 /* System error accessing API queue */
#define TERR_SERR_ACCS_EVQ	241 /* System error accessing Event queue */
#define TERR_MON_FUNC_INS	242 /* Monitor function already installed */
#define TERR_CLNT_NOT_MON	243 /* Client is not the monitor process */
#define TERR_WRONG_ACCS_VER	244 /* API not usable:  wrong ACCESS ver. */
#define TERR_ACCS_SMFR		245 /* Could not access/open a semaphore */
#define TERR_NO_FILE		246 /* No file at path specified */
#define TERR_CANT_FORK		247 /* Couldn't fork process at path */
#define TERR_LNK_MNGR_DEAD	248 /* Link Manager was already dead */
#define TERR_NOT_SPWN_LPM	249 /* Did not spawn LMP via m_Startlink */
#define TERR_DEAD_CHLD		250 /* Caller had dead child beesides LMP */
#define TERR_LMT_TOO_LONG	251 /* LMP took too long to die */
#define TERR_LH_MM_CMD_FAILED	252 /* LH not synch with MM cmmd failed */
#define TERR_LH_MM_CMD_SCCD	253 /* LH not synch with MM cmmd succeeded */
#define TERR_LH_NOT_SYNCH	254 /* LH not synchronized with MM */
#define TERR_UNEXPCTD_VAL	255 /* LH returneed an enexpected value */
#define TERR_MON_RESTRITC	256 /* API is restricted from monitor */
#define TERR_NO_LH_CONF		257 /* No LH configuration file found */

#define TERR_OP_NOT_CUR_SUP	258 /* Operation not currently supported */

#define TERR_INV_PASSWD		259 /* Invalid Password */
#define TERR_NO_MM_ACCS		260 /* No MM ACCESS Toolkit available */
#define TERR_SERVER_FULL	261 /* No free blocks, server is full */
#define TERR_DISK_SPACE		262 /* No free disk space in User Cabinet */
#define TERR_MUST_BE_LOGD	263 /* Must be logged on to use this command */
#define TERR_ACNT_ACCS_DEND	264 /* Access to account denied */
#define TERR_COMMAND_FAILED	265 /* Command Failed, check SEER console */
#define TERR_INV_ACCNT_TYPE	266 /* Invalid account type */
#define TERR_ALRDY_ACQUIRED	267 /* Already Acquired */
#define TERR_MNY_FAILD_MLOG	268 /* Too many failed m_Logon attempts */
#define TERR_API_NOT_SUP	269 /* API function is not supported */
#define TERR_BAD_USER_ID	270 /* Bad user id or mailbox number */
#define TERR_INV_FLAG		271 /* Invalid flag (0 or 1 are valid) */
#define TERR_WARN_LOGGED	272 /* Warning: Logged on elsewhere */
#define TERR_API_NOT_SUP_MM	273 /* API being used not supported by MM */
#define TERR_INV_CUST_SPEC	274 /* Invalid customer number specified */
#define TERR_CANT_ISSUE_CMD	275 /* Can't issue command while logged in */

#define TERR_APPL_ACK_ENS	276 /* An Appl has already acquired ENS */
#define TERR_BE_ENS_APPL	277 /* Must be ENS Appl to invoke APINS */

#define TERR_NOT_AVAIL_OPT	278 /* Option not availabele to customer */
#define TERR_ACQ_LIMIT_RCH	279 /* Max. # of acquire requests reached */
#define TERR_SESS_RELEASED	280 /* Session already released by system */
#define TERR_NO_CONNECTION	281 /* No connection has been established */
#define TERR_NO_VCHAN_AVAIL	282 /* No voice channel available */
#define TERR_INV_PLAY_POS	283 /* Invalid play position */
#define TERR_INV_RECORD_POS	284 /* Invalid recording position */
#define TERR_INV_DIRECTION	285 /* Invalid direction (parameter) */
#define TERR_VCHAN_IN_USE	286 /* Voice channel already in use */
#define TERR_NO_VCHAN_ACQ	287 /* No voice channel has been acquired */
#define TERR_NO_INC_CALL_ANS	288 /* No incoming call to answer */
#define TERR_ADDONCALL_FIRST	289 /* Must call m_AddOnCall first */
#define TERR_CHAN_ALRDY_ACPT	290 /* Channel already accepting calls */
#define TERR_OTHER_TEL_OPER	291 /* Other telephony operation in prog */
#define TERR_PLAY_CMD_IN_PRG	292 /* Play command already in progress */
#define TERR_INV_CMD_SEQ	293 /* Invalid command sequence */
#define TERR_REC_CMD_IN_PRG	294 /* Record command already in progress */
#define TERR_VOICE_OPER_FLR	295 /* Voice operation failure */
#define TERR_NO_VOICE_SEG	296 /* No voice to segment to play */
#define TERR_AT_END_VSEG	297 /* At end of voice segment */
#define TERR_TOO_MUCH_SLNCE	298 /* Ended because too much silence */
#define TERR_RECORD_LIMIT	299 /* recording limit has been reached */

#define TERR_BAD_NUM_OF_SEGS	300 /* Bad number of segments specified */
#define TERR_SEG_QUEUE_FULL	301 /* Segment play queue is full */
#define TERR_INV_DTMF_STRING	302 /* Invalid DTMF string */
#define TERR_BAD_CONTEXT	303 /* Context must be SOUND/SILENCE */
#define TERR_BAD_DURATION	304 /* Duration must be <= 5 Mins. */
#define TERR_NO_PREV_DETECT	305 /* No Previous Detect in progress */
#define TERR_SND_DETECT_PRGR	306 /* Sound Detect already in progress */

#define TERR_INST_EV_HANDLR	307 /* Must install event handler first */

#define TERR_NO_SUCH_ENTRY	308 /* No such entry found in directory */

#define TERR_UNABLE_ACCS_CAB	309 /* Unable to access user's cabinet */
#define TERR_INV_FILE_HND	310 /* Invalid file handle passed to cmd */
#define TERR_UNASGN_FILE_HND	311 /* Unassigned file handle */
#define TERR_INV_COMMIT_FLAG	312 /* Invalid commit flag (parameter) */
#define TERR_BEGN_OF_FILE	313 /* Reached the beginning of file */
#define TERR_CANT_OPEN_RD	314 /* Can't open Read file in Write mode */
#define TERR_END_OF_FILE	315 /* Reached the end of file */
#define TERR_FILE_ALRDY_OPEN	316 /* File is already open */
#define TERR_RONLY_FILE		317 /* Read-only file: Not commited */
#define TERR_CMD_RONLY_FILE	318 /* Can't do command on Read-only file */
#define TERR_INV_FNAME_FMT	319 /* Invalid filename format */
#define TERR_FILE_NUM_LIMIT	320 /* Maximum open file limit reached */
#define TERR_MFILEPTRN_FST	321 /* Must call m_FilePattern first */
#define TERR_FILE_NOT_EXIST	322 /* File does not exist */
#define TERR_INV_NEW_FLAG	323 /* Invalid new flag passed */
#define TERR_INV_FILE_ACCSS	324 /* Invalid file access mode used */
#define TERR_INV_DEL_PARM	325 /* Invalid delete parameter */
#define TERR_INV_FILE_CMD	326 /* Command invalid on this file type */
#define TERR_SEG_NOT_FOUND	327 /* Segment ID not found on file */
#define TERR_INV_FLD_LENGTH	328 /* Invalid length on field */
#define TERR_SEGPATTRN_FST	329 /* Must call m_SegPattern first */
#define TERR_INV_SCRIPT_LNG	330 /* Invalid script length field */
#define TERR_ISS_SCR_RTR	331 /* Issue script retrieve cmd first */
#define TERR_NO_VOICE_SEG_FL	332 /* No voice segments in the file */
#define TERR_TOO_MANY_SEG	333 /* Too many open seg. files for play */
#define TERR_SCRPT_TOO_LONG	334 /* Script for voice segment too long */
#define TERR_SEGS_LIMIT		335 /* Reached max # segs allowed in file */
#define TERR_BAD_VSEG_FTYPE	336 /* Bad voice segment file type */
#define TERR_INV_LANG		337 /* Invalid language specified */
#define TERR_INV_SEG_EDT_POS	338 /* Invalid segment editing position */
#define TERR_INV_SEG_EDT_OPR	339 /* Invalid segment editing operator */
#define TERR_INV_AMOUNT		340 /* Invalid amount specified */

#define TERR_NOT_MSG_FILE	341 /* File is not a message file */
#define TERR_INV_RECEIVER	342 /* Invalid receiver in address list */
#define TERR_MSG_RECPTS_LIM	343 /* Exceeded max. # of msg recipients */
#define TERR_INV_SUBJ_STR	344 /* Invalid subject string */
#define TERR_CANT_SEND_EMPT	345 /* Cannot send an empty message */
#define TERR_CALLSND_RCVD_MSG	346 /* CallSender/Reply only on recvd msgs */
#define TERR_MADDPATTERN_FST	347 /* Must call m_AddrPattern first */
#define TERR_CANT_RPLY		348 /* Cannot reply to external message */
#define TERR_CANT_FRWD		349 /* Cannot forward a private message */
#define TERR_NEED_RCVRS		350 /* Need 1 or more receivers to send */
#define TERR_MULT_NAMES		351 /* Multiple names matched, specify */
#define TERR_CANT_SEND_INC	352 /* Cannot send an incoming message */
#define TERR_DELAY_DLVRY	353 /* Delay delivery time too long */
#define TERR_RMT_SITE		354 /* Remote site not recognized */
#define TERR_OPER_INVALID	355 /* Operations invalid on system msgs */
#define TERR_CANT_RPLY_ALL	356 /* Cannot Reply All to Broadcast msg */
#define TERR_CANT_RPLY_AMIS	357 /* Cannot reply all on AMIS message */

#define TERR_NOT_FND_LIST	358 /* List number not found */
#define TERR_INV_PDL		359 /* Invalid PDL list number */
#define TERR_PDL_LIMIT		360 /* Exceeded max. # of entries in PDL */
#define TERR_UNACCS_USER_PRF	361 /* Unable to access user profile */
#define TERR_ADMIN_ACCS_ONLY	362 /* Resticted to admin access only */
#define TERR_INV_BOX_NUMBER	363 /* Invalid box number */
#define TERR_INV_LAST_NAME	364 /* Invalid last name */
#define TERR_INV_FST_NAME	365 /* Invalid first name */
#define TERR_INV_LIST_NUM	366 /* Invalid list number */
#define TERR_SHORT_PASSWD	367 /* Password too short */
#define TERR_INV_GRT_TYPE	368 /* Invalid greeting type */
#define TERR_OLD_PASSWD_LOG	369 /* Old password & logged on elsewhere */
#define TERR_OLD_PASSWD		370 /* Old passwords cannot be reused */
#define TERR_PERS_VRF_OPEN	371 /* Personal Verification already open */
#define TERR_GRTN_ALRDY_OPEN	372 /* Greeting already open */
#define TERR_NON_NUMERIC	373 /* Non-numeric in numeric field */
#define TERR_NO_MATCH_BOX	374 /* No matching box address in PDL */
#define TERR_MPDLPATTERN_FST	375 /* Must call m_PDLPattern first */
#define TERR_NOT_PDL_FILE	376 /* Not a PDL file */
#define TERR_INV_EXT_MSG_TYP	377 /* Invalid external message type */

#define TERR_HILEV_BFRE_API	378 /* Set HiLev flag before invoking API: */
#define TERR_INV_DIGIT		379 /* Invalid digit in ExitDigits */
#define TERR_DIG_TIMEOUT	380 /* Inter Digit Timeout occurred */
#define TERR_KBUF_OVRFLOW	381 /* Key Buffer overflow occurred */
#define TERR_API_INTRPTD	382 /* API interupted MM event */
#define TERR_INV_ITM		383 /* ItemToPlay in invalid format */
#define TERR_INV_PLAYTYPE	384 /* InvalidPlayType specified */
#define TERR_NO_PLAYEND		385 /* PLAYEND event not received */

#define TERR_INV_DIR_NUM	386 /* Invalid Directory Number passed */
#define TERR_INV_ANSWER_FLAG	387 /* Invalid answer flag */
#define TERR_DN_RESTR_PRF	388 /* DN has a restricted prefix */

#define TERR_LH_TAB_FULL	389 /* LH register Table full */
#define TERR_LHT_TAB_FULL	390 /* LH Trans Table full */
/*
 * call_status errors
 */
#define TERR_INV_PRIO		400 /* Invalid priority */
#define TERR_INV_MESSG_LEN	401 /* Invalid message length */
#define TERR_INV_ROUTE_ADDR	402 /* Invalid route address */
#define TERR_INV_APPL_TYPE	403 /* Invalid application type */
#define TERR_INV_MESSG_TYPE	404 /* Invalid message type */
#define TERR_INV_MESSG_REFID	405 /* Invalid message reference ID */
#define TERR_INV_CUSTOM_NUM	406 /* Invalid customer number */
#define TERR_UNAVL_CALL_REG	407 /* Can't obtain call register */
#define TERR_INV_CALL_REFID	408 /* Invalid call reference ID */
#define TERR_CALL_PRSNT		409 /* Call being presented, request rejected */
#define TERR_INAPPR_TRTM	410 /* Inappropriate first treatment, call in default */
#define TERR_NOT_ACQRD_CDN	411 /* Application has not acquired the CDN */
#define TERR_INV_SUBTYPE	412 /* Invalid subtype */
#define TERR_INV_MUSIC_ROUTE	413 /* Invalid music route or destination */
#define TERR_MUSIC_CONN_BLKD	414 /* Music connection blocked */
/*
 * The following 4 codes added 7/8/2002 for ER#42648:
 */
#define TERR_INV_DEST_DN        415 /* Invalid Destination DN */
#define TERR_INV_TONE_TREAT     416 /* Invalid Tone Treatment */
#define TERR_DN_MATCHES_CDN     417 /* Destination DN is the originating CDN */
#define TERR_TONE_CONN_BLKD     418 /* Tone Connection Blocked */

/*** ROCKWELL ***/
/* call_failed errors */
#define  TERR_OFFNET_NUMBER	450 /* The off-net number could not be dialed 
				       at this time */
#define  TERR_INVALID_RPR	451 /* The agent's Routing Privilige Level is invalid */
#define  TERR_ALL_TRUNKS_BUSY	452 /* An All Trunks Busy (ATB) condition 
				       was encountered */
#define  TERR_CALL_TRMTED	453 /* The call was terminated during routing */
#define  TERR_NO_AVL_LINE_KEYS	454 /* No available Line keys */
#define  TERR_LWP_INVALID	455 /* The Logical Workstation Number is invalid */
#define  TERR_POS_DN_INVALID	456 /* The Position DN is invalid */
#define  TERR_INOPER_DTMF_SNDR	457 /* The DTMF sender has become inoperate
				       during the call */
#define  TERR_DISALLW_OUTDIAL	458 /* The VRU's or staff person's COS 
				       disallows outdial */
#define  TERR_TARG_INVALID	459 /* The Target Party Identifier is invalid */
#define  TERR_CANT_INIT_DIAL	460 /* The position is not in valid state 
				       to initiate a dial request */
#define  TERR_TL_NOT_ACTIVTD	461 /* Transaction Link not activated for 
				       the indicated agent or supervisor */
#define  TERR_NO_ANS_DTCT	462 /* No answer detector or other necessary resources
				       are available for the call */
#define  TERR_INV_CALLING_DEV	463 /* Invalid Calling Device or Application ID 
				       was provided by host */
/* connection not cleared error */
#define  TERR_PARTY_NOT_ON_CALL	470	/* The party is not currently on call */
#define  TERR_PARTY_ON_HOLD	471 /* The party to be released has a call on hold */
#define  TERR_CANT_CLR_SUPERVS	472 /* A barged-in supervisor can't be cleared 
				       by an agent */
#define  TERR_CONSOLE_IN_MENU	473 /* The indicated console is in a menu mode */
#define  TERR_HEADSET_UNPLGD	474 /* Headset unplugged from indicated console */
#define  TERR_RELSE_ZIPFLASH	475 /* Attempted to release during zip/flash */
#define  TERR_INVLD_POSIT_DN	476 /* The Position DN is invalid */
#define  TERR_CALL_ID_INVALID	477 /* The Call ID is invalid */
#define  TERR_LWN_INVALID	478 /* The Logical Workstation Number is invalid */
#define  TERR_NOT_ACT_AGENT	479 /* Transaction Link not activated for indicated 
				       agent or supervisor or trunk */
#define  TERR_PORT_ID_INVALID	480 /* The Port ID is invalid */
/* new party transfer failed  */
#define  TERR_NOT_SIGNED_AGENT	481 /* The destination agent is not signed in */
#define  TERR_NOT_TRUNK_CALL	482 /* The call to be transfered is not a trunk call */
#define  TERR_SUPRV_BARG_CONSL	483 /* There is a supervisor barged in at 
				       the requesting console */
#define  TERR_BLIND_TRANSFR	484 /* Blind transfer of an emergency call 
				       is prohibited */
#define  TERR_TARG_ID_INVALID	485 /* The Target Identifier (Number of LWN) is invalid */
#define  TERR_INV_FOR_TRNSFR	486 /* The position is not a valid state 
				   to initiate a call transfer */
/* call not transferred errors */
#define  TERR_TARGET_BARGED_IN	487 /* The target parties have a supervisor barged in */
#define  TERR_TARGET_NOT_PRSNT	488 /* The target party is not present */
#define  TERR_ONLY_ONE_CALL	489 /* There is only one call at the console */
#define  TERR_TRNSFR_NOT_ALLWD	490 /* Transfer is not allowed */
#define  TERR_NO_LAST_HELD	491 /* No last held call */
#define  TERR_EMERGNCY_STATUS	492 /* Both parties to be transferred together 
				       have emergency status */
#define  TERR_INV_POSTN_STATE	493 /* The position is not in a valid state 
				       to initiate transfer request */
#define  TERR_NOT_ASSOC_POSTN	494 /* The position or the LWN is not associated 
				       with the ACD console */
/* host route failed */
#define  TERR_HOST_ROUTE_INV	495 /* The Host Route is invalid */
#define  TERR_INV_CALL_STATE	496 /* Call in invalid state */
#define  TERR_DEST_DN_INV	497 /* The Destination DN is invalid */
#define  TERR_BAD_CALL_PRIO	498 /* The Call Priority is out of range */
#define  TERR_BAD_INTERCPT	499 /* The Intercept Class is out of range */
#define  TERR_BAD_ORIG_ANN	500 /* The Origin Announcement ID is out of range */
#define  TERR_INV_APPL_ID	501 /* The Application ID is invalid */
#define  TERR_TOO_MORE_DEST	502 /* The host specified more then one destination */
/* no_caller_number */
#define  TERR_NETWORK_FAILED	503 /* The network failed to respond to request */
#define  TERR_NETWORK_REJECTED	504 /* The network rejected the request */
#define  TERR_NOT_STRTED_QUEUE	505 /* The trunk associated with this call does not
				       support any kind of netwotk quering after 
				       the initial call set-up */
#define  TERR_RECVD_INV_STATE	506 /* Request received in an invalid state */
/* call progress failture */
#define  TERR_CALL_TRM_SYS_RCVRY 507 /* The call was terminated due to
					a system recovery */
#define  TERR_TRUNK_RLSD_SYS_PBL 508 /* The trunk was released due to system problem */
#define  TERR_TRUNK_RLSD_END	509 /* The trunk was released due to distant end */
#define  TERR_BUSY_TONE_DETCTD	510 /* Busy tone was detected */
#define  TERR_REORDER_TONE	511 /* Reorder tone was detected */
#define  TERR_RING_TIMEOUT	512 /* Ring timeout was occurred */
#define  TERR_NO_ACTVTY_TRUNK	513 /* Trunk No Activity detected */
#define  TERR_ANS_DET_INOPER	514 /* The answer detector has become inoperable 
				       during the call */
#define  TERR_APPL_DN_INVALID	515 /* The application's DN is invalid */
#define  TERR_APPL_DN_UNASSOC	516 /* The application's DN is valid,
				       but not associated with an application */
#define  TERR_SIT_DETECTED	518 /* An SIT was detected */
#define  TERR_ANS_MACH_DETCTD	519 /* Answering machine detected */
/* negative response to make call */
#define  TERR_POS_INV_FOR_DIAL	520 /* The position is not a valid state 
				       to initiate a dial request */
#define  TERR_LINK_KEYS_USED	521 /* The Link's keys on the agent's console are 
				       all being used */
/* negative response to new party transfer */
#define  TERR_REQ_POS_DN_INV	522 /* The requesting position's DN is invalid */
#define  TERR_POS_INV_FOR_TRNSFR 523 /* The position is not a valid state
					to initiate a transfer request */
#define  TERR_INV_CALL_DEV	524 /* Invalid Calling Device or Application ID
				       was provided by the host */
/* negative response to feature access */
#define  TERR_CONS_NOT_VALID	525 /* The console is not in a valid condition to
				       allow the activity specified in the request */
#define  TERR_INV_SIGN_IN	526 /* Invalid sign-in number */
#define  TERR_ALRDY_SIGN_IN	527 /* The agent's sign-in number is already active
				       at another console */
#define  TERR_OUT_OF_SRVCE	528 /* The agent's or supervisor position is out of
				       service */
#define  TERR_VACANT_POS	529 /* The position is vacant */
#define  TERR_INVALID_GROUP	530 /* The agent's information group is invalid */
#define  TERR_INV_SIGN_IN_NUM	531 /* The agent's or supervisor's sign-in number
				       is invalid */
#define  TERR_AGENT_GRP_INV	532 /* The agent's agent group number is invalid */
#define  TERR_BARGED_IN		533 /* A supervisor is currently barged in to
				       the agent's console */
#define  TERR_CANT_SET_SUPRVS	534 /* The supervisor's position cannot be set
				       to Available and/or Call Work State(s) */
#define  TERR_DIR_NUM_INV	535 /* The agent's or supervisor's directory number
				       is invalid */
#define  TERR_2GRPS_SPCFD	536 /* Two primary or two secondary agent groups
				       were specified in the message */
#define  TERR_CANT_SIGN_IN	537 /* The supervisor signing-in can't sign in to
				       agent group(s) */
#define  TERR_POSTN_IN_MENU	538 /* The position is in a menu */
#define  TERR_ASSOC_WITH_VRU	539 /* The LWN or Position DN  is associated with
				       a VRU; Feature Access is for access to agent
				       or supervisor, not VRU */
#define  TERR_BAD_SIGN_IN_RSN	540 /* Sign-out reason received for agent not
				       provisioned on switch with that option */
/* general error codes */
#define  TERR_INV_MSG_TYPE	541 /* Invalid Message Type */
#define  TERR_MSG_INV_NOW	542 /* Message type not valid at this time */
#define  TERR_INV_MSG_ELEM_ID	543 /* Invalid message element identifier */
#define  TERR_INV_ELEM_ORDER	544 /* Invalid order of message elements */
#define  TERR_INV_ELEM_VAL	545 /* Invalid value within a message element */
#define  TERR_MISSING_ELEM	546 /* Missing mandatory message element */
#define  TERR_INV_ME_LENGTH_GT	547 /* Indicated length of last ME is greater
				       than number of bytes delivered */
#define  TERR_INV_ME_LENGTH_LT	548 /* Indicated length of last ME is less
				       than number of unprocessed bytes */
#define  TERR_OTHER_INV_FRMT	549 /* Other invalid format */
/*
 * Added 4/9/2003 ER#56454, corrected 4/24/2003 as requested by Zoubarev
 */
#define TERR_ALRDY_SIGN_IN_HERE  550 /* The position already has an agent or supervisor signed-in */
#define TERR_ALRDY_SIGN_OUT_HERE 551 /* The console position is already signed-out */

#define TERR_ROUTE_BFR_ACCEPT   552 /* The host attempted to route an overflow in call to a port before an ACCEPT was sent */
#define TERR_BAD_ORIG_LWN       553 /* The Originating LWN is invalid */
#define TERR_BAD_ORIG_POS       554 /* The Originating Position's DN is invalid */
#define TERR_BAD_ROUTE_ATTEMPT  555 /* An invalid routing attempt was made */
#define TERR_REQ_IGNORED        556 /* A request to perform a Network Transfer was ignored */
#define TERR_REQ_FAILED         557 /* A request to perform an action has failed because of lack of resources */
#define TERR_PRIOR_ROUTE_PEND   558 /* Prior Route Pending */
#define TERR_HOOKF_STATE        559 /* Call is in a Hookflash State */
#define TERR_ACD_BUSY           560 /* The ACD is busy sending */
#define TERR_CALL_EST_PEND      561 /* Call Established Pending */
#define TERR_TERMINATING_PORT   562 /* Terminating Port Error */
#define TERR_NO_CALL            563 /* No call to reroute */
#define TERR_TL_NOT_ACTIV_PORT  564 /* Transaction link not activated for indicated port */
#define TERR_INVALID_STATE      565 /* Invalid state */
#define TERR_BAD_DEVICE_STATE   566 /* The device is in an invalid state */
#define TERR_FAXMODEM_DTCTD     567 /* Fax/modem was detected */
#define TERR_NO_PSEUDO_PORT     568 /* No available pseudoports */
#define TERR_MAX_CALL_PERS      569 /* Maximum number of calls/second was exceeded */
#define TERR_INCRRT_USAGE_LWN_PRFX 570  /*  Incorrect usage of LWN prefix */

/*
 * Asai g3 specific error codes
 */
#define TERR_ASAI_START			600

#define TERR_ASAI_INVLDNUM		(TERR_ASAI_START+0)	/* Invalid origination or destination address */
#define TERR_ASAI_PROTERR		(TERR_ASAI_START+1)	/* Capability sequence has been violated, or underlying protocol error has been detected */
#define TERR_ASAI_RESUNAVL		(TERR_ASAI_START+2)	/* Resources to fulfill service are not available */
#define TERR_ASAI_FACUNSUB		(TERR_ASAI_START+3)	/* Capability is implemented but not subscribed to by requester */
#define TERR_ASAI_SER_UNIMP		(TERR_ASAI_START+4)	/* Noncompatible options selected */
#define TERR_ASAI_MAND_INFO		(TERR_ASAI_START+5)	/* One of the required parameters is missing */
#define TERR_ASAI_INVLDIE		(TERR_ASAI_START+6)	/* Value specified in parameter is not allowed or defined */
#define TERR_ASAI_SERV_UNAVIL		(TERR_ASAI_START+7)	/* Domain or call is being monitored by another adjunct */
#define TERR_ASAI_CALLID_TERM		(TERR_ASAI_START+8)	/* Call is no longer in active state */
#define TERR_ASAI_INCOM_ST		(TERR_ASAI_START+9)	/* Message not compatible with call state */
#define TERR_ASAI_INVALID_CRV		(TERR_ASAI_START+10)	/* Invalid call identifier used or call does not exist */
#define TERR_ASAI_INCOM_OPT		(TERR_ASAI_START+11)	/* Incompatible options used to establish the call */
#define TERR_ASAI_REC_TIMER		(TERR_ASAI_START+12)	/* Timer expired */
#define TERR_ASAI_NOLOGIN		(TERR_ASAI_START+13)	/* Agent not logged in to split */
#define TERR_ASAI_NOSPLIT_MEM		(TERR_ASAI_START+14)	/* Agent not member of specified split or split number specified incorrectly */
#define TERR_ASAI_USER_BUSY		(TERR_ASAI_START+15)	/* User busy */
#define TERR_ASAI_NOUSE_RESP		(TERR_ASAI_START+16)	/* Origination address does not respond to service */
#define TERR_ASAI_PERM_DENIED		(TERR_ASAI_START+17)	/* Permission checks for service have failed */
#define TERR_ASAI_CLUST_TERM		(TERR_ASAI_START+18)	/* Association terminated because service is not active */
#define TERR_ASAI_OUT_OF_SERV		(TERR_ASAI_START+19)	/* Domain has been removed by administration */
#define TERR_ASAI_INCS_AGT_ST		(TERR_ASAI_START+20)	/* Agent not in compatible state */
#define TERR_ASAI_MAXLOGIN		(TERR_ASAI_START+21)	/* Agent logged into the maximum number of splits */
#define TERR_ASAI_INC_PASWD		(TERR_ASAI_START+22)	/* Invalid login password */
#define TERR_ASAI_AGT_STATE		(TERR_ASAI_START+23)	/* Request to put agent in same state s/he already in */
#define TERR_ASAI_BAD_ADMIN		(TERR_ASAI_START+24)	/* ACD not provisioned or optioned */
#define TERR_ASAI_NORMAL		(TERR_ASAI_START+25)	/* Normal termination; call routed successfully */
#define TERR_ASAI_NETCONJ		(TERR_ASAI_START+26)	/* Association terminated because of network congestion */
#define TERR_ASAI_BAD_IE		(TERR_ASAI_START+27)	/* Unknown information element detected */
#define TERR_ASAI_QUEFULL		(TERR_ASAI_START+28)	/* Queue is full */
#define TERR_ASAI_REORDER_DENIAL	(TERR_ASAI_START+29)	/* Reorder/denial */
#define TERR_ASAI_ADMIN_PROGRESS	(TERR_ASAI_START+30)	/* Administration is in progress; request cannot be serviced */
#define TERR_ASAI_FEATURE_REJECTED	(TERR_ASAI_START+31)	/* The switch has rejected a request from the adjunct */
#define TERR_ASAI_UNASSIGNED_NUM	(TERR_ASAI_START+32)	/* Unassigned number */
#define TERR_ASAI_CALL_REJECTED		(TERR_ASAI_START+33)	/* Call rejected */
#define TERR_ASAI_NUM_CHANGED		(TERR_ASAI_START+34)	/* Number changed */
#define TERR_ASAI_NORMAL_UNSPECIF	(TERR_ASAI_START+35)	/* Normal, unspecified */
#define TERR_ASAI_NO_CIRCUIT		(TERR_ASAI_START+36)	/* No circuit or channel available */
#define TERR_ASAI_TEMP_FAILURE		(TERR_ASAI_START+37)	/* Temporary failure */
#define TERR_ASAI_BEARER_CAP_UNAVAIL	(TERR_ASAI_START+38)	/* Bearer capability not presently available */
#define TERR_ASAI_INCOMPAT_DESTINATION	(TERR_ASAI_START+39)	/* Incompatible destination */
#define TERR_ASAI_INVALID_MESSAGE	(TERR_ASAI_START+40)	/* Invalid message, unspecified (backward compatibility) */
#define TERR_ASAI_NON_EXIST_MESSAGE	(TERR_ASAI_START+41)	/* Message nonexistent/not implemented */
#define TERR_ASAI_UNSPECIFIED		(TERR_ASAI_START+42)	/* Unspecified */
#define TERR_ASAI_NO_ANSWER		(TERR_ASAI_START+43)	/* No answer */
#define TERR_ASAI_NO_TRUNKS		(TERR_ASAI_START+44)	/* Trunks not available */
#define TERR_ASAI_NO_CLASSIFIERS	(TERR_ASAI_START+45)	/* Classifiers not available */
#define TERR_ASAI_REDIRECT		(TERR_ASAI_START+46)	/* Redirected */
#define TERR_ASAI_NETWORK_OUT_OF_ORDER	(TERR_ASAI_START+47)	/* Network out of order */
#define TERR_ASAI_CAUSE_UNKNOWN		(TERR_ASAI_START+48)	/* Undefined value returned from switch */
#define TERR_ASAI_OUT_CALL_BARRED	(TERR_ASAI_START+49)	/* Outgoing call has been barred */
#define TERR_ASAI_REMAINS_IN_Q		(TERR_ASAI_START+50)	/* Call remains in queue */
#define TERR_ASAI_BEARER_SVC_NOT_IMPL	(TERR_ASAI_START+51)	/* Bearer service not implemented */
#define TERR_ASAI_TIMED_ANSWER		(TERR_ASAI_START+52)	/* Assumed answer based on internal timer */
#define TERR_ASAI_VOICE_ENERGY_ANSWER	(TERR_ASAI_START+53)	/* Voice energy detected by switch */
#define TERR_ASAI_NO_TONE_CHANNEL	(TERR_ASAI_START+54)	/* Channel/tone does not exist (no tone connected to the special call) */
#define TERR_ASAI_ANSWERING_MACHINE	(TERR_ASAI_START+55)	/* Answering machine detected */
#define TERR_ASAI_FACILITY_REJECTED	(TERR_ASAI_START+56)	/* Facility rejected */

/* DMS-100 errors */

#define TERR_DMS_START 700

#define TERR_INV_LOGIN_REQ		(TERR_DMS_START + 0)
#define TERR_INV_LOGOUT_REQ		(TERR_DMS_START + 1)
#define TERR_INV_READY_REQ		(TERR_DMS_START + 2)
#define TERR_INV_NOT_RDY_REQ		(TERR_DMS_START + 3)
#define TERR_INV_MAKE_CALL		(TERR_DMS_START + 4)
#define TERR_INV_ROUTE_REQ		(TERR_DMS_START + 5)
#define TERR_INV_MUTE_TRSFR		(TERR_DMS_START + 6)
#define TERR_INV_INIT_CONF		(TERR_DMS_START + 7)
#define TERR_INV_INIT_TRSFR		(TERR_DMS_START + 8)
#define TERR_INV_CMPL_CONF		(TERR_DMS_START + 9)
#define TERR_INV_CMPL_TRSFR		(TERR_DMS_START + 10)
#define TERR_INV_RETR_REQ		(TERR_DMS_START + 11)
#define TERR_INV_CNTL_DN		(TERR_DMS_START + 12)
#define TERR_CANT_CONVERT		(TERR_DMS_START + 13)
#define TERR_INV_CALL_ID		(TERR_DMS_START + 14)

/* DMS-100 specific errors */
#define TERR_DMS_NOT_ALLOWED		(TERR_DMS_START + 15)
#define TERR_DMS_NOT_IDLE		(TERR_DMS_START + 16)
#define TERR_DMS_NOT_LOGGED_IN		(TERR_DMS_START + 17)
#define TERR_DMS_ORIG_TIME_OUT		(TERR_DMS_START + 18)
#define TERR_DMS_MAKECALL_RCRS		(TERR_DMS_START + 19)
#define TERR_DMS_MISS_ORIG_ADDR		(TERR_DMS_START + 20)
#define TERR_DMS_MISS_DEST_ADDR		(TERR_DMS_START + 21)
#define TERR_DMS_MISS_CALL_TYPE		(TERR_DMS_START + 22)
#define TERR_DMS_INV_ORIG_ADDR		(TERR_DMS_START + 23)
#define TERR_DMS_INV_DEST_ADDR		(TERR_DMS_START + 24)
#define TERR_DMS_INV_CALL_TYPE		(TERR_DMS_START + 25)
#define TERR_DMS_INV_AUTHCODE		(TERR_DMS_START + 26)
#define TERR_DMS_INV_ACCTCODE		(TERR_DMS_START + 27)
#define TERR_DMS_AUTH_OP_NSUBSCR	(TERR_DMS_START + 28)
#define TERR_DMS_ACCT_OP_NSUBSCR	(TERR_DMS_START + 29)
#define TERR_DMS_OPER_ABORTED		(TERR_DMS_START + 30)
#define TERR_DMS_MISMATCH_STATE		(TERR_DMS_START + 31)
#define TERR_DMS_UNEXP_ACCT		(TERR_DMS_START + 32)

#define TERR_DMS_ILL_OPERATION		(TERR_DMS_START + 33)
#define TERR_DMS_INV_ASSOC_DN		(TERR_DMS_START + 34)
#define TERR_DMS_ASSOC_OTH_SESS		(TERR_DMS_START + 35)
#define TERR_DMS_MAX_NO_OF_LINES	(TERR_DMS_START + 36)
#define TERR_DMS_NO_RESOURCES		(TERR_DMS_START + 37)
#define TERR_DMS_MISSING_ASSOC_DN	(TERR_DMS_START + 38)

#define TERR_DMS_ALREADY_IN_SET		(TERR_DMS_START + 40)
#define TERR_DMS_NOT_IN_SET		(TERR_DMS_START + 41)
#define TERR_DMS_INV_DN			(TERR_DMS_START + 42)
#define TERR_DMS_UNKNOWN_DN		(TERR_DMS_START + 43)
#define TERR_DMS_INV_FILTER		(TERR_DMS_START + 44)

#define TERR_DMS_MIS_PARAM		(TERR_DMS_START + 45)
#define TERR_DMS_INV_PARAM		(TERR_DMS_START + 46)
#define TERR_DMS_INV_CONTENT		(TERR_DMS_START + 47)
#define TERR_DMS_INV_LINE_CONF		(TERR_DMS_START + 48)
#define TERR_DMS_ALRDY_LOGIN		(TERR_DMS_START + 49)
#define TERR_DMS_LOGID_IN_USE		(TERR_DMS_START + 50)
#define TERR_DMS_POS_ALRD_LOGIN		(TERR_DMS_START + 51)
#define TERR_DMS_INV_SET_STATE		(TERR_DMS_START + 52)
#define TERR_DMS_INV_PASSWD		(TERR_DMS_START + 53)
#define TERR_DMS_RSRC_UNAVAIL		(TERR_DMS_START + 54)
#define TERR_DMS_AGNT_NOT_LOGIN		(TERR_DMS_START + 55)
#define TERR_DMS_AGNT_LOG_PEND		(TERR_DMS_START + 56)
#define TERR_DMS_INV_POS_STATE		(TERR_DMS_START + 57)
#define TERR_DMS_AGNT_READY		(TERR_DMS_START + 58)
#define TERR_DMS_AGNT_NOT_RDY		(TERR_DMS_START + 59)
#define TERR_DMS_SUPERV_OVERRIDE	(TERR_DMS_START + 60)
#define TERR_DMS_INV_RECON_CALL         (TERR_DMS_START + 61)
#define TERR_DMS_INV_DEL_FROM_CONF	(TERR_DMS_START + 62)
#define TERR_DMS_AGENT_POSITION_BUSY	(TERR_DMS_START + 63) /* ER#34511 */

/* Intecom errors */
#define TERR_INTECOM_START 800

#define TERR_INTC_INVALID_LINE_ID		(TERR_INTECOM_START + 0)
#define TERR_INTC_INVALID_TRUNK_ID		(TERR_INTECOM_START + 1)
#define TERR_INTC_INVALID_DIGIT_STRING		(TERR_INTECOM_START + 2)
#define TERR_INTC_INVALID_OAI_VALUE		(TERR_INTECOM_START + 3)
#define TERR_INTC_INVALID_MSG_TYPE		(TERR_INTECOM_START + 4)
#define TERR_INTC_INVALID_MSG_ATTRIB		(TERR_INTECOM_START + 5)
#define TERR_INTC_ARC_ORIGIN_NOT_AVAIL		(TERR_INTECOM_START + 6)
#define TERR_INTC_NOT_ARC_ORIGIN_CALL		(TERR_INTECOM_START + 7)
#define TERR_INTC_ORIGIN_COS_DENIES_ARC_CALLS	(TERR_INTECOM_START + 8)
#define TERR_INTC_INVALID_TERMINAL_TYPE		(TERR_INTECOM_START + 9)
#define TERR_INTC_FEATURE_NOT_AVAILABLE		(TERR_INTECOM_START + 10)
#define TERR_INTC_DB_ERROR			(TERR_INTECOM_START + 11)
#define TERR_INTC_BUSY_IXL_TRUNKS		(TERR_INTECOM_START + 12)
#define TERR_INTC_ROUTE_TIMEOUT			(TERR_INTECOM_START + 13)
#define TERR_INTC_INVALID_DEST_ID		(TERR_INTECOM_START + 14)
#define TERR_INTC_INVALID_PORT_ID		(TERR_INTECOM_START + 15)
#define TERR_INTC_INVALID_STATE_COND		(TERR_INTECOM_START + 16)
#define TERR_INTC_INVALID_AGENT_PASSWORD	(TERR_INTECOM_START + 17)
#define TERR_INTC_INVALID_AGENT_ID		(TERR_INTECOM_START + 18)
#define TERR_INTC_INVALID_CALL_ID		(TERR_INTECOM_START + 19)
#define TERR_INTC_INVALID_TIMER_VALUE		(TERR_INTECOM_START + 20)
#define TERR_INTC_LACK_SYS_RESOURCE		(TERR_INTECOM_START + 21)
#define TERR_INTC_NO_IDLE_CALL_FACILITY		(TERR_INTECOM_START + 22)
#define TERR_INTC_BAD_DEST_DIGITS		(TERR_INTECOM_START + 23)
#define TERR_INTC_INV_STATE			(TERR_INTECOM_START + 24)
#define TERR_INTC_BAD_ADDR_TYPE			(TERR_INTECOM_START + 25)
#define TERR_INTC_BAD_ADDR_INFO_TYPE		(TERR_INTECOM_START + 26)
#define TERR_INTC_INTERNAL			(TERR_INTECOM_START + 50)

  enum {

   /* Aspect ACD specific errors */

   TERR_ASPECT_START			=  900,

   TERR_ASPECT_NEGATIVE_ACKNOWLEDGEMENT	= TERR_ASPECT_START + 10,

   TERR_ASPECT_INVALID_EQUIPMENT	= TERR_ASPECT_START + 11,
   TERR_ASPECT_INVALID_TELESET_STATE	= TERR_ASPECT_START + 12,

   TERR_ASPECT_INVALID_CCT		= TERR_ASPECT_START + 13,
   TERR_ASPECT_INVALID_DIALING_PATTERN	= TERR_ASPECT_START + 14,
   TERR_ASPECT_INVALID_MODE		= TERR_ASPECT_START + 15,
   TERR_ASPECT_INVALID_ORIGINATION	= TERR_ASPECT_START + 16,
   TERR_ASPECT_INVALID_ROUTE		= TERR_ASPECT_START + 17,

   TERR_ASPECT_INVALID_REASON_CODE	= TERR_ASPECT_START + 70,

   TERR_ASPECT_END			= TERR_ASPECT_START + 99

  };

#define TERR_EXR_START 1000
#define TERR_EXR_NO_SUCH_SERVER                 (TERR_EXR_START + 0)
#define TERR_EXR_REMOTE_SERVER_DISCONNECTED     (TERR_EXR_START + 1)
#define TERR_EXR_REMOTE_SERVER_ERROR            (TERR_EXR_START + 2)
#define TERR_EXR_WRONG_PROTOCOL_VERSION         (TERR_EXR_START + 3)
#define TERR_EXR_REMOTE_LINK_DISCONNECTED	(TERR_EXR_START + 4)
#define TERR_EXR_FEATURE_NOT_INITED		(TERR_EXR_START + 5)
#define TERR_EXR_NO_FREE_CDNS			(TERR_EXR_START + 6)
#define TERR_EXR_NO_ACCESS_NUMBER		(TERR_EXR_START + 7)
#define TERR_EXR_TCS_FEATURE_NOT_INITIATED	(TERR_EXR_START + 8)
#define TERR_EXR_BAD_ROUTE_TYPE			(TERR_EXR_START + 9)
#define TERR_EXR_BAD_REQUEST			(TERR_EXR_START + 10)  
#define TERR_EXR_NO_PRIMARY_ON_LOCATION		(TERR_EXR_START + 11)
#define TERR_EXR_BAD_LOCATION_SPECIFIED		(TERR_EXR_START + 12)  
#define TERR_ISCC_START				TERR_EXR_START
#define TERR_ISCC_LOCATION_IS_DISCONNECTED	TERR_EXR_REMOTE_SERVER_DISCONNECTED
#define TERR_ISCC_REMOTE_LINK_IS_DISCONNECTED	TERR_EXR_REMOTE_LINK_DISCONNECTED
#define TERR_ISCC_FEATURE_IS_NOT_ENABLED	TERR_EXR_FEATURE_NOT_INITED
#define TERR_ISCC_BAD_LOCATION_SPECIFIED	TERR_EXR_BAD_LOCATION_SPECIFIED  
#define TERR_ISCC_TCS_FEATURE_NOT_INITIATED     TERR_EXR_TCS_FEATURE_NOT_INITIATED
#define TERR_ISCC_TRANSACTION_TIME_EXPIRED	(TERR_ISCC_START + 13)  
#define TERR_ISCC_ACCS_RESOURCE_NOT_CONFIGURED	(TERR_ISCC_START + 14)  
#define TERR_ISCC_ACCS_RESOURCE_NOT_REGISTERED	(TERR_ISCC_START + 15)  
#define TERR_ISCC_CLIENT_NOT_AUTHORIZED		(TERR_ISCC_START + 16)
#define TERR_ISCC_BAD_XACTION_TYPE		(TERR_ISCC_START + 17)
#define TERR_ISCC_BAD_XACTION_DATA		(TERR_ISCC_START + 18)
#define TERR_ISCC_BAD_LOCATION_QUERY_REQUEST	(TERR_ISCC_START + 19)
#define TERR_ISCC_BAD_ORIGIN_LOCATION		(TERR_ISCC_START + 20)
#define TERR_ISCC_BAD_DESTINATION_DN            (TERR_ISCC_START + 21)

 enum {

   /* CSTA specific errors */

   TERR_CSTA_START			= 1100,

   TERR_CSTA_RO_GEN_UNREC_ADPU		= TERR_CSTA_START +  0,	/* Unrecognized APDU */
   TERR_CSTA_RO_GEN_MISTYP_ADPU,				/* Mistyped APDU */
   TERR_CSTA_RO_GEN_BAD_STR_ADPU,				/* Badly structured APDU */

   TERR_CSTA_RO_INV_DUPLICATE		= TERR_CSTA_START + 10,	/* Duplicate invocation */
   TERR_CSTA_RO_INV_UNREC_OP,					/* Unrecognized operation */
   TERR_CSTA_RO_INV_MISTYP_ARG,					/* Mistyped argument */
   TERR_CSTA_RO_INV_RES_LIMIT,					/* Resource limitation */
   TERR_CSTA_RO_INV_INITR_RELEASING,				/* Initiator releasing */
   TERR_CSTA_RO_INV_UNREC_LINK_ID,				/* Unrecognized linked ID */
   TERR_CSTA_RO_INV_LINK_RESP_UNEXP,				/* Linked response unexpected */
   TERR_CSTA_RO_INV_UNEXP_CHILD_OP,				/* Unexpected child operation */

   TERR_CSTA_RO_RES_UNREC_INVOK		= TERR_CSTA_START + 20,	/* Unrecognized invocation */
   TERR_CSTA_RO_RES_RESP_UNEXP,					/* Result response unexpected */
   TERR_CSTA_RO_RES_MISTYP_RES,					/* Mistyped result */

   TERR_CSTA_RO_ERR_UNREC_INVOK		= TERR_CSTA_START + 30,	/* Unrecognized invocation */
   TERR_CSTA_RO_ERR_RESP_UNEXP,					/* Error response unexpected */
   TERR_CSTA_RO_ERR_UNREC_ERROR,				/* Unrecognized error */
   TERR_CSTA_RO_ERR_UNEXP_ERROR,				/* Unexpected error */
   TERR_CSTA_RO_ERR_MISTYP_PARAM,				/* Mistyped parameter */

   TERR_CSTA_OPER_GENERIC		= TERR_CSTA_START + 40,	/* Generic operation error */
   TERR_CSTA_OPER_REQ_INCOMPAT,					/* Request incompatible with object */
   TERR_CSTA_OPER_OUT_OF_RANGE,					/* Value out of range */
   TERR_CSTA_OPER_OBJ_NOT_KNOWN,				/* Object not known */
   TERR_CSTA_OPER_INV_CALLING,					/* Invalid calling device */
   TERR_CSTA_OPER_INV_CALLED,					/* Invalid called device */
   TERR_CSTA_OPER_INV_FORWARDING,				/* Invalid forwarding device */
   TERR_CSTA_OPER_PRIV_VIOL_SPECIFIED,				/* Privilege violation on specified device */
   TERR_CSTA_OPER_PRIV_VIOL_CALLED,				/* Privilege violation on called device */
   TERR_CSTA_OPER_PRIV_VIOL_CALLING,				/* Privilege violation on calling device */
   TERR_CSTA_OPER_INV_CALL_ID,					/* Invalid call identifier */
   TERR_CSTA_OPER_INV_DEV_ID,					/* Invalid device identifier */
   TERR_CSTA_OPER_INV_CONN_ID,					/* Invalid connection identifier */
   TERR_CSTA_OPER_INV_DEST,					/* Invalid destination */
   TERR_CSTA_OPER_INV_FEATURE,					/* Invalid feature */
   TERR_CSTA_OPER_INV_ALLOC_STATE,				/* Invalid allocation state */
   TERR_CSTA_OPER_INV_XREF_ID,					/* Invalid cross-reference ID */
   TERR_CSTA_OPER_INV_OBJ_TYP,					/* Invalid object type */
   TERR_CSTA_OPER_SEC_VIOL,					/* Security violation */

   TERR_CSTA_INCOMP_GENERIC		= TERR_CSTA_START + 60,	/* Generic state incompatibility error */
   TERR_CSTA_INCOMP_INCORR_STATE,				/* Incorrect object state */
   TERR_CSTA_INCOMP_INV_CONN_ID,				/* Invalid connection ID */
   TERR_CSTA_INCOMP_NO_ACT_CALL,				/* No active call */
   TERR_CSTA_INCOMP_NO_HELD_CALL,				/* No held call */
   TERR_CSTA_INCOMP_NO_CALL_TO_CLEAR,				/* No call to clear */
   TERR_CSTA_INCOMP_NO_CONN_TO_CLEAR,				/* No connection to clear */
   TERR_CSTA_INCOMP_NO_CALL_TO_ANSW,				/* No call to answer */
   TERR_CSTA_INCOMP_NO_CALL_TO_COMPL,				/* No call to complete */

   TERR_CSTA_SYSRES_GENERIC		= TERR_CSTA_START + 70,	/* Generic system resource availability error */
   TERR_CSTA_SYSRES_SERV_BUSY,					/* Service busy */
   TERR_CSTA_SYSRES_RES_BUSY,					/* Resource busy */
   TERR_CSTA_SYSRES_RES_OUT_OF_SERV,				/* Resource out of service */
   TERR_CSTA_SYSRES_NET_BUSY,					/* Network busy */
   TERR_CSTA_SYSRES_NET_OUT_OF_SERV,				/* Network out of service */
   TERR_CSTA_SYSRES_MON_LIMIT_EXC,				/* Overall monitor limit exceeded */
   TERR_CSTA_SYSRES_CONF_LIMIT_EXC,				/* Conference member limit exceeded */

   TERR_CSTA_SUBRES_GENERIC		= TERR_CSTA_START + 80,	/* Generic subscribe resource availability error */
   TERR_CSTA_SUBRES_MON_LIMIT_EXC,				/* Object monitor limit exceeded */
   TERR_CSTA_SUBRES_TRUNK_LIMIT_EXC,				/* External trunk limit exceeded */
   TERR_CSTA_SUBRES_OUTST_LIMIT_EXC,				/* Outstanding request limit exceeded */

   TERR_CSTA_PERF_GENERIC		= TERR_CSTA_START + 85,	/* Generic performance management error */
   TERR_CSTA_PERF_LIMIT_EXC,					/* Performance limit exceeded */

   TERR_CSTA_SECUR_UNSPECIFIED		= TERR_CSTA_START + 90,	/* Unspecified security error */
   TERR_CSTA_SECUR_SEQ_NUM_VIOL,				/* Sequence number violated */
   TERR_CSTA_SECUR_TIME_STAMP_VIOL,				/* Time stamp violated */
   TERR_CSTA_SECUR_PAC_VIOL,					/* PAC violated */
   TERR_CSTA_SECUR_SEAL_VIOL,					/* Seal violated */

   TERR_CSTA_UNSPECIFIED		= TERR_CSTA_START + 99,	/* Unspecified CSTA error */

   TERR_ERI_VOID				= TERR_CSTA_UNSPECIFIED,
   TERR_ERI_OPERATIONS				= TERR_CSTA_OPER_GENERIC,
   TERR_ERI_STATEINCOMPATIBILITY		= TERR_CSTA_INCOMP_GENERIC,
   TERR_ERI_SYSTEMRESOURCEAVAILABILITY		= TERR_CSTA_SYSRES_GENERIC,
   TERR_ERI_SUBSCRIBEDRESOURCEAVAILABILITY	= TERR_CSTA_SUBRES_GENERIC,
   TERR_ERI_PERFORMANCEMANAGEMENT		= TERR_CSTA_PERF_GENERIC,
   TERR_ERI_SECURITY				= TERR_CSTA_SECUR_UNSPECIFIED,
   TERR_ERI_UNSPECIFIED				= TERR_CSTA_UNSPECIFIED,

   TERR_EOP_VOID				= TERR_CSTA_UNSPECIFIED,
   TERR_EOP_GENERIC				= TERR_ERI_OPERATIONS,
   TERR_EOP_REQUESTINCOMPATIBLEWITHOBJECT,
   TERR_EOP_VALUEOUTOFRANGE,
   TERR_EOP_OBJECTNOTKNOWN,
   TERR_EOP_INVALIDCALLINGDEVICE,
   TERR_EOP_INVALIDCALLEDDEVICE,
   TERR_EOP_INVALIDFORWARDINGDESTINATION,
   TERR_EOP_PRIVILEGEVIOLATIONDEVICE,
   TERR_EOP_PRIVILEGEVIOLATIONCALLEDDEVICE,
   TERR_EOP_PRIVILEGEVIOLATIONCALLINGDEVICE,
   TERR_EOP_INVALIDCSTACALLIDENTIFIER,
   TERR_EOP_INVALIDCSTADEVICEIDENTIFIER,
   TERR_EOP_INVALIDCSTACONNECTIONIDENTIFIER,
   TERR_EOP_INVALIDDESTINATION,
   TERR_EOP_INVALIDFEATURE,
   TERR_EOP_INVALIDALLOCATIONSTATE,
   TERR_EOP_INVALIDCROSSREFID,
   TERR_EOP_INVALIDOBJECTTYPE,
   TERR_EOP_SECURITYVIOLATION,

   TERR_EST_VOID				= TERR_CSTA_UNSPECIFIED,
   TERR_EST_GENERIC				= TERR_ERI_STATEINCOMPATIBILITY,
   TERR_EST_INVALIDOBJECTSTATE,
   TERR_EST_INVALIDCONNECTIONID,
   TERR_EST_NOACTIVECALL,
   TERR_EST_NOHELDCALL,
   TERR_EST_NOCALLTOCLEAR,
   TERR_EST_NOCONNECTIONTOCLEAR,
   TERR_EST_NOCALLTOANSWER,
   TERR_EST_NOCALLTOCOMPLETE,

   TERR_ESY_VOID				= TERR_CSTA_UNSPECIFIED,
   TERR_ESY_GENERIC				= TERR_ERI_SYSTEMRESOURCEAVAILABILITY,
   TERR_ESY_SERVICEBUSY,
   TERR_ESY_RESOURCEBUSY,
   TERR_ESY_RESOURCEOUTOFSERVICE,
   TERR_ESY_NETWORKBUSY,
   TERR_ESY_NETWORKOUTOFSERVICE,
   TERR_ESY_MONITORLIMITEXCEEDED,
   TERR_ESY_CONFERENCELIMITEXCEEDED,

   TERR_ESU_VOID				= TERR_CSTA_UNSPECIFIED,
   TERR_ESU_GENERIC				= TERR_ERI_SUBSCRIBEDRESOURCEAVAILABILITY,
   TERR_ESU_OBJECTMONITORLIMITEXCEEDED,
   TERR_ESU_EXTERNALTRUNKLIMITEXCEEDED,
   TERR_ESU_OUTSTANDINGREQUESTLIMITEXCEEDED,

   TERR_EPE_VOID				= TERR_CSTA_UNSPECIFIED,
   TERR_EPE_GENERIC				= TERR_ERI_PERFORMANCEMANAGEMENT,
   TERR_EPE_PERFORMANCELIMITEXCEEDED,

   TERR_ESE_UNSPECIFIED				= TERR_ERI_SECURITY,
   TERR_ESE_SEQUENCENUMBERVIOLATED,
   TERR_ESE_TIMESTAMPVIOLATED,
   TERR_ESE_PACVIOLATED,
   TERR_ESE_SEALVIOLATED,

   TERR_CSTA_END				= TERR_CSTA_START + 99,

   /* MCI Gateway800 specific errors */

   TERR_MCI_START			= 1200,

   TERR_MCI_PARK_NOCALLID		= TERR_MCI_START +  0,	/* Call has arrived from RDG w/o callid. PM requires callid. */

   TERR_MCI_PM_NOT_AVAIL,					/* no PM available */

   TERR_MCI_PARK_BADREQ,					/* Parking Request badly formatted (no details) */
   TERR_MCI_PARK_BADREQ_INVALDATA,				/* -- " -- (invalid data) */
   TERR_MCI_PARK_BADREQ_UNEXPINPUT,				/* -- " -- (unexpected input) */
   TERR_MCI_PARK_BADREQ_MISSINGPARAM,				/* -- " -- (missing parameter) */
   TERR_MCI_PARK_REJECT,					/* Format OK, but req rejected (no details) */
   TERR_MCI_PARK_REJECT_CORPRES,				/* -- " -- (corp resources overused) */
   TERR_MCI_PARK_REJECT_800RES,					/* -- " -- (8xx resources overused) */
   TERR_MCI_PARK_REJECT_PPRES,					/* -- " -- (PP res overused) */

   TERR_MCI_UNPARK_BADREQ,					/* Unpark request badly formatted (no details) */
   TERR_MCI_UNPARK_BADREQ_DESTLABEL,				/* -- " -- (invalid destlabel) */
   TERR_MCI_UNPARK_BADREQ_UNEXPINPUT,				/* -- " -- (unexpected input) */
   TERR_MCI_UNPARK_BADREQ_MISSINGPARAM,				/* -- " -- (parameter missing) */
   TERR_MCI_UNPARK_REJECTED,					/* Format OK, but req rejected (no details) */
   TERR_MCI_UNPARK_REJECTED_DESTBUSY,				/* -- " -- (destination busy) */
   TERR_MCI_UNPARK_REJECTED_DESTNOANS,				/* -- " -- (dest no answer) */

   TERR_MCI_PARK_FAILED_CUSTEXT,				/* Customer extension failed */
   TERR_MCI_PARK_FAILED_VMEXT,					/* VM extension failed */
   TERR_MCI_PARK_FAILED_NEVERPARKED,				/* Call was never parked */

   TERR_MCI_INCOMP_STATE,					/* Call in incompatible state (general) */
   TERR_MCI_INCOMP_STATE_ROUTE,					/* -- " -- for Route (general)  */
   TERR_MCI_INCOMP_STATE_ROUTE_NOCALL,				/* no call */
   TERR_MCI_INCOMP_STATE_ROUTE_ROUTING,				/* route already in progress */
   TERR_MCI_INCOMP_STATE_PARK,					/* -- " -- for Park  (general) */
   TERR_MCI_INCOMP_STATE_PARK_NOCALL,				/* no call */
   TERR_MCI_INCOMP_STATE_PARK_PARKED,				/* already parked */
   TERR_MCI_INCOMP_STATE_PARK_UNPARKING,			/* unparking in progress */

   TERR_MCI_PARK_INTERR,					/* internal error */

   /* Error in message from Gateway to TServer */
   TERR_MCI_HDW_TS_BAD_MCICONST,               /* MciConst is bad */ 
   TERR_MCI_HDW_TS_BAD_KEYNUM,                 /* Encryption key number is invalid */
   TERR_MCI_HDW_TS_BAD_CHECKSUM,               /* Checksum is bad */
   TERR_MCI_HDW_TS_BAD_SESSID,                 /* SessionId is bad */
   TERR_MCI_HDW_TS_BAD_PARAM,                  /* Bad parameter */
   TERR_MCI_HDW_TS_BAD_MESS_TYPE,              /* Bad message type */
   TERR_MCI_HDW_TS_UNEXP_MESSAGE,              /* Message out of protocol */
   TERR_MCI_HDW_TS_UDP_READ_ERROR,             /* UDP read error */
   TERR_MCI_HDW_TS_COM_ASN_DECODE_ERROR,       /* ASN decode failed on COM level */
   TERR_MCI_HDW_TS_APPL_ASN_DECODE_ERROR,      /* ASN decode failed on APPL level */
   TERR_MCI_HDW_TS_APPL_UNEXP_MESSAGE,         /* Unexpected message on APPL level */
   TERR_MCI_HDW_TS_INPUT_FROM_UNKN_HOST,       /* Input from uknown host received */
   TERR_MCI_HDW_TS_BAD_CONTTYPE,               /* Bad content type */
   TERR_MCI_HDW_TS_NOCONTENT,                  /* Content is absent */
   TERR_MCI_HDW_TS_MAX_ERRNO,                  /* maximum # of GWY to TServer errors */

   /* Error in message from PM to TServer */
   TERR_MCI_HDW_TSPM_CONNECT_FAILED,           /* Connection to PM failed */
   TERR_MCI_HDW_TSPM_BAD_MCICONST,             /* same as for Gateway */
   TERR_MCI_HDW_TSPM_BAD_KEYNUM,               /* same as for Gateway */
   TERR_MCI_HDW_TSPM_BAD_CHECKSUM,             /* same as for Gateway */
   TERR_MCI_HDW_TSPM_BAD_SESSID,               /* same as for Gateway */
   TERR_MCI_HDW_TSPM_BAD_PARAM,                /* same as for Gateway */
   TERR_MCI_HDW_TSPM_BAD_MESS_TYPE,            /* same as for Gateway */
   TERR_MCI_HDW_TSPM_UNEXP_MESSAGE,            /* same as for Gateway */
   TERR_MCI_HDW_TSPM_UDP_READ_ERROR,           /* same as for Gateway */
   TERR_MCI_HDW_TSPM_COM_ASN_DECODE_ERROR,     /* same as for Gateway */
   TERR_MCI_HDW_TSPM_APPL_ASN_DECODE_ERROR,    /* same as for Gateway */
   TERR_MCI_HDW_TSPM_APPL_UNEXP_MESSAGE,       /* same as for Gateway */
   TERR_MCI_HDW_TSPM_INPUT_FROM_UNKN_HOST,     /* same as for Gateway */
   TERR_MCI_HDW_TSPM_BAD_CONTTYPE,             /* Bad content type */
   TERR_MCI_HDW_TSPM_NOCONTENT,                /* Content is absent */
   TERR_MCI_HDW_TSPM_MAX_ERRNO,                /* maximum # of PM to TServer errors */

   /* Errors in TServer messages notified by NACK by Gateway */
   TERR_MCI_HDW_GWY_UNDEFINED,                 /* undefined */
   TERR_MCI_HDW_GWY_UNRECMSG,                  /* unrecognized message */
   TERR_MCI_HDW_GWY_UNEXPREQSEQ,               /* unexpected ReqSequence */
   TERR_MCI_HDW_GWY_UNKNSVCID,                 /* Unknown ServiceId */
   TERR_MCI_HDW_GWY_UNSUPCONTENT,              /* Unsupported content */
   TERR_MCI_HDW_GWY_CONTENTABS,                /* Content absent */
   TERR_MCI_HDW_GWY_PROTERROR,                 /* Protocol error */
   TERR_MCI_HDW_GWY_MAX_ERRNO,                 /* maximum # of NACK from Gwy */
   
   /* Errors in TServer messages notified by NACK by PM */
   TERR_MCI_HDW_PM_UNDEFINED,                  /* undefined */
   TERR_MCI_HDW_PM_UNEXPSEQ,                   /* Sequence value is not expected */
   TERR_MCI_HDW_PM_UNSUPMSGTYPE,               /* message type is bad or not supported */
   TERR_MCI_HDW_PM_NOWINDOW,                   /* no window avalilable for operation */
   TERR_MCI_HDW_PM_BADMSG,                     /* received message has bad format */
   TERR_MCI_HDW_PM_MAX_ERRNO,                  /* maximum # of NACK from PM */

   /* Errors in GWY msg responded by RouteRsp Error */
   TERR_MCI_HDW_TS_RSP_ERR_UKNOWN,             /* The CAP has an error of unknown type */
   TERR_MCI_HDW_TS_RSP_ERR_DIAL_NO,            /* the dialed digits were invalid */
   TERR_MCI_HDW_TS_RSP_ERR_UNEXP_INPUT_DATA,   /* data in the request message was provided
                                                  that was unexpected */
   TERR_MCI_HDW_TS_RSP_ERR_MISSING_PARAM,      /* a parameter was optional, but required */
   TERR_MCI_HDW_TS_RSP_ERR_UNEXP_PARAM,        /* unexpected parameter */
   TERR_MCI_HDW_TS_RSP_ERR_MAX,

   TERR_MCI_HDW_TS_RSP_RJCT_BAD_STRUCT_MSG,    /* badly structured msg */
   TERR_MCI_HDW_TS_RSP_RJCT_MISTYPED_PARAM,    /* e.g. out of range */
   TERR_MCI_HDW_TS_RSP_RJCT_RES_LIMIT,         /* CAP did not have sufficient resources */
   TERR_MCI_HDW_TS_RSP_RJCT_MAX,

   TERR_ABSOLUTE_MAX
  };

#define TERR_GLX_START				1300
#define TERR_GLX_PD_FIRST			(TERR_GLX_START + 1)	/* PD - Predictive Dialing Errors (28) */
#define TERR_GLX_PD_GATE_ID_INVALID		(TERR_GLX_START + 2)
#define TERR_GLX_PD_UNKNOWN			(TERR_GLX_START + 3)
#define TERR_GLX_PD_GATE_QUEUE_LIMIT		(TERR_GLX_START + 4)
#define TERR_GLX_PD_WRONG_TIME_TO_DIAL_NUMBER	(TERR_GLX_START + 5)
#define TERR_GLX_PD_INVALID_NUMBER		(TERR_GLX_START + 6)
#define TERR_GLX_PD_CLASS_TOO_LOW		(TERR_GLX_START + 7)
#define TERR_GLX_PD_ALL_TRUNKS_BUSY		(TERR_GLX_START + 8)
#define TERR_GLX_PD_TERMINATED_SWITCHOVER	(TERR_GLX_START + 9)
#define TERR_GLX_PD_TRUNK_RELEASED		(TERR_GLX_START + 10)
#define TERR_GLX_PD_CALL_TERMINATED		(TERR_GLX_START + 11)
#define TERR_GLX_PD_BUSY			(TERR_GLX_START + 12)
#define TERR_GLX_PD_REORDER			(TERR_GLX_START + 13)
#define TERR_GLX_PD_RING_TIMEOUT		(TERR_GLX_START + 14)
#define TERR_GLX_PD_TELCO_RECORDING		(TERR_GLX_START + 15)
#define TERR_GLX_PD_ANSWER_DETECTOR_INOPERABLE  (TERR_GLX_START + 16)
#define TERR_GLX_PD_ANSWER_DETECTOR_NOT_AVAILABLE  (TERR_GLX_START + 17)
#define TERR_GLX_PD_NO_BIN			(TERR_GLX_START + 18)
#define TERR_GLX_PD_NO_NULL_TERMINATOR		(TERR_GLX_START + 19)
#define TERR_GLX_PD_TRUNK_ABANDONED		(TERR_GLX_START + 20)
#define TERR_GLX_PD_SUCCESS			(TERR_GLX_START + 21)
#define TERR_GLX_PD_LAST			(TERR_GLX_START + 22)		/* Last code for PD */
#define TERR_GLX_D_FIRST			(TERR_GLX_START + 23)		/* D - Dialing Errors (9) */
#define TERR_GLX_D_POSITION_ID_INVALID		(TERR_GLX_START + 24)
#define TERR_GLX_D_POSITION_ID_INVALID_CONDITION  (TERR_GLX_START + 25)
#define TERR_GLX_D_AGENT_NOT_SIGNED_IN		(TERR_GLX_START + 26)
#define TERR_GLX_D_WRONG_TIME_TO_DIAL_NUMBER	(TERR_GLX_START + 27)
#define TERR_GLX_D_INVALID_NUMBER		(TERR_GLX_START + 28)
#define TERR_GLX_D_INVALID_POSITION_CLASS_OF_SERVICE  (TERR_GLX_START + 29)
#define TERR_GLX_D_ALL_TRUNKS_BUSY		(TERR_GLX_START + 30)
#define TERR_GLX_D_SWITCHOVER_IN_PROCESS	(TERR_GLX_START + 31)
#define TERR_GLX_D_DIAL_KEY_IS_NOT_AVAILABLE	(TERR_GLX_START + 32)
#define TERR_GLX_D_CALL_TERMINATED_DURING_ROUTING  (TERR_GLX_START + 33)
#define TERR_GLX_D_INVALID_CALL_SEQUENCE_NUMBER (TERR_GLX_START + 34)
#define TERR_GLX_D_UNABLE_TO_COMPLETE_OUTDIAL_CALL  (TERR_GLX_START + 35)
#define TERR_GLX_D_POSITION_HAS_MORE_THAN_ONE_CALL  (TERR_GLX_START + 36)
#define TERR_GLX_D_NO_BIN			(TERR_GLX_START + 37)
#define TERR_GLX_D_NO_NULL_TERMINATOR		(TERR_GLX_START + 38)
#define TERR_GLX_D_UNKNOWN			(TERR_GLX_START + 39)
#define TERR_GLX_D_LAST				(TERR_GLX_START + 40)		/* Last code for PD */

#define TERR_GLX_DFT_FIRST			(TERR_GLX_START + 41)		/* DFR - Not Dialed For A Trunk Errors (73) */
#define TERR_GLX_DFT_ALL_TRUNKS_BUSY		(TERR_GLX_START + 42)
#define TERR_GLX_DFT_INVALID_NUMBER		(TERR_GLX_START + 43)
#define TERR_GLX_DFT_WRONG_TIME_TO_DIAL_NUMBER  (TERR_GLX_START + 44)
#define TERR_GLX_DFT_INVALID_CALL_SEQUENCE_NUMBER  (TERR_GLX_START + 45)
#define TERR_GLX_DFT_SUBSCRIBER_RELEASED_FROM_AN_INBOUND_TRUNK  (TERR_GLX_START + 46)
#define TERR_GLX_DFT_FACILITY_CODE_IS_INVALID	(TERR_GLX_START + 47)
#define TERR_GLX_DFT_TRUNK_FAILURE		(TERR_GLX_START + 48)
#define TERR_GLX_DFT_POSITION_ID_INVALID_CONDITION  (TERR_GLX_START + 49)
#define TERR_GLX_DFT_UNKNOWN			(TERR_GLX_START + 50)
#define TERR_GLX_DFT_LAST			(TERR_GLX_START + 51)

#define TERR_GLX_T_FIRST			(TERR_GLX_START + 52)		/* T - Terminating Call Errors (10) */
#define TERR_GLX_T_POSITION_ID_INVALID		(TERR_GLX_START + 53)
#define TERR_GLX_T_POSITION_ID_IS_NOT_ON_CALL	(TERR_GLX_START + 54)
#define TERR_GLX_T_POSITION_HAS_CALL_ON_HOLD	(TERR_GLX_START + 55)
#define TERR_GLX_T_UNKNOWN			(TERR_GLX_START + 56)
#define TERR_GLX_T_LAST				(TERR_GLX_START + 57)		/* Last code for T */

#define TERR_GLX_SI_FIRST			(TERR_GLX_START + 58)		/* SI - Sign-In Errors (11) */
#define TERR_GLX_SI_POSITION_ID_INVALID		(TERR_GLX_START + 59)
#define TERR_GLX_SI_POSITION_ID_INVALID_CONDITION  (TERR_GLX_START + 60)
#define TERR_GLX_SI_SIGN_IN_NUMBER_INVALID	(TERR_GLX_START + 61)
#define TERR_GLX_SI_SIGN_IN_NUMBER_ALREADY_ACTIVE  (TERR_GLX_START + 62)
#define TERR_GLX_SI_POSITION_OUT_OF_SERVICE	(TERR_GLX_START + 63)
#define TERR_GLX_SI_POSITION_SET_BUSY		(TERR_GLX_START + 64)
#define TERR_GLX_SI_POSITION_WITHOUT_HEADSET	(TERR_GLX_START + 65)
#define TERR_GLX_SI_SWITCHOVER_IN_PROCESS	(TERR_GLX_START + 66)
#define TERR_GLX_SI_INFORMATION_GROUP_INVALID	(TERR_GLX_START + 67)
#define TERR_GLX_SI_INVALID_SUPERVISOR_ID	(TERR_GLX_START + 68)
#define TERR_GLX_SI_INVALID_GATE_NUMBER		(TERR_GLX_START + 69)
#define TERR_GLX_SI_NO_BIN			(TERR_GLX_START + 70)
#define TERR_GLX_SI_UNKNOWN			(TERR_GLX_START + 71)
#define TERR_GLX_SI_LAST			(TERR_GLX_START + 72)		/* Last code for SI */

#define TERR_GLX_SO_FIRST			(TERR_GLX_START + 73)		/* SO - Sign-Out Errors (12) */
#define TERR_GLX_SO_POSITION_ID_INVALID		(TERR_GLX_START + 74)
#define TERR_GLX_SO_CONSOLE_INVALID_CONDITION	(TERR_GLX_START + 75)
#define TERR_GLX_SO_UNKNOWN			(TERR_GLX_START + 76)
#define TERR_GLX_SO_LAST			(TERR_GLX_START + 77)		/* Last code for SO */

#define TERR_GLX_MAA_FIRST			(TERR_GLX_START + 78)		/* MAA - Make Agent Available Errors (41) */
#define TERR_GLX_MAA_POSITION_ID_INVALID	(TERR_GLX_START + 79)
#define TERR_GLX_MAA_AGENT_IN_DIALING_STATE	(TERR_GLX_START + 80)
#define TERR_GLX_MAA_AGENT_NOT_SIGNED_IN	(TERR_GLX_START + 81)
#define TERR_GLX_MAA_SUPERVISOR_PRIORITY	(TERR_GLX_START + 82)
#define TERR_GLX_MAA_POSITION_OUT_OF_SERVICE	(TERR_GLX_START + 83)
#define TERR_GLX_MAA_POSITION_SET_BUSY		(TERR_GLX_START + 84)
#define TERR_GLX_MAA_POSITION_VACANT		(TERR_GLX_START + 85)
#define TERR_GLX_MAA_SWITCHOVER_IN_PROCESS	(TERR_GLX_START + 86)
#define TERR_GLX_MAA_UNKNOWN			(TERR_GLX_START + 87)
#define TERR_GLX_MAA_LAST			(TERR_GLX_START + 88)		/* Last code for MAA */

#define TERR_GLX_MAU_FIRST			(TERR_GLX_START + 89)		/* MAU - Make Agent Unavailable Errors (42) */
#define TERR_GLX_MAU_POSITION_ID_INVALID	(TERR_GLX_START + 90)
#define TERR_GLX_MAU_UNKNOWN			(TERR_GLX_START + 91)
#define TERR_GLX_MAU_LAST			(TERR_GLX_START + 92)		/* Last code for MAU */

/* Number of T-Server logical errors */
#define TERR_GLX_D_UNCOMPLETED_CALL		(TERR_GLX_START + 93)
#define TERR_GLX_D_NOWHERE_TO_CALL		(TERR_GLX_START + 94)
#define TERR_GLX_PD_NOWHERE_TO_CALL		(TERR_GLX_START + 95)
#define TERR_GLX_TR_CAN_NOT_FIND_CALL		(TERR_GLX_START + 96)
#define TERR_GLX_RT_CAN_NOT_FIND_CALL		(TERR_GLX_START + 97) /* RT - Route Errors */

#define TERR_GLX_DTMF_FIRST			(TERR_GLX_START + 98)		/* DTMF - DTMF Out Tone Negative Responce ( 112 ) */
#define TERR_GLX_DTMF_UNKNOWN			(TERR_GLX_START + 99)
#define TERR_GLX_DTMF_MF_SENDER_EQUIP_FAIL	(TERR_GLX_START + 100)
#define TERR_GLX_DTMF_TNDB_INVALID_STATE	(TERR_GLX_START + 101)
#define TERR_GLX_DTMF_AGENT_TERMINATED_DIALING  (TERR_GLX_START + 102)
#define TERR_GLX_DTMF_NO_FREE_STORAGE		(TERR_GLX_START + 103)
#define TERR_GLX_DTMF_NO_NULL_TERMINATOR	(TERR_GLX_START + 104)
#define TERR_GLX_DTMF_LAST			(TERR_GLX_START + 105)		/* Last Code for DTMF */
#define TERR_GLX_TR_ABORTED			(TERR_GLX_START + 106)		/* TR - Transfer Errors */
#define TERR_GLX_GENERAL_SYSTEM_ERROR		(TERR_GLX_START + 107)  
#define TERR_GLX_INVALID_AGENT			(TERR_GLX_START + 108)  

#define TERR_GLX_NR_FIRST                       (TERR_GLX_START + 109)  /* First Code for Call Action Negative Response */
#define TERR_GLX_NR_POSITION_ID_INVALID         (TERR_GLX_START + 110)
#define TERR_GLX_NR_REQUEST_CODE_INVALID        (TERR_GLX_START + 111)
#define TERR_GLX_NR_INVALID_STATE               (TERR_GLX_START + 112)   /* Position in invalid state */
#define TERR_GLX_NR_INVALID_TYPE                (TERR_GLX_START + 113)   /* Request not valid for position type */
#define TERR_GLX_NR_INVALID_SEQUENCE_NUMBER     (TERR_GLX_START + 114)   /* Invalid Call Sequence number */
#define TERR_GLX_NR_INVALID_PORT_ID             (TERR_GLX_START + 115)   /* Invalid Target Port ID */
#define TERR_GLX_NR_UNKNOWN                     (TERR_GLX_START + 116)   /* Unknown NR Error Code */
#define TERR_GLX_NR_LAST                        (TERR_GLX_START + 117)   /* Last Code for NR */

/***********************NEC************************/

#define TERR_NEC_START                        1600
#define TERR_NEC_CLIENTERROR                  TERR_NEC_START + 1
#define TERR_NEC_SWITCH_ERROR                 TERR_NEC_START + 2
#define TERR_NEC_NOCALL                       TERR_NEC_START + 3
#define TERR_NEC_DN_NOT_REGISTERED            TERR_NEC_START + 4
#define TERR_NEC_INVALIDPARTY                 TERR_NEC_START + 5 /* IY, IX code 01 */
#define TERR_NEC_INVALIDPARTYSTATE            TERR_NEC_START + 6 /* IY, IX code 02 */ 
#define TERR_NEC_INVALIDSEQUENCE              TERR_NEC_START + 7 /* IY, IX code 04 */
#define TERR_NEC_INVALIDFIELD                 TERR_NEC_START + 8 /* IY, IX code 05 */
#define TERR_NEC_INTERNALERROR                TERR_NEC_START + 9 /* IY, IX code 06 */
#define TERR_NEC_LOGONINUSE                   TERR_NEC_START + 10 /* IY, IX code 07 */
#define TERR_NEC_LOGONUNKNOWN                 TERR_NEC_START + 11 /* IY, IX code 08 */
#define TERR_NEC_POSITIONLOGGED               TERR_NEC_START + 12 /* IY, IX code 09 */
#define TERR_NEC_LOGONINVALID                 TERR_NEC_START + 13 /* IY, IX code 10 */
#define TERR_NEC_UNKNOWN_ERROR                TERR_NEC_START + 14
#define TERR_NEC_CALL_IN_ROUTING_STATE        TERR_NEC_START + 15
#define TERR_NEC_LOGIN_TOO_LONG               TERR_NEC_START + 16
#define TERR_NEC_DN_TOO_LONG                  TERR_NEC_START + 17
#define TERR_NEC_TRANSFER_NUMBER_TOO_LONG     TERR_NEC_START + 18
#define TERR_NEC_ROUTE_NUMBER_TOO_LONG        TERR_NEC_START + 19
#define TERR_NEC_DESTINATION_NUMBER_TOO_LONG  TERR_NEC_START + 20
#define TERR_NEC_DESTINATION_NOT_ANSWERED     TERR_NEC_START + 21
#define TERR_NEC_CALL_TO_UNKNOWN_QUEUE        TERR_NEC_START + 22
#define TERR_NEC_DN_WITHOUT_PILOT             TERR_NEC_START + 23

/**************** Agent Reservation *******************/
#define  TERR_AGENT_ALREADY_RESERVED 1700 /* Agent reservation attempt failed */

/*
 * Soft Agent (agent states emulation in TServer):
 */
#define TERR_SOFT_AGENT_WRONG_ID          1703
#define TERR_SOFT_AGENT_ID_IN_USE         1704
#define TERR_SOFT_AGENT_PSWD_DOESNT_MATCH 1705
#define TERR_SOFT_AGENT_ALREADY_LOGGED_IN 1706
#define TERR_SOFT_AGENT_NOT_LOGGED_IN     1707

/*
 * CTI-less TServer (ER#48860):
 */
#define TERR_CTL_START           1710
#define TERR_CTL_CALL_REJECTED  (TERR_CTL_START+0) /* Preview: Call has been rejected */
#define TERR_CTL_CALL_EXPIRED   (TERR_CTL_START+1) /* Preview: Call has been expired  */
#define TERR_CTL_INV_CALL_STATE (TERR_CTL_START+2) /* Invalid call state for this operation */

/* TERR code for Lucent SCP T-Server (so-called GFA). Added by Oleg OREL */

#define TERR_GFA_START                        1800
#define TERR_GFA_TIMEOUT                      (TERR_GFA_START+1)
#define TERR_GFA_IPTIMEOUT                    (TERR_GFA_START+2)
#define TERR_GFA_FAILURE                      (TERR_GFA_START+3)
#define TERR_GFA_CHANNELS_BUSY                (TERR_GFA_START+4)
#define TERR_GFA_RESOURCE_NOT_AVAILABLE       (TERR_GFA_START+5)
#define TERR_GFA_CANCELED                     (TERR_GFA_START+6)
#define TERR_GFA_ABANDONED                    (TERR_GFA_START+7)
#define TERR_GFA_ABORT                        (TERR_GFA_START+8)

#ifdef __cplusplus
extern "C" {
#endif
  const char *terrcode_to_string(int ecode);

#ifdef _MESSAGE_H
  void add_err_str(struct message *msg);
#endif
#ifdef __cplusplus
}
#endif
#endif /* _TLIBRERR_H_ */

