// ClientWnd.cpp : implementation file
// Last update:2000/5/8 10:57

#include "stdafx.h"
#include "talk.h"
#include "MainFrm.h"
#include "ClientWnd.h"
#include "TalkSock.h"
#include "ABDlg.h"
#include "CDlg.h"
#include "LogDlg.h"
#include "MsgPageW.h"
#include "MsgPageA.h"
#include "CfgGen.h"
#include "CfgPersonal.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientWnd


CClientWnd::CClientWnd()
{
	ID_SEED=0;
	m_pListenSock=NULL;
	m_bWantTalk=true;
	m_nNewLog=0;
	m_sPath="";
}

CClientWnd::~CClientWnd()
{
	POSITION pos=m_ABList.GetHeadPosition();
	while(pos){
		ABITEM * abi=m_ABList.GetNext(pos);
		if(abi)
			delete abi;
	}
	m_ABList.RemoveAll();

	pos=m_EmoteList.GetHeadPosition();
	while(pos){
		EMOTEITEM * ei=m_EmoteList.GetNext(pos);
		if(ei)
			delete ei;
	}
	m_EmoteList.RemoveAll();

	pos=m_ResolveList.GetHeadPosition();
	while(pos){
		RESOLVEITEM* pri=m_ResolveList.GetNext(pos);
		if(pri){
			WSACancelAsyncRequest(pri->handle);
			delete pri;
		}
	}
	m_ResolveList.RemoveAll();

	pos=TSL.GetHeadPosition();
	while(pos){
		CTalkSock* pSock=TSL.GetNext(pos);
		if(pSock)
			delete pSock;
	}
	TSL.RemoveAll();
	
	if(m_pListenSock){
		if(m_pListenSock->m_hSocket!=INVALID_SOCKET)
			m_pListenSock->AsyncSelect(0);
		delete m_pListenSock;
	}
}



BEGIN_MESSAGE_MAP(CClientWnd, CWnd)
	//{{AFX_MSG_MAP(CClientWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_ADDRBOOK, OnAddrbook)
	ON_COMMAND(ID_CONNECT, OnConnect)
	ON_COMMAND(ID_LOG, OnLog)
	ON_UPDATE_COMMAND_UI(ID_BEEP, OnUpdateBeep)
	ON_COMMAND(ID_BEEP, OnBeep)
	ON_COMMAND(ID_DISC, OnDisc)
	ON_UPDATE_COMMAND_UI(ID_DISC, OnUpdateDisc)
	ON_UPDATE_COMMAND_UI(ID_WANTTALK, OnUpdateWanttalk)
	ON_COMMAND(ID_WANTTALK, OnWanttalk)
	ON_WM_TIMER()
	ON_COMMAND(ID_SETTING, OnSetting)
	ON_COMMAND(ID_FONT, OnFont)
	ON_COMMAND(ID_BACKCOLOR, OnBackcolor)
	ON_COMMAND(ID_HSCROLL, OnHscroll)
	ON_COMMAND(ID_VSCROLL, OnVscroll)
	ON_UPDATE_COMMAND_UI(ID_VSCROLL, OnUpdateVscroll)
	ON_UPDATE_COMMAND_UI(ID_HSCROLL, OnUpdateHscroll)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI(ID_REC, OnUpdateReconnect)
	ON_COMMAND(ID_REC, OnReconnect)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CONFIRM_OVER,OnConfirmOver)
	ON_MESSAGE(WM_RESOLVE_OVER,OnResolveOver)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CClientWnd message handlers

BOOL CClientWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(NULL, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_BTNFACE+1), NULL);

	return TRUE;	
}

BOOL CClientWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(&rect,::GetSysColor(COLOR_BTNFACE));
	CPen * pPenLight=(CPen*)new CPen;
	if(!pPenLight)
		return false;
	CPen * pPenShadow=(CPen*)new CPen;
	if(!pPenShadow){
		delete pPenLight;
		return false;
	}

	CPen * pOld;

	pPenLight->CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DHILIGHT));
	pPenShadow->CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DSHADOW));
	pOld=pDC->SelectObject(pPenShadow);
	pDC->MoveTo(0,0);
	pDC->LineTo(rect.right,0);
	pDC->SelectObject(pPenLight);
	pDC->MoveTo(0,1);
	pDC->LineTo(rect.right,1);
	pDC->SelectObject(pOld);

	delete pPenShadow;
	delete pPenLight;
	return true;	
}

int CClientWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndBar.Create( WS_CHILD|WS_VISIBLE, CRect(0,0,0,0),
		this, 100 ))
	{
		TRACE0("Failed to create COutlookBar...\n");
		return -1;
	}
	m_wndBar.SetOwner (this);
	m_wndBar.m_ImageList.Create (32, 32, true, 3, 1);

	HICON hIcon;
		
	hIcon= AfxGetApp()->LoadIcon (IDI_TRY);
	m_wndBar.m_ImageList.Add (hIcon);
	hIcon= AfxGetApp()->LoadIcon (IDI_ACTIVE);
	m_wndBar.m_ImageList.Add (hIcon);
	hIcon= AfxGetApp()->LoadIcon (IDI_DEAD);
	m_wndBar.m_ImageList.Add (hIcon);
	hIcon= AfxGetApp()->LoadIcon (IDI_ICON5);
	m_wndBar.m_ImageList.Add (hIcon);
	
	//retrieve executable's path name
	int count;
	char buf[256];

	GetModuleFileName(AfxGetInstanceHandle(),buf,256);
	CString path(buf);

	count=path.GetLength();
	while(count){
		count--;
		if(path.GetAt(count)=='\\')
			break;
	}
	m_sPath=path.Left(count+1);

	//load config data
	m_Config.m_sFileName=m_sPath+CFGFILE;
	if(!m_Config.Load()){
		AfxMessageBox("Failed to load Config data!");
		return -1;
	}
	//load addressbook file
	if(!LoadAddressBook())
		return -1;

	
	if(!m_wndLocal.Create(
		WS_TABSTOP|
		WS_VISIBLE|
		WS_CHILD|
		ES_MULTILINE|
		ES_AUTOHSCROLL|
		ES_AUTOVSCROLL|
		ES_READONLY,
		CRect(0,0,0,0),
		this,
		102))
		return -1;
	if(!m_wndRemote.Create(
		WS_TABSTOP|
		WS_CHILD|
		WS_VISIBLE|
		ES_MULTILINE|
		ES_AUTOHSCROLL|
		ES_AUTOVSCROLL|
		ES_READONLY,
		CRect(0,0,0,0),
		this,
		103))
		return -1;
	
	if(m_Config.bHScroll){
		m_wndLocal.ModifyStyle(0,WS_HSCROLL);
		m_wndRemote.ModifyStyle(0,WS_HSCROLL);
	}
	if(m_Config.bVScroll){
		m_wndLocal.ModifyStyle(0,WS_VSCROLL);
		m_wndRemote.ModifyStyle(0,WS_VSCROLL);
	}
	
	m_wndLocal.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	m_wndRemote.ModifyStyleEx(0,WS_EX_CLIENTEDGE);

	CBrush br(m_Config.clrEditBack);

	m_wndLocal.m_clrText=m_Config.clrEditText;
	m_wndLocal.m_clrBack=m_Config.clrEditBack;
	m_wndLocal.m_hbrBack=HBRUSH(br);

	m_wndRemote.m_clrText=m_Config.clrEditText;
	m_wndRemote.m_clrBack=m_Config.clrEditBack;
	m_wndRemote.m_hbrBack=HBRUSH(br);
	br.Detach();

	if(m_Config.lfEdit.lfHeight){
		CFont ft;
		ft.CreateFontIndirect(&m_Config.lfEdit);
		m_wndLocal.SetFont(&ft);
		m_wndRemote.SetFont(&ft);
		ft.Detach();
	}else{
		m_wndLocal.SetFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
		m_wndRemote.SetFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
	}

	if(!m_wndStatus.Create(CCS_NORESIZE|WS_VISIBLE|WS_CHILD|SS_LEFTNOWORDWRAP,CRect(0,0,0,0),this,104))
		return -1;

	if(!SetTimer(TALKTIMER,100,NULL))
		return -1;

	m_pListenSock = new CListenSock(this);
	if (!m_pListenSock->Create(PORT)){
		AfxMessageBox("Server socket create failed, maybe AndyTalk is already running!");
		return -1;
	}
	
	if (!m_pListenSock->Listen())
		return -1;

	m_nNewLog=CheckNew();
	SetTrayIcon();
