// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "talk.h"
#include "Log.h"
#include "cpassdlg.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLog::CLog(CRijndael *paes)
{
	bReady=false;
	bEncrypted=false;
	bLocked=false;
	if(paes==NULL)
		pAES_engine=&((CMainFrame*)AfxGetMainWnd())->m_wndClient.m_AES_engine;
	else
		pAES_engine=paes;
}

CLog::CLog(CString &sFilename,BOOL bRW,CRijndael *paes)
{
	bReady=false;
	bEncrypted=false;
	if(paes==NULL)
		pAES_engine=&((CMainFrame*)AfxGetMainWnd())->m_wndClient.m_AES_engine;
	else
		pAES_engine=paes;

	CFile	logf;
	UINT	mode;

	if(bRW)
		mode=CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite;
	else
		mode=CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead;

	if(!logf.Open(sFilename,mode)){
		AfxMessageBox("Failed to open logfile "+sFilename);
		return;
	}
	if(logf.GetLength()){
		CArchive logar(&logf,CArchive::load);
		(*this)<<logar;
	}
	if(bEncrypted)
		bLocked=true;
	else
		bLocked=false;
	bReady=true;
}

CLog::CLog(CArchive &ar,CRijndael *paes)
{
	bReady=false;
	bEncrypted=false;
	bLocked=false;
	if(paes==NULL)
		pAES_engine=&((CMainFrame*)AfxGetMainWnd())->m_wndClient.m_AES_engine;
	else
		pAES_engine=paes;

	(*this)<<ar;
	if(bEncrypted)
		bLocked=true;
	else
		bLocked=false;
	bReady=true;
}

CLog::~CLog()
{
	bReady=false;
	POSITION	pos=GetHeadPosition();
	while(pos){
		LOGITEM* li=(LOGITEM*)GetNext(pos);
		delete li;
	}
	RemoveAll();
}

CArchive & CLog::operator <<(CArchive & logar)
{
	UINT	count;

	TRY{
	logar>>count;
	}
	CATCH_ALL(e){
		count=0;
	}
	END_CATCH_ALL
	TRY{
	while(count--){
		LOGITEM *li=(LOGITEM*)new LOGITEM;
		logar>>li->bNew;
		logar>>li->bOut;
		logar>>li->sIP;
		logar>>li->sLocal>>li->sRemote;
		logar>>li->sTalkName;
		logar>>li->tBeginTime;
		logar>>li->tEndTime;
		AddTail(li);
	}
	}
	CATCH_ALL(e){
		if(AfxMessageBox("Failed to load Log data! Ignore?",MB_YESNO)!=IDYES){
			POSITION	pos=GetHeadPosition();
			while(pos){
				LOGITEM* li=(LOGITEM*)GetNext(pos);
			delete li;
			}
			RemoveAll();
		}
	}
	END_CATCH_ALL
	TRY{
		logar>>bEncrypted;
	}
	CATCH_ALL(e){
		bEncrypted=false;	//default value
	}
	END_CATCH_ALL
	if(bEncrypted)
		bLocked=true;
	else
		bLocked=false;
	bReady=true;
	return logar;
}

CArchive & CLog::operator >>(CArchive & logar)
{
	logar<<GetCount();
	POSITION	pos=GetHeadPosition();
	if(bEncrypted && !bLocked && pAES_engine!=NULL)
		Encrypt();
	while(pos){
		LOGITEM* li=(LOGITEM*)GetNext(pos);
		logar<<li->bNew;
		logar<<li->bOut;
		logar<<li->sIP;
		logar<<li->sLocal<<li->sRemote;
		logar<<li->sTalkName;
		logar<<li->tBeginTime;
		logar<<li->tEndTime;
	}
	logar<<bEncrypted;
	return logar;
}

