#ifndef AFX_STATEMACHINE_H
#define AFX_STATEMACHINE_H

class CStateMachine
{
public:
	int UpdateState(int state,CString connID);
	int QueryCurState();
	/*
	int get_m_PreState() { return m_PreState; };
	void set_m_PreState(int val) { m_PreState = val; };
	int get_m_CurState() { return m_CurState; };
	void set_m_CurState(int val) {  m_CurState = val; };
	CString get_m_CurConnID() { return m_CurConnID; };
	void set_m_CurConnID(CString val) { m_CurConnID = val; };
	CString get_m_ConsultConnID() { return m_ConsultConnID; };
	void set_m_ConsultConnID(CString val) { m_ConsultConnID = val; };
	*/

	CStateMachine();
	~CStateMachine();
protected:
private:
	CString m_CurConnID;	//当前的呼叫连接串
	CString m_ConsultConnID;//咨询呼叫连接串
	int m_PreState;			//前一状态
	int m_CurState;			//当前状态
};
#endif