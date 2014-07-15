# Microsoft Developer Studio Project File - Name="WInJPEGDateCopy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WInJPEGDateCopy - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WInJPEGDateCopy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WInJPEGDateCopy.mak" CFG="WInJPEGDateCopy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WInJPEGDateCopy - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WInJPEGDateCopy - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WInJPEGDateCopy - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "..\openexif-2_1_4-src\src" /I "..\openexif-2_1_4-src\src\OpenExifJpeg" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "WInJPEGDateCopy - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "..\openexif-2_1_4-src\src" /I "..\openexif-2_1_4-src\src\OpenExifJpeg" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WInJPEGDateCopy - Win32 Release"
# Name "WInJPEGDateCopy - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dlgtxtctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\WInJPEGDateCopy.cpp
# End Source File
# Begin Source File

SOURCE=.\WInJPEGDateCopy.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dlgtxtctrl.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\small.ico
# End Source File
# Begin Source File

SOURCE=.\TimeStampWin.ICO
# End Source File
# Begin Source File

SOURCE=.\WInJPEGDateCopy.ico
# End Source File
# End Group
# Begin Group "OpenExiffile"

# PROP Default_Filter ""
# Begin Group "OpenExifJpeg"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcapimin.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcapistd.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jccoefct.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jccolor.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcdctmgr.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jchuff.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jchuff.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcinit.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcmainct.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcmarker.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcmaster.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcomapi.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jconfig.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcparam.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcphuff.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcprepct.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jcsample.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdapimin.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdapistd.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdatadst.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdatasrc.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdcoefct.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdcolor.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdct.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jddctmgr.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdhuff.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdhuff.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdinput.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdmainct.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdmarker.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdmaster.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdmerge.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdphuff.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdpostct.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jdsample.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jerror.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jerror.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jfdctflt.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jfdctfst.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jfdctint.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jidctflt.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jidctfst.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jidctint.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jidctred.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jinclude.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jmemansi.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jmemmgr.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jmemsys.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jmorecfg.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jpegint.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jquant1.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jquant2.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jutils.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExif_jversion.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\OpenExifJpeg\OpenExifJpegLib.h"
# End Source File
# End Group
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifApp0Seg.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifApp0Seg.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifAppSegManager.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifAppSegManager.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifAppSegment.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifAppSegment.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifComMarker.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifComp.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifConf.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifDefs.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifErrorCodes.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifFileIO.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifFileIO.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifHuffmanTable.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifHuffmanTable.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifIFD.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifIFD.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifIJGWrapper.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifIJGWrapper.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifIJGWriteFrame.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifIJGWriteFrame.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifImageDescUtils.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifImageDescUtils.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifImageFile.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifImageFile.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifImageFileIO.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifImageFileRead.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifImageFileWrite.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifInternetIO.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifInternetIO.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifIO.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifIO.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifJpegDataDst.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifJpegDataSrc.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifJpegExtn.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifJpegImage.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifJpegImage.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifJpegTables.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifMemoryIO.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifMemoryIO.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifMisc.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifMisc.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifOpenFile.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifOpenFile.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifRawAppSeg.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifRawAppSeg.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifStripImage.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifStripImage.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifTagEntry.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifTags.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifTiffAppSeg.cpp"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifTiffAppSeg.h"
# End Source File
# Begin Source File

SOURCE="..\openexif-2_1_4-src\src\ExifTypeDefs.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
