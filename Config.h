// Config.h: interface for the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIG_H__08562D48_A25D_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_CONFIG_H__08562D48_A25D_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfig  
{
public:
	CString m_sIP;
	BOOL bVScroll;
	BOOL bHScroll;
	COLORREF clrEditText;
	COLORREF clrEditBack;
	LOGFONT lfEdit;
	BOOL bNeedConfirm;
	BOOL bIPAB;
	BOOL bBeep;
	int nMaxConnections;

	CString sWelMsg;
	CString sAbsentMsg;
	CString sBusyMsg;
	BOOL bWelMsg;
	BOOL bAbsentMsg;
	BOOL bBusyMsg;
	int nTimeOut1;
	int nTimeOut2;
	CString sMyName;


	CConfig();
	virtual ~CConfig();

};

#endif // !defined(AFX_CONFIG_H__08562D48_A25D_11D3_8382_0080C86BAA81__INCLUDED_)

