// LogView.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "LogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogView dialog


CLogView::CLogView(CWnd* pParent /*=NULL*/)
	: CDialog(CLogView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogView)
	m_remote = _T("");
	m_local = _T("");
	//}}AFX_DATA_INIT
}


void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogView)
	DDX_Text(pDX, IDC_REMOTE, m_remote);
	DDX_Text(pDX, IDC_LOCAL, m_local);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogView, CDialog)
	//{{AFX_MSG_MAP(CLogView)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogView message handlers

HBRUSH CLogView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	int id=pWnd->GetDlgCtrlID();
	if(id==IDC_REMOTE||id==IDC_LOCAL||id==IDC_RSTATIC){
		pDC->SetBkColor(RGB(255,255,255));
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
	return hbr;
}

BOOL CLogView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(title);	
	return TRUE;  
}
