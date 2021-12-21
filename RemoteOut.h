#if !defined(AFX_REMOTEOUT_H__FE26A885_9DEE_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_REMOTEOUT_H__FE26A885_9DEE_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemoteOut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRemoteOut window

class CRemoteOut : public CEdit
{
// Construction
public:
	CRemoteOut();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteOut)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF m_clrBack;
	HBRUSH m_hbrBack;
	COLORREF m_clrText;
	virtual ~CRemoteOut();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRemoteOut)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMOTEOUT_H__FE26A885_9DEE_11D3_8382_0080C86BAA81__INCLUDED_)
