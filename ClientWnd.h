#if !defined(AFX_CLIENTWND_H__6C840621_8BA6_11D3_8381_0080C86BAA81__INCLUDED_)
#define AFX_CLIENTWND_H__6C840621_8BA6_11D3_8381_0080C86BAA81__INCLUDED_

#include "ListenSock.h"	// Added by ClassView
#include "TalkSock.h"
#include "LocalOut.h"	// Added by ClassView
#include "RemoteOut.h"
#include "Config.h"	// Added by ClassView
#include "Confirm.h"
#include "OutlookBar.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientWnd.h : header file
//
#define BUFFER_SIZE 1024
#define TALKTIMER 1234
#define NAMERESOLVMSG 9494
/////////////////////////////////////////////////////////////////////////////
// CClientWnd window

class CClientWnd : public CWnd
{
	// Construction
public:
	CClientWnd();

// Attributes
public:

// Operations
public:
	CTalkSession  * m_pCurTalkSession;
	void SetMyStatus(int Status);
	void SetTrayIcon(int IconID);
	BOOL m_bClosing;
	int CheckNew();
	CObList EmoteList;
	void Sound(int nType);
	void DeleteBarItem(int nIndex);
	BOOL m_bWantTalk;
	int AddBarItem(CString str,int nImage,DWORD dwData);
	CTalkSock * GetCurSock();
	void UpdateView();
	CString m_sPath;
	void OnLocalChange();
	BOOL WantClose();

	CStatusBarCtrl Status;

	CConfig Config;

	CObList TSL;
	CObList AddrBook;
	
	COutlookBar Bar;
	CLocalOut Local;
	CRemoteOut Remote;

	CListenSock* m_psockListen;

	void Connect(CString Dest,CString Name);

	void OnAccept(int nErrorCode);
	void OnInput(CString& str,int nType);

	virtual ~CClientWnd();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientWnd)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	CObList m_lstTalkSession;
	//{{AFX_MSG(CClientWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAddrbook();
	afx_msg void OnConnect();
	afx_msg void OnLog();
	afx_msg void OnUpdateBeep(CCmdUI* pCmdUI);
	afx_msg void OnBeep();
	afx_msg void OnDisc();
	afx_msg void OnUpdateDisc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWanttalk(CCmdUI* pCmdUI);
	afx_msg void OnWanttalk();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetting();
	afx_msg void OnFont();
	afx_msg void OnBackcolor();
	afx_msg void OnHscroll();
	afx_msg void OnVscroll();
	afx_msg void OnUpdateVscroll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHscroll(CCmdUI* pCmdUI);
	afx_msg void OnSave();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	friend class CTalkApp;
private:
	BOOL getline(CString& str,FILE *fp);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTWND_H__6C840621_8BA6_11D3_8381_0080C86BAA81__INCLUDED_)
 