/*
	if(m_nNewLog>0){
		CString str;
		if(m_nNewLog==1)
			str="a piece of";
		else
			str.Format("%d pieces of",m_nNewLog);
		AfxMessageBox(CString("You have got ")+str+" new message!");
		SendMessage(WM_COMMAND,ID_LOG);
	}
*/

	return 0;
}

void CClientWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd ::OnSize(nType, cx, cy);
	
	CRect r;
	GetClientRect(&r);
	NONCLIENTMETRICS ncm;
	ncm.cbSize=sizeof(NONCLIENTMETRICS);

	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,sizeof(NONCLIENTMETRICS),
		&ncm,0);
	int m=ncm.iMenuHeight;
	int l=r.left;
	int w=r.Width()-82;
	int t=r.top+4;
	int b=r.bottom;
	int h=r.Height();
	m_wndBar.MoveWindow(l,t,80,b-t);

	l+=82;
	int lh=(h-7-m)/2;
	int rh=(h-7-m)-lh;
	m_wndRemote.MoveWindow(l,t,w,rh);
	m_wndLocal.MoveWindow(l,t+=2+rh,w,lh);
	m_wndStatus.MoveWindow(l,t+=lh+1,w,m);

	int parts[]={0,-1};
	parts[0]=w-55;
	m_wndStatus.SetParts(2,parts);
}

void CClientWnd::ProcessOnAccept(int nErrorCode)
{
	if(nErrorCode==WSAENETDOWN){
		AfxMessageBox("Net down! AndyTalk will exit!");
		PostQuitMessage(-1);
		return;
	}

	CTalkSock * pSock = (CTalkSock*)new CTalkSock(ID_SEED++,this,true);
	if(!pSock)
		return;
	pSock->m_nRetry=m_Config.nRetry;
	pSock->m_nRetryInterval=m_Config.nRetryInterval;
		
	if(!m_pListenSock->Accept(*pSock)){
		delete pSock;			
		return;
	}

	//check current connections
	//  if reached the maximum limit of 
	//	connections,then reject the request.
	int i=0;
	POSITION pos=TSL.GetHeadPosition();

	while(pos){
		CTalkSock * pSock=(CTalkSock*)TSL.GetNext(pos);
		if(pSock && pSock->m_nStatus!=S_CLOSED)
			i++;
	}
	if(i>=m_Config.nMaxConnections){
		delete pSock;
		return;
	}

	pSock->AsyncSelect(FD_READ|FD_CLOSE|FD_WRITE);
	pSock->m_MyPos=TSL.AddTail(pSock);
	pSock->m_nStatus=S_CONNECTED;
	pSock->m_nElapsedTime=0;

	UINT port;
	CString ip;
	pSock->GetPeerName(ip,port);
	pSock->m_sIP=ip;

	//both sides should send version and name messages
	//  as soon as connected,otherwise deadlock will occur.
	pSock->SendName();
}

//process input of inplace editbox 
void CClientWnd::OnInput(CString &str,int nType)
{
	if(m_wndLocal.GetStyle()&ES_READONLY){
		NotifySound(-1);
		return;
	}	
	CTalkSock * pSock=GetCurSock();
	if(!pSock)
		return;

	if(str.GetLength()==0)
		return;
	if(nType!=0){
		BOOL found=false;

		CString emote(str);
		emote.TrimLeft();
		emote.TrimRight();
		CString emt,obj;
		
		sscanf(emote,"%s%s",emt.GetBuffer(256),obj.GetBuffer(256));
		emt.ReleaseBuffer();
		obj.ReleaseBuffer();
		emote=emt;
		
		if(emote.GetLength()==0)
			return;
		EMOTEITEM * ei;
		POSITION pos=m_EmoteList.GetHeadPosition();
		while(pos){
			ei=m_EmoteList.GetNext(pos);
			if(!emote.Compare(ei->Emote)){
				found=true;
				break;
			}
		}
		if(!found){
			FILE * fp=fopen(m_sPath+"emote.txt","rb");
			CString line;	
			if(fp){
				while(getline(line,fp)){
					if(!line.GetLength())
						continue;

					line.TrimRight();
					if(line.Compare(CString("-")+emote))
						continue;
					found=true;
					break;
				}
				if(found){
					ei=(EMOTEITEM*)new EMOTEITEM;

					m_EmoteList.AddTail(ei);
					ei->Emote=emote;
					while(getline(line,fp)){
						if(!line.GetLength())
							continue;
						if(line[0]=='-')
							break;
						if(line.GetLength()<=2)
							continue;
						if(line[0]=='1'&&line[1]==':'){
							line.Delete(0,2);
							ei->ToNone=line;
						}
						if(line[0]=='2'&&line[1]==':'){
							line.Delete(0,2);
							ei->ToHe=line;
						}
						if(line[0]=='3'&&line[1]==':'){
							line.Delete(0,2);
							ei->ToMe=line;
						}
					}
				}
				fclose(fp);
			}
		}
		if(found){
			switch(nType){
			case 1:
				str=ei->ToNone;
				break;
			case 2:
				str=ei->ToHe;
				break;
			case 3:
				str=ei->ToMe;
				break;
			default:
				ASSERT(false);
				break;
			}
			//str=CString("¡¾ÏÐÁÄ¡¿")+str;
			str.Replace("%ME%",m_Config.sMyName);
			str.Replace("%HE%",obj.IsEmpty()?pSock->m_sNickName:obj);
			m_wndLocal.ReplaceSel(str+"\r\n");
		}
	}else
		m_wndLocal.ReplaceSel(str);		
}

