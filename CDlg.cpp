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
	m_sHostname = _T("");
	//}}AFX_DATA_INIT
}


void CCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDlg)
	DDX_Control(pDX, IDC_IPHOST, m_Host);
	DDX_CBString(pDX, IDC_IPHOST, m_sHostname);
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
	BYTE a,b,c,d;
	m_IP.GetAddress(a,b,c,d);
	strIP.Format("%d.%d.%d.%d",a,b,c,d);
	CDialog::OnOK();
}

BOOL CCDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	BYTE a,b,c,d;
	if(strIP.GetLength()){
		sscanf(strIP,"%d.%d.%d.%d",&a,&b,&c,&d);
		m_IP.SetAddress(a,b,c,d);		
	}
	return TRUE;  
}
