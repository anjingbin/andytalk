

#if !defined(OUTLOOKBAR_H_INCLUDED)
#define OUTLOOKBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// OutlookBar class

class  COutlookBar : public CListBox
{
	DECLARE_DYNAMIC(COutlookBar)

// Construction
public:
	COutlookBar();

// Attributes
public:
	CImageList		m_ImageList;
 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookBar)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetString(int nIndex,CString str);
	int DeleteListString(int nIndex);
	void SetImage(int nIndex,int iImage);
	int Image[30];
	int InsertString( int nIndex, LPCTSTR lpszItem ,int iImage);
	virtual ~COutlookBar();

// Generated message map functions
protected:
	//{{AFX_MSG(COutlookBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(OUTLOOKBAR_H_INCLUDED)

