// InputCombo.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "ClientWnd.h"
#include "InputCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputCombo

CInputCombo::CInputCombo()
{
}

CInputCombo::~CInputCombo()
{
}


BEGIN_MESSAGE_MAP(CInputCombo, CComboBox)
	//{{AFX_MSG_MAP(CInputCombo)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputCombo message handlers

BOOL CInputCombo::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message==WM_KEYDOWN){
		if(pMsg->wParam==VK_RETURN){
			CEdit *pEdit=(CEdit*)GetWindow(GW_CHILD);
			CString str;
			pEdit->GetWindowText(str);
			pEdit->SetSel(0,-1,true);
			InsertString(-1,(LPCTSTR)str);
			((CClientWnd*)GetParent())->OnInput(str);
			return true;
		}
		if(pMsg->wParam=='\t'){
			((CClientWnd*)GetParent())->GetDlgItem(103)->SetFocus();
			return true;
		}

	}	
	return CComboBox::PreTranslateMessage(pMsg);
}



int CInputCombo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
	CEdit *pEdit=(CEdit*)GetWindow(GW_CHILD);
	if(pEdit){
		pEdit->SetFont(CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT)));
		pEdit->MoveWindow(0,0,0,20);
	}

	return 0;
}

