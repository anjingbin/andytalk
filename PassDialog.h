#if !defined(AFX_PASSDIALOG_H__70283931_CF79_4D66_A109_10C2128FE1DA__INCLUDED_)
#define AFX_PASSDIALOG_H__70283931_CF79_4D66_A109_10C2128FE1DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPassDialog dialog

class CPassDialog : public CDialog
{
// Construction
public:
	CPassDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassDialog)
	enum { IDD = IDD_PASSWD };
	CString	m_old;
	CString	m_new;
	CString	m_confirm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSDIALOG_H__70283931_CF79_4D66_A109_10C2128FE1DA__INCLUDED_)
