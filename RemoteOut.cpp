// RemoteOut.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "ClientWnd.h"
#include "RemoteOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRemoteOut

CRemoteOut::CRemoteOut()
{
	m_clrText=RGB(0,0,0);
}

CRemoteOut::~CRemoteOut()
{
}


BEGIN_MESSAGE_MAP(CRemoteOut, CEdit)
	//{{AFX_MSG_MAP(CRemoteOut)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRemoteOut message handlers

HBRUSH CRemoteOut::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_clrText);
	pDC->SetBkColor(m_clrBack);	
	return m_hbrBack;
}

int CRemoteOut::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;


	//	SetFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
	return 0;
}

BOOL CRemoteOut::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message==WM_KEYDOWN)
		if(pMsg->wParam=='\t'){
			((CClientWnd*)GetParent())->GetDlgItem(102)->SetFocus();
			return true;
		}	
	return CEdit::PreTranslateMessage(pMsg);
}