BOOL CLog::Encrypt(CRijndael *paes)
{
	if(!paes)
		paes=pAES_engine;
	POSITION	pos=GetHeadPosition();
	while(pos){
		LOGITEM* li=(LOGITEM*)GetNext(pos);
		if(!::Encrypt(li->sLocal,*paes) || !::Encrypt(li->sRemote,*paes))
			return false;
	}
	bEncrypted=true;
	bLocked=true;
	return true;
}

BOOL CLog::Decrypt(CRijndael *paes)
{
	if(!paes)
		paes=pAES_engine;
	POSITION	pos=GetHeadPosition();
	while(pos){
		LOGITEM* li=(LOGITEM*)GetNext(pos);
		if(!::Decrypt(li->sLocal,*paes) || !::Decrypt(li->sRemote,*paes))
			return false;
	}
	return true;
}

void CLog::operator <<(LOGITEM *li)
{
	if(!bReady)
		return;
	if(bEncrypted || (pAES_engine->KeyInited() && GetCount()==0)){
		::Encrypt(li->sLocal,*pAES_engine);
		::Encrypt(li->sRemote,*pAES_engine);
		bEncrypted=true;
		bLocked=true;
	}
	AddTail(li);
}

LOGITEM * CLog::operator [] (POSITION pos)
{
	if(bReady)
		return GetAt(pos);
	return NULL;
}

LOGITEM * CLog::operator [](UINT index)
{
	if(!bReady)
		return NULL;
	POSITION pos=FindIndex(index);
	return GetAt(pos);
}

BOOL CLog::UnLock(void)
{
	if(bLocked){
		CPassDlg	enterpassDlg(((CMainFrame*)AfxGetMainWnd())->m_wndClient.m_Config.m_Password,pAES_engine);
		if(enterpassDlg.DoModal()!=IDOK)
			return false;
		if(!Decrypt())
			return false;
		bLocked=false;
	}
	return true;
}

BOOL CLog::IsReady()
{
	return bReady;
}

BOOL CLog::IsLocked()
{
	return bLocked;
}

void CLog::SetAES_engine(CRijndael *paes)
{
	pAES_engine=paes;
}

void CLog::SetEncrypt(BOOL benc)
{
	bEncrypted=benc;
}

BOOL CLog::ContainItem(LOGITEM *item)
{
	POSITION	pos=GetHeadPosition();
	while(pos){
		LOGITEM* li=(LOGITEM*)GetNext(pos);
		if(li->bNew==item->bNew && li->bOut==item->bNew && li->sIP==item->sIP &&
			li->sTalkName==item->sTalkName && li->tBeginTime==item->tBeginTime && li->tEndTime==item->tEndTime)
			return true;
	}
	return false;
}

CLog & CLog::operator <<(CLog & src)
{
	POSITION pos=src.GetHeadPosition();
	LOGITEM *li,*sli;
	while(pos){
		li=new LOGITEM;
		sli=src.GetNext(pos);
		li->bNew=sli->bNew;
		li->bOut=sli->bOut;
		li->m_nParam=sli->m_nParam;
		li->sIP=sli->sIP;
		li->sLocal=sli->sLocal;
		li->sRemote=sli->sRemote;
		li->sTalkName=sli->sTalkName;
		li->tBeginTime=sli->tBeginTime;
		li->tEndTime=sli->tEndTime;
		AddTail(li);
	}
	return *this;
}

CLog & CLog::operator >>(CLog & des)
{
	POSITION pos=GetTailPosition();
	LOGITEM *li,*sli;
	while(pos){
		li=new LOGITEM;
		sli=GetPrev(pos);
		li->bNew=sli->bNew;
		li->bOut=sli->bOut;
		li->m_nParam=sli->m_nParam;
		li->sIP=sli->sIP;
		li->sLocal=sli->sLocal;
		li->sRemote=sli->sRemote;
		li->sTalkName=sli->sTalkName;
		li->tBeginTime=sli->tBeginTime;
		li->tEndTime=sli->tEndTime;
		des.AddHead(li);
	}
	return des;
}
