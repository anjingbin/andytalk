#if !defined(AFX_MSGPAGEB_H__08562D51_A25D_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_MSGPAGEB_H__08562D51_A25D_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgPageB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgPageB dialog

class CMsgPageB : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgPageB)

// Construction
public:
	CMsgPageB();
	~CMsgPageB();

// Dialog Data
	//{{AFX_DATA(CMsgPageB)
	enum { IDD = IDD_CFG_MSG_3 };
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgPageB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgPageB)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGPAGEB_H__08562D51_A25D_11D3_8382_0080C86BAA81__INCLUDED_)
