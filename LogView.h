#if !defined(AFX_LOGVIEW_H__DD788024_A651_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_LOGVIEW_H__DD788024_A651_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogView dialog

class CLogView : public CDialog
{
// Construction
public:
	CString title;
	CLogView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogView)
	enum { IDD = IDD_VIEW };
	CString	m_remote;
	CString	m_local;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogView)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGVIEW_H__DD788024_A651_11D3_8382_0080C86BAA81__INCLUDED_)
