#if !defined(AFX_INPLACEEDIT_H__148252A1_B861_11D3_81F2_0080C86BAA81__INCLUDED_)
#define AFX_INPLACEEDIT_H__148252A1_B861_11D3_81F2_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InplaceEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInplaceEdit window

class CInplaceEdit : public CEdit
{
// Construction
public:
	CInplaceEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInplaceEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nType;
	virtual ~CInplaceEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInplaceEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACEEDIT_H__148252A1_B861_11D3_81F2_0080C86BAA81__INCLUDED_)
