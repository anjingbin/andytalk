#ifndef _TALKSOCK_H
#define _TALKSOCK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTalkSock command target
class CTalkSession;
class CTalkSock : public CAsyncSocket
{
	DECLARE_DYNAMIC(CTalkSock)

// Attributes
public:

// Operations
public:
	CTalkSock();
	virtual ~CTalkSock();

// Overrides
public:
	void CloseSocket(CString sWhy);

	void SendShakeHand();
	void SendBeep();
	void SendString(CString str);
	void SendNew();


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkSock)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CTalkSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CTalkSession * m_pTalkSession;
	friend class CTalkSession;
private:
};

/////////////////////////////////////////////////////////////////////////////

#endif

