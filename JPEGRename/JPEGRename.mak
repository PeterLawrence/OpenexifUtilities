# Microsoft Developer Studio Generated NMAKE File, Based on JPEGRename.dsp
!IF "$(CFG)" == ""
CFG=JPEGRename - Win32 Debug
!MESSAGE No configuration specified. Defaulting to JPEGRename - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "JPEGRename - Win32 Release" && "$(CFG)" != "JPEGRename - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JPEGRename.mak" CFG="JPEGRename - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JPEGRename - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "JPEGRename - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "JPEGRename - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\JPEGRename.exe"


CLEAN :
	-@erase "$(INTDIR)\dlgtxtctrl.obj"
	-@erase "$(INTDIR)\ExifApp0Seg.obj"
	-@erase "$(INTDIR)\ExifAppSegManager.obj"
	-@erase "$(INTDIR)\ExifAppSegment.obj"
	-@erase "$(INTDIR)\ExifFileIO.obj"
	-@erase "$(INTDIR)\ExifHuffmanTable.obj"
	-@erase "$(INTDIR)\ExifIFD.obj"
	-@erase "$(INTDIR)\ExifIJGWrapper.obj"
	-@erase "$(INTDIR)\ExifIJGWriteFrame.obj"
	-@erase "$(INTDIR)\ExifImageDescUtils.obj"
	-@erase "$(INTDIR)\ExifImageFile.obj"
	-@erase "$(INTDIR)\ExifImageFileRead.obj"
	-@erase "$(INTDIR)\ExifImageFileWrite.obj"
	-@erase "$(INTDIR)\ExifInternetIO.obj"
	-@erase "$(INTDIR)\ExifIO.obj"
	-@erase "$(INTDIR)\ExifJpegDataDst.obj"
	-@erase "$(INTDIR)\ExifJpegDataSrc.obj"
	-@erase "$(INTDIR)\ExifJpegImage.obj"
	-@erase "$(INTDIR)\ExifMemoryIO.obj"
	-@erase "$(INTDIR)\ExifMisc.obj"
	-@erase "$(INTDIR)\ExifOpenFile.obj"
	-@erase "$(INTDIR)\ExifRawAppSeg.obj"
	-@erase "$(INTDIR)\ExifStripImage.obj"
	-@erase "$(INTDIR)\ExifTiffAppSeg.obj"
	-@erase "$(INTDIR)\JPEGRename.obj"
	-@erase "$(INTDIR)\JPEGRename.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\JPEGRename.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GR /GX /O2 /I "F:\Direct X Work\jpeg\jpeg-6b" /I "F:\Direct X Work\jpeg\openexif-2_0_1-src\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\JPEGRename.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\JPEGRename.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib jpeg.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\JPEGRename.pdb" /machine:I386 /out:"$(OUTDIR)\JPEGRename.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dlgtxtctrl.obj" \
	"$(INTDIR)\JPEGRename.obj" \
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
	"$(INTDIR)\JPEGRename.res"

"$(OUTDIR)\JPEGRename.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\JPEGRename.exe" "$(OUTDIR)\JPEGRename.bsc"


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
	-@erase "$(INTDIR)\JPEGRename.obj"
	-@erase "$(INTDIR)\JPEGRename.res"
	-@erase "$(INTDIR)\JPEGRename.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\JPEGRename.bsc"
	-@erase "$(OUTDIR)\JPEGRename.exe"
	-@erase "$(OUTDIR)\JPEGRename.ilk"
	-@erase "$(OUTDIR)\JPEGRename.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GR /GX /ZI /Od /I "F:\Direct X Work\jpeg\jpeg-6b" /I "F:\Direct X Work\jpeg\openexif-2_0_1-src\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\JPEGRename.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\JPEGRename.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dlgtxtctrl.sbr" \
	"$(INTDIR)\JPEGRename.sbr" \
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

"$(OUTDIR)\JPEGRename.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib jpeg.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\JPEGRename.pdb" /debug /machine:I386 /out:"$(OUTDIR)\JPEGRename.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dlgtxtctrl.obj" \
	"$(INTDIR)\JPEGRename.obj" \
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
	"$(INTDIR)\JPEGRename.res"

