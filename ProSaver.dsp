# Microsoft Developer Studio Project File - Name="ProSaver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ProSaver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProSaver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProSaver.mak" CFG="ProSaver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProSaver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ProSaver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProSaver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ProSaver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ProSaver - Win32 Release"
# Name "ProSaver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Source\audio.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\dxaudio.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\errlog.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\playback.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\prosaver.rc
# End Source File
# Begin Source File

SOURCE=.\Source\savers.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\source.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\svrmgr.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Source\audio.h
# End Source File
# Begin Source File

SOURCE=.\Source\dxaudio.h
# End Source File
# Begin Source File

SOURCE=.\Source\errlog.h
# End Source File
# Begin Source File

SOURCE=.\Source\main.h
# End Source File
# Begin Source File

SOURCE=.\Source\playback.h
# End Source File
# Begin Source File

SOURCE=.\Source\resource.h
# End Source File
# Begin Source File

SOURCE=.\Source\savers.h
# End Source File
# Begin Source File

SOURCE=.\Source\source.h
# End Source File
# Begin Source File

SOURCE=.\Source\svrmgr.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Source\asplogo.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\back1.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\back2.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\cards1.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\cards2.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\computer.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\folder.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\folderlt.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\icon1.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Source\psbuy.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\saver1.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\saver2.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\screen1.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\splash1.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\stars.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\stars2.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\up1.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\up2.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\wblogo2.bmp
# End Source File
# Begin Source File

SOURCE=.\Source\welcome.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\addsvr3.wav
# End Source File
# Begin Source File

SOURCE=.\Source\bomsnd4.wav
# End Source File
# Begin Source File

SOURCE=.\Source\clksnd4.wav
# End Source File
# Begin Source File

SOURCE=.\Source\clrsel2.wav
# End Source File
# Begin Source File

SOURCE=.\Source\newsel9.wav
# End Source File
# Begin Source File

SOURCE=.\Source\nullsnd.mp3
# End Source File
# Begin Source File

SOURCE=.\Source\ProSaver.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\Source\srtsnd6.wav
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\MSIMG32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\WINMM.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\VFW32.LIB"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\Microsoft Visual Studio\VC98\Lib\IMAGEHLP.LIB"
# End Source File
# Begin Source File

SOURCE=.\Source\htmlhelp\htmlhelp.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\DXSDK\lib\dxguid.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\DXSDK\lib\dsound.lib
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\DXSDK\lib\DxErr8.lib
# End Source File
# End Target
# End Project
