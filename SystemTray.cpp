
#include "stdafx.h"
#include "SystemTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSystemTray, CWnd)

UINT CSystemTray::m_nIDEvent = 4567;


CSystemTray::CSystemTray()
{
    Initialise();
}

CSystemTray::CSystemTray(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, 
                         HICON icon, UINT uID)
{
    Initialise();
    Create(pParent, uCallbackMessage, szToolTip, icon, uID);
}

BOOL CSystemTray::Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, 
                         HICON icon, UINT uID)
{
    VERIFY(m_bEnabled = ( GetVersion() & 0xff ) >= 4);
    if (!m_bEnabled) return FALSE;

    ASSERT(uCallbackMessage >= WM_USER);

    ASSERT(_tcslen(szToolTip) <= 64);

    CWnd::CreateEx(0, AfxRegisterWndClass(0), _T(""), WS_POPUP, 0,0,10,10, NULL, 0);

    m_tnd.cbSize = sizeof(NOTIFYICONDATA);
    m_tnd.hWnd   = pParent->GetSafeHwnd()? pParent->GetSafeHwnd() : m_hWnd;
    m_tnd.uID    = uID;
    m_tnd.hIcon  = icon;
    m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_tnd.uCallbackMessage = uCallbackMessage;
    _tcscpy(m_tnd.szTip, szToolTip);

    VERIFY(m_bEnabled = Shell_NotifyIcon(NIM_ADD, &m_tnd));
    return m_bEnabled;
}

