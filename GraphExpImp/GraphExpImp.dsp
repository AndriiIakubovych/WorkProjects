# Microsoft Developer Studio Project File - Name="GraphExpImp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GraphExpImp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GraphExpImp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GraphExpImp.mak" CFG="GraphExpImp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GraphExpImp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GraphExpImp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GraphExpImp - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "GraphExpImp - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GraphExpImp - Win32 Release"
# Name "GraphExpImp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutProgramDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddFilesExpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddFilesImpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddProfileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddSampleProfileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AdvToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DesspaceRead.cpp
# End Source File
# Begin Source File

SOURCE=.\EditFilesExpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditFilesImpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditProfileExpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditProfileImpDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditProfileReorgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditProfileTransDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FilesExpImpRead.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphExpImp.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphExpImp.rc
# End Source File
# Begin Source File

SOURCE=.\GraphExpImpDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphExpImpView.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemMenuRead.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\NameNewTableDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NregionRead.cpp
# End Source File
# Begin Source File

SOURCE=.\PlsizeRead.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfilesExpImpRead.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TplevRead.cpp
# End Source File
# Begin Source File

SOURCE=.\TplineRead.cpp
# End Source File
# Begin Source File

SOURCE=.\TpnameRead.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutProgramDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddFilesExpDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddFilesImpDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddProfileDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddSampleProfileDlg.h
# End Source File
# Begin Source File

SOURCE=.\AdvToolBar.h
# End Source File
# Begin Source File

SOURCE=.\DesspaceRead.h
# End Source File
# Begin Source File

SOURCE=.\EditFilesExpDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditFilesImpDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditProfileExpDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditProfileImpDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditProfileReorgDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditProfileTransDlg.h
# End Source File
# Begin Source File

SOURCE=.\FilesExpImpRead.h
# End Source File
# Begin Source File

SOURCE=.\GraphExpImp.h
# End Source File
# Begin Source File

SOURCE=.\GraphExpImpDoc.h
# End Source File
# Begin Source File

SOURCE=.\GraphExpImpView.h
# End Source File
# Begin Source File

SOURCE=.\ItemMenuRead.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\NameNewTableDlg.h
# End Source File
# Begin Source File

SOURCE=.\NregionRead.h
# End Source File
# Begin Source File

SOURCE=.\PlsizeRead.h
# End Source File
# Begin Source File

SOURCE=.\ProfilesExpImpRead.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TplevRead.h
# End Source File
# Begin Source File

SOURCE=.\TplineRead.h
# End Source File
# Begin Source File

SOURCE=.\TpnameRead.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\City.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FileExp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FileImp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GraphExpImp.ico
# End Source File
# Begin Source File

SOURCE=.\res\GraphExpImp.rc2
# End Source File
# Begin Source File

SOURCE=.\res\GraphExpImpDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ProfileExp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProfileImp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProfileReorg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProfileTrans.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
