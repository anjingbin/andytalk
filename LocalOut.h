#if !defined(AFX_LOCALOUT_H__FE26A884_9DEE_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_LOCALOUT_H__FE26A884_9DEE_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalOut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocalOut window

class CLocalOut : public CEdit
{
// Construction
public:
	CLocalOut();

// Attributes
public:
	COLORREF m_clrText;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalOut)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_sInplace[4];
	COLORREF m_clrBack;
	HBRUSH m_hbrBack;
	virtual ~CLocalOut();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLocalOut)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChange();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALOUT_H__FE26A884_9DEE_11D3_8382_0080C86BAA81__INCLUDED_)
