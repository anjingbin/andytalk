#if !defined(AFX_LOGDLG_H__5E062124_9FEA_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_LOGDLG_H__5E062124_9FEA_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog

class CLogDlg : public CDialog
{
// Construction
public:
	CString m_sLogFile;

	CString name;
	POSITION POS;
	CString IP;

	CList<LOGITEM*,LOGITEM*> Log;
	CList<ABITEM *,ABITEM*> * AB;

	CLogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogDlg)
	enum { IDD = IDD_LOG };
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogDlg)
	afx_msg void OnReconn();
	virtual BOOL OnInitDialog();
	afx_msg void OnView();
	afx_msg void OnLogDel();
	afx_msg void OnLogAdd();
	afx_msg void OnDestroy();
	afx_msg void OnDblclkLoglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickLoglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLogMerge();
	afx_msg void OnLogEncrypt();
	afx_msg void OnLogMerEnc();
	afx_msg void OnLogExp();
	afx_msg void OnLogMer2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int MergeString2Log(CString,BOOL bremote,LOGITEM *li);
	CString Log2MergeString(LOGITEM *,BOOL bremote);
	CToolTipCtrl m_wndTip;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGDLG_H__5E062124_9FEA_11D3_8382_0080C86BAA81__INCLUDED_)
