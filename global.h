#ifndef _GLOBAL_H
#define _GLOBAL_H

//main timer id
#define TALKTIMER 1234

//bar icon index
#define NOR		1
#define RED		2
#define YEL		0	
#define GRN		3

//files used
#define ABFILE "AddressBook.dat"
#define LOGFILE "Log.dat"
#define CFGFILE "Config.dat"

//CTalkSock object status
#define S_NEW			0		//object conctructed
#define S_CREATED		5		//socket created
#define S_CONNECTING	10		//connecting or resolving
#define S_CONNECTFAILED	15		//resolve or connect failed
#define S_CONNECTED		20		//connected
#define S_VERSIONOK		25		//version message (ID=0) received
#define S_NAMEOK		30		//name message (ID=1) received
#define S_CLOSED		40		//socket closed,this means member m_hSocket=INVALID_SOCKET 

//listen tcp port
/* Changed by pubb, enclosure for debug */
#ifndef	PORT
#define PORT		813
#endif
/* end of change */

//own-defined message
#define WM_ICON_NOTIFY (WM_USER+11)		//tray icon notify
#define WM_CONFIRM_OVER  (WM_USER+88)	//confirm over
#define WM_RESOLVE_OVER  (WM_USER+99)	//resolve over

#pragma pack(push,1)
struct _message_r{
	BYTE bCommand;
	WORD wLength;
	BYTE * pBuf;
protected:
	DWORD dwIndex;   //recved octets
	friend class CTalkSock;
};
typedef struct _message_r MESSAGE;   //changed for recv only

//Originally,we use the same data struct (MESSAGE) for both 
//  send and receive,but because of drawbacks of the old version 
//  of Andytalk,it's surely that the "bad format message" error
//	will occur,so we use MESSAGE_S for send and MESSAGE for receive only.

struct _message_s{
protected:
	DWORD dwIndex;	//sent octets
	friend class CTalkSock;
public:
	BYTE * pBuf;
	struct{
		BYTE bCommand;
		WORD wLength;
	}Header;
};
typedef struct _message_s MESSAGE_S; //for send only
#pragma pack(pop)

#define MESSAGE_HEADER_SIZE 3


struct _abitem{
	CString Name;
	CString IP;
	CString WelMsg;
	CString LvWord;
	BOOL	bWelMsg;
	BOOL    bLvWord;
};
typedef struct _abitem ABITEM;

struct _resolveitem{
	CString host;
	int id;
	HANDLE handle;
	char far * buf;
};
typedef struct _resolveitem RESOLVEITEM;

struct _emoteitem{
	CString ToNone;
	CString ToMe;
	CString ToHe;
	CString Emote;
};
typedef struct _emoteitem EMOTEITEM;

struct _logitem {
	BOOL bNew;
	BOOL bOut;
	CString sIP;
	CString sTalkName;
	CTime tBeginTime;
	CTime tEndTime;
	CString sLocal,sRemote;
	int m_nParam;
};
typedef struct _logitem LOGITEM;

//all configurable things here
class CConfig  
{
public:
	int nRetryInterval;		//retry interval time in minutes
	int nRetry;				//retry times
	CString m_sFileName;	//full path name of config file	
	BOOL Load();			//load from file
	BOOL Store();			//store to file

	CString m_sIP;			//recently used hostname to connect to,
	BOOL bVScroll;			//display vertical scrollbar or not
	BOOL bHScroll;			//dispaly horizontal scrollbar or not
	COLORREF clrEditText;	//text color
	COLORREF clrEditBack;	//background color of edit box
	LOGFONT lfEdit;			//font properties
	BOOL bBeep;				//beep or not(popup) on new message 
							//	received when main window is 
							//	invisible or in background
	int nMaxConnections;	//maximum connections allowed	

	CString sWelMsg;		//welcome message
	CString sAbsentMsg;		//absent message
	int nIdleTime;			//idle time in seconds 
	int nConfirmTime;		//confirm tine in seconds
	CString sMyName;		//my name

	char	m_Emote1;
	char	m_Emote2;
	char	m_Emote3;
	char	m_EmoteEsc;


	CConfig();
	virtual ~CConfig();

};

#endif //_GLOBAL_H