void CClientWnd::OnAddrbook() 
{
	CABDlg ab;

	ab.AB=&m_ABList;
	if(ab.DoModal()==ID_CONNECT){
		if(ab.m_bSchedule){
			int i=0;
			POSITION pos=TSL.GetHeadPosition();

			while(pos){
				CTalkSock * pSock=(CTalkSock*)TSL.GetNext(pos);
				if(pSock && pSock->m_nStatus!=S_CLOSED)
					i++;
			}
			if(i>=m_Config.nMaxConnections){
				AfxMessageBox("Too many connections!");
			}else{
				CTalkSock * pSock = (CTalkSock*)new CTalkSock(ID_SEED++,this,false);
				if(pSock && pSock->Create(0,SOCK_STREAM,FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE)){
					pSock->m_MyPos=TSL.AddTail(pSock);

					pSock->m_nRetry=m_Config.nRetry;
					pSock->m_nRetryInterval=m_Config.nRetryInterval;

					pSock->m_nStatus=S_CREATED;
					pSock->m_nElapsedTime=0;

					pSock->m_tSchedule=ab.m_tTime;
					pSock->m_sNickName=ab.name;
					pSock->m_sIP=ab.IP;

					AddBarItem(ab.name,YEL,pSock->m_MyPos);
				}else{
					if(pSock) 
						delete pSock;
					AfxMessageBox("Faied to create socket!");
				}
			}
		}else{
			if(!m_bWantTalk){
				m_bWantTalk=true;
				SetTrayIcon();
			}
			Connect(ab.IP,ab.name);
		}
	}
	StoreAddressBook();
}

void CClientWnd::OnConnect() 
{
	CCDlg cd;
	cd.m_sHost=m_Config.m_sIP;

	if(cd.DoModal()==IDOK){
		m_Config.m_sIP=cd.m_sHost;
		if(!m_bWantTalk){
			m_bWantTalk=true;
			SetTrayIcon();
		}
		Connect(cd.m_sHost,cd.m_sHost);
	}
}

//called by: OnConnect(),OnAddrbook(),OnLog()
void CClientWnd::Connect(CString sHost,CString sName)
{
	int i=0;
	POSITION pos=TSL.GetHeadPosition();

	while(pos){
		CTalkSock * pSock=(CTalkSock*)TSL.GetNext(pos);
		if(pSock && pSock->m_nStatus!=S_CLOSED)
			i++;
	}
	if(i>=m_Config.nMaxConnections){
		AfxMessageBox("Too many connections!");
		return;
	}

	CTalkSock * pSock = (CTalkSock*)new CTalkSock(ID_SEED++,this,false);
	if(!pSock){
		AfxMessageBox("Faied to create socket!");
		return;
	}
	pSock->m_nRetry=m_Config.nRetry;
	pSock->m_nRetryInterval=m_Config.nRetryInterval;

	pSock->m_MyPos=TSL.AddTail(pSock);

	if(!pSock->Create(0,SOCK_STREAM,FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE)){
		TSL.RemoveAt(pSock->m_MyPos);
		delete pSock;
		AfxMessageBox("Faied to create socket!");
		return;
	}

	pSock->m_nStatus=S_CONNECTING;
	pSock->m_nElapsedTime=0;
	
	//resolve hostname 
	DWORD ip;
	if((ip=inet_addr(sHost))==INADDR_NONE){   //not a ip address
		pSock->m_sHostName=sHost;
		pSock->m_sIP.Empty();

		RESOLVEITEM* pri=(RESOLVEITEM*) new RESOLVEITEM;
		if(!pri)
			AfxAbort();
		pri->host=sHost;
		pri->id=pSock->m_nID;
		pri->buf=(char far*)malloc(MAXGETHOSTSTRUCT);
			

		if((pri->handle=WSAAsyncGetHostByName(GetSafeHwnd(),WM_RESOLVE_OVER,pri->host,pri->buf,MAXGETHOSTSTRUCT))==0){
			AfxMessageBox("Cannot start resolving!");
			TSL.RemoveAt(pSock->m_MyPos);
			delete pSock;
			delete pri;
			return;
		}		
		pSock->m_bResolving=true;	
		m_ResolveList.AddTail(pri);
	}else{   //it's a ip address
		pSock->m_sIP=sHost;
		pSock->m_sHostName.Empty();

		if(!pSock->Connect(sHost,PORT))
			if(pSock->GetLastError()!=WSAEWOULDBLOCK){
				TSL.RemoveAt(pSock->m_MyPos);
				delete pSock;
				AfxMessageBox("Failed to connect to specified host!");
				return;
			}
	}

	AddBarItem(sName,GRN,pSock->m_MyPos);
}

void CClientWnd::OnLog() 
{
	CLogDlg ld(this);
	ld.AB=&m_ABList;
	ld.m_sLogFile=m_sPath+LOGFILE;
	if(ld.DoModal()==ID_RECONN){
		if(!m_bWantTalk){
			m_bWantTalk=true;
			SetTrayIcon();
		}

		Connect(ld.IP,ld.name);
	}
	m_nNewLog=CheckNew();
	SetTrayIcon();

	StoreAddressBook();
}

void CClientWnd::OnUpdateBeep(CCmdUI* pCmdUI) 
{
	CTalkSock * pSock=GetCurSock();
	if(pSock && pSock->m_nStatus==S_NAMEOK)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CClientWnd::OnBeep() 
{
	CTalkSock * pSock=GetCurSock();
	if(pSock && pSock->m_nStatus==S_NAMEOK)
		pSock->SendBeep();
}

void CClientWnd::OnDisc() 
{
	int i=m_wndBar.GetCurSel();

	if(i==LB_ERR)
		return;

	POSITION pos=IndexToPosition(i);
	if(!pos)
		return;
	CTalkSock * pSock=TSL.GetAt(pos);
	ASSERT(pSock);
	if(!pSock)
		return;
	if(pSock->m_nStatus<=S_NAMEOK){
		CloseSocket(pSock);
	}else if(pSock->m_nStatus==S_CLOSED){
		TSL.RemoveAt(pSock->m_MyPos);
		delete pSock;
		m_wndBar.DeleteListString(i);

		SetTrayIcon(); //Added by andy,2k1.5.12

		if(m_wndBar.GetCount()){
			if(m_wndBar.SetCurSel(i)==LB_ERR)
				m_wndBar.SetCurSel(0);
		}
		UpdateView();
	}
}

void CClientWnd::OnUpdateDisc(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndBar.GetCurSel()!=LB_ERR);
}


void CClientWnd::OnUpdateWanttalk(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bWantTalk?1:0);
}

void CClientWnd::OnWanttalk() 
{
	m_bWantTalk=!m_bWantTalk;
	SetTrayIcon();
/*
	if(m_bWantTalk){
		int New=m_nNewLog;
		if(New){
			CString str;
			if(New==1)
				str="a piece of";
			else
				str.Format("%d pieces of",New);
			AfxMessageBox(CString("You have got ")+str+" new message!");
			//5.7
			SendMessage(WM_COMMAND,ID_LOG);
		}
	}
*/
}

