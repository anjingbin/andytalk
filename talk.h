// talk.h : main header file for the TALK application
//

#if !defined(AFX_TALK_H__EE0A508F_8B0F_11D3_8381_0080C86BAA81__INCLUDED_)
#define AFX_TALK_H__EE0A508F_8B0F_11D3_8381_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "global.h"
#include <Imm.h>

/////////////////////////////////////////////////////////////////////////////
// CTalkApp:
// See talk.cpp for the implementation of this class
//

class CTalkApp : public CWinApp
{ 
public:
	CTalkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL SaveAllModified();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CTalkApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALK_H__EE0A508F_8B0F_11D3_8381_0080C86BAA81__INCLUDED_)
