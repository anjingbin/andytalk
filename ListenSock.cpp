// ListenSock.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "ListenSock.h"
#include "ClientWnd.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSock

CListenSock::CListenSock()
{
}
CListenSock::CListenSock(CWnd * pWnd)
{
	m_pWnd=pWnd;
}

CListenSock::~CListenSock()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSock member functions

void CListenSock::OnAccept(int nErrorCode) 
{
	if(m_pWnd)
		((CClientWnd*)m_pWnd)->ProcessOnAccept(nErrorCode);
}


