#include "stdafx.h"
#include "StateMachine.h"

CStateMachine::CStateMachine()
{
  this->m_CurState = -1;
  this->m_PreState = -1;
  this->m_CurConnID = "";
  this->m_ConsultConnID = "";

}

CStateMachine::~CStateMachine()
{

}



int CStateMachine::QueryCurState()
{
	return m_CurState;
	//return get_m_CurState();
}

int CStateMachine::UpdateState(int state, CString connID)
{
	//函数功能说明：
	//外部调用此方法去更新状态机的内部状态，状态机根据前一个状态情况来变化当前的状态
	//处理完成后将前一状态返回

  m_PreState = this->m_CurState;
  m_CurState = state;

	switch (state)
	{
	case PHONE_STATE_DISABLE:
	{

		break;
	}
	case PHONE_STATE_INIT:
	{

		break;
	}
	case PHONE_STATE_LOGIN:
	{

		break;
	}
	case PHONE_STATE_LOGOUT:
	{

		break;
	}
	case PHONE_STATE_BUSY:
	{

		break;
	}
	case PHONE_STATE_IDLE:
	{
		m_PreState = m_CurState;
		m_CurState = state;

		break;
	}
	case PHONE_STATE_DIALING:
	{

		break;
	}
	case PHONE_STATE_TALKING:
	{

		break;
	}

	case PHONE_STATE_HOLD:
	{

		break;
	}

	case PHONE_STATE_CONFERENCE:
	{

		break;
	}
	}

	return m_PreState;
}
