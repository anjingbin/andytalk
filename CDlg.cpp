// CDlg.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "CDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCDlg dialog


CCDlg::CCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCDlg)
	m_sHost = _T("");
	//}}AFX_DATA_INIT
}


void CCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDlg)
	DDX_Text(pDX, IDC_HOST, m_sHost);
	DDV_MaxChars(pDX, m_sHost, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCDlg, CDialog)
	//{{AFX_MSG_MAP(CCDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDlg message handlers

void CCDlg::OnOK() 
{
	UpdateData();
	m_sHost.Remove(0x20);
	if(!m_sHost.IsEmpty())
		CDialog::OnOK();
}
