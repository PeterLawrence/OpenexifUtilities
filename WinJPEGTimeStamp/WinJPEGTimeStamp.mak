# Microsoft Developer Studio Generated NMAKE File, Based on WinJPEGTimeStamp.dsp
!IF "$(CFG)" == ""
CFG=WinJPEGTimeStamp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WinJPEGTimeStamp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WinJPEGTimeStamp - Win32 Release" && "$(CFG)" != "WinJPEGTimeStamp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinJPEGTimeStamp.mak" CFG="WinJPEGTimeStamp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinJPEGTimeStamp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinJPEGTimeStamp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinJPEGTimeStamp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\WinJPEGTimeStamp.exe" "$(OUTDIR)\WinJPEGTimeStamp.bsc"


CLEAN :
	-@erase "$(INTDIR)\dlgtxtctrl.obj"
	-@erase "$(INTDIR)\dlgtxtctrl.sbr"
	-@erase "$(INTDIR)\ExifApp0Seg.obj"
	-@erase "$(INTDIR)\ExifApp0Seg.sbr"
	-@erase "$(INTDIR)\ExifAppSegManager.obj"
	-@erase "$(INTDIR)\ExifAppSegManager.sbr"
	-@erase "$(INTDIR)\ExifAppSegment.obj"
	-@erase "$(INTDIR)\ExifAppSegment.sbr"
	-@erase "$(INTDIR)\ExifFileIO.obj"
	-@erase "$(INTDIR)\ExifFileIO.sbr"
	-@erase "$(INTDIR)\ExifHuffmanTable.obj"
	-@erase "$(INTDIR)\ExifHuffmanTable.sbr"
	-@erase "$(INTDIR)\ExifIFD.obj"
	-@erase "$(INTDIR)\ExifIFD.sbr"
	-@erase "$(INTDIR)\ExifIJGWrapper.obj"
	-@erase "$(INTDIR)\ExifIJGWrapper.sbr"
	-@erase "$(INTDIR)\ExifIJGWriteFrame.obj"
	-@erase "$(INTDIR)\ExifIJGWriteFrame.sbr"
	-@erase "$(INTDIR)\ExifImageDescUtils.obj"
	-@erase "$(INTDIR)\ExifImageDescUtils.sbr"
	-@erase "$(INTDIR)\ExifImageFile.obj"
	-@erase "$(INTDIR)\ExifImageFile.sbr"
	-@erase "$(INTDIR)\ExifImageFileRead.obj"
	-@erase "$(INTDIR)\ExifImageFileRead.sbr"
	-@erase "$(INTDIR)\ExifImageFileWrite.obj"
	-@erase "$(INTDIR)\ExifImageFileWrite.sbr"
	-@erase "$(INTDIR)\ExifInternetIO.obj"
	-@erase "$(INTDIR)\ExifInternetIO.sbr"
	-@erase "$(INTDIR)\ExifIO.obj"
	-@erase "$(INTDIR)\ExifIO.sbr"
	-@erase "$(INTDIR)\ExifJpegDataDst.obj"
	-@erase "$(INTDIR)\ExifJpegDataDst.sbr"
	-@erase "$(INTDIR)\ExifJpegDataSrc.obj"
	-@erase "$(INTDIR)\ExifJpegDataSrc.sbr"
	-@erase "$(INTDIR)\ExifJpegImage.obj"
	-@erase "$(INTDIR)\ExifJpegImage.sbr"
	-@erase "$(INTDIR)\ExifMemoryIO.obj"
	-@erase "$(INTDIR)\ExifMemoryIO.sbr"
	-@erase "$(INTDIR)\ExifMisc.obj"
	-@erase "$(INTDIR)\ExifMisc.sbr"
	-@erase "$(INTDIR)\ExifOpenFile.obj"
	-@erase "$(INTDIR)\ExifOpenFile.sbr"
	-@erase "$(INTDIR)\ExifRawAppSeg.obj"
	-@erase "$(INTDIR)\ExifRawAppSeg.sbr"
	-@erase "$(INTDIR)\ExifStripImage.obj"
	-@erase "$(INTDIR)\ExifStripImage.sbr"
	-@erase "$(INTDIR)\ExifTiffAppSeg.obj"
	-@erase "$(INTDIR)\ExifTiffAppSeg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinJPEGTimeStamp.obj"
	-@erase "$(INTDIR)\WinJPEGTimeStamp.res"
	-@erase "$(INTDIR)\WinJPEGTimeStamp.sbr"
	-@erase "$(OUTDIR)\WinJPEGTimeStamp.bsc"
	-@erase "$(OUTDIR)\WinJPEGTimeStamp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /I "F:\Direct X Work\jpeg\jpeg-6b" /I "F:\Direct X Work\jpeg\openexif-2_0_1-src\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\WinJPEGTimeStamp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WinJPEGTimeStamp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dlgtxtctrl.sbr" \
	"$(INTDIR)\WinJPEGTimeStamp.sbr" \
	"$(INTDIR)\ExifApp0Seg.sbr" \
	"$(INTDIR)\ExifAppSegManager.sbr" \
	"$(INTDIR)\ExifAppSegment.sbr" \
	"$(INTDIR)\ExifFileIO.sbr" \
	"$(INTDIR)\ExifHuffmanTable.sbr" \
	"$(INTDIR)\ExifIFD.sbr" \
	"$(INTDIR)\ExifIJGWrapper.sbr" \
	"$(INTDIR)\ExifIJGWriteFrame.sbr" \
	"$(INTDIR)\ExifImageDescUtils.sbr" \
	"$(INTDIR)\ExifImageFile.sbr" \
	"$(INTDIR)\ExifImageFileRead.sbr" \
	"$(INTDIR)\ExifImageFileWrite.sbr" \
	"$(INTDIR)\ExifInternetIO.sbr" \
	"$(INTDIR)\ExifIO.sbr" \
	"$(INTDIR)\ExifJpegDataDst.sbr" \
	"$(INTDIR)\ExifJpegDataSrc.sbr" \
	"$(INTDIR)\ExifJpegImage.sbr" \
	"$(INTDIR)\ExifMemoryIO.sbr" \
	"$(INTDIR)\ExifMisc.sbr" \
	"$(INTDIR)\ExifOpenFile.sbr" \
	"$(INTDIR)\ExifRawAppSeg.sbr" \
	"$(INTDIR)\ExifStripImage.sbr" \
	"$(INTDIR)\ExifTiffAppSeg.sbr"

