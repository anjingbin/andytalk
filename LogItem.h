#if !defined(AFX_LOGITEM_H__E9830748_9E5A_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_LOGITEM_H__E9830748_9E5A_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogItem.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CLogItem command target

class CLogItem : public CObject
{
public:
	CLogItem();           // protected constructor used by dynamic creation
	virtual ~CLogItem();

// Attributes
public:
	BOOL bNew;
	BOOL bOut;
	CString sIP;
	CString sTalkName;
	CTime tBeginTime;
	CTime tEndTime;
	CString sLocal,sRemote;

// Operations
public:
	int m_nParam;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogItem)
	public:
	//}}AFX_VIRTUAL

// Implementation
protected:


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGITEM_H__E9830748_9E5A_11D3_8382_0080C86BAA81__INCLUDED_)
