// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__EE0A5093_8B0F_11D3_8381_0080C86BAA81__INCLUDED_)
#define AFX_MAINFRM_H__EE0A5093_8B0F_11D3_8381_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientWnd.h"


class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame(); 
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:
	CClientWnd    m_wndClient;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetTrayIcon(int nID);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;
	NOTIFYICONDATA m_NID;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnTrayNotify(WPARAM wParam,LPARAM lParam);
	afx_msg	LRESULT	OnHotKey(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bLeftDown;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__EE0A5093_8B0F_11D3_8381_0080C86BAA81__INCLUDED_)