"$(OUTDIR)\WinJPEGTimeStamp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib jpeg.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\WinJPEGTimeStamp.pdb" /machine:I386 /out:"$(OUTDIR)\WinJPEGTimeStamp.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dlgtxtctrl.obj" \
	"$(INTDIR)\WinJPEGTimeStamp.obj" \
	"$(INTDIR)\ExifApp0Seg.obj" \
	"$(INTDIR)\ExifAppSegManager.obj" \
	"$(INTDIR)\ExifAppSegment.obj" \
	"$(INTDIR)\ExifFileIO.obj" \
	"$(INTDIR)\ExifHuffmanTable.obj" \
	"$(INTDIR)\ExifIFD.obj" \
	"$(INTDIR)\ExifIJGWrapper.obj" \
	"$(INTDIR)\ExifIJGWriteFrame.obj" \
	"$(INTDIR)\ExifImageDescUtils.obj" \
	"$(INTDIR)\ExifImageFile.obj" \
	"$(INTDIR)\ExifImageFileRead.obj" \
	"$(INTDIR)\ExifImageFileWrite.obj" \
	"$(INTDIR)\ExifInternetIO.obj" \
	"$(INTDIR)\ExifIO.obj" \
	"$(INTDIR)\ExifJpegDataDst.obj" \
	"$(INTDIR)\ExifJpegDataSrc.obj" \
	"$(INTDIR)\ExifJpegImage.obj" \
	"$(INTDIR)\ExifMemoryIO.obj" \
	"$(INTDIR)\ExifMisc.obj" \
	"$(INTDIR)\ExifOpenFile.obj" \
	"$(INTDIR)\ExifRawAppSeg.obj" \
	"$(INTDIR)\ExifStripImage.obj" \
	"$(INTDIR)\ExifTiffAppSeg.obj" \
	"$(INTDIR)\WinJPEGTimeStamp.res"

