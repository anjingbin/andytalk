// Config.cpp: implementation of the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "talk.h"
#include "Config.h"

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
	sAbsentMsg="I'm not here now!\r\nYou can leave words or call me later\r\n";
	sBusyMsg="Sorry!\r\nI'm talking with another,please call me later!\r\n";
	bWelMsg=true;
	bAbsentMsg=true;
	bBusyMsg=true;
	nTimeOut1=120;
	nTimeOut2=5;
	sMyName="Anonymous";
	nMaxConnections=10;
	bBeep=true;
	bIPAB=false;
	bNeedConfirm=true;
	lfEdit.lfHeight=0;
	clrEditBack=RGB(255,255,255);
	clrEditText=RGB(0,0,0);
	bHScroll=true;
	bVScroll=true;
}

CConfig::~CConfig()
{

}
