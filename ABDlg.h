#if !defined(AFX_ABDLG_H__9BDE6761_9D1E_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_ABDLG_H__9BDE6761_9D1E_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ABDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CABDlg dialog

class CABDlg : public CDialog
{
// Construction
public:
	CString name;
	CString IP;
	CList<ABITEM *,ABITEM*> * AB;
	CABDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CABDlg)
	enum { IDD = IDD_ADDRBOOK };
	CDateTimeCtrl	m_wndTime;
	CListCtrl	m_List;
	CString	m_Name;
	CString	m_Host;
	BOOL	m_bSchedule;
	CTime	m_tTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CABDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CABDlg)
	afx_msg void OnDelete();
	afx_msg void OnSave();
	afx_msg void OnConnect();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClear();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSchedule();
	afx_msg void OnDatetimechangeTime(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolTipCtrl m_wndTip;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABDLG_H__9BDE6761_9D1E_11D3_8382_0080C86BAA81__INCLUDED_)
