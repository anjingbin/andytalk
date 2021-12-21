// MsgPageB.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "MsgPageB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgPageB property page

IMPLEMENT_DYNCREATE(CMsgPageB, CPropertyPage)

CMsgPageB::CMsgPageB() : CPropertyPage(CMsgPageB::IDD)
{
	//{{AFX_DATA_INIT(CMsgPageB)
	m_msg = _T("");
	//}}AFX_DATA_INIT
}

CMsgPageB::~CMsgPageB()
{
}

void CMsgPageB::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgPageB)
	DDX_Text(pDX, IDC_EDIT, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgPageB, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgPageB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgPageB message handlers


