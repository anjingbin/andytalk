#if !defined(AFX_CPASSDLG_H__E480F98E_91C2_4D54_B881_5DA2176E443E__INCLUDED_)
#define AFX_CPASSDLG_H__E480F98E_91C2_4D54_B881_5DA2176E443E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CPassDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPassDlg dialog

class CPassDlg : public CDialog
{
// Construction
public:
	CPassDlg(CString sOldPass, CRijndael *pAES_engine, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassDlg)
	enum { IDD = IDD_EPASS };
	CString	m_Password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRijndael *pAES_engine;
	CString sOldPass;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPASSDLG_H__E480F98E_91C2_4D54_B881_5DA2176E443E__INCLUDED_)
