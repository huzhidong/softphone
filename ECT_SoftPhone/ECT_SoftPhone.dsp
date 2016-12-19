# Microsoft Developer Studio Project File - Name="ECT_SoftPhone" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ECT_SoftPhone - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ECT_SoftPhone.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ECT_SoftPhone.mak" CFG="ECT_SoftPhone - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ECT_SoftPhone - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ECT_SoftPhone - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ECT_SoftPhone - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ECT_SoftPhone - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ECT_SoftPhone - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /U "_INC_STDLIB" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /u
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib common_MD_dll.lib tlib_MD_dll.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /pdb:none /incremental:yes /nodefaultlib
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=.\Release\ECT_SoftPhone.ocx
InputPath=.\Release\ECT_SoftPhone.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ECT_SoftPhone - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MT /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tlib_MD_dll.lib common_MD_dll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\ECT_SoftPhone.ocx
InputPath=.\Debug\ECT_SoftPhone.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ECT_SoftPhone - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Ext "ocx"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\ECT_SoftPhone.ocx
InputPath=.\DebugU\ECT_SoftPhone.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ECT_SoftPhone - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tlib_MD_dll.lib common_MD_dll.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\ECT_SoftPhone.ocx
InputPath=.\ReleaseU\ECT_SoftPhone.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ECT_SoftPhone - Win32 Release"
# Name "ECT_SoftPhone - Win32 Debug"
# Name "ECT_SoftPhone - Win32 Unicode Debug"
# Name "ECT_SoftPhone - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AgentFormDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BITMAPDIALOG.CPP
# End Source File
# Begin Source File

SOURCE=.\BusyReasonDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorStaticST.cpp
# End Source File
# Begin Source File

SOURCE=.\ConsultDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlCenter.cpp
# End Source File
# Begin Source File

SOURCE=.\CTIInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\DialDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DIB256.CPP
# End Source File
# Begin Source File

SOURCE=.\DIBPAL.CPP
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhone.cpp
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhone.def
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhone.odl
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhone.rc
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhoneCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhonePpg.cpp
# End Source File
# Begin Source File

SOURCE=.\GenesysInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ListenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Module1.cpp
# End Source File
# Begin Source File

SOURCE=.\ROUNDBUTTON.CPP
# End Source File
# Begin Source File

SOURCE=.\StateMachine.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TransferDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AgentFormDlg.h
# End Source File
# Begin Source File

SOURCE=.\BITMAPDIALOG.H
# End Source File
# Begin Source File

SOURCE=.\BusyReasonDlg.h
# End Source File
# Begin Source File

SOURCE=.\ColorStaticST.h
# End Source File
# Begin Source File

SOURCE=.\ConsultDlg.h
# End Source File
# Begin Source File

SOURCE=.\ControlCenter.h
# End Source File
# Begin Source File

SOURCE=.\CTIInterface.h
# End Source File
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\DialDlg.h
# End Source File
# Begin Source File

SOURCE=.\DIB256.H
# End Source File
# Begin Source File

SOURCE=.\DIBPAL.H
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhone.h
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhoneCtl.h
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhonePpg.h
# End Source File
# Begin Source File

SOURCE=.\GenesysInterface.h
# End Source File
# Begin Source File

SOURCE=.\ImageButton.h
# End Source File
# Begin Source File

SOURCE=.\ListenDlg.h
# End Source File
# Begin Source File

SOURCE=.\Module1.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RoundButton.h
# End Source File
# Begin Source File

SOURCE=.\StateMachine.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TransferDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\answer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BACK1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bargein.bmp
# End Source File
# Begin Source File

SOURCE=.\res\consult.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Dial.bmp
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhone.ico
# End Source File
# Begin Source File

SOURCE=.\ECT_SoftPhoneCtl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\forcebreak.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hold.bmp
# End Source File
# Begin Source File

SOURCE=.\res\listen.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.ico
# End Source File
# Begin Source File

SOURCE=.\res\ready.bmp
# End Source File
# Begin Source File

SOURCE=.\res\reconnect.bmp
# End Source File
# Begin Source File

SOURCE=.\res\transfer.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\common_MD.dll
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\tlib_MD.dll
# End Source File
# End Target
# End Project