"$(OUTDIR)\JPEGRename.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("JPEGRename.dep")
!INCLUDE "JPEGRename.dep"
!ELSE 
!MESSAGE Warning: cannot find "JPEGRename.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "JPEGRename - Win32 Release" || "$(CFG)" == "JPEGRename - Win32 Debug"
SOURCE=.\dlgtxtctrl.cpp

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\dlgtxtctrl.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\dlgtxtctrl.obj"	"$(INTDIR)\dlgtxtctrl.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\JPEGRename.cpp

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\JPEGRename.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\JPEGRename.obj"	"$(INTDIR)\JPEGRename.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\JPEGRename.rc

"$(INTDIR)\JPEGRename.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifApp0Seg.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifApp0Seg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifApp0Seg.obj"	"$(INTDIR)\ExifApp0Seg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifAppSegManager.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifAppSegManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifAppSegManager.obj"	"$(INTDIR)\ExifAppSegManager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifAppSegment.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifAppSegment.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifAppSegment.obj"	"$(INTDIR)\ExifAppSegment.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifFileIO.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifFileIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifFileIO.obj"	"$(INTDIR)\ExifFileIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifHuffmanTable.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifHuffmanTable.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifHuffmanTable.obj"	"$(INTDIR)\ExifHuffmanTable.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifIFD.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifIFD.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifIFD.obj"	"$(INTDIR)\ExifIFD.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifIJGWrapper.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifIJGWrapper.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifIJGWrapper.obj"	"$(INTDIR)\ExifIJGWrapper.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifIJGWriteFrame.c"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifIJGWriteFrame.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifIJGWriteFrame.obj"	"$(INTDIR)\ExifIJGWriteFrame.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifImageDescUtils.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifImageDescUtils.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifImageDescUtils.obj"	"$(INTDIR)\ExifImageDescUtils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifImageFile.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifImageFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifImageFile.obj"	"$(INTDIR)\ExifImageFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifImageFileRead.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifImageFileRead.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifImageFileRead.obj"	"$(INTDIR)\ExifImageFileRead.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifImageFileWrite.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifImageFileWrite.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifImageFileWrite.obj"	"$(INTDIR)\ExifImageFileWrite.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifInternetIO.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifInternetIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifInternetIO.obj"	"$(INTDIR)\ExifInternetIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifIO.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifIO.obj"	"$(INTDIR)\ExifIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifJpegDataDst.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifJpegDataDst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifJpegDataDst.obj"	"$(INTDIR)\ExifJpegDataDst.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifJpegDataSrc.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifJpegDataSrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifJpegDataSrc.obj"	"$(INTDIR)\ExifJpegDataSrc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifJpegImage.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifJpegImage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifJpegImage.obj"	"$(INTDIR)\ExifJpegImage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifMemoryIO.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifMemoryIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifMemoryIO.obj"	"$(INTDIR)\ExifMemoryIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifMisc.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifMisc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifMisc.obj"	"$(INTDIR)\ExifMisc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifOpenFile.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifOpenFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifOpenFile.obj"	"$(INTDIR)\ExifOpenFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifRawAppSeg.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifRawAppSeg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifRawAppSeg.obj"	"$(INTDIR)\ExifRawAppSeg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifStripImage.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifStripImage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifStripImage.obj"	"$(INTDIR)\ExifStripImage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE="..\..\jpeg\openexif-2_0_1-src\src\ExifTiffAppSeg.cpp"

!IF  "$(CFG)" == "JPEGRename - Win32 Release"


"$(INTDIR)\ExifTiffAppSeg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "JPEGRename - Win32 Debug"


"$(INTDIR)\ExifTiffAppSeg.obj"	"$(INTDIR)\ExifTiffAppSeg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

