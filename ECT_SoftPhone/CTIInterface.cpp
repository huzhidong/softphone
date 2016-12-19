// CTIInterface.cpp: implementation of the CCTIInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ECT_SoftPhone.h"
#include "CTIInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCTIInterface::CCTIInterface()
{
  m_bConnectCTIOk = false;
  m_bLonginOK = false;
}

CCTIInterface::~CCTIInterface()
{
}

void CCTIInterface::SetState(int state)
{
	m_State = state;
	if (PHONE_STATE_LOGIN==m_State)
	{
		SetLoginOkFlag(true);
	}
	else if (PHONE_STATE_LOGOUT==m_State)
	{
		SetLoginOkFlag(false);
	}
}


bool CCTIInterface::GetLoginOkFlag()
{
	return m_bLonginOK;
}

void CCTIInterface::SetLoginOkFlag(bool value)
{
	m_bLonginOK = value;
}

bool CCTIInterface::GetSupervisorFlag()	
{
    if(m_AgentID == "9002")
		return true;
	else
	    return false;
}

int CCTIInterface::ForceLogout(CString AgentDN)
{
	return OK;
}

bool CCTIInterface::IsCanBargein(CString ObjAgentID)
{
	return false;
}

