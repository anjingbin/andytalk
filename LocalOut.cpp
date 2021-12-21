// LocalOut.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "ClientWnd.h"
#include "InplaceEdit.h"
#include "LocalOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalOut

CLocalOut::CLocalOut()
{
	m_clrText=RGB(0,0,0);
}

CLocalOut::~CLocalOut()
{
}


BEGIN_MESSAGE_MAP(CLocalOut, CEdit)
	//{{AFX_MSG_MAP(CLocalOut)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalOut message handlers

HBRUSH CLocalOut::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_clrText);
	pDC->SetBkColor(m_clrBack);
	return m_hbrBack;
}

int CLocalOut::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CLocalOut::OnChange() 
{
	if(GetParent())
		((CClientWnd*)GetParent())->OnLocalChange();
}

BOOL CLocalOut::PreTranslateMessage(MSG* pMsg) 
{
	CWnd * pWnd;
	if (pMsg->message==WM_KEYDOWN)
		if(pMsg->wParam=='\t'){
			pWnd=GetParent();
			if(pWnd)
				pWnd=((CClientWnd*)pWnd)->GetDlgItem(103);
			if(pWnd)
				pWnd->SetFocus();
			return true;
		}

	return CEdit::PreTranslateMessage(pMsg);
}

void CLocalOut::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CClientWnd * pWnd=(CClientWnd*)GetParent();
	CConfig * m_pConfig;
	if(pWnd)
		m_pConfig=&pWnd->m_Config;

	char ch=(char)nChar;
	
	if((ch==m_pConfig->m_Emote1||ch==m_pConfig->m_Emote2||ch==m_pConfig->m_Emote3||ch==m_pConfig->m_EmoteEsc)&&!(GetStyle()&ES_READONLY)){
		CInplaceEdit *pEdit = new CInplaceEdit();
		CPoint pt=GetCaretPos();
		if(pEdit && pEdit->Create( WS_BORDER|WS_CHILD|ES_AUTOHSCROLL,
			CRect(pt,CSize(100,16)),
			this, 
			100)){

			if(ch==m_pConfig->m_Emote1)
				pEdit->m_nType=1;
			else if(ch==m_pConfig->m_Emote2)
				pEdit->m_nType=2;
			else if(ch==m_pConfig->m_Emote3)
				pEdit->m_nType=3;
			else if(ch==m_pConfig->m_EmoteEsc)
				pEdit->m_nType=0;

			DestroyCaret();
			pEdit->ShowWindow(SW_SHOW);
			pEdit->SetWindowText(m_sInplace[pEdit->m_nType]);
			pEdit->SetSel(0,-1,true);
			pEdit->SetFocus();
			return;
		}
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

