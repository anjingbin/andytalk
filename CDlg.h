#if !defined(AFX_CDLG_H__E9830744_9E5A_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_CDLG_H__E9830744_9E5A_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCDlg dialog

class CCDlg : public CDialog
{
// Construction
public:
	CCDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCDlg)
	enum { IDD = IDD_CONNECT };
	CString	m_sHost;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDLG_H__E9830744_9E5A_11D3_8382_0080C86BAA81__INCLUDED_)
