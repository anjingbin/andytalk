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
	m_nReturn=-1;
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
	SetWindowText(m_sName);
	if(m_bCallIn){
		m_text.Format("   %s from %s want to talk with you....",m_sName,m_sIP);
	}else{
		m_text.Format("   Connected to %s at %s!",m_sName,m_sIP);
	}


	CDialog::OnInitDialog();
	if(!SetTimer(TIMERCONFIRM,200,NULL))
		return false;

	CString str;
	str.Format("%d",m_nTimer);
	GetDlgItem(IDC_TIME)->SetWindowText(str);	
//	MessageBeep(-1);
	::PlaySound((const char *)IDR_NOTIFY,AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC);	

	m_nTimer*=5;

	SetActiveWindow();
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
//	MessageBeep(-1);
	if(m_nTimer%8==0)
		::PlaySound((const char *)IDR_NOTIFY,AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC);	

	if(m_nTimer<=0){
		m_nReturn=2;
		OnCancel();
	}
}

void CConfirm::OnOK() 
{
	KillTimer(TIMERCONFIRM);
	m_nReturn=1;
	DestroyWindow();
}

void CConfirm::OnCancel() 
{
	KillTimer(TIMERCONFIRM);
	if(m_nReturn!=2)
		m_nReturn=0;
	DestroyWindow();
}

void CConfirm::PostNcDestroy() 
{
	//5.7
	m_pWnd->SendMessage(WM_CONFIRM_OVER,(WPARAM)m_nSockID,(LPARAM)m_nReturn);
	delete this;
}

BOOL CConfirm::Create(CWnd * pCW)
{
	CWnd* pWnd=GetDesktopWindow();
	if(!pWnd)
		return false;

	if(!pCW)
		return false;
	m_pWnd=pCW;

	return CDialog::Create(IDD_CONFIRM, pWnd);
}