void CClientWnd::OnTimer(UINT nIDEvent) 
{
	POSITION pos=TSL.GetHeadPosition();
	while(pos){
		CTalkSock * pSock=(CTalkSock*)TSL.GetNext(pos);
		if(!pSock)
			continue;
		pSock->m_nElapsedTime++;

		switch(pSock->m_nStatus){
		case S_NEW:
		case S_CREATED:
			if(pSock->m_tSchedule==CTime::GetCurrentTime()){
				pSock->m_nStatus=S_CONNECTFAILED;
				pSock->m_nElapsedTime=pSock->m_nRetryInterval*600;
			}
			break;
		case S_CONNECTING:
			break;
		case S_CONNECTFAILED:
			if(pSock->m_nElapsedTime>=pSock->m_nRetryInterval*600){
				pSock->m_nStatus=S_CONNECTING;
				pSock->m_nElapsedTime=0;
				m_wndBar.SetImage(PositionToIndex(pSock->m_MyPos),GRN);

				if(inet_addr(pSock->m_sIP)==INADDR_NONE){   //not a ip address
					pSock->m_sHostName=pSock->m_sIP;
					pSock->m_sIP.Empty();
				}
				
				if(pSock->m_sIP.IsEmpty()){
					//hostname resolve
					RESOLVEITEM* pri=(RESOLVEITEM*) new RESOLVEITEM;
					if(!pri)
						AfxAbort();
					pri->host=pSock->m_sHostName;
					pri->id=pSock->m_nID;
					pri->buf=(char far*)malloc(MAXGETHOSTSTRUCT);
					if((pri->handle=WSAAsyncGetHostByName(
						GetSafeHwnd(),
						WM_RESOLVE_OVER,
						pri->host,
						pri->buf,
						MAXGETHOSTSTRUCT))==0){
						CloseSocket(pSock);	
						delete pri;
					}else{
						pSock->m_bResolving=true;	
						m_ResolveList.AddTail(pri);
					}
				}else{
					if(!pSock->Connect(pSock->m_sIP,PORT)){
						if(pSock->GetLastError()!=WSAEWOULDBLOCK){
							pSock->m_nStatus=S_CONNECTFAILED;
							pSock->m_nElapsedTime=0;
							m_wndBar.SetImage(PositionToIndex(pSock->m_MyPos),YEL);
							pSock->m_nTried++;
							if(pSock->m_nTried==pSock->m_nRetry)
								CloseSocket(pSock);
						}
					}
				}
			}
			break;
		case S_CONNECTED:	
		case S_VERSIONOK:		
			if(pSock->m_nElapsedTime>=1000)
				CloseSocket(pSock);
			break;
		case S_NAMEOK:	
			if((++pSock->m_nIdleTime)>=m_Config.nIdleTime*10)
				CloseSocket(pSock);
			break;
		case S_CLOSED:		
		default:
			break;
		}
	}
	
	//set pane text of status bar
	//clock
	m_wndStatus.SetText(CTime::GetCurrentTime().Format("%H:%M:%S"),1,0);
	
	if(m_wndBar.GetCount()==0){
		m_wndStatus.SetWindowText("No connections.");
		return;
	}

	int sel=m_wndBar.GetCurSel();
	if(sel==LB_ERR)
		return;

	CTalkSock * pSock=TSL.GetAt((POSITION)m_wndBar.GetItemData(sel));
	ASSERT(pSock);
	if(!pSock)
		return;

	CString str,time,host=pSock->m_sIP;
	int t;
	if(host.IsEmpty())
		host=pSock->m_sHostName;

	time.Format(" %02d:%02d:%02d",pSock->m_nElapsedTime/36000,(pSock->m_nElapsedTime%36000)/600,((pSock->m_nElapsedTime%36000)%600)/10);

	switch(pSock->m_nStatus){
	case S_NEW:
	case S_CREATED:
		str.Format("Scheduled to connect to %s at ",pSock->m_sNickName);
		time=pSock->m_tSchedule.Format("%H:%M:%S.");
		break;
	case S_CONNECTING:
		if(pSock->m_bResolving)
			str.Format("Resolving %s....... ",host);
		else
			str.Format("Connecting to %s at %s....... ",pSock->m_sNickName,host);
		break;
	case S_CONNECTFAILED:
		str.Format("Failed connect to %s at %s,retry(%d/%d) after",pSock->m_sNickName,host,pSock->m_nTried+1,pSock->m_nRetry);

		t=pSock->m_nRetryInterval*600-pSock->m_nElapsedTime;
		time.Format(" %02d:%02d",(t%36000)/600,((t%36000)%600)/10);
		break;		
	case S_CONNECTED:
	case S_VERSIONOK:
		str.Format("Connected to %s at %s,waiting for response.....",pSock->m_sNickName,host);
		break;
	case S_NAMEOK:
		str.Format("Talking with %s at %s. ",pSock->m_sNickName,host);
		break;
	case S_CLOSED:
		str.Format("Closed talk with %s at %s ",pSock->m_sNickName,host);
		time=pSock->m_tEndTime.Format(" %H:%M:%S");
		break;
	default:
		break;
	}

	m_wndStatus.SetText(str+time,0,0);
}

//called by CMainFrame::OnClose()
BOOL CClientWnd::WantClose()
{
	if(MessageBox("Do you really want to exit?","AndyTalk",MB_ICONQUESTION|MB_OKCANCEL)==IDOK)
		return true;
	return false;
}


void CClientWnd::OnSetting() 
{
	CMsgPageW pw;
	CMsgPageA pa;
	CCfgGen cg;
	CCfgPersonal cp;

	CPropertySheet sheet(IDR_MAINFRAME);

	pw.m_msg	=m_Config.sWelMsg	;
	pa.m_msg	=m_Config.sAbsentMsg;

	cg.m_beep		=m_Config.bBeep		;
	cg.m_max		=m_Config.nMaxConnections;
	cg.m_name		=m_Config.sMyName		;
	cg.m_time1		=m_Config.nIdleTime	;
	cg.m_time2		=m_Config.nConfirmTime	;
	cg.m_nRetry		=m_Config.nRetry;
	cg.m_nRetryInterval		=m_Config.nRetryInterval;
	cg.m_Emote1		=CString(m_Config.m_Emote1);
	cg.m_Emote2		=CString(m_Config.m_Emote2);
	cg.m_Emote3		=CString(m_Config.m_Emote3);
	cg.m_EmoteEsc		=CString(m_Config.m_EmoteEsc);

	HKEY hKey=NULL;
	char * ValueName="AndyTalk";
	DWORD type=REG_SZ;
	BYTE path[256];
	DWORD size=256;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
		0, KEY_WRITE|KEY_READ,
		&hKey)!=ERROR_SUCCESS){
		AfxMessageBox("Error to open REGISTRY!");
		return;
	}else{
		if(RegQueryValueEx(hKey,
			ValueName,
			NULL,
			&type,
			path,
			&size)==ERROR_SUCCESS)
			cg.m_startup=true;
		else
			cg.m_startup=false;
	}
	

	cp.AB=&m_ABList;
	sheet.AddPage(&cg);
	sheet.AddPage(&pw);
	sheet.AddPage(&pa);
	sheet.AddPage(&cp);

	sheet.m_psh.dwFlags|=PSH_NOAPPLYNOW;

	if(sheet.DoModal()!=IDOK){
		RegCloseKey(hKey);
		return;
	}

	m_Config.sWelMsg=pw.m_msg;
	m_Config.sAbsentMsg=pa.m_msg;
/*
	char * str;
	str=(char*)malloc(pa.m_msg.GetLength()+3);
	ZeroMemory(str,pa.m_msg.GetLength()+3);
	strcpy(str+2,pa.m_msg);
	str[0]=0x0d;
	str[1]=0x0a;

	char* msg=strstr(str,"\r\n>>>");
	msg+=5;
	strchr(
*/

	m_Config.bBeep			=cg.m_beep	;
	m_Config.nMaxConnections	=cg.m_max	;
	m_Config.sMyName			=cg.m_name	;
	m_Config.nIdleTime		=cg.m_time1	;
	m_Config.nConfirmTime		=cg.m_time2	;
	m_Config.nRetry		=cg.m_nRetry;
	m_Config.nRetryInterval =cg.m_nRetryInterval;
	m_Config.m_Emote1=cg.m_Emote1.GetLength()>0?cg.m_Emote1[0]:0;
	m_Config.m_Emote2=cg.m_Emote2.GetLength()>0?cg.m_Emote2[0]:0;
	m_Config.m_Emote3=cg.m_Emote3.GetLength()>0?cg.m_Emote3[0]:0;
	m_Config.m_EmoteEsc=cg.m_EmoteEsc.GetLength()>0?cg.m_EmoteEsc[0]:0;

	if(!cg.m_startup){
		RegDeleteValue(hKey,ValueName);
	}else{
		GetModuleFileName(AfxGetInstanceHandle(),(char *)path,256);
		RegSetValueEx(hKey,
			ValueName,
			0,
			REG_SZ,
			path,
			strlen((char*)path));
	}
	RegCloseKey(hKey);

	StoreAddressBook();
	m_Config.Store();
}

