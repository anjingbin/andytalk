// CfgPersonal.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"

#include "CfgPersonal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCfgPersonal property page

IMPLEMENT_DYNCREATE(CCfgPersonal, CPropertyPage)

CCfgPersonal::CCfgPersonal() : CPropertyPage(CCfgPersonal::IDD)
{
	//{{AFX_DATA_INIT(CCfgPersonal)
	m_wm = _T("");
	m_am = _T("");
	m_bAbsMsg = FALSE;
	m_bWelMsg = FALSE;
	//}}AFX_DATA_INIT
	AB=NULL;
	m_Pos=0;
}

CCfgPersonal::~CCfgPersonal()
{
}

void CCfgPersonal::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgPersonal)
	DDX_Control(pDX, IDC_NAMELIST, m_wndNameList);
	DDX_Text(pDX, IDC_WELMSG, m_wm);
	DDV_MaxChars(pDX, m_wm, 1024);
	DDX_Text(pDX, IDC_ABSMSG, m_am);
	DDV_MaxChars(pDX, m_am, 1024);
	DDX_Check(pDX, IDC_BABSMSG, m_bAbsMsg);
	DDX_Check(pDX, IDC_BWELMSG, m_bWelMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCfgPersonal, CPropertyPage)
	//{{AFX_MSG_MAP(CCfgPersonal)
	ON_LBN_SELCHANGE(IDC_NAMELIST, OnSelchangeNamelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgPersonal message handlers

BOOL CCfgPersonal::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	if(AB && !AB->IsEmpty()){
		POSITION pos=AB->GetHeadPosition(),pos2;
		int i=0,ret=0;
		while(pos){	
			pos2=pos;
			ABITEM* pItem=AB->GetNext(pos);
			m_wndNameList.SetItemData(m_wndNameList.AddString(pItem->Name),(DWORD)pos2);
		}
	}	
	m_wndNameList.SetCurSel(0);
	OnSelchangeNamelist();

	return TRUE;  
}

void CCfgPersonal::OnOK() 
{
	int CurSel=m_wndNameList.GetCurSel();
	if(CurSel!=LB_ERR){
		ABITEM * abi;
		if(m_Pos){
			abi=AB->GetAt((POSITION)m_wndNameList.GetItemData(CurSel));
			if(abi){
				UpdateData();
				abi->bLvWord=m_bAbsMsg;
				abi->bWelMsg=m_bWelMsg;
				abi->LvWord	=m_am;
				abi->WelMsg	=m_wm; 
			}
		}
	}
	CPropertyPage::OnOK();
}

void CCfgPersonal::OnSelchangeNamelist() 
{
	int CurSel=m_wndNameList.GetCurSel();
	if(CurSel==LB_ERR)
		return;

	ABITEM * abi;
	if(m_Pos){
		abi=AB->GetAt(m_Pos);
		if(abi){
			UpdateData();
			abi->bLvWord=m_bAbsMsg;
			abi->bWelMsg=m_bWelMsg;
			abi->LvWord	=m_am;
			abi->WelMsg	=m_wm; 
		}
	}
	m_Pos=(POSITION)m_wndNameList.GetItemData(CurSel);	
	
	
	abi=AB->GetAt(m_Pos);
	if(abi){
		m_bAbsMsg=abi->bLvWord;
		m_bWelMsg=abi->bWelMsg;
		m_am=abi->LvWord;
		m_wm=abi->WelMsg;
		UpdateData(false);
	}
}
