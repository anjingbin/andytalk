# Microsoft Developer Studio Project File - Name="talk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=talk - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "talk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "talk.mak" CFG="talk - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "talk - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "talk - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "talk - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib imm32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/AndyTalkR.exe"

!ELSEIF  "$(CFG)" == "talk - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib imm32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/AndyTalkD.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "talk - Win32 Release"
# Name "talk - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ABDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CfgGen.cpp
# End Source File
# Begin Source File

SOURCE=.\CfgPersonal.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\Confirm.cpp
# End Source File
# Begin Source File

SOURCE=.\InplaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ListenSock.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalOut.cpp
# End Source File
# Begin Source File

SOURCE=.\LogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LogView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgPageA.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgPageW.cpp
# End Source File
# Begin Source File

SOURCE=.\OutlookBar.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoteOut.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\talk.cpp
# End Source File
# Begin Source File

SOURCE=.\talk.rc
# End Source File
# Begin Source File

SOURCE=.\TalkSock.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ABDlg.h
# End Source File
# Begin Source File

SOURCE=.\CDlg.h
# End Source File
# Begin Source File

SOURCE=.\CfgGen.h
# End Source File
# Begin Source File

SOURCE=.\CfgPersonal.h
# End Source File
# Begin Source File

SOURCE=.\ClientWnd.h
# End Source File
# Begin Source File

SOURCE=.\Confirm.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\InplaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\ListenSock.h
# End Source File
# Begin Source File

SOURCE=.\LocalOut.h
# End Source File
# Begin Source File

SOURCE=.\LogDlg.h
# End Source File
# Begin Source File

SOURCE=.\LogView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MsgPageA.h
# End Source File
# Begin Source File

SOURCE=.\MsgPageW.h
# End Source File
# Begin Source File

SOURCE=.\OutlookBar.h
# End Source File
# Begin Source File

SOURCE=.\RemoteOut.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\talk.h
# End Source File
# Begin Source File

SOURCE=.\TalkSock.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\129.ico
# End Source File
# Begin Source File

SOURCE=.\res\130.ico
# End Source File
# Begin Source File

SOURCE=.\res\131.ico
# End Source File
# Begin Source File

SOURCE=.\res\active.ico
# End Source File
# Begin Source File

SOURCE=.\res\Arw06lt.ico
# End Source File
# Begin Source File

SOURCE=.\res\Arw06rt.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\conn.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\idd_abou.ico
# End Source File
# Begin Source File

SOURCE=.\res\talk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\talk.ico
# End Source File
# Begin Source File

SOURCE=.\res\talk.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\try.ico
# End Source File
# Begin Source File

SOURCE=.\res\W95mbx04.ico
# End Source File
# Begin Source File

SOURCE=.\res\wintalk.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChangeLog.txt
# End Source File
# Begin Source File

SOURCE=.\res\Notify.wav
# End Source File
# Begin Source File

SOURCE=.\res\ohoh.wav
# End Source File
# Begin Source File

SOURCE=.\protocol.txt
# End Source File
# Begin Source File

SOURCE=.\res\ringin.wav
# End Source File
# Begin Source File

SOURCE=.\res\ringout.wav
# End Source File
# Begin Source File

SOURCE=.\ToDo.txt
# End Source File
# End Target
# End Project