//called when local editbox contents changed
void CClientWnd::OnLocalChange()
{
	CTalkSock * pSock=GetCurSock();
	if(!pSock)
		return;
	pSock->m_bNew=false;
	m_wndLocal.GetWindowText(pSock->m_sLocal);
	if(pSock->m_nStatus==S_NAMEOK)
		pSock->SendLocal();
}

void CClientWnd::OnFont() 
{
	CFontDialog fd;
	CFont ft,*pft;
	LOGFONT lf;
	pft=m_wndLocal.GetFont();
	if(pft){
		pft->GetLogFont(&lf);
		fd.m_cf.lpLogFont=&lf;
		fd.m_cf.Flags|=CF_INITTOLOGFONTSTRUCT;
	}
	fd.m_cf.rgbColors=(DWORD)m_wndLocal.m_clrText;
	if(fd.DoModal()==IDOK){
		m_wndLocal.m_clrText=fd.GetColor();
		m_wndRemote.m_clrText=fd.GetColor();	
		m_Config.clrEditText=fd.GetColor();

		fd.GetCurrentFont(&lf);
		m_Config.lfEdit=lf;
		ft.CreateFontIndirect(&lf);
		m_wndLocal.SetFont(&ft);
		m_wndRemote.SetFont(&ft);
		ft.Detach();
	}
}

void CClientWnd::OnBackcolor() 
{
	CColorDialog cd;
	if(cd.DoModal()==IDOK){
		m_Config.clrEditBack=cd.GetColor();
		DeleteObject(m_wndLocal.m_hbrBack);

		CBrush br(cd.GetColor());
		m_wndLocal.m_clrBack=cd.GetColor();
		m_wndRemote.m_clrBack=cd.GetColor();
		m_wndLocal.m_hbrBack=(HBRUSH)br;
		m_wndRemote.m_hbrBack=(HBRUSH)br;
		br.Detach();

		m_wndLocal.Invalidate();
		m_wndRemote.Invalidate();
	}
}

