// TalkSession.cpp: implementation of the CTalkSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "talk.h"
#include "ABItem.h"
#include "OutLookBar.h"
#include "TalkSession.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTalkSession::CTalkSession()
{

}

CTalkSession::~CTalkSession()
{

}

void CTalkSession::ReConnect()
{

}

void CTalkSession::Open()
{
	CTalkSock * pSock = (CTalkSock*)new CTalkSock();
	if(!pSock){
		AfxMessageBox("Error:create socket failed!");
		m_sStatusLine="Failed to create socket!";
	}else{
		pSock->m_pTalkSession=this;
		m_pSocket=pSock;
	}
}

void CTalkSession::Create()
{
	m_pBar->AddItem(m_sHisName);
	m_pBar->SetImage(m_nBarIemID,1);//??????
}

void CTalkSession::Accept(CAsyncSocket *pListenSock)
{
	CTalkSock * pSock = (CTalkSock*)new CTalkSock();
	if(!pSock)
		return;
			
	if(!pListenSock->Accept(*pSock)){
		delete pSock;			
		return;
	}
	m_pSocket=pSock;
	Connected();
}

void CTalkSession::Connected()
{
	m_nStatus=S_CONNECTED;
	m_sStatusLine="Connected. Waiting for response.....";

	CString ip;
	UINT port;
	m_pSocket->GetPeerName(ip,port);
	m_sIP=ip;

	BOOL allow=true;
	if(m_bCallIn&&m_pConfig->bIPAB){
		allow=false;
		POSITION pos=m_pClientWnd->AddrBook.GetHeadPosition();
		while(pos){
			CABItem * abi=(CABItem*)m_pClientWnd->AddrBook.GetNext(pos);
			if(!m_sIP.Compare(abi->IP)){
				allow=true;
				break;
			}
		}
		if(!allow)
			delete this;
	}
	if(allow){
		m_lTimer=100;
		m_pSocket->SendShakeHand();	
	}
}

void CTalkSession::ConnFailed()
{
}

void CTalkSession::ShakeHandReceived(CString HisName)
{
	m_nStatus=S_NICKNAMEOK;
	m_tBeginTime=CTime::GetCurrentTime();

	if(m_bCallIn){
		if(m_pClienWnd->m_bWantTalk){
			m_bWantTalk=true;
			if(m_pClientWnd->Config.bNeedConfirm){
				m_bConfirming=true;

				CWnd * pWnd=AfxGetMainWnd();
				if(pWnd)
					pWnd->SetActiveWindow();

				CConfirm cd;
				cd.m_nTimer=m_pConfig->nTimeOut2;
				cd.m_sIP=m_sIP;
				cd.m_sName=m_sNickName;
				if(cd.DoModal()!=IDOK)
					m_bWantTalk=false;
			}
		}else
			m_bWantTalk=false;
	}else{
		m_pBar->SetImage(GetBarItemID(),1);
		m_pBar->SetString(m_mBarItemID,m_sHisName);
	}

	m_nStatus=S_TALKING;
	m_sStatusLine.Format("Talking with %s on %s.",m_sHisname,m_sIP);
	
	if(m_bWantTalk){
		if(!AfxGetMainWnd()->IsWindowVisible()){
			AfxGetMainWnd()->ShowWindow(SW_SHOW);
			AfxGetMainWnd()->ShowWindow(SW_RESTORE);
		}
		AfxGetMainWnd()->SetForegroundWindow();
	}
	
	m_lTimer=0;
	if(m_bWantTalk)
		Sound(1);

	CString wm,am;
	if(m_pConfig->bWelMsg)
		wm=m_pConfig->sWelMsg;
	if(m_pConfig->bAbsentMsg)
		am=m_pConfig->sAbsentMsg;

	if(wm.GetLength()){
		wm.Replace("%name%",pSock->m_sNickName);
		m_sLocalBuf+=wm;	
		Flush();
	}
	if(!pSock->m_bWantTalk&&am.GetLength()){
		m_sLocalBuf+=am;	
		Flush();
	}
}

