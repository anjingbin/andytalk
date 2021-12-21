// CfgGen.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "CfgGen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCfgGen property page

IMPLEMENT_DYNCREATE(CCfgGen, CPropertyPage)

CCfgGen::CCfgGen() : CPropertyPage(CCfgGen::IDD)
{
	//{{AFX_DATA_INIT(CCfgGen)
	m_name = _T("");
	m_sb1 = 0;
	m_sb2 = 0;
	m_time2 = 0;
	m_time1 = 0;
	m_max = 0;
	m_startup = FALSE;
	m_nConfirm = 0;
	m_nIdle = 0;
	m_nRetry = 0;
	m_nRetryInterval = 0;
	m_beep = FALSE;
	m_Emote1 = _T("");
	m_Emote2 = _T("");
	m_Emote3 = _T("");
	m_EmoteEsc = _T("");
	//}}AFX_DATA_INIT
}

CCfgGen::~CCfgGen()
{
}

void CCfgGen::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgGen)
	DDX_Text(pDX, IDC_MYNAME, m_name);
	DDV_MaxChars(pDX, m_name, 16);
	DDX_Text(pDX, IDC_TIME2, m_time2);
	DDV_MinMaxInt(pDX, m_time2, 1, 60);
	DDX_Text(pDX, IDC_TIME1, m_time1);
	DDV_MinMaxInt(pDX, m_time1, 1, 3600);
	DDX_Text(pDX, IDC_MAXCONN, m_max);
	DDV_MinMaxInt(pDX, m_max, 1, 20);
	DDX_Check(pDX, IDC_STARTUP, m_startup);
	DDX_Text(pDX, IDC_RETRY, m_nRetry);
	DDV_MinMaxInt(pDX, m_nRetry, 1, 1000);
	DDX_Text(pDX, IDC_RETRYINTERVAL, m_nRetryInterval);
	DDV_MinMaxInt(pDX, m_nRetryInterval, 1, 10000);
	DDX_Check(pDX, IDC_BEEP, m_beep);
	DDX_Text(pDX, IDC_EMOTE1, m_Emote1);
	DDV_MaxChars(pDX, m_Emote1, 1);
	DDX_Text(pDX, IDC_EMOTE2, m_Emote2);
	DDV_MaxChars(pDX, m_Emote2, 1);
	DDX_Text(pDX, IDC_EMOTE3, m_Emote3);
	DDV_MaxChars(pDX, m_Emote3, 1);
	DDX_Text(pDX, IDC_EMOTEESC, m_EmoteEsc);
	DDV_MaxChars(pDX, m_EmoteEsc, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCfgGen, CPropertyPage)
	//{{AFX_MSG_MAP(CCfgGen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgGen message handlers



