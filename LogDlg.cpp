// LogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "LogItem.h"
#include "ABItem.h"
#include "LogView.h"
#include "LogDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog


CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogDlg)
	DDX_Control(pDX, IDC_LOGLIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	//{{AFX_MSG_MAP(CLogDlg)
	ON_BN_CLICKED(ID_RECONN, OnReconn)
	ON_BN_CLICKED(ID_VIEW, OnView)
	ON_BN_CLICKED(ID_LOG_DEL, OnLogDel)
	ON_BN_CLICKED(ID_LOG_ADD, OnLogAdd)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_LOGLIST, OnDblclkLoglist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogDlg message handlers

void CLogDlg::OnReconn() 
{
	
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if(!pos){
		AfxMessageBox("No item selected!");
		return;
	}
	int i=m_List.GetNextSelectedItem(pos);
	
	pos=(POSITION)m_List.GetItemData(i);
	
	CLogItem * li=(CLogItem*)Log.GetAt(pos);

	IP=m_List.GetItemText(i,1);
	name=m_List.GetItemText(i,0);
	EndDialog(ID_RECONN);
}

BOOL CLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int count;
	CFile logf;
	if(!logf.Open(m_sLogFile,
		CFile::modeCreate|
		CFile::modeNoTruncate|
		CFile::modeRead)){
		AfxMessageBox("Failed to open logfile!");
	}else{
		if(logf.GetLength()){
			CArchive logar(&logf,CArchive::load);
			logar>>count;
			while(count--){
				CLogItem *li=(CLogItem*)new CLogItem;
				ASSERT(li);
				logar>>li->bNew;
				logar>>li->bOut;
				logar>>li->sIP;
				logar>>li->sLocal>>li->sRemote;
				logar>>li->sTalkName;
				logar>>li->tBeginTime;
				logar>>li->tEndTime;
				Log.AddTail(li);
			}
			logar.Close();
		}
		logf.Close();
		CFile::Remove(m_sLogFile);
	}
	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_List.InsertColumn(0,"Name",LVCFMT_LEFT,80,0);
	m_List.InsertColumn(1,"IP address",LVCFMT_LEFT,100,1);
	m_List.InsertColumn(2,"Begin Time",LVCFMT_LEFT,80,2);
	m_List.InsertColumn(3,"End Time",LVCFMT_LEFT,200,3);
	CImageList il;
	il.Create(16,16,ILC_MASK,3,6);
	il.SetBkColor(CLR_NONE);
	il.Add(AfxGetApp()->LoadIcon (IDI_IN));
	il.Add(AfxGetApp()->LoadIcon (IDI_OUT));
	il.Add(AfxGetApp()->LoadIcon (IDI_NEW));
	m_List.SetImageList(&il,LVSIL_SMALL);
	il.Detach();

	if(!Log.IsEmpty()){
		POSITION pos=Log.GetHeadPosition(),pos2;
		int i=0;
		while(pos){	
			pos2=pos;
			CLogItem* pItem=(CLogItem*)Log.GetNext(pos);
			int img;
			if(pItem->bNew)
				img=2;
			else{
				if(pItem->bOut)
					img=1;
				else
					img=0;
			}
			pItem->m_nParam=i;
			m_List.InsertItem(LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE,i,pItem->sTalkName,0,0,img,(LONG)pos2);
			m_List.SetItemText(i,1,pItem->sIP);
			m_List.SetItemText(i,2,pItem->tBeginTime.Format("%H:%M:%S"));
			m_List.SetItemText(i,3,pItem->tEndTime.Format("%H:%M:%S    %a,%b %d"));
			i++;
		}
	}
	return TRUE;  
}


void CLogDlg::OnView() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if(!pos){
		AfxMessageBox("No item selected!");
		return;
	}
	int i=m_List.GetNextSelectedItem(pos);
	pos=(POSITION)m_List.GetItemData(i);
	CLogItem * li=(CLogItem*)Log.GetAt(pos);
	if(!li)
		return;
	
	m_List.SetItem(i,0,LVIF_IMAGE,NULL,li->bOut?1:0,0,0,0);
	li->bNew=false;	
	CLogView lv;
	lv.m_local=li->sLocal;
	lv.m_remote=li->sRemote;
	lv.title.Format("%s on %s %s--%s",
			li->sTalkName,
			li->sIP,
			li->tBeginTime.Format("%H:%M:%S"),
			li->tEndTime.Format("%H:%M:%S %a,%b %d"));
	lv.DoModal();
}