//cmd:Command Number
//len:Data Length
//buf:Data itself with a byte "0" at tail,so we can use *buf 
//    as a string directly!
void CTalkSession::OnCommand(BYTE cmd, WORD len, BYTE *buf)
{
	int i;
	WORD w,wa,wb,wc,wd;
	if(m_nStatus==S_TALKING)
		m_lTimer=0;

	switch(cmd){
	case 0:
		break;
	case 1:
		m_sHisName.Empty();
		for(i=0;i<len;i++)
			m_sHisName.Insert(i,buf[i]);
		ShakeHandReceived();
		break;
	case 2:
		if(m_bForeGround){
			m_pClientWnd->Remote.SetWindowText((char*)buf);
		}
		m_sRemoteBuf=buf;
		break;
	case 3:
		w=MAKEWORD(buf[0],buf[1]);
		m_wRemotePos=w;
		if(m_bForeGround)
			m_pClientWnd->Remote.SetSel(w,w);
		break;
	case 4:
		wa=MAKEWORD(buf[0],buf[1]);
		wb=MAKEWORD(buf[2],buf[3]);
		if(wb>m_sRemoteBuf.GetLength())
			wb=m_sRemoteBuf.GetLength();
		wc=wb-wa;
		m_sRemoteBuf.Delete(wa,wc);
		m_sRemoteBuf.Insert(wa,buf[4]);
		if(buf[4]==0x0d)
			m_sRemoteBuf.Insert(wa+1,0x0a);
		if(m_bForeGround){
			m_pClientWnd->Remote.SetSel(wa,wa+wc);
			if(buf[4]==0x0d)
				m_pClientWnd->Remote.ReplaceSel("\r\n");
			else
				m_pClientWnd->Remote.ReplaceSel((const char*)&buf[4]);
		}
		break;
	case 5:
		wa=MAKEWORD(buf[0],buf[1]);
		wb=MAKEWORD(buf[2],buf[3]);
		if(len==9){
			wc=MAKEWORD(buf[5],buf[6]);
			wd=MAKEWORD(buf[7],buf[8]);
			if(wb>m_sRemoteBuf.GetLength())
				wb=m_sRemoteBuf.GetLength();
			m_sRemoteBuf.Delete(wa,wb-wa);
			if(m_bForeGround){
				m_pClientWnd->Remote.SetSel(wa,wb);
				m_pClientWnd->Remote.ReplaceSel("");
			}
		}else{
			wc=MAKEWORD(buf[4],buf[5]);
			wd=MAKEWORD(buf[6],buf[7]);
			if(wb>m_sRemoteBuf.GetLength())
				wb=m_sRemoteBuf.GetLength();
			m_sRemoteBuf.Delete(wa,wb-wa);
			if(wa>m_sRemoteBuf.GetLength())
				wa=m_sRemoteBuf.GetLength();
			m_sRemoteBuf.Delete(wc,wa-wc);
			if(m_bForeGround){
				m_pClientWnd->Remote.SetSel(wa,wb);
				m_pClientWnd->Remote.ReplaceSel("");
				m_pClientWnd->Remote.SetSel(wc,wa);
				m_pClientWnd->Remote.ReplaceSel("");
			}
		}			
		break;
	case 6:
		wa=MAKEWORD(buf[0],buf[1]);
		wb=MAKEWORD(buf[2],buf[3]);
		if(wb>m_sRemoteBuf.GetLength()-wa)
			wb=m_sRemoteBuf.GetLength()-wa;
		m_sRemoteBuf.Delete(wa,wb);
		if(m_bForeGround){
			m_pClientWnd->Remote.SetSel(wa,wa+wb);
			m_pClientWnd->Remote.ReplaceSel("");
		}
		break;
	case 7:
		wa=MAKEWORD(buf[0],buf[1]);
		wb=MAKEWORD(buf[2],buf[3]);
		if(wb>m_sRemoteBuf.GetLength())
			wb=m_sRemoteBuf.GetLength();
		wc=wb-wa;
		m_sRemoteBuf.Delete(wa,wc);
		m_sRemoteBuf.Insert(wa,buf[4]);
		m_sRemoteBuf.Insert(wa+1,buf[5]);
		if(m_bForeGround){
			m_pClientWnd->Remote.SetSel(wa,wa+wc);
			m_pClientWnd->Remote.ReplaceSel((const char *)&buf[4]);
		}
		break;
	case 8:
		if(m_pClientWnd->m_bWantTalk)
			m_pClientWnd->Sound(1);
		break;
	default:	
		break;
	}
	if(m_nStatus==S_TALKING
		&&m_bWantTalk
		&&m_pClientWnd->m_bWantTalk
		&&cmd>=2&&cmd<=7&&cmd!=3
		&&m_pClientWnd->GetCurSock()==this)
		if(!AfxGetMainWnd()->IsWindowVisible()
			||(CWnd::GetForegroundWindow()&&AfxGetMainWnd()->m_hWnd!=CWnd::GetForegroundWindow()->m_hWnd))
			if(m_pClientWnd->Config.bBeep)
				m_pClientWnd->Sound(1);
			else{
				if(!AfxGetMainWnd()->IsWindowVisible()){
					AfxGetMainWnd()->ShowWindow(SW_SHOW);
					AfxGetMainWnd()->ShowWindow(SW_RESTORE);
				}
				AfxGetMainWnd()->SetForegroundWindow();
			}
}

