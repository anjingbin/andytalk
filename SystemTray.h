
#ifndef _INCLUDED_SYSTEMTRAY_H_
#define _INCLUDED_SYSTEMTRAY_H_

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CSystemTray window

class CSystemTray : public CWnd
{
public:
    CSystemTray();
    CSystemTray(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID);
    virtual ~CSystemTray();

    DECLARE_DYNAMIC(CSystemTray)

// Operations
public:
//DEL     BOOL Enabled() { return m_bEnabled; }
    BOOL Visible() { return !m_bHidden; }

    // Create the tray icon
    Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID);

    // Change or retrieve the Tooltip text
    BOOL    SetTooltipText(LPCTSTR pszTooltipText);
    BOOL    SetTooltipText(UINT nID);

    // Change or retrieve the icon displayed
    BOOL  SetIcon(HICON hIcon);
    BOOL  SetIcon(LPCTSTR lpszIconName);
    BOOL  SetIcon(UINT nIDResource);
    BOOL  SetStandardIcon(LPCTSTR lpIconName);
    BOOL  SetStandardIcon(UINT nIDResource);
    void  HideIcon();
    void  ShowIcon();

    BOOL  SetIconList(UINT uFirstIconID, UINT uLastIconID); 
    BOOL  SetIconList(HICON* pHIconList, UINT nNumIcons); 
    BOOL  StepAnimation();
    BOOL  StopAnimation();

    BOOL SetMenuDefaultItem(UINT uItem, BOOL bByPos);

    // Change or retrieve the window to send notification messages to
    BOOL  SetNotificationWnd(CWnd* pNotifyWnd);

    // Default handler for tray notification message
    virtual LRESULT OnTrayNotification(WPARAM uID, LPARAM lEvent);
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSystemTray)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:

    BOOL            m_bEnabled;   // does O/S support tray icon?
    BOOL            m_bHidden;    // Has the icon been hidden?
    NOTIFYICONDATA  m_tnd;

    CArray<HICON, HICON> m_IconList;
    static UINT  m_nIDEvent;
    UINT         m_uIDTimer;
    int          m_nCurrentIcon;
    COleDateTime m_StartTime;
    int          m_nAnimationPeriod;
    HICON        m_hSavedIcon;
    UINT         m_DefaultMenuItemID;
    BOOL         m_DefaultMenuItemByPos;

protected:
	//{{AFX_MSG(CSystemTray)
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};


#endif

/////////////////////////////////////////////////////////////////////////////
