// ABDlg.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
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
	m_Host = _T("");
	m_bSchedule = FALSE;
	m_tTime = 0;
	//}}AFX_DATA_INIT
	IP="";
}


void CABDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CABDlg)
	DDX_Control(pDX, IDC_TIME, m_wndTime);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 32);
	DDX_Text(pDX, IDC_HOST, m_Host);
	DDV_MaxChars(pDX, m_Host, 256);
	DDX_Check(pDX, IDC_SCHEDULE, m_bSchedule);
	DDX_DateTimeCtrl(pDX, IDC_TIME, m_tTime);
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
	ON_BN_CLICKED(IDC_SCHEDULE, OnSchedule)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_TIME, OnDatetimechangeTime)
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
	delete (ABITEM*)AB->GetAt(pos);
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
	ABITEM *abi;

	UpdateData();
/* Changed by pubb, allowing to update an entry in Addressbook, and not allowing null input */
	if(m_Name=="" || m_Host==""){
		AfxMessageBox("Null input not allowed!");
		return;
	}
	if(GetKeyState(VK_SHIFT)>=0 || m_List.GetSelectedCount()==0){	//insert save
		POSITION pos=AB->GetHeadPosition();
		while(pos){
			abi=(ABITEM*)AB->GetNext(pos);
			if(!abi->IP.Compare(m_Host) && !abi->Name.Compare(m_Name)){
				AfxMessageBox("Same item exists!");
				return;
			}
		}
	
		abi=(ABITEM*)new ABITEM;
		if(!abi){
			AfxMessageBox("Failed!");
			return;
		}
	
		abi->Name=m_Name;
		abi->IP=m_Host;
		pos=AB->AddTail(abi);
	
		int ret=m_List.InsertItem(LVIF_TEXT|LVIF_PARAM,m_List.GetItemCount(),m_Name,0,0,0,(LONG)pos);
		m_List.SetItemText(ret,1,m_Host);
	}else{	//shift-save, for update
		POSITION pos=m_List.GetFirstSelectedItemPosition();
		if(!pos)
			return;
		int i=m_List.GetNextSelectedItem(pos);
		
		m_List.SetItemText(i,0,m_Name);
		m_List.SetItemText(i,1,m_Host);

		abi=new ABITEM;
		abi->Name=m_Name;
		abi->IP=m_Host;
		pos=AB->FindIndex(i);
		AB->SetAt(pos,abi);
	}
/* end of change */
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
	m_List.InsertColumn(1,"Host",LVCFMT_LEFT,100,1);
	m_List.DeleteAllItems();
	if(AB&&!AB->IsEmpty()){
		POSITION pos=AB->GetHeadPosition(),pos2;
		int i=0,ret=0;
		while(pos){	
			pos2=pos;
			ABITEM* pItem=(ABITEM*)AB->GetNext(pos);
			ret=m_List.InsertItem(LVIF_TEXT|LVIF_PARAM,i++,pItem->Name,0,0,0,(LONG)pos2);
			m_List.SetItemText(ret,1,pItem->IP);
		}
	}

	m_wndTime.SetFormat("' 'HH':'mm':'ss'    'yyy'-'MM'-'dd");
	m_wndTime.SetTime(&CTime::GetCurrentTime());
/* Added by pubb, for tips of update AB entry */
	if(m_wndTip.Create(this)){
		m_wndTip.AddTool(GetDlgItem(IDC_SAVE),"Shift: update entry");
		m_wndTip.Activate(true);
	}

	m_wndTime.EnableWindow(false);
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

			ABITEM * abi=(ABITEM*)AB->GetAt((POSITION)m_List.GetItemData(i));
			if(!abi)
				return;

			m_Name=abi->Name;
			m_Host=abi->IP;
			UpdateData(false);
	}
	
}

void CABDlg::OnClear() 
{
	m_Name="";
	m_Host="";
	UpdateData(false);
}

void CABDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnConnect();	
	*pResult = 0;
}

void CABDlg::OnSchedule() 
{
	UpdateData();
	m_wndTime.EnableWindow(m_bSchedule);
	m_wndTime.SetTime(&CTime::GetCurrentTime());
}

void CABDlg::OnDatetimechangeTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_wndTime.GetTime(m_tTime);	
	*pResult = 0;
}

BOOL CABDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message){
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE :
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN :
	case WM_MBUTTONDOWN :
	case WM_RBUTTONUP :
	case WM_MBUTTONUP :
		m_wndTip.RelayEvent(pMsg);
		break;
	default:
		break;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
