// Config.cpp: implementation of the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "talk.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfig::CConfig()
{
	sWelMsg="Hi,%name%!\r\n";
	sAbsentMsg="I'm not here now!\r\nYou can leave words or call me later!\r\n";
	nIdleTime=600;
	nConfirmTime=5;
	sMyName="Anonymous";
	nMaxConnections=10;
	bBeep=true;
	lfEdit.lfHeight=0;
	clrEditBack=RGB(255,255,255);
	clrEditText=RGB(0,0,0);
	bHScroll=false;
	bVScroll=true;
	nRetry=3;
	nRetryInterval=1;

	m_Emote1='@';
	m_Emote2='#';
	m_Emote3='$';
	m_EmoteEsc='\\';

}

CConfig::~CConfig()
{

}

BOOL CConfig::Store()
{
	CFile cfgf;
	if(cfgf.Open(m_sFileName,CFile::modeCreate|CFile::modeReadWrite)){
		CArchive cfgar(&cfgf,CArchive::store);
		cfgar<<bBeep;
		cfgar<<nMaxConnections;
		cfgar<<nIdleTime;
		cfgar<<nConfirmTime;
		cfgar<<sAbsentMsg;
		cfgar<<sMyName;
		cfgar<<sWelMsg;
		cfgar<<(DWORD)clrEditBack;
		cfgar<<(DWORD)clrEditText;
		cfgar.Write(&lfEdit,sizeof(LOGFONT));
		cfgar<<bHScroll;
		cfgar<<bVScroll;
		cfgar<<nRetry;
		cfgar<<nRetryInterval;
		cfgar<<m_Emote1;
		cfgar<<m_Emote2;
		cfgar<<m_Emote3;
		cfgar<<m_EmoteEsc;
		return true;
	}	
	return false;
}

BOOL CConfig::Load()
{
	CFile cfgf;
	if(!cfgf.Open(m_sFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead))
		return false;
	if(cfgf.GetLength()){
		CArchive cfgar(&cfgf,CArchive::load);
		cfgar>>bBeep;
		cfgar>>nMaxConnections;
		cfgar>>nIdleTime;
		cfgar>>nConfirmTime;
		cfgar>>sAbsentMsg;
		cfgar>>sMyName;
		cfgar>>sWelMsg;
		cfgar>>(DWORD)clrEditBack;
		cfgar>>(DWORD)clrEditText;
		cfgar.Read(&lfEdit,sizeof(LOGFONT));
		cfgar>>bHScroll;
		cfgar>>bVScroll;
		cfgar>>nRetry;
		cfgar>>nRetryInterval;
		cfgar>>m_Emote1;
		cfgar>>m_Emote2;
		cfgar>>m_Emote3;
		cfgar>>m_EmoteEsc;

	}
	return true;
}