void CClientWnd::OnHscroll() 
{
	if(m_wndLocal.GetStyle()&WS_HSCROLL){
		m_wndLocal.ModifyStyle(WS_HSCROLL,0	
			,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		m_wndRemote.ModifyStyle(WS_HSCROLL,0	
			,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		m_Config.bHScroll=false;
	}else{
		m_wndLocal.ModifyStyle(0,WS_HSCROLL	
			,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		m_wndRemote.ModifyStyle(0,WS_HSCROLL	
			,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		m_Config.bHScroll=true;
	}	
}

void CClientWnd::OnVscroll() 
{
	if(m_wndLocal.GetStyle()&WS_VSCROLL){
		m_wndLocal.ModifyStyle(WS_VSCROLL,0	
			,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		m_wndRemote.ModifyStyle(WS_VSCROLL,0	
			,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		m_Config.bVScroll=false;
	}else{
		m_wndLocal.ModifyStyle(0,WS_VSCROLL	
			,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		m_wndRemote.ModifyStyle(0,WS_VSCROLL	
			,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		m_Config.bVScroll=true;
	}
}

void CClientWnd::OnUpdateVscroll(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndLocal.GetStyle()&WS_VSCROLL);	
	
}

void CClientWnd::OnUpdateHscroll(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndLocal.GetStyle()&WS_HSCROLL);	
}

void CClientWnd::OnEditCopy() 
{
	CWnd * pWnd=GetFocus();
	if(!pWnd)
		return;
	if(pWnd->IsKindOf(RUNTIME_CLASS(CEdit)))
		((CEdit*)pWnd)->Copy();	
}

void CClientWnd::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	CWnd * pWnd=GetFocus();
	if(!pWnd){
		pCmdUI->Enable(false);
		return;
	}
	if(pWnd->IsKindOf(RUNTIME_CLASS(CEdit))){
		int start,end;
		((CEdit*)pWnd)->GetSel(start,end);
		if(start==end)
			pCmdUI->Enable(false);
		else
			pCmdUI->Enable(true);
	}else
			pCmdUI->Enable(false);
}

void CClientWnd::OnEditCut() 
{
	CWnd * pWnd=GetFocus();
	if(!pWnd)
		return;
	if(pWnd->IsKindOf(RUNTIME_CLASS(CEdit)))
		((CEdit*)pWnd)->Cut();	
}

void CClientWnd::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	CWnd * pWnd=GetFocus();
	if(!pWnd){
		pCmdUI->Enable(false);
		return;
	}
	BOOL ret;
	if(pWnd->IsKindOf(RUNTIME_CLASS(CEdit))){
		if(((CEdit*)pWnd)->GetStyle()&ES_READONLY){
			ret=false;
		}else{
			int start,end;
			((CEdit*)pWnd)->GetSel(start,end);
			if(start==end)
				ret=false;
			else
				ret=true;
		}
	}else
			ret=false;
	pCmdUI->Enable(ret);
}

void CClientWnd::OnEditPaste() 
{
	CWnd * pWnd=GetFocus();
	if(!pWnd)
		return;
	if(pWnd->IsKindOf(RUNTIME_CLASS(CEdit)))
		((CEdit*)pWnd)->Paste();	
}

void CClientWnd::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	CWnd * pWnd=GetFocus();
	if(!pWnd){
		pCmdUI->Enable(false);
		return;
	}
	BOOL ret;
	if(pWnd->IsKindOf(RUNTIME_CLASS(CEdit))){
		if(((CEdit*)pWnd)->GetStyle()&ES_READONLY){
			ret=false;
		}else{
			if(!OpenClipboard())
				ret=false;
			else{
				ret=(int)GetClipboardData(CF_TEXT);
				CloseClipboard();
			}
		}
	}else
			ret=false;
	pCmdUI->Enable(ret);
}

BOOL CClientWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if(HIWORD(wParam)==LBN_SELCHANGE){
		UpdateView();
		return true;
	}
	return CWnd::OnCommand(wParam, lParam);
}

//add bar item.if reached the limit(30),we delete first closed one to make space.
//called by:CClientWnd::Connect(),CClientWnd::ProcessMessage()
int CClientWnd::AddBarItem(CString sText, int nIcon,POSITION Pos)
{
	int count=m_wndBar.GetCount();
	CTalkSock * pSock;

	POSITION pos;
	int i=count;
	if(count>=30)
		for(i=0;i<count;i++){
			pos=(POSITION)m_wndBar.GetItemData(i);
			pSock=(CTalkSock*)TSL.GetAt(pos);
			ASSERT(pSock);
			if(pSock->m_nStatus==S_CLOSED){ 
				m_wndBar.DeleteListString(i);
				break;
			}
		}

	m_wndBar.InsertString(i,sText,nIcon);

	SetTrayIcon(); //Added by andy,2k1.5.12
	
	m_wndBar.SetItemData(i,(DWORD)Pos);
	m_wndBar.SetCurSel(i);			
	UpdateView();

	return i;
}

//pass the focus to local editbox
void CClientWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	GetDlgItem(102)->SetFocus();
}

//called by:CMainFrame::DestroyWindow()
BOOL CClientWnd::DestroyWindow() 
{
	StoreAddressBook();
	m_Config.Store();

	return CWnd::DestroyWindow();
}


//check and return number of new log items
// if error occurs,0 will be returned;
int CClientWnd::CheckNew()
{
	int count;
	int ret=0;
	CFile logf;
	if(!logf.Open(m_sPath+LOGFILE,
		CFile::modeCreate|
		CFile::modeNoTruncate|
		CFile::modeRead)){
	}else{
		if(logf.GetLength()){
			LOGITEM *li=(LOGITEM*)new LOGITEM;
			CArchive logar(&logf,CArchive::load);
			logar>>count;
			while(count--){
				logar>>li->bNew;
				if(li->bNew)
					ret++;
				logar>>li->bOut;
				logar>>li->sIP;
				logar>>li->sLocal>>li->sRemote;
				logar>>li->sTalkName;
				logar>>li->tBeginTime;
				logar>>li->tEndTime;
			}
			delete li;
		}
	}
	return ret;
}

void CClientWnd::ProcessMessage(CTalkSock* pSock,MESSAGE msg)
{
	ASSERT(pSock);
	if(!pSock)
		return;

	CWnd *pMain=AfxGetApp()->m_pMainWnd, *pFore=GetForegroundWindow();
	BOOL bInvisible=(pMain && (!pMain->IsWindowVisible() || (pFore && pFore->GetSafeHwnd()!=pMain->GetSafeHwnd())));

	int i=PositionToIndex(pSock->m_MyPos);

	if(msg.bCommand==1){
		BOOL bConfirm=(m_bWantTalk && bInvisible) || (m_bWantTalk && pSock->m_bCallIn);

		if(bConfirm){
			CConfirm * pConfirm=(CConfirm*)new CConfirm;
			if(pConfirm){
				pConfirm->m_sName=pSock->m_sNickName;
				pConfirm->m_nSockID=pSock->m_nID;
				pConfirm->m_sIP=pSock->m_sIP;
				pConfirm->m_nTimer=m_Config.nConfirmTime;
				pConfirm->m_bCallIn=pSock->m_bCallIn;
				pConfirm->Create(this);

				pSock->m_bConfirming=true;
			}
		}else{
			if(pSock->m_bCallIn)
				NotifySound(1);
		}
		
		ABITEM * abi=NULL;
		POSITION pos=m_ABList.GetHeadPosition();
		while(pos){
			abi=m_ABList.GetNext(pos);
			if(!abi)
				continue;
			if(!abi->Name.Compare(pSock->m_sNickName))
				break;
			abi=NULL;
		}
		
		CString wm,am;
		if(abi && abi->bWelMsg)
			wm=abi->WelMsg;
		else
			wm=m_Config.sWelMsg;
		if(abi && abi->bLvWord)
			am=abi->LvWord;
		else
			am=m_Config.sAbsentMsg;
		if(wm.GetLength()>=2 && wm.Right(2).Compare("\r\n"))
			wm+="\r\n";

		wm.Replace("%name%",pSock->m_sNickName);
		pSock->m_sLocal=wm+pSock->m_sLocal;
		
		if(!m_bWantTalk){
			am.Replace("%name%",pSock->m_sNickName);
			am=CString("\r\n")+am;
			pSock->m_sLocal+=am;
			pSock->m_bWantTalk=false;
		}

		pSock->SendLocal();
		UpdateView();
	}

	if(i!=LB_ERR){ //in bar
		if(msg.bCommand==1){
			m_wndBar.SetImage(i,NOR);
			m_wndBar.SetString(i,pSock->m_sNickName);
			UpdateView();
		}

		if(i==m_wndBar.GetCurSel()){
			WORD w,wa,wb,wc,wd;
			CString str;
			m_wndRemote.GetWindowText(str);
			int len=str.GetLength();

			switch(msg.bCommand){
			case 2:
				m_wndRemote.SetWindowText((char*)msg.pBuf);
				break;
			case 3:
				w=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
				m_wndRemote.SetSel(w,w);
				break;
			case 4:
				wa=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
				wb=MAKEWORD(msg.pBuf[2],msg.pBuf[3]);

				if(wb>len)
					wb=len;

				m_wndRemote.SetSel(wa,wb);
				if(msg.pBuf[4]==0x0d)
					m_wndRemote.ReplaceSel("\r\n");
				else
					m_wndRemote.ReplaceSel((const char*)&msg.pBuf[4]);
				break;
			case 5:
				wa=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
				wb=MAKEWORD(msg.pBuf[2],msg.pBuf[3]);
				if(msg.wLength==9){
					wc=MAKEWORD(msg.pBuf[5],msg.pBuf[6]);
					wd=MAKEWORD(msg.pBuf[7],msg.pBuf[8]);

					if(wb>len)
						wb=len;
					m_wndRemote.SetSel(wa,wb);
					m_wndRemote.ReplaceSel("");
				}else{
					wc=MAKEWORD(msg.pBuf[4],msg.pBuf[5]);
					wd=MAKEWORD(msg.pBuf[6],msg.pBuf[7]);

					if(wb>len)
						wb=len;
					if( wa>wb)
						wa=wb;
					m_wndRemote.SetSel(wa,wb);
					m_wndRemote.ReplaceSel("");

					len-=(wb-wa);

					if(wa>len)
						wa=len;
					m_wndRemote.SetSel(wc,wa);
					m_wndRemote.ReplaceSel("");
				}			
				break;
			case 6:
				wa=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
				wb=MAKEWORD(msg.pBuf[2],msg.pBuf[3]);

				if(wb>len-wa)
					wb=len-wa;

				m_wndRemote.SetSel(wa,wa+wb);
				m_wndRemote.ReplaceSel("");
				break;
			case 7:
				wa=MAKEWORD(msg.pBuf[0],msg.pBuf[1]);
				wb=MAKEWORD(msg.pBuf[2],msg.pBuf[3]);

				if(wb>len)
					wb=len;

				m_wndRemote.SetSel(wa,wb);
				m_wndRemote.ReplaceSel((const char *)&msg.pBuf[4]);
				break;
			default:	
				break;
			} //switch
		}
	}else{  //not in bar
		if(msg.bCommand==1){
			AddBarItem(pSock->m_sNickName,NOR,pSock->m_MyPos);
		}		
	}

	//ring the bell!
	if(i!=LB_ERR && msg.bCommand==8 )//&& m_bWantTalk && pSock->m_bWantTalk)
		NotifySound(1);

	//on message received	
	if(i!=LB_ERR && i==m_wndBar.GetCurSel() && pSock->m_bWantTalk && msg.bCommand<8 && msg.bCommand>3){
		if(bInvisible && !pSock->m_bConfirming){
			if(m_Config.bBeep){
				NotifySound(-1);
				pMain->FlashWindow(TRUE);
			}else{ 
				if(!pMain->IsWindowVisible()){
					AfxGetMainWnd()->ShowWindow(SW_SHOW);
					AfxGetMainWnd()->ShowWindow(SW_RESTORE);
				}
				pMain->SetForegroundWindow();
			}
		}
	}

	free(msg.pBuf);
}

LRESULT CClientWnd::OnConfirmOver(WPARAM wParam,LPARAM lParam)
{
	int id=(int)wParam,ret=(int)lParam;
	
	CTalkSock* pSock=NULL;
	POSITION pos=TSL.GetHeadPosition();
	while(pos){
		pSock=TSL.GetNext(pos);
		if(!pSock)
			continue;
		if(pSock->m_nID==id)
			break;
	}
	if(!pSock)
		return 0;

	if(pSock->m_nStatus!=S_NAMEOK)
		return 0;

	pSock->m_bConfirming=false;

	ABITEM * abi=NULL;
	pos=m_ABList.GetHeadPosition();
	while(pos){
		abi=m_ABList.GetNext(pos);
		if(!abi)
			continue;
		if(!abi->Name.Compare(pSock->m_sNickName))
			break;
		abi=NULL;
	}
	
	CString am;
	if(abi && abi->bLvWord)
		am=abi->LvWord;
	else
		am=m_Config.sAbsentMsg;

	am.Replace("%name%",pSock->m_sNickName);
	am=CString("\r\n")+am;

	if(ret==2){
		m_bWantTalk=false;
		pSock->m_bWantTalk=false;
		SetTrayIcon();
		
		pSock->m_bNew=true;

		pSock->m_sLocal+=am;
		pSock->SendLocal();
		UpdateView();
	}else{
		if(pSock->m_nStatus=S_NAMEOK){
			if(ret){
				CWnd *pMain=AfxGetApp()->m_pMainWnd;
				if(pMain){
					pMain->SetForegroundWindow();
					if(!pMain->IsWindowVisible()){
						pMain->ShowWindow(SW_SHOW);
						pMain->ShowWindow(SW_RESTORE);
					}
				}
			}else{
				pSock->m_bWantTalk=false;

				//message	
				pSock->m_sLocal+=am;
				pSock->SendLocal();
				UpdateView();
			}
		}
	}

	return 0;	
}

void CClientWnd::ProcessOnConnect(CTalkSock* pSock,int nErrorCode)
{
	if(nErrorCode){
		pSock->m_nStatus=S_CONNECTFAILED;
		pSock->m_nElapsedTime=0;
		m_wndBar.SetImage(PositionToIndex(pSock->m_MyPos),YEL);
		pSock->m_nTried++;
		if(pSock->m_nTried==pSock->m_nRetry){
			//5.7
			CloseSocket(pSock);
		}
	}else{	//connected successfully
		pSock->m_nStatus=S_CONNECTED;
		pSock->m_nElapsedTime=0;
		pSock->AsyncSelect(FD_READ|FD_WRITE|FD_CLOSE);

		UINT port;
		CString ip;
		pSock->GetPeerName(ip,port);
		pSock->m_sIP=ip;

		pSock->SendName();
	}	
}

void CClientWnd::NotifySound(int nType)
{
	printf("\7\7\7\7");
	if(nType==1)
		::PlaySound((const char *)IDR_NOTIFY,AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC);	
	if(nType==0)
		::PlaySound((const char *)IDR_LOGOUT,AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC);	
}

void CClientWnd::SetTrayIcon()
{
	CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	if(!pMain)
		return;

//Added by andy,2k1.5.12
	int nBarItem=m_wndBar.GetCount();
	if(nBarItem>0){

//	if(m_nNewLog>0){
		if(m_bWantTalk)
			pMain->SetTrayIcon(IDI_ACTIVE);
		else
			pMain->SetTrayIcon(IDI_ICON2);
	}else{
		if(m_bWantTalk)
			pMain->SetTrayIcon(IDI_ICON4);
		else
			pMain->SetTrayIcon(IDI_ICON1);
	}		

}

BOOL CClientWnd::LoadAddressBook()
{
	POSITION pos=m_ABList.GetHeadPosition();
	while(pos){
		ABITEM * abi=m_ABList.GetNext(pos);
		if(abi)
			delete abi;
	}
	m_ABList.RemoveAll();

	CFile abf;
	if(!abf.Open(m_sPath+ABFILE,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead))
		return false;

	if(abf.GetLength()){
		int count;

		CArchive abar(&abf,CArchive::load);
		abar>>count;
		while(count--){
			ABITEM *abi=(ABITEM*)new ABITEM;
			if(!abi)
				return -1;
			abar>>abi->Name;
			abar>>abi->IP;
			abar>>abi->WelMsg;
			abar>>abi->LvWord;
			abar>>abi->bWelMsg;
			abar>>abi->bLvWord;
			m_ABList.AddTail(abi);
		}
	}
	return true;
}

BOOL CClientWnd::StoreAddressBook()
{
	CFile abf;
	if(abf.Open(m_sPath+ABFILE,CFile::modeCreate|CFile::modeReadWrite)){
		CArchive abar(&abf,CArchive::store);
		abar<<m_ABList.GetCount();
		
		POSITION pos=m_ABList.GetHeadPosition();
		while(pos){
			ABITEM* abi=m_ABList.GetNext(pos);
			if(!abi)
				continue;
			abar<<abi->Name;
			abar<<abi->IP;
			abar<<abi->WelMsg;
			abar<<abi->LvWord;
			abar<<abi->bWelMsg;
			abar<<abi->bLvWord;
		}
		return true;
	}
	return false;
}

void CClientWnd::CloseSocket(CTalkSock *pSock)
{
	int i=PositionToIndex(pSock->m_MyPos);
	
	if(i!=LB_ERR)
		m_wndBar.SetImage(i,RED);

	//log it if not empty
	if(!(pSock->m_sLocal.IsEmpty() && pSock->m_sRemote.IsEmpty())){
		if(pSock->m_bNew){
			m_nNewLog++;
			SetTrayIcon();
		}
		CFile logf;
		if(logf.Open(m_sPath+"Log.dat",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite)){
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
			// logar<<pSock->m_bNew;

			logar<<false;  //modified on 2001/5/4. It seems useless and carking! :-( 

			logar<<!pSock->m_bCallIn;
			logar<<pSock->m_sIP;
			logar<<pSock->m_sLocal<<pSock->m_sRemote;
			logar<<pSock->m_sNickName;
			logar<<pSock->m_tBeginTime;
			logar<<CTime::GetCurrentTime();
		}
	}
	pSock->m_tEndTime=CTime::GetCurrentTime();

	pSock->ClearBuffer();
	pSock->m_nStatus=S_CLOSED;
	pSock->m_nElapsedTime=0;

	
	if(pSock->m_hSocket!=INVALID_SOCKET)
		pSock->AsyncSelect(0);
	pSock->Close();

	NotifySound(0);
	UpdateView();
}

void CClientWnd::UpdateView()
{
	m_wndRemote.SetReadOnly(true);
	m_wndLocal.SetReadOnly(true);

	if(!m_wndBar.GetCount()){
		m_wndRemote.SetWindowText("");
		m_wndLocal.SetWindowText("");
	}else{
		int sel=m_wndBar.GetCurSel();
		if(sel==LB_ERR){
			m_wndBar.SetCurSel(0);
			sel=0;
		}
		CTalkSock* pSock=TSL.GetAt((POSITION)m_wndBar.GetItemData(sel));
		ASSERT(pSock);
		if(pSock){
			m_wndRemote.SetWindowText(pSock->m_sRemote);
			m_wndRemote.SetSel(pSock->m_wRemotePos,pSock->m_wRemotePos);
			m_wndLocal.SetWindowText(pSock->m_sLocal);
			m_wndLocal.SetSel(pSock->m_wLocalPos,pSock->m_wLocalPos);
			if(pSock->m_nStatus<=S_NAMEOK)
				m_wndLocal.SetReadOnly(false);
		}
	}
}

int CClientWnd::PositionToIndex(POSITION Pos)
{
	int count=m_wndBar.GetCount();
	if(count!=LB_ERR)
	for(int i=0;i<count;i++){
		POSITION pos=(POSITION)m_wndBar.GetItemData(i);
		if(pos==Pos)
			return i;
	}
	return LB_ERR;
}

POSITION CClientWnd::IndexToPosition(int i)
{
	int n=m_wndBar.GetCount();
	if(!n || i>=n)
		return NULL;
	POSITION pos=(POSITION)m_wndBar.GetItemData(i),p;
	p=TSL.GetHeadPosition();
	while(p){
		if(p==pos)
			return pos;
		TSL.GetNext(p);
	}
	return NULL;
}

void CClientWnd::OnUpdateReconnect(CCmdUI* pCmdUI) 
{
	CTalkSock* pSock=GetCurSock();
	if(pSock && (pSock->m_nStatus==S_CONNECTFAILED || pSock->m_nStatus==S_CLOSED))
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);

}