void CLogDlg::OnLogDel() 
{
	POSITION pos;
	if(GetKeyState(VK_SHIFT)<0){
		int count=m_List.GetItemCount();
		if(!count)
			return;
		int k=0;
		for(int i=0;i<count;i++){
			pos=(POSITION)m_List.GetItemData(k);
			CLogItem* pItem=(CLogItem*)Log.GetAt(pos);
			if(pItem->bNew){
				k++;
			}else{
				delete pItem;
				Log.RemoveAt(pos);
				m_List.DeleteItem(k);
			}
		}
	}else{
		pos=m_List.GetFirstSelectedItemPosition();
		if(!pos){
			AfxMessageBox("No item selected!");
			return;
		}
		int i=m_List.GetNextSelectedItem(pos),k;
		pos=(POSITION)m_List.GetItemData(i);
		delete (CLogItem*)Log.GetAt(pos);
		Log.RemoveAt(pos);
		m_List.DeleteItem(i);
		if(k=m_List.GetItemCount()){
			if(k==i)
				m_List.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED);
			else 
				m_List.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
		}
	}
}

void CLogDlg::OnLogAdd() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	if(!pos){
		AfxMessageBox("No item selected!");
		return;
	}
	int i=m_List.GetNextSelectedItem(pos);
	CString ip=m_List.GetItemText(i,1);

	CABItem * abi;
	pos=AB->GetHeadPosition();
	while(pos){
		abi=(CABItem*)AB->GetNext(pos);
		if(!abi->IP.Compare(ip)){
			AfxMessageBox("Same address exists!");
			return;
		}
	}
	abi=(CABItem*) new CABItem;
	if(!abi){
		AfxMessageBox("Failed!");
		return;
	}
	abi->IP=ip;
	abi->Name=m_List.GetItemText(i,0);
	AB->AddTail(abi);
}

void CLogDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	int count;
	CFile logf;
	if(!logf.Open(m_sLogFile,
		CFile::modeCreate|
		CFile::modeNoTruncate|
		CFile::modeRead)){
		AfxMessageBox("Failed to save logfile!");
	}else{
		if(logf.GetLength()){
			CArchive logar(&logf,CArchive::load);
			logar>>count;
			while(count--){
				CLogItem *li=(CLogItem*)new CLogItem;
				ASSERT(li);
				logar>>li->bNew;
				logar>>li->bOut;
				logar>>li->sIP;
				logar>>li->sLocal>>li->sRemote;
				logar>>li->sTalkName;
				logar>>li->tBeginTime;
				logar>>li->tEndTime;
				Log.AddTail(li);
			}
			logar.Close();
		}
		logf.Close();
	}

	if(logf.Open(m_sLogFile,CFile::modeCreate|CFile::modeReadWrite)){
		CArchive logar(&logf,CArchive::store);
		logar<<Log.GetCount();
		
		POSITION	pos=Log.GetHeadPosition();
		int New=0;
		while(pos){
			CLogItem* li=(CLogItem*)Log.GetNext(pos);
			if(li->bNew)
				New++;
			logar<<li->bNew;
			logar<<li->bOut;
			logar<<li->sIP;
			logar<<li->sLocal<<li->sRemote;
			logar<<li->sTalkName;
			logar<<li->tBeginTime;
			logar<<li->tEndTime;
			delete li;
		}

		CMainFrame * pMainWnd=(CMainFrame*)AfxGetMainWnd();
		if(pMainWnd){
			if(pMainWnd->m_wndClient.m_bWantTalk)
				pMainWnd->SetTrayIcon(New?IDI_ICON3:IDI_ICON4);
			else
				pMainWnd->SetTrayIcon(New?IDI_ICON2:IDI_ICON1);
		}
	}
	Log.RemoveAll();

}

void CLogDlg::OnDblclkLoglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnView();	
	*pResult = 0;
}
