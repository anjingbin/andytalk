#if !defined(AFX_CONFIRM_H__65DF98E3_A5C1_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_CONFIRM_H__65DF98E3_A5C1_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Confirm.h : header file
//
#define TIMERCONFIRM 2345
/////////////////////////////////////////////////////////////////////////////
// CConfirm dialog

class CConfirm : public CDialog
{
// Construction
public:
	BOOL m_bCallIn;
	int m_nSockID;
	int m_nReturn;
	CString m_sIP;
	CString m_sName;
	int m_nTimer;
	CConfirm(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CConfirm)
	enum { IDD = IDD_CONFIRM };
	CString	m_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfirm)
	public:
	virtual BOOL Create(CWnd * pCW);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfirm)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWnd* m_pWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIRM_H__65DF98E3_A5C1_11D3_8382_0080C86BAA81__INCLUDED_)