void CClientWnd::OnReconnect() 
{
	if(!m_bWantTalk){
		m_bWantTalk=true;
		SetTrayIcon();
	}

	CTalkSock* pSock=GetCurSock();
	if(!pSock)
		return;

	if(pSock->m_nStatus==S_CONNECTFAILED){
		pSock->m_nElapsedTime=pSock->m_nRetryInterval*600;
	}else if(pSock->m_nStatus==S_CLOSED){
		int i=0;
		POSITION pos=TSL.GetHeadPosition();

		while(pos){
			CTalkSock * pSock=(CTalkSock*)TSL.GetNext(pos);
			if(pSock && pSock->m_nStatus!=S_CLOSED)
				i++;
		}
		if(i>=m_Config.nMaxConnections){
			AfxMessageBox("Too many connections!");
			return;
		}

		//create new sokcet
		if(!pSock->Create(0,SOCK_STREAM,FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE)){
			AfxMessageBox("Faied to create socket!");
			return;
		}

		//renew the CTalkSocket object
		pSock->m_nRetry=m_Config.nRetry;
		pSock->m_nTried=0;
		pSock->m_nRetryInterval=m_Config.nRetryInterval;

		pSock->m_sLocal.Empty();
		pSock->m_sOldLocal.Empty();
		pSock->m_sRemote.Empty();
		pSock->m_bCallIn=false;
		pSock->m_wLocalPos=0;
		pSock->m_wRemotePos=0;

		pSock->m_bNew=false;
		pSock->m_nIdleTime=0;

		pSock->m_bConfirming=false;
		pSock->m_bWantTalk=true;

		pSock->m_bResolving=false;
		memset(&(pSock->m_Msg),0,sizeof(MESSAGE));
		
		pSock->m_nStatus=S_CONNECTFAILED;
		pSock->m_nElapsedTime=pSock->m_nRetryInterval*600;

		m_wndBar.SetImage(PositionToIndex(pSock->m_MyPos),GRN);
		UpdateView();
	}
}

