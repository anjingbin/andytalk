// Confirm.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "Confirm.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfirm dialog


CConfirm::CConfirm(CWnd* pParent /*=NULL*/)
	: CDialog(CConfirm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfirm)
	m_text = _T("");
	//}}AFX_DATA_INIT
}

void CConfirm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfirm)
	DDX_Text(pDX, IDC_TEXT, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfirm, CDialog)
	//{{AFX_MSG_MAP(CConfirm)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfirm message handlers

BOOL CConfirm::OnInitDialog() 
{
	m_text.Format("   %s from %s want to talk with you....",
		m_sName,
		m_sIP);

	CDialog::OnInitDialog();
	if(!SetTimer(TIMERCONFIRM,200,NULL))
		return false;

	CString str;
	str.Format("%d",m_nTimer);
	GetDlgItem(IDC_TIME)->SetWindowText(str);	
	MessageBeep(-1);
	::PlaySound((const char *)IDR_NOTIFY,AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC);	

	m_nTimer*=5;
	return TRUE;  
}

void CConfirm::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent!=TIMERCONFIRM){
		CDialog::OnTimer(nIDEvent);
		return;
	}
	CString str;
	str.Format("%d",(--m_nTimer)/5);
	GetDlgItem(IDC_TIME)->SetWindowText(str);
	MessageBeep(-1);
	if(m_nTimer%5==0)
		::PlaySound((const char *)IDR_NOTIFY,AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC);	

	if(m_nTimer<=0)
		OnCancel();
}

void CConfirm::OnOK() 
{
	KillTimer(TIMERCONFIRM);
	CDialog::OnOK();
}

void CConfirm::OnCancel() 
{
	KillTimer(TIMERCONFIRM);
	CDialog::OnCancel();
}

