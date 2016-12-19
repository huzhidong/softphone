#ifndef AFX_MODULE1_H
#define AFX_MODULE1_H

class CControlCenter;

extern BOOL	    g_bWriteLog;          //是否写日志
extern LogLevel g_nLogLevel;          //日志详细级别，1，2，3级， 详细程度渐增
extern CString	g_LogPath;            //日志路径
extern CFile	  g_File;
extern BOOL     g_bCheckPassword;
extern bool     g_bConnectTServerOK;  //CTI Server连接状态标志

extern CString g_strAgentID;
extern CString g_strCallID;
extern CString g_strBeMonitorAgentID; 
extern CString g_strMonitorAgentDN;	  //监控者的分机
extern CString g_strAgentPwd;
extern CString g_strAgentExt;
extern CString g_strAgentGroup;
extern CallType g_nCallType;
extern CTime	  g_CallBeginTime;
extern CTime   g_CallEndTime;
extern CTime   g_CurStatusBeginTime;
extern CString g_strRouteSource;  
extern CString g_strRouteDest;	
extern TimerOperType g_TimerType;
extern CString g_strANI;
extern CString g_strANITPIN; 
extern CString g_strDNIS;
extern AgentLoginType     g_nLoginType;
extern bool    g_bBargeinFlag;
extern bool    g_bTpinFlag;
extern bool	   g_bTransFlag;
extern bool	   g_bListenFlag;
extern long	   g_nErrorCode ;
extern CString g_strErrorStr ;
extern int     g_nTransTpye;        // 转接类型 0-未转接|1-转接中|2-转接取回
extern bool    g_bSetBusyFlag;      // 预约预约置忙标识

extern long		 g_nCTISvrType;       //CTI服务器类型
extern CString g_strCTISvrIp;	      //CTI服务器IP
extern long	   g_strCTISvrPort;	    //CTI服务器端口
extern CString g_strCTISvrIpBak;    //备用CTI服务器IP
extern long	   g_strCTISvrPortBak;	//备用CTI服务器端口

// add by hzd 2016-11-7
extern bool    g_strRecParaSetFlag; //录音参数设置标识
extern CString g_strRecSvrIp;       //录音服务器IP
extern long    g_strRecSvrPort;     //录音服务器端口
extern CString g_strRecUrlPath;     //录音文件url路径
extern CString g_strRecCCID;        //录音数据库服务器认证标识
extern CString g_strRecUsrName;     //录音数据库服务器认证用户名
extern CString g_strRecPassWord;    //录音数据库服务器认证密码
extern CString g_strRecUrlFiles;    //录音url文件列表(JSON串)
extern CTime   g_timeRecEnd;        //挂机录音结束时间
// add by hzd 2016-11-7

extern CString g_strConnID;
extern CString g_strConsultConnID;
extern CString g_strOriConnID;       // 转接或咨询时的原ConnID add by hzd 2016-11-18
extern TKVList *g_UserData;

extern CString g_PBX;
extern CString g_strBusyReason;
extern CString g_strPasswordReason;   //验密原因
extern CString g_strBusyReasonList;
extern CString g_strAllAgents;

extern CControlCenter* g_pCtrlCenter; //
extern CAgentGroupList g_AgentGroupList;

extern bool g_bReconnect;     //重连服务器

extern int  g_nReconnInterval;//重连间隔时间 单位：秒
extern bool g_bSysExit;       //系统退出标识
extern char TMessageTypeNames[][64];
extern CString g_RecordIP;
extern UINT    g_RecordPort;
extern CString g_RecordID;

bool OpenLog(CString filename);
void WriteLog(CString logstr,int type,int Level);  
CString SearchStr(CString SourStr,char InterChar,int Position);
void RecordID();
void GetRecFiles(CString CallUUID);
CString HttpGetResponse(CString CallUUID);
CString GetFileList(CString info);
CString base64encode(CString src, int srclen);
#endif