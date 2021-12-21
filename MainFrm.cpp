// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "talk.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ICON_NOTIFY,OnTrayNotify)      
	ON_MESSAGE(WM_HOTKEY,OnHotKey)      
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bLeftDown=false;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//create tray icon
    m_NID.cbSize = sizeof(NOTIFYICONDATA);
    m_NID.hWnd   = GetSafeHwnd();
    m_NID.uID    = IDR_TRAYMENU;
    m_NID.hIcon  = AfxGetApp()->LoadIcon(IDI_ICON4);
    m_NID.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_NID.uCallbackMessage =WM_ICON_NOTIFY;
    strcpy(m_NID.szTip,"AndyTalk(CTRL+ALT+INS)");

	if(!m_NID.hWnd)
		return -1;

	if(!Shell_NotifyIcon(NIM_ADD, &m_NID))
		return -1;
	//create mainframe and child windows
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndClient.Create(NULL, NULL, WS_CHILD|WS_VISIBLE,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		|  CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
		return -1;
		
	// setup each toolbar button
	CImageList img;
	img.Create(IDB_TOOLBAR, 30, 0, RGB(191,191,191));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	img.Detach();

	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(50, 150);
	
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);
	m_wndToolBar.SetButtons(NULL, 11);
	
	m_wndToolBar.SetButtonInfo(0, ID_ADDRBOOK, TBSTYLE_BUTTON, 0);
	m_wndToolBar.SetButtonInfo(1, ID_LOG, TBSTYLE_BUTTON, 1);
	m_wndToolBar.SetButtonInfo(2, 0, TBBS_SEPARATOR, 4);
	m_wndToolBar.SetButtonInfo(3, ID_EDIT_CUT, TBSTYLE_BUTTON, 2);
	m_wndToolBar.SetButtonInfo(4, ID_EDIT_COPY, TBSTYLE_BUTTON, 3);
	m_wndToolBar.SetButtonInfo(5, ID_EDIT_PASTE, TBSTYLE_BUTTON, 4);
	m_wndToolBar.SetButtonInfo(6, 0, TBBS_SEPARATOR, 4);
	m_wndToolBar.SetButtonInfo(7, ID_CONNECT, TBSTYLE_BUTTON, 6);
	m_wndToolBar.SetButtonInfo(8, ID_REC, TBSTYLE_BUTTON, 7);
	m_wndToolBar.SetButtonInfo(9, ID_DISC, TBSTYLE_BUTTON, 8);
	m_wndToolBar.SetButtonInfo(10, ID_BEEP, TBSTYLE_BUTTON, 9);

	m_wndToolBar.SetButtonText(0, "Address");
	m_wndToolBar.SetButtonText(1, "Log");
	m_wndToolBar.SetButtonText(3, "Cut");
	m_wndToolBar.SetButtonText(4, "Copy");
	m_wndToolBar.SetButtonText(5, "Paste");
	m_wndToolBar.SetButtonText(7, "Connect");
	m_wndToolBar.SetButtonText(8, "Reconn");
	m_wndToolBar.SetButtonText(9, "Stop");
	m_wndToolBar.SetButtonText(10, "Beep");

	m_wndToolBar.SetSizes(CSize(53,42), CSize(30,22));
	m_wndToolBar.SetBorders(2,5,2,3);
	
	//set mainframe icon
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON4),true);
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON4),false);

	RegisterHotKey(GetSafeHwnd(),0,MOD_CONTROL|MOD_ALT,VK_INSERT);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	//turn off the bored clientedge
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	m_wndClient.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	//we process all commands in client window
	if (m_wndClient.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{
	//make it invisible in the taskbar when minimized
	if((nID&0xfff0)==SC_CLOSE){        
		SendMessage(WM_SYSCOMMAND,SC_ICON);
		return;
	}
	else
		CFrameWnd::OnSysCommand(nID, lParam);
	nID&=0xfff0;
	if(nID==SC_ICON)
		ShowWindow(SW_HIDE);
	else
		if(IsWindow(m_hWnd)&&!IsWindowVisible())
			ShowWindow(SW_SHOW);
}
void CMainFrame::OnTrayNotify(WPARAM wParam,LPARAM lParam)
{
	//process tray notify message
	if (wParam != m_NID.uID)
		return;

	CMenu menu, *pSubMenu;

	if (LOWORD(lParam) == WM_RBUTTONUP)
	{    
		if (!menu.LoadMenu(m_NID.uID))
			return;
		if (!(pSubMenu = menu.GetSubMenu(0)))
			return;

		::SetMenuDefaultItem(pSubMenu->m_hMenu,0,true);
		CPoint pos;
		GetCursorPos(&pos);
		SetForegroundWindow();  
		::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, 
						 GetSafeHwnd(), NULL);
		PostMessage(WM_NULL, 0, 0);
		menu.DestroyMenu();
	} 
	else if(LOWORD(lParam) == WM_LBUTTONDBLCLK) 
	{
		if(m_bLeftDown)
			KillTimer(666);

		SetForegroundWindow();  

		UINT uItem;
		if (!menu.LoadMenu(m_NID.uID)) 
			return;
		if (!(pSubMenu = menu.GetSubMenu(0))) 
			return;

		uItem = pSubMenu->GetMenuItemID(0);

		SendMessage(WM_COMMAND, uItem, 0);

		menu.DestroyMenu();

	}else if(LOWORD(lParam) == WM_LBUTTONDOWN){

		m_bLeftDown=true;		

		if(IsWindowVisible()){
			HWND wnd=::GetActiveWindow();
			if(wnd==GetSafeHwnd())
				m_bLeftDown=3;
		}

		SetTimer(666,GetDoubleClickTime(),NULL);	

	}
}