"$(OUTDIR)\WinJPEGTimeStamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WinJPEGTimeStamp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\WinJPEGTimeStamp.exe" "$(OUTDIR)\WinJPEGTimeStamp.bsc"


CLEAN :
	-@erase "$(INTDIR)\dlgtxtctrl.obj"
	-@erase "$(INTDIR)\dlgtxtctrl.sbr"
	-@erase "$(INTDIR)\ExifApp0Seg.obj"
	-@erase "$(INTDIR)\ExifApp0Seg.sbr"
	-@erase "$(INTDIR)\ExifAppSegManager.obj"
	-@erase "$(INTDIR)\ExifAppSegManager.sbr"
	-@erase "$(INTDIR)\ExifAppSegment.obj"
	-@erase "$(INTDIR)\ExifAppSegment.sbr"
	-@erase "$(INTDIR)\ExifFileIO.obj"
	-@erase "$(INTDIR)\ExifFileIO.sbr"
	-@erase "$(INTDIR)\ExifHuffmanTable.obj"
	-@erase "$(INTDIR)\ExifHuffmanTable.sbr"
	-@erase "$(INTDIR)\ExifIFD.obj"
	-@erase "$(INTDIR)\ExifIFD.sbr"
	-@erase "$(INTDIR)\ExifIJGWrapper.obj"
	-@erase "$(INTDIR)\ExifIJGWrapper.sbr"
	-@erase "$(INTDIR)\ExifIJGWriteFrame.obj"
	-@erase "$(INTDIR)\ExifIJGWriteFrame.sbr"
	-@erase "$(INTDIR)\ExifImageDescUtils.obj"
	-@erase "$(INTDIR)\ExifImageDescUtils.sbr"
	-@erase "$(INTDIR)\ExifImageFile.obj"
	-@erase "$(INTDIR)\ExifImageFile.sbr"
	-@erase "$(INTDIR)\ExifImageFileRead.obj"
	-@erase "$(INTDIR)\ExifImageFileRead.sbr"
	-@erase "$(INTDIR)\ExifImageFileWrite.obj"
	-@erase "$(INTDIR)\ExifImageFileWrite.sbr"
	-@erase "$(INTDIR)\ExifInternetIO.obj"
	-@erase "$(INTDIR)\ExifInternetIO.sbr"
	-@erase "$(INTDIR)\ExifIO.obj"
	-@erase "$(INTDIR)\ExifIO.sbr"
	-@erase "$(INTDIR)\ExifJpegDataDst.obj"
	-@erase "$(INTDIR)\ExifJpegDataDst.sbr"
	-@erase "$(INTDIR)\ExifJpegDataSrc.obj"
	-@erase "$(INTDIR)\ExifJpegDataSrc.sbr"
	-@erase "$(INTDIR)\ExifJpegImage.obj"
	-@erase "$(INTDIR)\ExifJpegImage.sbr"
	-@erase "$(INTDIR)\ExifMemoryIO.obj"
	-@erase "$(INTDIR)\ExifMemoryIO.sbr"
	-@erase "$(INTDIR)\ExifMisc.obj"
	-@erase "$(INTDIR)\ExifMisc.sbr"
	-@erase "$(INTDIR)\ExifOpenFile.obj"
	-@erase "$(INTDIR)\ExifOpenFile.sbr"
	-@erase "$(INTDIR)\ExifRawAppSeg.obj"
	-@erase "$(INTDIR)\ExifRawAppSeg.sbr"
	-@erase "$(INTDIR)\ExifStripImage.obj"
	-@erase "$(INTDIR)\ExifStripImage.sbr"
	-@erase "$(INTDIR)\ExifTiffAppSeg.obj"
	-@erase "$(INTDIR)\ExifTiffAppSeg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WinJPEGTimeStamp.obj"
	-@erase "$(INTDIR)\WinJPEGTimeStamp.res"
	-@erase "$(INTDIR)\WinJPEGTimeStamp.sbr"
	-@erase "$(OUTDIR)\WinJPEGTimeStamp.bsc"
	-@erase "$(OUTDIR)\WinJPEGTimeStamp.exe"
	-@erase "$(OUTDIR)\WinJPEGTimeStamp.ilk"
	-@erase "$(OUTDIR)\WinJPEGTimeStamp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I "F:\Direct X Work\jpeg\jpeg-6b" /I "F:\Direct X Work\jpeg\openexif-2_0_1-src\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\WinJPEGTimeStamp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WinJPEGTimeStamp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dlgtxtctrl.sbr" \
	"$(INTDIR)\WinJPEGTimeStamp.sbr" \
	"$(INTDIR)\ExifApp0Seg.sbr" \
	"$(INTDIR)\ExifAppSegManager.sbr" \
	"$(INTDIR)\ExifAppSegment.sbr" \
	"$(INTDIR)\ExifFileIO.sbr" \
	"$(INTDIR)\ExifHuffmanTable.sbr" \
	"$(INTDIR)\ExifIFD.sbr" \
	"$(INTDIR)\ExifIJGWrapper.sbr" \
	"$(INTDIR)\ExifIJGWriteFrame.sbr" \
	"$(INTDIR)\ExifImageDescUtils.sbr" \
	"$(INTDIR)\ExifImageFile.sbr" \
	"$(INTDIR)\ExifImageFileRead.sbr" \
	"$(INTDIR)\ExifImageFileWrite.sbr" \
	"$(INTDIR)\ExifInternetIO.sbr" \
	"$(INTDIR)\ExifIO.sbr" \
	"$(INTDIR)\ExifJpegDataDst.sbr" \
	"$(INTDIR)\ExifJpegDataSrc.sbr" \
	"$(INTDIR)\ExifJpegImage.sbr" \
	"$(INTDIR)\ExifMemoryIO.sbr" \
	"$(INTDIR)\ExifMisc.sbr" \
	"$(INTDIR)\ExifOpenFile.sbr" \
	"$(INTDIR)\ExifRawAppSeg.sbr" \
	"$(INTDIR)\ExifStripImage.sbr" \
	"$(INTDIR)\ExifTiffAppSeg.sbr"

