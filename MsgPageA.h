#if !defined(AFX_MSGPAGEA_H__08562D50_A25D_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_MSGPAGEA_H__08562D50_A25D_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgPageA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgPageA dialog

class CMsgPageA : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgPageA)

// Construction
public:
	CMsgPageA();
	~CMsgPageA();

// Dialog Data
	//{{AFX_DATA(CMsgPageA)
	enum { IDD = IDD_CFG_MSG_3 };
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgPageA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgPageA)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGPAGEA_H__08562D50_A25D_11D3_8382_0080C86BAA81__INCLUDED_)