CSystemTray::~CSystemTray()
{
    RemoveIcon();
    m_IconList.RemoveAll();
    DestroyWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray icon manipulation

void CSystemTray::HideIcon()
{
    if (m_bEnabled && !m_bHidden) {
        m_tnd.uFlags = NIF_ICON;
        Shell_NotifyIcon (NIM_DELETE, &m_tnd);
        m_bHidden = TRUE;
    }
}

void CSystemTray::ShowIcon()
{
    if (m_bEnabled && m_bHidden) {
        m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        Shell_NotifyIcon(NIM_ADD, &m_tnd);
        m_bHidden = FALSE;
    }
}

BOOL CSystemTray::SetIcon(HICON hIcon)
{
    if (!m_bEnabled) return FALSE;

    m_tnd.uFlags = NIF_ICON;
    m_tnd.hIcon = hIcon;

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

BOOL CSystemTray::SetIcon(LPCTSTR lpszIconName)
{
    HICON hIcon = AfxGetApp()->LoadIcon(lpszIconName);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetIcon(UINT nIDResource)
{
    HICON hIcon = AfxGetApp()->LoadIcon(nIDResource);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetStandardIcon(LPCTSTR lpIconName)
{
    HICON hIcon = LoadIcon(NULL, lpIconName);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetStandardIcon(UINT nIDResource)
{
    HICON hIcon = LoadIcon(NULL, MAKEINTRESOURCE(nIDResource));

    return SetIcon(hIcon);
}
 
BOOL CSystemTray::SetIconList(UINT uFirstIconID, UINT uLastIconID) 
{
	if (uFirstIconID > uLastIconID)
        return FALSE;

	UINT uIconArraySize = uLastIconID - uFirstIconID + 1;
	const CWinApp * pApp = AfxGetApp();
    ASSERT(pApp != 0);

    m_IconList.RemoveAll();
    try {
	    for (UINT i = uFirstIconID; i <= uLastIconID; i++)
		    m_IconList.Add(pApp->LoadIcon(i));
    }
    catch (CMemoryException *e)
    {
        e->ReportError();
        e->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}

BOOL CSystemTray::SetIconList(HICON* pHIconList, UINT nNumIcons)
{
    m_IconList.RemoveAll();

    try {
	    for (UINT i = 0; i <= nNumIcons; i++)
		    m_IconList.Add(pHIconList[i]);
    }
    catch (CMemoryException *e)
    {
        e->ReportError();
        e->Delete();
        m_IconList.RemoveAll();
        return FALSE;
    }

    return TRUE;
}

//DEL BOOL CSystemTray::Animate(UINT nDelayMilliSeconds, int nNumSeconds /*=-1*/)
//DEL {
//DEL     StopAnimation();
//DEL 
//DEL     m_nCurrentIcon = 0;
//DEL     m_StartTime = COleDateTime::GetCurrentTime();
//DEL     m_nAnimationPeriod = nNumSeconds;
//DEL     m_hSavedIcon = GetIcon();
//DEL 
//DEL 	// Setup a timer for the animation
//DEL 	m_uIDTimer = SetTimer(m_nIDEvent, nDelayMilliSeconds, NULL);
//DEL 
//DEL     return (m_uIDTimer != 0);
//DEL }

BOOL CSystemTray::StepAnimation()
{
    if (!m_IconList.GetSize())
        return FALSE;

    m_nCurrentIcon++;
    if (m_nCurrentIcon >= m_IconList.GetSize())
        m_nCurrentIcon = 0;

    return SetIcon(m_IconList[m_nCurrentIcon]);
}

BOOL CSystemTray::StopAnimation()
{
    BOOL bResult = FALSE;

    if (m_uIDTimer)
	    bResult = KillTimer(m_uIDTimer);
    m_uIDTimer = 0;

    if (m_hSavedIcon)
        SetIcon(m_hSavedIcon);
    m_hSavedIcon = NULL;

    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray tooltip text manipulation

BOOL CSystemTray::SetTooltipText(LPCTSTR pszTip)
{
    if (!m_bEnabled) return FALSE;

    m_tnd.uFlags = NIF_TIP;
    _tcscpy(m_tnd.szTip, pszTip);

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

BOOL CSystemTray::SetTooltipText(UINT nID)
{
    CString strText;
    VERIFY(strText.LoadString(nID));

    return SetTooltipText(strText);
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray notification window stuff

BOOL CSystemTray::SetNotificationWnd(CWnd* pWnd)
{
    if (!m_bEnabled) return FALSE;

    // Make sure Notification window is valid
    ASSERT(pWnd && ::IsWindow(pWnd->GetSafeHwnd()));

    m_tnd.hWnd = pWnd->GetSafeHwnd();
    m_tnd.uFlags = 0;

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray menu manipulation

BOOL CSystemTray::SetMenuDefaultItem(UINT uItem, BOOL bByPos)
{
    if ((m_DefaultMenuItemID == uItem) && (m_DefaultMenuItemByPos == bByPos)) 
        return TRUE;

    m_DefaultMenuItemID = uItem;
    m_DefaultMenuItemByPos = bByPos;   

    CMenu menu, *pSubMenu;

    if (!menu.LoadMenu(m_tnd.uID)) return FALSE;
    if (!(pSubMenu = menu.GetSubMenu(0))) return FALSE;

    ::SetMenuDefaultItem(pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CSystemTray, CWnd)
	//{{AFX_MSG_MAP(CSystemTray)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LRESULT CSystemTray::OnTrayNotification(WPARAM wParam, LPARAM lParam) 
{
    if (wParam != m_tnd.uID)
        return 0L;

    CMenu menu, *pSubMenu;
    CWnd* pTarget = AfxGetMainWnd();

    if (LOWORD(lParam) == WM_RBUTTONUP)
    {    
        if (!menu.LoadMenu(m_tnd.uID)) return 0;
        if (!(pSubMenu = menu.GetSubMenu(0))) return 0;

        ::SetMenuDefaultItem(pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);

        CPoint pos;
        GetCursorPos(&pos);

        pTarget->SetForegroundWindow();  
        ::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, 
                         pTarget->GetSafeHwnd(), NULL);

        // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
        pTarget->PostMessage(WM_NULL, 0, 0);

        menu.DestroyMenu();
    } 
    else if (LOWORD(lParam) == WM_LBUTTONDBLCLK) 
    {
        // double click received, the default action is to execute default menu item
        pTarget->SetForegroundWindow();  

        UINT uItem;
        if (m_DefaultMenuItemByPos)
        {
            if (!menu.LoadMenu(m_tnd.uID)) return 0;
            if (!(pSubMenu = menu.GetSubMenu(0))) return 0;
            uItem = pSubMenu->GetMenuItemID(m_DefaultMenuItemID);
        }
        else
            uItem = m_DefaultMenuItemID;
        
        pTarget->SendMessage(WM_COMMAND, uItem, 0);

        menu.DestroyMenu();
    }else if(LOWORD(lParam) == WM_LBUTTONDOWN){
		if(!pTarget->IsWindowVisible()){
			pTarget->ShowWindow(SW_SHOW);
			pTarget->ShowWindow(SW_RESTORE);
		}
		pTarget->SetForegroundWindow();
		
	}

    return 1;
}

LRESULT CSystemTray::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if (message == m_tnd.uCallbackMessage)
        return OnTrayNotification(wParam, lParam);
	
	return CWnd::WindowProc(message, wParam, lParam);
}
