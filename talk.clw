; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCfgGen
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "talk.h"
LastPage=0

ClassCount=22
Class1=CABDlg
Class2=CCDlg
Class3=CCfgGen
Class4=CCfgPersonal
Class5=CClientWnd
Class6=CConfirm
Class7=CInplaceEdit
Class8=CInputCombo
Class9=CListenSock
Class10=CLocalOut
Class11=CLogDlg
Class12=CLogView
Class13=CMainFrame
Class14=CMsgPageA
Class15=CMsgPageB
Class16=CMsgPageW
Class17=COutlookBar
Class18=CRemoteOut
Class19=CSystemTray
Class20=CTalkApp
Class21=CAboutDlg
Class22=CTalkSock

ResourceCount=12
Resource1=IDD_CONFIRM
Resource2=IDD_PERSONAL
Resource3=IDR_MAINFRAME
Resource4=IDR_TRAYMENU
Resource5=IDD_CFG_MSG_3
Resource6=IDD_CONNECT
Resource7=IDD_CFG_MSG_1
Resource8=IDD_CFG_GENERAL
Resource9=IDD_ADDRBOOK
Resource10=IDD_LOG
Resource11=IDD_VIEW
Resource12=IDD_ABOUTBOX

[CLS:CABDlg]
Type=0
BaseClass=CDialog
HeaderFile=ABDlg.h
ImplementationFile=ABDlg.cpp
LastObject=IDC_TIME
Filter=D
VirtualFilter=dWC

[CLS:CCDlg]
Type=0
BaseClass=CDialog
HeaderFile=CDlg.h
ImplementationFile=CDlg.cpp
LastObject=IDC_EDIT1
Filter=D
VirtualFilter=dWC

[CLS:CCfgGen]
Type=0
BaseClass=CPropertyPage
HeaderFile=CfgGen.h
ImplementationFile=CfgGen.cpp
LastObject=IDC_EMOTE1
Filter=D
VirtualFilter=idWC

[CLS:CCfgPersonal]
Type=0
BaseClass=CPropertyPage
HeaderFile=CfgPersonal.h
ImplementationFile=CfgPersonal.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_WELMSG

[CLS:CClientWnd]
Type=0
BaseClass=CWnd
HeaderFile=ClientWnd.h
ImplementationFile=ClientWnd.cpp
Filter=W
VirtualFilter=WC

[CLS:CConfirm]
Type=0
BaseClass=CDialog
HeaderFile=Confirm.h
ImplementationFile=Confirm.cpp
Filter=T
VirtualFilter=dWC

[CLS:CInplaceEdit]
Type=0
BaseClass=CEdit
HeaderFile=InplaceEdit.h
ImplementationFile=InplaceEdit.cpp

[CLS:CInputCombo]
Type=0
BaseClass=CComboBox
HeaderFile=InputCombo.h
ImplementationFile=InputCombo.cpp

[CLS:CListenSock]
Type=0
BaseClass=CAsyncSocket
HeaderFile=ListenSock.h
ImplementationFile=ListenSock.cpp

[CLS:CLocalOut]
Type=0
BaseClass=CEdit
HeaderFile=LocalOut.h
ImplementationFile=LocalOut.cpp

[CLS:CLogDlg]
Type=0
BaseClass=CDialog
HeaderFile=LogDlg.h
ImplementationFile=LogDlg.cpp
Filter=D
VirtualFilter=dWC

[CLS:CLogView]
Type=0
BaseClass=CDialog
HeaderFile=LogView.h
ImplementationFile=LogView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMsgPageA]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgPageA.h
ImplementationFile=MsgPageA.cpp

[CLS:CMsgPageB]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgPageB.h
ImplementationFile=MsgPageB.cpp
Filter=D
VirtualFilter=idWC

[CLS:CMsgPageW]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgPageW.h
ImplementationFile=MsgPageW.cpp
Filter=D
VirtualFilter=idWC
LastObject=CMsgPageW

[CLS:COutlookBar]
Type=0
BaseClass=CListBox
HeaderFile=OutlookBar.h
ImplementationFile=OutlookBar.cpp

[CLS:CRemoteOut]
Type=0
BaseClass=CEdit
HeaderFile=RemoteOut.h
ImplementationFile=RemoteOut.cpp

[CLS:CSystemTray]
Type=0
BaseClass=CWnd
HeaderFile=SystemTray.h
ImplementationFile=SystemTray.cpp

[CLS:CTalkApp]
Type=0
BaseClass=CWinApp
HeaderFile=talk.h
ImplementationFile=talk.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=talk.cpp
ImplementationFile=talk.cpp
LastObject=CAboutDlg

[CLS:CTalkSock]
Type=0
BaseClass=CAsyncSocket
HeaderFile=TalkSock.h
ImplementationFile=TalkSock.cpp
Filter=N
VirtualFilter=q

