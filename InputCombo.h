#if !defined(AFX_INPUTCOMBO_H__6C840626_8BA6_11D3_8381_0080C86BAA81__INCLUDED_)
#define AFX_INPUTCOMBO_H__6C840626_8BA6_11D3_8381_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputCombo window

class CInputCombo : public CComboBox
{
// Construction
public:
	CInputCombo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputCombo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInputCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInputCombo)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTCOMBO_H__6C840626_8BA6_11D3_8381_0080C86BAA81__INCLUDED_)
