# Microsoft Developer Studio Project File - Name="izfree" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=izfree - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "izfree.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "izfree.mak" CFG="izfree - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "izfree - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "izfree - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "izfree - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "izfree - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "izfree - Win32 Release"
# Name "izfree - Win32 Debug"
# Begin Source File

SOURCE=.\izfree.hhp

!IF  "$(CFG)" == "izfree - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__IZFRE="izfree.hhc"	
# Begin Custom Build
InputPath=.\izfree.hhp

"izfree.chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"c:\program files\html help workshop\hhc" $(InputPath) 
	echo done. 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "izfree - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__IZFRE="izfree.hhc"	
# Begin Custom Build
InputPath=.\izfree.hhp

"izfree.chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"c:\program files\html help workshop\hhc" $(InputPath) 
	echo done. 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
