// InplaceEdit.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "ClientWnd.h"
#include "LocalOut.h"
#include "InplaceEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInplaceEdit

CInplaceEdit::CInplaceEdit()
{
}

CInplaceEdit::~CInplaceEdit()
{
}


BEGIN_MESSAGE_MAP(CInplaceEdit, CEdit)
	//{{AFX_MSG_MAP(CInplaceEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_CREATE()
	ON_WM_NCDESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInplaceEdit message handlers

void CInplaceEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	DestroyWindow();
}

void CInplaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CWnd* pWnd;
	if( nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if(nChar==VK_RETURN){
			CString str;
			GetWindowText(str);

			pWnd=GetParent();
			if(pWnd){
				((CLocalOut*)pWnd)->m_sInplace[m_nType]=str;
				pWnd=pWnd->GetParent();
			}
			if(pWnd)
				((CClientWnd*)pWnd)->OnInput(str,m_nType);
		}
		pWnd=GetParent();
		if(pWnd)
			pWnd=pWnd->GetParent();
		if(pWnd)
			pWnd->SetFocus();
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
	
	pWnd=GetParent();
	if(!pWnd)
		return;
	//make the inplace edit window fit to it's  content and parent window
	CString str;
	GetWindowText( str );
	CWindowDC dc(this);
	CFont *pFont = GetParent()->GetFont();
	CFont *pFontDC = dc.SelectObject( pFont );
	CSize size = dc.GetTextExtent( str );
	dc.SelectObject( pFontDC );
	size.cx += 5;
	if(size.cx<100)
		size.cx=100;

	CRect rect,parentrect;
	GetClientRect(&rect);
	pWnd->GetClientRect( &parentrect );

	ClientToScreen( &rect );
	pWnd->ScreenToClient( &rect );
	
	rect.right=rect.left+size.cx;
	if(rect.right>parentrect.right){
		rect.right=parentrect.right;
		rect.left=rect.right-size.cx;
	}
	if(rect.left<parentrect.left)
		rect.left=parentrect.left;

	MoveWindow( &rect );
}

int CInplaceEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	CFont font;
	if(font.CreatePointFont(90,"ËÎÌו"))
		SetFont(&font);
	font.Detach();
	SetWindowText("");
	SetFocus();
	SetCapture();
	return 0;
}

void CInplaceEdit::OnNcDestroy() 
{
	CEdit::OnNcDestroy();
	delete this;
}

BOOL CInplaceEdit::PreTranslateMessage(MSG* pMsg) 
{

	return CEdit::PreTranslateMessage(pMsg);

}

void CInplaceEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEdit::OnLButtonDown(nFlags, point);

	CRect rect;
	GetWindowRect(&rect);
	if(!rect.PtInRect(point))
		DestroyWindow();
}

void CInplaceEdit::OnMButtonDown(UINT nFlags, CPoint point) 
{
	CEdit::OnMButtonDown(nFlags, point);
	CRect rect;
	GetClientRect(&rect);
	if(!rect.PtInRect(point))
		DestroyWindow();
}

void CInplaceEdit::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CEdit::OnRButtonDown(nFlags, point);
	CRect rect;
	GetWindowRect(&rect);
	if(!rect.PtInRect(point))
		DestroyWindow();
}

BOOL CInplaceEdit::DestroyWindow() 
{
	ReleaseCapture();
	CWnd* pWnd=GetParent();
	if(pWnd)
		pWnd=pWnd->GetParent();
	if(pWnd)
		pWnd->SetFocus();
	return CEdit::DestroyWindow();
}