"$(OUTDIR)\WinJPEGTimeStamp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib jpeg.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\WinJPEGTimeStamp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\WinJPEGTimeStamp.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dlgtxtctrl.obj" \
	"$(INTDIR)\WinJPEGTimeStamp.obj" \
	"$(INTDIR)\ExifApp0Seg.obj" \
	"$(INTDIR)\ExifAppSegManager.obj" \
	"$(INTDIR)\ExifAppSegment.obj" \
	"$(INTDIR)\ExifFileIO.obj" \
	"$(INTDIR)\ExifHuffmanTable.obj" \
	"$(INTDIR)\ExifIFD.obj" \
	"$(INTDIR)\ExifIJGWrapper.obj" \
	"$(INTDIR)\ExifIJGWriteFrame.obj" \
	"$(INTDIR)\ExifImageDescUtils.obj" \
	"$(INTDIR)\ExifImageFile.obj" \
	"$(INTDIR)\ExifImageFileRead.obj" \
	"$(INTDIR)\ExifImageFileWrite.obj" \
	"$(INTDIR)\ExifInternetIO.obj" \
	"$(INTDIR)\ExifIO.obj" \
	"$(INTDIR)\ExifJpegDataDst.obj" \
	"$(INTDIR)\ExifJpegDataSrc.obj" \
	"$(INTDIR)\ExifJpegImage.obj" \
	"$(INTDIR)\ExifMemoryIO.obj" \
	"$(INTDIR)\ExifMisc.obj" \
	"$(INTDIR)\ExifOpenFile.obj" \
	"$(INTDIR)\ExifRawAppSeg.obj" \
	"$(INTDIR)\ExifStripImage.obj" \
	"$(INTDIR)\ExifTiffAppSeg.obj" \
	"$(INTDIR)\WinJPEGTimeStamp.res"

