// MsgPageA.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "MsgPageA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgPageA property page

IMPLEMENT_DYNCREATE(CMsgPageA, CPropertyPage)

CMsgPageA::CMsgPageA() : CPropertyPage(CMsgPageA::IDD)
{
	//{{AFX_DATA_INIT(CMsgPageA)
	m_msg = _T("");
	//}}AFX_DATA_INIT
}

CMsgPageA::~CMsgPageA()
{
}

void CMsgPageA::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgPageA)
	DDX_Text(pDX, IDC_EDIT, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgPageA, CPropertyPage)
	//{{AFX_MSG_MAP(CMsgPageA)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgPageA message handlers


