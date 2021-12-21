// LogDlg.cpp : implementation file
// Last update:2000/5/7 10:50

#include "stdafx.h"
#include "talk.h"

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
	ON_NOTIFY(NM_RCLICK, IDC_LOGLIST, OnRclickLoglist)
	ON_COMMAND(ID_LOG_MER, OnLogMerge)
	ON_COMMAND(ID_LOG_ENC, OnLogEncrypt)
	ON_COMMAND(ID_LOG_MER_ENC, OnLogMerEnc)
	ON_COMMAND(ID_LOG_EXP, OnLogExp)
	ON_COMMAND(ID_LOG_MER2, OnLogMer2)
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
	
	LOGITEM * li=(LOGITEM*)Log.GetAt(pos);

	IP=m_List.GetItemText(i,1);
	name=m_List.GetItemText(i,0);
	EndDialog(ID_RECONN);
}

BOOL CLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_wndTip.Create(this)){
		m_wndTip.AddTool(GetDlgItem(ID_LOG_DEL),"Shift: delete all");
		m_wndTip.Activate(true);
	}


	int count;
	CFile logf;
	if(!logf.Open(m_sLogFile,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead)){
		AfxMessageBox("Failed to open logfile!");
	}else{
		if(logf.GetLength()){
			CArchive logar(&logf,CArchive::load);
			logar>>count;
			while(count--){
				LOGITEM *li=(LOGITEM*)new LOGITEM;
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
	m_List.InsertColumn(2,"Begin Time",LVCFMT_LEFT,100,2);
	m_List.InsertColumn(3,"End Time",LVCFMT_LEFT,100,3);

	CImageList il;
	il.Create(16,16,ILC_MASK,3,6);
	il.SetBkColor(CLR_NONE);
	il.Add(AfxGetApp()->LoadIcon (IDI_IN));
	il.Add(AfxGetApp()->LoadIcon (IDI_OUT));
	il.Add(AfxGetApp()->LoadIcon (IDI_NEW));
	m_List.SetImageList(&il,LVSIL_SMALL);
	il.Detach();

	int i=0;
	int nFirstNew=-1;
	if(!Log.IsEmpty()){
		POSITION pos=Log.GetHeadPosition(),pos2;
		while(pos){	
			pos2=pos;
			LOGITEM* pItem=(LOGITEM*)Log.GetNext(pos);
			int img;
			if(pItem->bNew){
				if(nFirstNew==-1)
					nFirstNew=i;
				img=2;
			}else{
				if(pItem->bOut)
					img=1;
				else
					img=0;
			}
			pItem->m_nParam=i;
			m_List.InsertItem(LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE,i,pItem->sTalkName,0,0,img,(LONG)pos2);
			m_List.SetItemText(i,1,pItem->sIP);
			m_List.SetItemText(i,2,pItem->tBeginTime.Format("%H:%M:%S ,%b %d"));
			m_List.SetItemText(i,3,pItem->tEndTime.Format("%H:%M:%S ,%b %d"));
			i++;
		}
	}

	//make first new  or just first(if no new item) item selected and visible
	if(nFirstNew==-1)
		nFirstNew=i-1;
	m_List.SetItemState(nFirstNew,LVIS_SELECTED,LVIS_SELECTED);
	m_List.EnsureVisible(nFirstNew,true);
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
	LOGITEM *li=(LOGITEM*)Log.GetAt(pos);
	if(!li)
		return;

/* Changed by pubb, use bNew in an another way */
	//m_List.SetItem(i,0,LVIF_IMAGE,NULL,li->bOut?1:0,0,0,0);
	//li->bNew=false;	
/* end of change */
	CLogView lv;
/* Changed by pubb, empty merged item seperator '\b\b' */
	CString	temp;	//backup
	temp=li->sLocal;
	temp.Replace("\b\b","");
	lv.m_local=temp;
	temp=li->sRemote;
	temp.Replace("\b\b","");
	lv.m_remote=temp;
/* end of change */
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

		if(AfxMessageBox("Do you really want to delete all log items?",MB_YESNO)!=IDYES)
			return;

		int k=0;
		for(int i=0;i<count;i++){
			pos=(POSITION)m_List.GetItemData(k);
			LOGITEM* pItem=(LOGITEM*)Log.GetAt(pos);
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
		if(!pos)
			return;
/* Changed by pubb, multi-delete enabled */
		if(m_List.GetSelectedCount()>1
			&& AfxMessageBox("Multi-Deletion, r u sure?",MB_YESNO)!=IDYES)
			return;
		int i,k;
		POSITION item;
		while(pos){
			i=m_List.GetNextSelectedItem(pos);
			item=(POSITION)m_List.GetItemData(i);
			delete (LOGITEM*)Log.GetAt(item);
			Log.RemoveAt(item);
		}
		// Can't delete m_List item before GetItemData(),
		// So delete the Logs, and then delete the m_List
		while(pos=m_List.GetFirstSelectedItemPosition()){
			i=m_List.GetNextSelectedItem(pos);
			m_List.DeleteItem(i);
		}
/* end of change */
		if(k=m_List.GetItemCount()){
			if(k==i)
				k=0;
			else 
				k=i;
			m_List.SetItemState(k,LVIS_SELECTED,LVIS_SELECTED);
			m_List.EnsureVisible(k,true);
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
/* Changed by pubb, multi-addtoaddress enabled */
	int i;
	CString ip,name;
	ABITEM * abi;
	POSITION item,thisitem;
	BOOL	newloop;
	while(pos){
		newloop=false;
		i=m_List.GetNextSelectedItem(pos);
		ip=m_List.GetItemText(i,1);
		name=m_List.GetItemText(i,0);

		item=AB->GetHeadPosition();
		BOOL found=false;
		while(item){
			thisitem=item;
			abi=(ABITEM*)AB->GetNext(item);
			if(!abi->Name.Compare(name)){
				if(!abi->IP.Compare(ip)){
					AfxMessageBox("Same item '"+name+"' exists in Addressbook!");
					newloop=true;
					break;
				}
				if(AfxMessageBox("Same name '"+name+"' exists in Addressbook! Update?",MB_YESNO)!=IDYES){
					newloop=true;
					break;
				}
				else{
					found=true;
					break;
				}
			}
		}
		if(newloop)
			continue;
		if(!found){
			abi=(ABITEM*) new ABITEM;
			if(!abi){
				AfxMessageBox("Failed!");
				return;
			}
			abi->IP=ip;
			abi->Name=name;
			AB->AddTail(abi);
		}else{
			abi->IP=ip;
			AB->SetAt(thisitem,abi);
		}
	}
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
				LOGITEM *li=(LOGITEM*)new LOGITEM;
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
			LOGITEM* li=(LOGITEM*)Log.GetNext(pos);
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

BOOL CLogDlg::PreTranslateMessage(MSG* pMsg) 
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

/* Added by pubb, right click to do Merge and Encrypt in logs */
void CLogDlg::OnRclickLoglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu menu,*pSubMenu;

	if (!menu.LoadMenu(IDR_LOGMENU))
		return;
	if (!(pSubMenu = menu.GetSubMenu(0)))
		return;

	//::SetMenuDefaultItem(pSubMenu->m_hMenu,0,true);
	POSITION item_pos;
	unsigned int i;
	item_pos=m_List.GetFirstSelectedItemPosition();
	if(!item_pos){
		return;
	}else{
		i=m_List.GetNextSelectedItem(item_pos);
		item_pos=(POSITION)m_List.GetItemData(i);
		LOGITEM *li=Log.GetAt(item_pos);
		if(m_List.GetSelectedCount()==1){
			pSubMenu->EnableMenuItem(ID_LOG_MER,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_LOG_MER_ENC,MF_GRAYED);
			if(!li->bNew){
				pSubMenu->EnableMenuItem(ID_LOG_EXP,MF_GRAYED);
			}
		}
		if(m_List.GetSelectedCount()>1){
			pSubMenu->EnableMenuItem(ID_LOG_EXP,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_LOG_MER2,MF_GRAYED);
		}
	}
	CPoint pos;
	GetCursorPos(&pos);
	SetForegroundWindow();
	::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0,  GetSafeHwnd(), NULL);
	PostMessage(WM_NULL, 0, 0);
	menu.DestroyMenu();
	*pResult = 0;
}

void CLogDlg::OnLogMerge() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition(),item,addpos=(POSITION)-1;
	int i,j=-1;	//'j' and 'addpos' for 'selected head'
	LOGITEM * li;
	LOGITEM	*merged_item=new LOGITEM;
	BOOL	bSameTalker=true,bSameIP=true;

	merged_item->bNew=true;
	merged_item->sIP="multiple IPs";
	merged_item->sTalkName="(merged)";
	merged_item->tBeginTime=CTime(2038,1,18,0,0,0); //biggest time
	merged_item->tEndTime=CTime(1980,1,1,0,0,0);	//smallest time
	merged_item->sLocal="";
	merged_item->sRemote="";
	while(pos){
		i=m_List.GetNextSelectedItem(pos);
		if(j<0) j=i;
		item=(POSITION)m_List.GetItemData(i);
		if((LONG)addpos<0){
			addpos=item;
			Log.GetPrev(addpos);
		}
		li=(LOGITEM*)Log.GetAt(item);
		//merge all selected contents, with '\b\b' as break
		if(bSameTalker && li->sTalkName.Compare(merged_item->sTalkName)){
			if(!merged_item->sTalkName.Compare("(merged)"))
				merged_item->sTalkName=li->sTalkName;
			else{
				bSameTalker=false;
				merged_item->sTalkName="(merged)";
			}
		}
		if(bSameIP && li->sIP.Compare(merged_item->sIP)){
			if(!merged_item->sIP.Compare("multiple IPs"))
				merged_item->sIP=li->sIP;
			else{
				bSameIP=false;
				merged_item->sIP="multiple IPs";
			}
		}
		if(li->bNew){	//merged item
			merged_item->sLocal+=li->sLocal;
			merged_item->sRemote+=li->sRemote;
		}else{
			merged_item->sLocal+=Log2MergeString(li,false)+"\b\b";
			merged_item->sRemote+=Log2MergeString(li,true)+"\b\b";
		}
		if(merged_item->tBeginTime>li->tBeginTime)
			merged_item->tBeginTime=li->tBeginTime;
		if(merged_item->tEndTime<li->tEndTime)
			merged_item->tEndTime=li->tEndTime;
		delete li;
		Log.RemoveAt(item);
	}
	Log.InsertAfter(addpos,merged_item);
	// Can't delete m_List item before GetItemData(),
	// So delete the Logs, and then delete the m_List
	// the same conditions as OnLogDel()
	while(pos=m_List.GetFirstSelectedItemPosition()){
		i=m_List.GetNextSelectedItem(pos);
		m_List.DeleteItem(i);
	}
	m_List.InsertItem(LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE,j,merged_item->sTalkName,0,0,2,(LONG)Log.Find(merged_item));
	m_List.SetItemText(j,1,merged_item->sIP);
	m_List.SetItemText(j,2,merged_item->tBeginTime.Format("%H:%M:%S, %b %d"));
	m_List.SetItemText(j,3,merged_item->tEndTime.Format("%H:%M:%S, %b %d"));
}

/* make album */
void CLogDlg::OnLogMer2() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition();
	int	i=m_List.GetNextSelectedItem(pos);
	CString	sTalkName=m_List.GetItemText(i,0);

	for(i=0;i<m_List.GetItemCount();i++)
		if(!m_List.GetItemText(i,0).Compare(sTalkName))
			m_List.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
	OnLogMerge();
}

void CLogDlg::OnLogEncrypt() 
{
	// TODO: Add your command handler code here
	
}

void CLogDlg::OnLogMerEnc() 
{
	// TODO: Add your command handler code here
	
}

void CLogDlg::OnLogExp() 
{
	POSITION pos=m_List.GetFirstSelectedItemPosition(),item;
	int i=m_List.GetNextSelectedItem(pos),j1=0,j2=0;
	LOGITEM	*li,*merged_item;
	
	pos=item=(POSITION)m_List.GetItemData(i);
	m_List.DeleteItem(i);
	merged_item=Log.GetAt(pos);
	while(j1<merged_item->sLocal.GetLength() && j2<merged_item->sRemote.GetLength()){
		li=new LOGITEM;
		j1+=MergeString2Log(merged_item->sLocal.Mid(j1),false,li);
		j2+=MergeString2Log(merged_item->sRemote.Mid(j2),true,li);
		li->m_nParam=i;
		pos=Log.InsertAfter(pos,li);
		m_List.InsertItem(LVIF_TEXT|LVIF_PARAM|LVIF_IMAGE,i,li->sTalkName,0,0,li->bOut,(LONG)pos);
		m_List.SetItemText(i,1,li->sIP);
		m_List.SetItemText(i,2,li->tBeginTime.Format("%H:%M:%S ,%b %d"));
		m_List.SetItemText(i++,3,li->tEndTime.Format("%H:%M:%S ,%b %d"));
	}
	Log.RemoveAt(item);
}

/* merge logs to string, the first line indicate the caller and callee */
CString CLogDlg::Log2MergeString(LOGITEM * li,BOOL bremote)
{
	if(!bremote)
		return (li->bOut?"To ":"to ")+li->sTalkName+"("+li->sIP+") "+li->tBeginTime.Format("%H:%M:%S")+" -- "+li->tEndTime.Format("%H:%M:%S %a,%m %d")+"\r\n"+li->sLocal+"\r\n";
	else
		return (li->bOut?"from ":"From ")+li->sTalkName+"("+li->sIP+") "+li->tBeginTime.Format("%H:%M:%S")+" -- "+li->tEndTime.Format("%H:%M:%S %a,%m %d")+"\r\n"+li->sRemote+"\r\n";
}

/* expand merged string to log structure, return next entry */
int CLogDlg::MergeString2Log(CString s,BOOL bremote,LOGITEM *li)
{
	int i,j;
	int month,day,hour1,hour2,minute1,minute2,second1,second2;
    CString temp;

	if(s.IsEmpty())
		return -1;
	
	temp=s.Left(1);
	if(!temp.Compare("T") || !temp.Compare("f"))
		li->bOut=true;
	else
		li->bOut=false;
	li->bNew=false;
	i=s.Find(' ');
	j=s.Find('(');
	li->sTalkName=s.Mid(i+1,j-i-1);
	i=s.Find(')');
	li->sIP=s.Mid(j+1,i-j-1);
	j=s.Find(' ',i+2);
	sscanf(s.Mid(i+2,j-i-1),"%d:%d:%d",&hour1,&minute1,&second1);
	i=s.Find('\r',j+4);
	sscanf(s.Mid(j+4,i-j-4),"%d:%d:%d %[^,],%d %d",&hour2,&minute2,&second2,temp.GetBuffer(8),&month,&day);
	temp.ReleaseBuffer();
	li->tBeginTime=CTime(2000,month,day,hour1,minute1,second1);
	li->tEndTime=CTime(2000,month,day,hour2,minute2,second2);
	j=s.Find('\b',i);
	if(bremote)
		li->sRemote=s.Mid(i+2,j-i-1);
	else
		li->sLocal=s.Mid(i+2,j-i-1);
	return j+2;
}
/* end of add */
