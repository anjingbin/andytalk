// TalkSession.h: interface for the CTalkSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TALKSESSION_H__32A6B341_1511_11D4_819E_0080C86BAA81__INCLUDED_)
#define AFX_TALKSESSION_H__32A6B341_1511_11D4_819E_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define S_CREATED  0
#define S_RESOLVING 3
#define S_CONNECTING 5
#define S_CLOSING	10
#define S_CLOSED	15
#define S_CONNECTED  20
#define S_VERSIONOK	25
#define S_NICKNAMEOK 30
#define S_CONFIRMING 35
#define S_TALKING	40

#include "TalkSock.h"
#include "ClientWnd.h"

class CTalkSession : public CObject  
{
public:
	void Delete();
	int GetBarItemID();
	void Beep();
	COutlookBar * m_pBar;
	void OnClose(CString Why);
	CString m_sOldLocalBuf;
	BOOL m_bForeGround;
	void OnCommand(BYTE cmd, WORD len, BYTE *buf);
	WORD m_wRemotePos;
	void ShakeHandReceived(CString HisName);
	void ConnFailed();
	LONG m_lTimer;
	CString m_sIP;
	void Connected();
	CConfig * m_pConfig;
	void Accept(CAsyncSocket * pListenSock);
	void Create();
	POSITION m_posPosition;
	void Open();
	void ReConnect();
	void Flush();



	CTalkSession();
	virtual ~CTalkSession();

private:
	BOOL m_bConfirming;
	BOOL m_bWantTalk;
	WORD m_wLocalPos;
	CString m_sStatusLine;
	BYTE* m_pHostName;
	HANDLE m_hGetHostByName;
	CClientWnd * m_pClientWnd;
	CTime m_tEndTime;
	CTime m_tBeginTime;
	LONG m_lElapsedTime;
	CString m_sHisName;
	CString m_sMyName;
	int m_nStatus;
	BOOL m_bCallIn;
	CString m_sRemoteBuf;
	CString m_sLocalBuf;
	CTalkSock * m_pSocket;
};

#endif // !defined(AFX_TALKSESSION_H__32A6B341_1511_11D4_819E_0080C86BAA81__INCLUDED_)
