#if !defined(AFX_CLIENTWND_H__6C840621_8BA6_11D3_8381_0080C86BAA81__INCLUDED_)
#define AFX_CLIENTWND_H__6C840621_8BA6_11D3_8381_0080C86BAA81__INCLUDED_

#include "ListenSock.h"	// Added by ClassView
#include "TalkSock.h"
#include "LocalOut.h"	// Added by ClassView
#include "RemoteOut.h"
#include "Confirm.h"
#include "OutlookBar.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClientWnd window

class CClientWnd : public CWnd
{
// Construction
public:
	CClientWnd();

// Attributes
public:
	int m_nNewLog;
	BOOL m_bWantTalk;
	CString m_sPath;

	CConfig m_Config;

	COutlookBar m_wndBar;
	CLocalOut m_wndLocal;
	CRemoteOut m_wndRemote;

	HIMC m_hIMC;
	CStatusBarCtrl m_wndStatus;

	CListenSock* m_pListenSock;

	CList<ABITEM *,ABITEM*> m_ABList;
	CList<EMOTEITEM*,EMOTEITEM*> m_EmoteList;
	CList<RESOLVEITEM*,RESOLVEITEM*> m_ResolveList;
	CList<CTalkSock*,CTalkSock*> TSL;

// Operations
public:
	POSITION IndexToPosition(int i);
	int PositionToIndex(POSITION Pos);
	void UpdateView();
	void CloseSocket(CTalkSock* pSock);
	BOOL LoadAddressBook();
	BOOL StoreAddressBook();
	void SetTrayIcon();
	void NotifySound(int nType);
	void ProcessOnConnect(CTalkSock* pSock,int nErrorCode);
	void ProcessMessage(CTalkSock* pSock,MESSAGE msg);
	int CheckNew();
	int AddBarItem(CString sText, int nIcon,POSITION Pos);
	CTalkSock * GetCurSock();
	void OnLocalChange();
	BOOL WantClose();


	void Connect(CString sHost,CString sName);

	void ProcessOnAccept(int nErrorCode);
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
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnUpdateReconnect(CCmdUI* pCmdUI);
	afx_msg void OnReconnect();
	//}}AFX_MSG
	afx_msg LRESULT OnConfirmOver(WPARAM wParam,LPARAM lParam); 
	afx_msg LRESULT OnResolveOver(WPARAM wParam,LPARAM lParam); 
	DECLARE_MESSAGE_MAP()

	friend class CTalkApp;
private:
	int ID_SEED;
	BOOL getline(CString& str,FILE *fp);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTWND_H__6C840621_8BA6_11D3_8381_0080C86BAA81__INCLUDED_)
 
