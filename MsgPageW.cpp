// MsgPageW.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "MsgPageW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgPageW property page

IMPLEMENT_DYNCREATE(CMsgPageW, CPropertyPage)

CMsgPageW::CMsgPageW() : CPropertyPage(CMsgPageW::IDD)
{
	//{{AFX_DATA_INIT(CMsgPageW)
	m_msg = _T("");
	//}}AFX_DATA_INIT
}

CMsgPageW::~CMsgPageW()
{
}

void CMsgPageW::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgPageW)
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Control(pDX, IDC_EDIT, m_wndEdit);
	DDX_Text(pDX, IDC_EDIT, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgPageW, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgPageW)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgPageW message handlers



void CMsgPageW::OnSelchangeList() 
{
	m_wndEdit.GetWindowText	
}
