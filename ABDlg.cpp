// ABDlg.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "ABItem.h"
#include "ABDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CABDlg dialog

CABDlg::CABDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CABDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CABDlg)
	m_Name = _T("");
	//}}AFX_DATA_INIT
	IP="";
}


void CABDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CABDlg)
	DDX_Control(pDX, IDC_IP, m_IP);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CABDlg, CDialog)
	//{{AFX_MSG_MAP(CABDlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CABDlg message handlers

void CABDlg::OnDelete() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if(!pos)
		return;
	int i=m_List.GetNextSelectedItem(pos),k;

	pos=(POSITION)m_List.GetItemData(i);
	delete (CABItem*)AB->GetAt(pos);
	AB->RemoveAt(pos);
	m_List.DeleteItem(i);
	if(k=m_List.GetItemCount()){
		if(k==i)
			m_List.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED);
		else 
			m_List.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
	}

}

void CABDlg::OnSave() 
{
	int i;
	CABItem *abi;

	UpdateData();

	BYTE a,b,c,d;
	CString ip;

	m_IP.GetAddress(a,b,c,d);
	ip.Format("%d.%d.%d.%d",a,b,c,d);

	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if(pos){
		i=m_List.GetNextSelectedItem(pos);
		if(!m_List.GetItemText(i,1).Compare(ip)){
			m_List.SetItemText(i,0,m_Name);
			abi=(CABItem*)AB->GetAt((POSITION)m_List.GetItemData(i));

			abi->Name=m_Name;
			abi->IP=ip;
			return;
		}
	}

	pos=AB->GetHeadPosition();
	while(pos){
		abi=(CABItem*)AB->GetNext(pos);
		if(!abi->IP.Compare(ip)){
			AfxMessageBox("Same address exists!");
			return;
		}
	}
	
	abi=(CABItem*)new CABItem;
	if(!abi){
		AfxMessageBox("Failed!");
		return;
	}

	abi->Name=m_Name;
	abi->IP=ip;
	pos=AB->AddTail(abi);

	int ret=m_List.InsertItem(LVIF_TEXT|LVIF_PARAM,m_List.GetItemCount(),m_Name,0,0,0,(LONG)pos);
	m_List.SetItemText(ret,1,ip);
}

void CABDlg::OnConnect() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if(!pos){
		AfxMessageBox("No address selected!");
		return;
	}
	int i=m_List.GetNextSelectedItem(pos);
	IP=m_List.GetItemText(i,1);
	name=m_List.GetItemText(i,0);
	EndDialog(ID_CONNECT);
}



BOOL CABDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_List.InsertColumn(0,"Name",LVCFMT_LEFT,80,0);
	m_List.InsertColumn(1,"IP",LVCFMT_LEFT,100,1);
	m_List.DeleteAllItems();
	if(AB&&!AB->IsEmpty()){
		POSITION pos=AB->GetHeadPosition(),pos2;
		int i=0,ret=0;
		while(pos){	
			pos2=pos;
			CABItem* pItem=(CABItem*)AB->GetNext(pos);
			ret=m_List.InsertItem(LVIF_TEXT|LVIF_PARAM,i++,pItem->Name,0,0,0,(LONG)pos2);
			m_List.SetItemText(ret,1,pItem->IP);
		}
	}
	return TRUE;  
}
void CABDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	POSITION pos;
	if(!(pos=m_List.GetFirstSelectedItemPosition()))
		return;
	int i=m_List.GetNextSelectedItem(pos);

	if((pNMListView->uChanged&LVIF_STATE)
		&&!(pNMListView->uChanged&~LVIF_STATE)
		&&(pNMListView->iItem==i)){

			CABItem * abi=(CABItem*)AB->GetAt((POSITION)m_List.GetItemData(i));
			if(!abi)
				return;

			CString name;
			BYTE a,b,c,d;

			m_Name=abi->Name;
			sscanf(abi->IP,"%d.%d.%d.%d",&a,&b,&c,&d);
			m_IP.SetAddress(a,b,c,d);
			UpdateData(false);
	}
	
}

void CABDlg::OnClear() 
{
	m_Name="";
	UpdateData(false);
	m_IP.ClearAddress();
}

void CABDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnConnect();	
	*pResult = 0;
}
