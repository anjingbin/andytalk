#if !defined(AFX_MSGPAGEW_H__08562D4F_A25D_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_MSGPAGEW_H__08562D4F_A25D_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgPageW.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgPageW dialog

class CMsgPageW : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgPageW)

// Construction
public:
	CMsgPageW();
	~CMsgPageW();

// Dialog Data
	//{{AFX_DATA(CMsgPageW)
	enum { IDD = IDD_CFG_MSG_1 };
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgPageW)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgPageW)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGPAGEW_H__08562D4F_A25D_11D3_8382_0080C86BAA81__INCLUDED_)