[DLG:IDD_ADDRBOOK]
Type=1
Class=CABDlg
ControlCount=13
Control1=IDC_LIST,SysListView32,1350631709
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NAME,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_HOST,edit,1350631552
Control7=IDC_CLEAR,button,1342242816
Control8=IDC_DELETE,button,1342242816
Control9=IDC_SAVE,button,1342242816
Control10=IDC_SCHEDULE,button,1342242819
Control11=IDC_TIME,SysDateTimePick32,1342242857
Control12=IDC_CONNECT,button,1342242817
Control13=IDOK,button,1342242816

[DLG:IDD_CONNECT]
Type=1
Class=CCDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_HOST,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_CFG_GENERAL]
Type=1
Class=CCfgGen
ControlCount=34
Control1=IDC_STATIC,button,1342177287
Control2=IDC_MYNAME,edit,1350631552
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_RETRYINTERVAL,edit,1350639744
Control6=IDC_SPIN6,msctls_updown32,1342177591
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_RETRY,edit,1350639744
Control10=IDC_SPIN5,msctls_updown32,1342177591
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308876
Control14=IDC_MAXCONN,edit,1350770816
Control15=IDC_SPIN1,msctls_updown32,1342177719
Control16=IDC_STATIC,static,1342308864
Control17=IDC_TIME1,edit,1350770816
Control18=IDC_SPIN2,msctls_updown32,1342177591
Control19=IDC_STATIC,static,1342308864
Control20=IDC_STATIC,static,1342308864
Control21=IDC_TIME2,edit,1350770816
Control22=IDC_SPIN3,msctls_updown32,1342177719
Control23=IDC_STATIC,static,1342308864
Control24=IDC_BEEP,button,1342242819
Control25=IDC_STARTUP,button,1342242819
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,static,1342308864
Control28=IDC_EMOTE1,edit,1350631425
Control29=IDC_STATIC,static,1342308864
Control30=IDC_EMOTE2,edit,1350631425
Control31=IDC_STATIC,static,1342308864
Control32=IDC_EMOTE3,edit,1350631425
Control33=IDC_STATIC,static,1342308864
Control34=IDC_EMOTEESC,edit,1350631425

[DLG:IDD_PERSONAL]
Type=1
Class=CCfgPersonal
ControlCount=6
Control1=IDC_STATIC,static,1342308864
Control2=IDC_NAMELIST,listbox,1352728835
Control3=IDC_BWELMSG,button,1342242819
Control4=IDC_WELMSG,edit,1352732868
Control5=IDC_BABSMSG,button,1342242819
Control6=IDC_ABSMSG,edit,1352732868

[DLG:IDD_CONFIRM]
Type=1
Class=CConfirm
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEXT,static,1342308352
Control4=IDC_TIME,static,1342308876
Control5=IDC_STATIC,static,1342308876
Control6=IDC_STATIC,static,1342177283

[DLG:IDD_LOG]
Type=1
Class=CLogDlg
ControlCount=6
Control1=IDC_LOGLIST,SysListView32,1350631437
Control2=ID_VIEW,button,1342242817
Control3=ID_RECONN,button,1342242816
Control4=ID_LOG_DEL,button,1342242816
Control5=ID_LOG_ADD,button,1342242816
Control6=IDCANCEL,button,1342242816

[DLG:IDD_VIEW]
Type=1
Class=CLogView
ControlCount=3
Control1=IDOK,button,1342242816
Control2=IDC_REMOTE,edit,1353783492
Control3=IDC_LOCAL,edit,1353783492

[DLG:IDD_CFG_MSG_3]
Type=1
Class=CMsgPageB
ControlCount=1
Control1=IDC_EDIT,edit,1353781444

[DLG:IDD_CFG_MSG_1]
Type=1
Class=CMsgPageW
ControlCount=1
Control1=IDC_EDIT,edit,1353781444

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_CONNECT
Command2=ID_REC
Command3=ID_DISC
Command4=ID_BEEP
Command5=ID_APP_EXIT
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_HSCROLL
Command10=ID_VSCROLL
Command11=ID_WANTTALK
Command12=ID_SETTING
Command13=ID_FONT
Command14=ID_BACKCOLOR
Command15=ID_ADDRBOOK
Command16=ID_LOG
Command17=ID_APP_ABOUT
CommandCount=17

[MNU:IDR_TRAYMENU]
Type=1
Class=?
Command1=ID_WANTTALK
Command2=ID_SETTING
Command3=ID_APP_EXIT
Command4=ID_APP_ABOUT
CommandCount=4

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_CONNECT
Command4=ID_REC
Command5=ID_DISC
Command6=ID_BEEP
Command7=ID_ADDRBOOK
Command8=ID_LOG
Command9=ID_WANTTALK
Command10=ID_EDIT_CUT
CommandCount=10