void CTalkSession::Flush()
{
	m_pSocket->SendNew();
}

void CTalkSession::OnClose(CString Why)
{
	delete m_pSocket;
	m_pSocket=NULL;

	if(m_bWantTalk)
		m_pClientWnd->Sound(0);

	if(!m_bWantTalk&&GetIndex()!=-1)
		m_bNew=true;
	m_tEndTime=CTime::GetCurrentTime();


	if(m_nStatus==S_TALKING||m_nStatus==S_CONFIRMING){
		CFile logf;
		if(logf.Open(m_pWnd->m_sPath+"Log.dat",
			CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite)){
			logf.SeekToBegin();
			int count=0;
			if(logf.GetLength()){
				CArchive logarr(&logf,CArchive::load);
				logarr>>count;
			}
			CArchive logar(&logf,CArchive::store);
			logar.GetFile()->SeekToBegin();
			logar<<count+1;
			logar.Flush();
			logar.GetFile()->SeekToEnd();
			logar<<m_bNew;
			logar<<!m_bCallIn;
			logar<<m_sIP;
			logar<<m_sLocal<<m_sRemote;
			logar<<m_sNickName;
			logar<<m_tBeginTime;
			logar<<m_tEndTime;
			if(m_bNew){
				CMainFrame * pMainWnd=(CMainFrame*)AfxGetMainWnd();
				if(pMainWnd){
					if(m_pWnd->m_bWantTalk)
						pMainWnd->SetTrayIcon(IDI_ICON3);

					else
						pMainWnd->SetTrayIcon(IDI_ICON2);
				}
			}
		}
	}
	m_nStatus=S_CLOSED;

	m_sStatusLine.Format("%s:%s on %s. %s",
		m_bCallIn?"From":"To",
		m_sNickName,
		m_sIP,
		sWhy);

	if(GetBarItemID()!=-1)
		m_pBar->SetImage(GetBarItemID(),2);
}

void CTalkSession::Beep()
{
	if(m_nStatus==S_TALKING)
		if(m_pSocket)
			m_pSocket->SendBeep();
		
}

int CTalkSession::GetBarItemID()
{
	int count=m_pBar->GetCount();
	if(count!=LB_ERR)
		for(int i=0;i<count;i++){
			POSITION pos=(POSITION)m_pBar->GetItemData(i);
			if(pos==m_posPosition)
				return i;
		}
	return -1;
}

void CTalkSession::Delete()
{
	if(m_pSocket)
		m_pSocket->CloseSocket("Closed by me!");
	if(GetBarItemID()!=-1)
		m_pBar->DeleteListString()
}
