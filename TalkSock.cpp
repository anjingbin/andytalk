// TalkSock.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "TalkSock.h"
#include "ClientWnd.h"
#include "Confirm.h"
#include "ABItem.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MAX_MSG_LEN_ALLOW 65530
/////////////////////////////////////////////////////////////////////////////
// CTalkSock

CTalkSock::CTalkSock()
{
}

CTalkSock::~CTalkSock()
{
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
	if(nErrorCode==WSAENETDOWN){
		CloseSocket("Closed! Netdown!");
		return;
	}
	
	BYTE * buf;
	struct _header{
		BYTE cmd;
		BYTE lenl;
		BYTE lenh; 
	}header;
	int len;
	int ret;

	for(;;){
		ret=Receive(&header,sizeof(_header));
		if(ret==SOCKET_ERROR){
			if(GetLastError()!=WSAEWOULDBLOCK)
				CloseSocket("Closed! Receive error!");
			return;
		}
		if(ret!=sizeof(_header)){
			CloseSocket("Closed! Receive error!");
			return;
		}

		len=MAKEWORD(header.lenl,header.lenh);

		buf=(BYTE*)malloc(len+1);
		ASSERT(buf);

		buf[len]=0;
		ret=Receive(buf,len);
		if(ret==SOCKET_ERROR){
			if(GetLastError()!=WSAEWOULDBLOCK)
				CloseSocket("Closed! Receive error!");
			free(buf);
			return;
		}
		if(ret!=len){
			CloseSocket("Closed! Error message format!");
			free(buf);
			return;
		}

		if(header.cmd<=8)
			m_pTalkSession->OnCommand(header.cmd,len,buf);
		else{
			CloseSocket("Closed! Unknown message!");
			free(buf);
			return;
		}
		free(buf);
	}
}

void CTalkSock::OnClose(int nErrorCode) 
{
	CloseSocket("Closed by peer!");
}

void CTalkSock::OnConnect(int nErrorCode) 
{
	if(nErrorCode){
		m_pTalkSession->ConnFailed();
	}else{
		m_pTalkSession->Connected();
	}
}

void CTalkSock::SendNew()
{
	if(m_nStatus==S_TALKING)
		m_lTimer=0;

	CString OldText=m_pTalkSession->m_sOldLocalBuf,NewText;

	m_sOldLocal=m_sLocalBuf;
	NewText=m_sLocalBuf;

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

	BYTE cmd3[7]={3,4,0,0,0,0,0},
		cmd5[11]={5,8,0,0,0,0,0,0,0,0,0};

	cmd3[3]=LOBYTE(LOWORD(end_o));
	cmd3[4]=HIBYTE(LOWORD(end_o));

	cmd5[3]=LOBYTE(LOWORD(begin));
	cmd5[4]=HIBYTE(LOWORD(begin));
	cmd5[5]=LOBYTE(LOWORD(end_o));
	cmd5[6]=HIBYTE(LOWORD(end_o));

	cmd5[7]=LOBYTE(LOWORD(begin));
	cmd5[8]=HIBYTE(LOWORD(begin));
	cmd5[9]=LOBYTE(LOWORD(begin));
	cmd5[10]=HIBYTE(LOWORD(begin));

	Send(cmd3,sizeof(cmd3));
	
	if(begin!=end_o)
		Send(cmd5,sizeof(cmd5));

	m_wLocalPos=begin;
	
	NewText.Delete(end_n,ln-end_n);
	NewText.Delete(0,begin);
	if(!NewText.IsEmpty())
		SendString(NewText);
}

void CTalkSock::SendString(CString str)
{
	WORD pos=0;
	BYTE buf[9];
	int i,k,count;
	BOOL wc=false;
	BYTE fc;

	pos=m_pTalkSession->m_wLocalPos;

	str.Replace("\r\n","\r");
	count=str.GetLength();
	for(i=0;i<count;i++){
		if(wc){
			wc=false;
			k=0;
			buf[k++]=7;
			buf[k++]=6;
			buf[k++]=0;
			buf[k++]=LOBYTE(pos);
			buf[k++]=HIBYTE(pos);
			buf[k++]=LOBYTE(pos);
			buf[k++]=HIBYTE(pos);
			buf[k++]=fc;
			buf[k++]=str[i];
			Send(buf,k);
			pos+=2;
		}else{
			k=0;
			buf[k++]=3;
			buf[k++]=4;
			buf[k++]=0;
			buf[k++]=LOBYTE(pos);
			buf[k++]=HIBYTE(pos);
			buf[k++]=0;
			buf[k++]=0;
			Send(buf,k);
			if(str[i]&0x80){
				wc=true;
				fc=str[i];
				continue;
			}			
			k=0;
			buf[k++]=4;
			buf[k++]=5;
			buf[k++]=0;
			buf[k++]=LOBYTE(pos);
			buf[k++]=HIBYTE(pos);
			buf[k++]=LOBYTE(pos);
			buf[k++]=HIBYTE(pos);
			buf[k++]=str[i];
			Send(buf,k);
			pos++;
			if(str[i]=='\r')
				pos++;
		}
	}
}

void CTalkSock::SendBeep()
{
	BYTE buf[]={8,2,0,0,0};
		Send(buf,sizeof(buf));
}

void CTalkSock::SendShakeHand()
{
	int count=m_pTalkSession->m_sMyName.GetLength();

	CString hdr('a',10);
	hdr.SetAt(0,0);
	hdr.SetAt(1,4);
	hdr.SetAt(2,0);
	hdr.SetAt(3,3);
	hdr.SetAt(4,1);
	hdr.SetAt(5,106);
	hdr.SetAt(6,0);
	hdr.SetAt(7,1);
	hdr.SetAt(8,(char)count);
	hdr.SetAt(9,0);
	Send((const void *)(hdr+m_pTalkSession->m_sMyName),count+10);
}

BOOL CTalkSock::Connect(CString Name, CString IP)
{
	if(CAsyncSocket::Connect(IP,813))
		return false;
	if(GetLastError()!=WSAEWOULDBLOCK)
		return false;
	m_sStatusString.Format("Try connecting to %s on %s........",
		Name,IP);
	m_sNickName=Name;
	m_sIP=IP;
	return true;
}

void CTalkSock::CloseSocket(CString sWhy)
{
	if (m_hSocket == INVALID_SOCKET)
		return;
	Close();
	m_pTalkSession->OnClose(sWhy);
}
