#if !defined(AFX_LISTENSOCK_H__6C840627_8BA6_11D3_8381_0080C86BAA81__INCLUDED_)
#define AFX_LISTENSOCK_H__6C840627_8BA6_11D3_8381_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListenSock command target

class CListenSock : public CAsyncSocket
{
// Attributes
public:
	CWnd* m_pWnd;

// Operations
public:
	CListenSock();
	CListenSock(CWnd * pWnd);
	virtual ~CListenSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSock)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCK_H__6C840627_8BA6_11D3_8381_0080C86BAA81__INCLUDED_)
