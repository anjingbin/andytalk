#if !defined(AFX_CFGGEN_H__65DF98E1_A5C1_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_CFGGEN_H__65DF98E1_A5C1_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CfgGen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCfgGen dialog 

class CCfgGen : public CPropertyPage
{
	DECLARE_DYNCREATE(CCfgGen)

// Construction
public:
	CCfgGen();
	~CCfgGen();

// Dialog Data
	//{{AFX_DATA(CCfgGen)
	enum { IDD = IDD_CFG_GENERAL };
	CString	m_name;
	int		m_sb1;
	int		m_sb2;
	int		m_time2;
	int		m_time1;
	int		m_max;
	BOOL	m_startup;
	int		m_nConfirm;
	int		m_nIdle;
	int		m_nRetry;
	int		m_nRetryInterval;
	BOOL	m_beep;
	CString	m_Emote1;
	CString	m_Emote2;
	CString	m_Emote3;
	CString	m_EmoteEsc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCfgGen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCfgGen)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGGEN_H__65DF98E1_A5C1_11D3_8382_0080C86BAA81__INCLUDED_)
