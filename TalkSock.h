#ifndef _TALKSOCK_H
#define _TALKSOCK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "confirm.h"
//message posted to clientwnd 
//let clientwnd to close specific socket
	
/////////////////////////////////////////////////////////////////////////////
// CTalkSock command target
class CClientWnd;
class CTalkSock : public CAsyncSocket
{
	DECLARE_DYNAMIC(CTalkSock)

// Attributes
public:

// Operations
public:
	CTalkSock();
	CTalkSock(int nID,CClientWnd * pWnd,BOOL bCallIn);
	
	virtual ~CTalkSock();

// Overrides
public:
	CTime m_tSchedule;
	BOOL m_bWantTalk;
	BOOL m_bConfirming;
	int m_nID;
	CTime m_tEndTime;
	BOOL m_bResolving;
	int m_nRetryInterval; //in tenth seconds
	CString m_sHostName;
	POSITION m_MyPos;
	BOOL m_bNew;
	int m_nRetry;
	int m_nTried;
	CTime m_tBeginTime;

	WORD m_wRemotePos;
	WORD m_wLocalPos;
	CString m_sRemote;
	CString m_sLocal;
	CString m_sOldLocal;

	int m_nStatus;

	int	m_nIdleTime;
	int m_nElapsedTime;

	BOOL m_bCallIn;
	CString m_sIP;
	CString m_sNickName;
	CClientWnd* m_pWnd;


	void SendName();
	void SendBeep();
	void SendString(CString str);
	void SendLocal();

	void ClearBuffer();

	MESSAGE m_Msg;   

	//for send
	CList<MESSAGE_S*,MESSAGE_S*> m_OutMsgList;
	
private:
	//helper
	MESSAGE_S* NewMessage(WORD wLen);
	void SendMessage(MESSAGE_S * pMsg);

	void OnMessage(MESSAGE msg);


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkSock)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CTalkSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:


};

/////////////////////////////////////////////////////////////////////////////

#endif

