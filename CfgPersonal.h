#if !defined(AFX_CFGPERSONAL_H__65DF98E4_A5C1_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_CFGPERSONAL_H__65DF98E4_A5C1_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CfgPersonal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCfgPersonal dialog

class CCfgPersonal : public CPropertyPage
{
	DECLARE_DYNCREATE(CCfgPersonal)

// Construction
public:
	CList<ABITEM *,ABITEM*> * AB;
	CCfgPersonal();
	~CCfgPersonal();

// Dialog Data
	//{{AFX_DATA(CCfgPersonal)
	enum { IDD = IDD_PERSONAL };
	CListBox	m_wndNameList;
	CString	m_wm;
	CString	m_am;
	BOOL	m_bAbsMsg;
	BOOL	m_bWelMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCfgPersonal)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCfgPersonal)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeNamelist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	POSITION m_Pos;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGPERSONAL_H__65DF98E4_A5C1_11D3_8382_0080C86BAA81__INCLUDED_)
