// TalkSock.cpp : implementation file
// Last update:2000/5/6 18:17

#include "stdafx.h"
#include "talk.h"
#include "TalkSock.h"
#include "ClientWnd.h"
#include "Confirm.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTalkSock

CTalkSock::CTalkSock()
{

}
CTalkSock::CTalkSock(int nID,CClientWnd * pWnd,BOOL bCallIn)
{
	m_pWnd=pWnd;
	m_bCallIn=bCallIn;
	m_nID=nID;
	m_MyPos=0;

	m_bNew=true;
	if(!m_bCallIn)
		m_bNew=false;


	m_bConfirming=false;
	m_bWantTalk=true;
	m_bResolving=false;

	m_nStatus=S_NEW;

	m_nIdleTime=0;
	m_nElapsedTime=0;

	m_nTried=0;
	m_nRetry=3; 
	m_nRetryInterval=1;

	m_sNickName="Unknown";

	memset(&m_Msg,0,sizeof(MESSAGE));
}

CTalkSock::~CTalkSock()
{
	ClearBuffer();
	//5.11
	if(m_hSocket!=INVALID_SOCKET)
		AsyncSelect(0);
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CTalkSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CTalkSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CTalkSock member functions

IMPLEMENT_DYNAMIC(CTalkSock,CAsyncSocket)

void CTalkSock::OnReceive(int nErrorCode) 
{
	if(nErrorCode==WSAENETDOWN)
		return;
	
	int ret;
	if(m_Msg.dwIndex<MESSAGE_HEADER_SIZE){
		ret=Receive(&m_Msg+m_Msg.dwIndex,MESSAGE_HEADER_SIZE-m_Msg.dwIndex);
		if(ret==SOCKET_ERROR)
			return;

		m_Msg.dwIndex+=ret;
	}
	if(m_Msg.dwIndex==MESSAGE_HEADER_SIZE){
		if(!m_Msg.pBuf){
			m_Msg.pBuf=(BYTE*)malloc(m_Msg.wLength+1);  
			if(!m_Msg.pBuf)
				AfxAbort();
			m_Msg.pBuf[m_Msg.wLength]=0;
		}
		if(m_Msg.wLength==0){
			OnMessage(m_Msg);
			memset(&m_Msg,0,sizeof(MESSAGE));
			AsyncSelect(FD_READ|FD_WRITE|FD_CLOSE);
			return;
		}
	}
	if(m_Msg.dwIndex>=MESSAGE_HEADER_SIZE){
		ret=Receive(m_Msg.pBuf+m_Msg.dwIndex-MESSAGE_HEADER_SIZE,m_Msg.wLength+MESSAGE_HEADER_SIZE-m_Msg.dwIndex);
		if(ret==SOCKET_ERROR){
			AsyncSelect(FD_READ|FD_WRITE|FD_CLOSE);
			return;
		}
		m_Msg.dwIndex+=ret;

		if(m_Msg.dwIndex==(DWORD)(m_Msg.wLength+MESSAGE_HEADER_SIZE)){
			OnMessage(m_Msg);
			memset(&m_Msg,0,sizeof(MESSAGE));
		}
	}

	AsyncSelect(FD_READ|FD_WRITE|FD_CLOSE);
}

void CTalkSock::OnClose(int nErrorCode) 
{
	m_pWnd->CloseSocket(this);
}

void CTalkSock::OnConnect(int nErrorCode) 
{
	m_pWnd->ProcessOnConnect(this,nErrorCode);
}

void CTalkSock::SendLocal()
{
	//a trick here!
	//We just send changes to remote rather than catch all 
	//  key events and send them.
	CString OldText=m_sOldLocal,NewText;

	m_sOldLocal=m_sLocal;
	NewText=m_sLocal;

	int lo=OldText.GetLength();
	int ln=NewText.GetLength();
	int count=lo<ln?lo:ln;

	int begin,end_o,end_n;
	int i;

	for(i=0;i<count;i++){
		if(NewText[i]!=OldText[i])
			break;
	}
	begin=i;

	for(i=1;i<=count-begin;i++){
		if(NewText[ln-i]!=OldText[lo-i])
			break;
	}
	end_o=lo-i+1;
	end_n=ln-i+1;

	BYTE cmd5[11]={5,8,0,0,0,0,0,0,0,0,0};

	
	if(begin!=end_o){

		MESSAGE_S* pMsg=NewMessage(8);
		pMsg->Header.bCommand=5;
		pMsg->pBuf[0]=LOBYTE(LOWORD(begin));
		pMsg->pBuf[1]=HIBYTE(LOWORD(begin));
		pMsg->pBuf[2]=LOBYTE(LOWORD(end_o));
		pMsg->pBuf[3]=HIBYTE(LOWORD(end_o));

		pMsg->pBuf[4]=LOBYTE(LOWORD(begin));
		pMsg->pBuf[5]=HIBYTE(LOWORD(begin));
		pMsg->pBuf[6]=LOBYTE(LOWORD(begin));
		pMsg->pBuf[7]=HIBYTE(LOWORD(begin));

		SendMessage(pMsg);
	}

	m_wLocalPos=begin;
	
	NewText.Delete(end_n,ln-end_n);
	NewText.Delete(0,begin);
	if(!NewText.IsEmpty())
		SendString(NewText);
}

void CTalkSock::SendString(CString str)
{
	WORD pos=0;
	int i,count;
	BOOL wc=false;
	BYTE fc;

	pos=m_wLocalPos;
	m_wLocalPos+=str.GetLength();

	str.Replace("\r\n","\r");
	count=str.GetLength();
	for(i=0;i<count;i++){
		if(wc){
			wc=false;

			MESSAGE_S * pMsg=NewMessage(6);
			pMsg->Header.bCommand=7;

			pMsg->pBuf[0]=LOBYTE(pos);
			pMsg->pBuf[1]=HIBYTE(pos);
			pMsg->pBuf[2]=LOBYTE(pos);
			pMsg->pBuf[3]=HIBYTE(pos);
			pMsg->pBuf[4]=fc;
			pMsg->pBuf[5]=str[i];
			SendMessage(pMsg);
			pos+=2;
		}else{
			MESSAGE_S * pMsg=NewMessage(4);
			pMsg->Header.bCommand=3;

			pMsg->pBuf[0]=LOBYTE(pos);
			pMsg->pBuf[1]=HIBYTE(pos);

			SendMessage(pMsg);
			if(str[i]&0x80){
				wc=true;
				fc=str[i];
				continue;
			}			
			pMsg=NewMessage(5);

			pMsg->Header.bCommand=4;

			pMsg->pBuf[0]=LOBYTE(pos);
			pMsg->pBuf[1]=HIBYTE(pos);
			pMsg->pBuf[2]=LOBYTE(pos);
			pMsg->pBuf[3]=HIBYTE(pos);
			pMsg->pBuf[4]=str[i];
			SendMessage(pMsg);

			pos++;
			if(str[i]=='\r')
				pos++;
		}
	}
}

void CTalkSock::SendBeep()
{
	MESSAGE_S * pMsg=NewMessage(2);
	pMsg->Header.bCommand=8;

	SendMessage(pMsg);
}

void CTalkSock::SendName()
{
	CString name=m_pWnd->m_Config.sMyName;
	int count=name.GetLength();

	MESSAGE_S * pMsg=NewMessage(4);
	pMsg->Header.bCommand=0;
	pMsg->pBuf[0]=3;
	pMsg->pBuf[1]=1;
	pMsg->pBuf[2]=106;

	SendMessage(pMsg);

	pMsg=NewMessage(count);
	pMsg->Header.bCommand=1;
	memcpy(pMsg->pBuf,(LPCTSTR)name,count);

	SendMessage(pMsg);
}

//This function is only called by OnReceive() function
//  at the end we'll call CClientWnd::ProcessMessage() 
//  function and let him do all work related with GUI.

void CTalkSock::OnMessage(MESSAGE msg)
{
	int i;
	WORD w,wa,wb,wc,wd;
	if(m_nStatus==S_NAMEOK)
		m_nIdleTime=0;

	switch(msg.bCommand){
	case 0:
		m_nStatus=S_VERSIONOK;
		m_nElapsedTime=0;
		break;
	case 1:
		if(m_nStatus==S_NAMEOK){
			msg.bCommand=44;  //44 means nothing,just let CClientWnd::ProcessMessage do nothing.
			break;
		}
		m_sNickName.Empty();
		for(i=0;i<msg.wLength;i++)
			m_sNickName.Insert(i,msg.pBuf[i]);
		m_nStatus=S_NAMEOK;
		m_nElapsedTime=0;

		m_tBeginTime=CTime::GetCurrentTime();
		SendLocal();
		//check name, not availible now.
		break;
	case 2:
		m_sRemote=msg.pBuf;
		break;
	case 3:
		w=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
		m_wRemotePos=w;
		break;
	case 4:
		wa=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
		wb=MAKEWORD(msg.pBuf[2],msg.pBuf[3]);
		if(wb>m_sRemote.GetLength())
			wb=m_sRemote.GetLength();
		wc=wb-wa;
		m_sRemote.Delete(wa,wc);
		m_sRemote.Insert(wa,msg.pBuf[4]);
		if(msg.pBuf[4]==0x0d)
			m_sRemote.Insert(wa+1,0x0a);
		break;
	case 5:
		wa=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
		wb=MAKEWORD(msg.pBuf[2],msg.pBuf[3]);
		if(msg.wLength==9){
			wc=MAKEWORD(msg.pBuf[5],msg.pBuf[6]);
			wd=MAKEWORD(msg.pBuf[7],msg.pBuf[8]);
			if(wb>m_sRemote.GetLength())
				wb=m_sRemote.GetLength();
			m_sRemote.Delete(wa,wb-wa);
		}else{
			wc=MAKEWORD(msg.pBuf[4],msg.pBuf[5]);
			wd=MAKEWORD(msg.pBuf[6],msg.pBuf[7]);
			if(wb>m_sRemote.GetLength())
				wb=m_sRemote.GetLength();
			m_sRemote.Delete(wa,wb-wa);
			if(wa>m_sRemote.GetLength())
				wa=m_sRemote.GetLength();
			m_sRemote.Delete(wc,wa-wc);
		}			
		break;
	case 6:
		wa=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
		wb=MAKEWORD(msg.pBuf[2],msg.pBuf[3]);
		if(wb>m_sRemote.GetLength()-wa)
			wb=m_sRemote.GetLength()-wa;
		m_sRemote.Delete(wa,wb);
		break;
	case 7:
		wa=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
		wb=MAKEWORD(msg.pBuf[2],msg.pBuf[3]);
		if(wb>m_sRemote.GetLength())
			wb=m_sRemote.GetLength();
		wc=wb-wa;
		m_sRemote.Delete(wa,wc);
		m_sRemote.Insert(wa,msg.pBuf[4]);
		m_sRemote.Insert(wa+1,msg.pBuf[5]);
		break;
	case 8:
		//all sound events be looked as GUI-related
		//so we do nothing here
		break;
	default:	
		break;
	}
	m_pWnd->ProcessMessage(this,msg);
}

void CTalkSock::OnSend(int nErrorCode) 
{
	if(m_hSocket==INVALID_SOCKET)
		return;

	int ret;
	DWORD dwWant;

	while(!m_OutMsgList.IsEmpty()){
		MESSAGE_S* pMsg=m_OutMsgList.GetHead();
		if(!pMsg){
			m_OutMsgList.RemoveHead();
			continue;
		}

		dwWant=(DWORD)(pMsg->Header.wLength+MESSAGE_HEADER_SIZE);
		if(pMsg->dwIndex>=dwWant){
			m_OutMsgList.RemoveHead();
			free(pMsg);
			continue;
		}else{
			ret=Send(&pMsg->Header+pMsg->dwIndex,dwWant-pMsg->dwIndex);
			if(ret==SOCKET_ERROR)
				return;
			pMsg->dwIndex+=ret;
			continue;
		}
	}
}

void CTalkSock::SendMessage(MESSAGE_S *pMsg)
{
	if(m_nStatus==S_NAMEOK)
		m_nIdleTime=0;
	m_OutMsgList.AddTail(pMsg);
	AsyncSelect(FD_READ|FD_WRITE|FD_CLOSE);
}


MESSAGE_S* CTalkSock::NewMessage(WORD wLen)
{
	
	BYTE * pBuf=(BYTE*)malloc(wLen+sizeof(MESSAGE_S));
	if(!pBuf)
		AfxAbort();
	memset(pBuf,0,wLen+sizeof(MESSAGE_S));

	MESSAGE_S * pMsg=(MESSAGE_S*)pBuf;

	pMsg->Header.wLength=wLen;
	pMsg->pBuf=pBuf+sizeof(MESSAGE_S);
	return pMsg;
}

//When CTalkSock object's status changed to S_CLOSED,
// we call this function to clear all left buffers.
void CTalkSock::ClearBuffer()
{
	POSITION pos=m_OutMsgList.GetHeadPosition();
	while(pos){
		MESSAGE_S* pMsg=m_OutMsgList.GetNext(pos);
		if(pMsg)
			free(pMsg);
	}

	m_OutMsgList.RemoveAll();

	if(m_Msg.pBuf && m_Msg.wLength>=0)
		free(m_Msg.pBuf);	
}
