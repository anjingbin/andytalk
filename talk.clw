; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCDlg
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

ResourceCount=13
Resource1=IDD_LOG
Resource2=IDR_MAINFRAME
Resource3=IDD_VIEW
Resource4=IDD_ADDRBOOK
Resource5=IDR_TRAYMENU
Resource6=IDD_CFG_MSG_2
Resource7=IDD_ABOUTBOX
Resource8=IDD_CFG_MSG_1
Resource9=IDD_CONNECT
Resource10=IDD_CFG_GENERAL
Resource11=IDD_PERSONAL
Resource12=IDD_CFG_MSG_3
Resource13=IDD_CONFIRM

[CLS:CABDlg]
Type=0
BaseClass=CDialog
HeaderFile=ABDlg.h
ImplementationFile=ABDlg.cpp
LastObject=CABDlg

[CLS:CCDlg]
Type=0
BaseClass=CDialog
HeaderFile=CDlg.h
ImplementationFile=CDlg.cpp
LastObject=IDC_IPHOST
Filter=D
VirtualFilter=dWC

[CLS:CCfgGen]
Type=0
BaseClass=CPropertyPage
HeaderFile=CfgGen.h
ImplementationFile=CfgGen.cpp
LastObject=IDC_TIME1

[CLS:CCfgPersonal]
Type=0
BaseClass=CPropertyPage
HeaderFile=CfgPersonal.h
ImplementationFile=CfgPersonal.cpp

[CLS:CClientWnd]
Type=0
BaseClass=CWnd
HeaderFile=ClientWnd.h
ImplementationFile=ClientWnd.cpp

[CLS:CConfirm]
Type=0
BaseClass=CDialog
HeaderFile=Confirm.h
ImplementationFile=Confirm.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDOK

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

[CLS:CMsgPageW]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgPageW.h
ImplementationFile=MsgPageW.cpp
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

[CLS:CTalkSock]
Type=0
BaseClass=CAsyncSocket
HeaderFile=TalkSock.h
ImplementationFile=TalkSock.cpp

[DLG:IDD_ADDRBOOK]
Type=1
Class=CABDlg
ControlCount=11
Control1=IDC_LIST,SysListView32,1350631709
Control2=IDC_STATIC,static,1342308352
Control3=IDC_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_IP,SysIPAddress32,1342242816
Control6=IDC_CLEAR,button,1342242816
Control7=IDC_DELETE,button,1342242816
Control8=IDC_SAVE,button,1342242817
Control9=IDC_CONNECT,button,1342242816
Control10=IDOK,button,1342242816
Control11=IDC_STATIC,button,1342177287

[DLG:IDD_CONNECT]
Type=1
Class=CCDlg
ControlCount=4
Control1=IDC_STATIC,button,1342177287
Control2=IDC_IP,SysIPAddress32,1342242816
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_CFG_GENERAL]
Type=1
Class=CCfgGen
ControlCount=18
Control1=IDC_STATIC,button,1342177287
Control2=IDC_MYNAME,edit,1350631552
Control3=IDC_STATIC,static,1342308876
Control4=IDC_MAXCONN,edit,1350770816
Control5=IDC_SPIN1,msctls_updown32,1342177719
Control6=IDC_STATIC,static,1342308864
Control7=IDC_TIME1,edit,1350770816
Control8=IDC_SPIN2,msctls_updown32,1342177591
Control9=IDC_STATIC,static,1342308864
Control10=IDC_STATIC,static,1342308864
Control11=IDC_TIME2,edit,1350770816
Control12=IDC_SPIN3,msctls_updown32,1342177719
Control13=IDC_STATIC,static,1342308864
Control14=IDC_BEEP,button,1342242819
Control15=IDC_NEED,button,1342242819
Control16=IDC_ONLY,button,1342242819
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STARTUP,button,1342242819

[DLG:IDD_PERSONAL]
Type=1
Class=CCfgPersonal
ControlCount=8
Control1=IDC_STATIC,static,1342308864
Control2=IDC_LIST1,SysListView32,1350664589
Control3=IDC_STATIC,button,1342177287
Control4=IDC_WELMSG,edit,1352732868
Control5=IDC_CHECK1,button,1342242819
Control6=IDC_LVWORD,edit,1352732868
Control7=IDC_STATIC,button,1342177287
Control8=IDC_CHECK2,button,1342242819

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

[DLG:IDD_CFG_MSG_2]
Type=1
Class=CMsgPageA
ControlCount=2
Control1=IDC_ENABLE,button,1342242819
Control2=IDC_EDIT,edit,1353781444

[DLG:IDD_CFG_MSG_3]
Type=1
Class=CMsgPageB
ControlCount=2
Control1=IDC_ENABLE,button,1342242819
Control2=IDC_EDIT,edit,1353781444

[DLG:IDD_CFG_MSG_1]
Type=1
Class=CMsgPageW
ControlCount=2
Control1=IDC_ENABLE,button,1342242819
Control2=IDC_EDIT,edit,1353781444

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
Command2=ID_DISC
Command3=ID_BEEP
Command4=ID_APP_EXIT
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_HSCROLL
Command9=ID_VSCROLL
Command10=ID_WANTTALK
Command11=ID_SETTING
Command12=ID_FONT
Command13=ID_BACKCOLOR
Command14=ID_ADDRBOOK
Command15=ID_LOG
Command16=ID_SAVE
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