LRESULT CClientWnd::OnResolveOver(WPARAM wParam,LPARAM lParam)
{
	HOSTENT * pHost;
	CTalkSock* pSock;
	RESOLVEITEM * pri=NULL;

	POSITION p,pos=m_ResolveList.GetHeadPosition();
	while(pos){
		p=pos;
		pri=m_ResolveList.GetNext(pos);
		if(!pri)
			continue;
		if(pri->handle==(HANDLE)wParam)
			break;
		else pri=NULL;
	}
	if(!pri)
		return 0;
	m_ResolveList.RemoveAt(p);

	//check if the pSock exists in TSL
	BOOL ok=false;
	pos=TSL.GetHeadPosition();
	while(pos){
		pSock=TSL.GetNext(pos);
		if(pSock && pSock->m_nID==pri->id){
			ok=true;
			break;
		}
	}
	if(!ok)
		goto END;

	if(pSock->m_nStatus==S_CLOSED)
		goto END;

	//$&*%^YU*&^%&#%*%& ok,now let's do with the resolve result
	pHost=(HOSTENT*)pri->buf;
	pSock->m_bResolving=false;

	if(WSAGETASYNCERROR(lParam)){ //error:unresolvable hostname
		pSock->m_nStatus=S_CONNECTFAILED;
		pSock->m_nElapsedTime=0;
		m_wndBar.SetImage(PositionToIndex(pSock->m_MyPos),YEL);
		pSock->m_nTried++;
		if(pSock->m_nTried==pSock->m_nRetry)
			CloseSocket(pSock);
	}else{ //succeed
		CString sIP;
		sIP.Format("%d.%d.%d.%d",
			(BYTE)pHost->h_addr_list[0][0],
			(BYTE)pHost->h_addr_list[0][1],
			(BYTE)pHost->h_addr_list[0][2],
			(BYTE)pHost->h_addr_list[0][3]);

		pSock->m_nStatus=S_CONNECTING;
		pSock->m_nElapsedTime=0;
		pSock->m_sIP=sIP;
		m_wndBar.SetImage(PositionToIndex(pSock->m_MyPos),GRN);
		if(!pSock->Connect(sIP,PORT))
			if(pSock->GetLastError()!=WSAEWOULDBLOCK){
				pSock->m_nStatus=S_CONNECTFAILED;
				pSock->m_nElapsedTime=0;
				m_wndBar.SetImage(PositionToIndex(pSock->m_MyPos),YEL);
				pSock->m_nTried++;
				if(pSock->m_nTried==pSock->m_nRetry)
					CloseSocket(pSock);
			}
	}

END:
	free(pri->buf);
	delete pri;

	return 0;	
}

CTalkSock * CClientWnd::GetCurSock()
{
	int i=m_wndBar.GetCurSel();
	if(i==LB_ERR)
		return NULL;
	POSITION pos=(POSITION)m_wndBar.GetItemData(i);
	return 	(CTalkSock*)TSL.GetAt(pos);
}

//helper used to load emote
BOOL CClientWnd::getline(CString &str,FILE * fp)
{
	CString buffer;
	char * buf=buffer.GetBuffer(1024);
	int i=0;

	LONG pos=ftell(fp);
	if(fread(buf,1,1024,fp)==0)
		return false;

	buffer.ReleaseBuffer();
	if(buffer.IsEmpty())
		return false;

	for(i=0;i<1023;i++)
		if(buffer[i]=='\r'||buffer[i]=='\n'){
			str=buffer.Left(i);
			if(buffer[i]=='\r'||buffer[i+1]=='\n')
				fseek(fp,i+2+pos,SEEK_SET);
			else
				fseek(fp,i+1+pos,SEEK_SET);
			break;
		}
	if(i==1023)
		return false;

	buffer=str;
	if((i=buffer.Find("//",0))!=-1)
		str=buffer.Left(i);
	return true;
}