"$(OUTDIR)\WinJPEGTimeStamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WinJPEGTimeStamp.dep")
!INCLUDE "WinJPEGTimeStamp.dep"
!ELSE 
!MESSAGE Warning: cannot find "WinJPEGTimeStamp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WinJPEGTimeStamp - Win32 Release" || "$(CFG)" == "WinJPEGTimeStamp - Win32 Debug"
SOURCE=.\dlgtxtctrl.cpp

"$(INTDIR)\dlgtxtctrl.obj"	"$(INTDIR)\dlgtxtctrl.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WinJPEGTimeStamp.cpp

"$(INTDIR)\WinJPEGTimeStamp.obj"	"$(INTDIR)\WinJPEGTimeStamp.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WinJPEGTimeStamp.rc

"$(INTDIR)\WinJPEGTimeStamp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifApp0Seg.cpp"

"$(INTDIR)\ExifApp0Seg.obj"	"$(INTDIR)\ExifApp0Seg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifAppSegManager.cpp"

"$(INTDIR)\ExifAppSegManager.obj"	"$(INTDIR)\ExifAppSegManager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifAppSegment.cpp"

"$(INTDIR)\ExifAppSegment.obj"	"$(INTDIR)\ExifAppSegment.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifFileIO.cpp"

"$(INTDIR)\ExifFileIO.obj"	"$(INTDIR)\ExifFileIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifHuffmanTable.cpp"

"$(INTDIR)\ExifHuffmanTable.obj"	"$(INTDIR)\ExifHuffmanTable.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifIFD.cpp"

"$(INTDIR)\ExifIFD.obj"	"$(INTDIR)\ExifIFD.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifIJGWrapper.cpp"

"$(INTDIR)\ExifIJGWrapper.obj"	"$(INTDIR)\ExifIJGWrapper.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifIJGWriteFrame.c"

"$(INTDIR)\ExifIJGWriteFrame.obj"	"$(INTDIR)\ExifIJGWriteFrame.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifImageDescUtils.cpp"

"$(INTDIR)\ExifImageDescUtils.obj"	"$(INTDIR)\ExifImageDescUtils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifImageFile.cpp"

"$(INTDIR)\ExifImageFile.obj"	"$(INTDIR)\ExifImageFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifImageFileRead.cpp"

"$(INTDIR)\ExifImageFileRead.obj"	"$(INTDIR)\ExifImageFileRead.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifImageFileWrite.cpp"

"$(INTDIR)\ExifImageFileWrite.obj"	"$(INTDIR)\ExifImageFileWrite.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifInternetIO.cpp"

"$(INTDIR)\ExifInternetIO.obj"	"$(INTDIR)\ExifInternetIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifIO.cpp"

"$(INTDIR)\ExifIO.obj"	"$(INTDIR)\ExifIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifJpegDataDst.cpp"

"$(INTDIR)\ExifJpegDataDst.obj"	"$(INTDIR)\ExifJpegDataDst.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifJpegDataSrc.cpp"

"$(INTDIR)\ExifJpegDataSrc.obj"	"$(INTDIR)\ExifJpegDataSrc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifJpegImage.cpp"

"$(INTDIR)\ExifJpegImage.obj"	"$(INTDIR)\ExifJpegImage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifMemoryIO.cpp"

"$(INTDIR)\ExifMemoryIO.obj"	"$(INTDIR)\ExifMemoryIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifMisc.cpp"

"$(INTDIR)\ExifMisc.obj"	"$(INTDIR)\ExifMisc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifOpenFile.cpp"

"$(INTDIR)\ExifOpenFile.obj"	"$(INTDIR)\ExifOpenFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifRawAppSeg.cpp"

"$(INTDIR)\ExifRawAppSeg.obj"	"$(INTDIR)\ExifRawAppSeg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifStripImage.cpp"

"$(INTDIR)\ExifStripImage.obj"	"$(INTDIR)\ExifStripImage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifTiffAppSeg.cpp"

"$(INTDIR)\ExifTiffAppSeg.obj"	"$(INTDIR)\ExifTiffAppSeg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