void CMainFrame::OnClose() 
{
	//let client window do all things!!!
	if(!m_wndClient.WantClose())
		return;
	CFrameWnd::OnClose();
}



BOOL CMainFrame::DestroyWindow() 
{
	//delete trayicon before quit
    m_NID.cbSize = sizeof(NOTIFYICONDATA);
    m_NID.hWnd   = GetSafeHwnd();
    m_NID.uID    = IDR_TRAYMENU;
    m_NID.uFlags = 0;
	if(m_NID.hWnd)
		Shell_NotifyIcon(NIM_DELETE, &m_NID);

	UnregisterHotKey(GetSafeHwnd(),0);

	m_wndClient.DestroyWindow();	
	return CFrameWnd::DestroyWindow();
}

void CMainFrame::SetTrayIcon(int nID)
{
    m_NID.cbSize = sizeof(NOTIFYICONDATA);
    m_NID.hWnd   = GetSafeHwnd();
	if(!m_NID.hWnd)
		return ;
    m_NID.uID    = IDR_TRAYMENU;
    m_NID.hIcon  = AfxGetApp()->LoadIcon(nID);
    m_NID.uFlags = NIF_ICON;

	Shell_NotifyIcon(NIM_MODIFY, &m_NID);
	return;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==666){

		if(!IsWindowVisible()){
			ShowWindow(SW_SHOW);
			ShowWindow(SW_RESTORE);
			SetForegroundWindow();
		}else{
			if(m_bLeftDown!=3){
				SetForegroundWindow();
			}else{
				SendMessage(WM_SYSCOMMAND,SC_CLOSE);
			}

		}

		m_bLeftDown=false;
		KillTimer(666);

	}

	CFrameWnd::OnTimer(nIDEvent);
}

LRESULT	CMainFrame::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	if(wParam != 0)
		return true;

	if(!IsWindowVisible()){
		ShowWindow(SW_SHOW);
		ShowWindow(SW_RESTORE);
		SetForegroundWindow();
	}else{
		HWND wnd=::GetActiveWindow();
		if(wnd !=GetSafeHwnd())
		{
			SetForegroundWindow();
		}
		else
		{
			SendMessage(WM_SYSCOMMAND,SC_CLOSE);
		}

	}
	return true;

}
