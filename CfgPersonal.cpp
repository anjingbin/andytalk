// CfgPersonal.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "ABItem.h"
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
	m_bwm = FALSE;
	m_blw = FALSE;
	m_lw = _T("");
	m_wm = _T("");
	//}}AFX_DATA_INIT
	AB=NULL;
}

CCfgPersonal::~CCfgPersonal()
{
}

void CCfgPersonal::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgPersonal)
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Check(pDX, IDC_CHECK1, m_bwm);
	DDX_Check(pDX, IDC_CHECK2, m_blw);
	DDX_Text(pDX, IDC_LVWORD, m_lw);
	DDV_MaxChars(pDX, m_lw, 10240);
	DDX_Text(pDX, IDC_WELMSG, m_wm);
	DDV_MaxChars(pDX, m_wm, 10240);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCfgPersonal, CPropertyPage)
	//{{AFX_MSG_MAP(CCfgPersonal)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST1, OnItemchangingList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgPersonal message handlers

BOOL CCfgPersonal::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	m_List.InsertColumn(0,"Name",LVCFMT_LEFT,80,0);
	
	if(AB&&!AB->IsEmpty()){
		POSITION pos=AB->GetHeadPosition(),pos2;
		int i=0,ret=0;
		while(pos){	
			pos2=pos;
			CABItem* pItem=(CABItem*)AB->GetNext(pos);
			m_List.InsertItem(LVIF_TEXT|LVIF_PARAM,i++,pItem->Name,0,0,0,(LONG)pos2);
		}
	}	
	return TRUE;  
}

void CCfgPersonal::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	POSITION pos;
	if(!(pos=m_List.GetFirstSelectedItemPosition())){
		m_blw=false;
		m_bwm=false;
		m_lw="";
		m_wm="";
		UpdateData(false);
		return;
	}
	int i=m_List.GetNextSelectedItem(pos);
	if((pNMListView->uChanged&LVIF_STATE)
		&&!(pNMListView->uChanged&~LVIF_STATE)
		&&(pNMListView->iItem==i)){
			CABItem * abi=(CABItem*)AB->GetAt((POSITION)m_List.GetItemData(i));
			if(!abi)
				return;
			m_blw=abi->bLvWord;
			m_bwm=abi->bWelMsg;
			m_lw=abi->LvWord;
			m_wm=abi->WelMsg;
			UpdateData(false);
	}
}

void CCfgPersonal::OnOK() 
{
	POSITION pos;
	if(pos=m_List.GetFirstSelectedItemPosition()){
		int i=m_List.GetNextSelectedItem(pos);
		CABItem * abi=(CABItem*)AB->GetAt((POSITION)m_List.GetItemData(i));
		if(!abi)
			return;
		UpdateData();
		abi->bLvWord=m_blw;
		abi->bWelMsg=m_bwm;
		abi->LvWord	=m_lw;
		abi->WelMsg	=m_wm; 
	}	
	CPropertyPage::OnOK();
}

void CCfgPersonal::OnItemchangingList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos;
	if(pos=m_List.GetFirstSelectedItemPosition()){
		int i=m_List.GetNextSelectedItem(pos);
		CABItem * abi=(CABItem*)AB->GetAt((POSITION)m_List.GetItemData(i));
		if(!abi)
			return;
		UpdateData();
		abi->bLvWord=m_blw;
		abi->bWelMsg=m_bwm;
		abi->LvWord	=m_lw;
		abi->WelMsg	=m_wm; 
	}
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
