  !include "MUI.nsh"

  Name "map3d"
  OutFile "map3d-win32-7.3.0a.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\map3d"

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\map3d" ""

;Pages

  ; installation pages
  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !define MUI_FINISHPAGE_RUN "$INSTDIR\map3d.exe"
  !insertmacro MUI_PAGE_FINISH
  
  ; uninstallation pages:
  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Install"

  SetOutPath "$INSTDIR"

  File release\map3d.exe

  ; basic data
  File /r /x .svn ..\data
  File /r /x .svn ..\geom 

  ; the QTDIR environment variable must be set - copy all required Qt dlls
  File $%QTDIR%\bin\Qt5Core.dll
  File $%QTDIR%\bin\Qt5Gui.dll
  File $%QTDIR%\bin\Qt5OpenGL.dll
  File $%QTDIR%\bin\Qt5Widgets.dll

  ; 5.4 needs these; 5.7 does not
  File $%QTDIR%\bin\icuin53.dll
  File $%QTDIR%\bin\icuuc53.dll
  File $%QTDIR%\bin\icudt53.dll

  ; Install Microsoft Runtime libraries
  ;File winfix\vcruntime140.DLL
  ;File winfix\msvcp140.DLL

  File winfix\MSVCR120.DLL
  File winfix\MSVCP120.DLL
  ;File winfix\32bit\MSVCR120.DLL
  ;File winfix\32bit\MSVCP120.DLL
  ;File winfix\32bit\MSVCR110.DLL
  ;File winfix\32bit\MSVCP110.DLL


  ; Qt interface to opengl functions, when using Qt OpenGL Dynamic - 5.7 junk
  ; File $%QTDIR%\bin\libEGL.dll
  ; File $%QTDIR%\bin\libGLESv2.dll
  ; File $%QTDIR%\bin\opengl32sw.dll

  ; Qt Dependencies for platforms
  CreateDirectory $INSTDIR\platforms
  SetOutPath $INSTDIR\platforms
  File $%QTDIR%\plugins\platforms\qwindows.dll
  SetOutPath $INSTDIR

  ;Store installation folder in the registry for the uninstaller to use:
  WriteRegStr HKCU "Software\map3d" "" $INSTDIR
  
  ;Create the uninstaller:
  WriteUninstaller "$INSTDIR\uninstall.exe"

  ;Create start menu shortcuts:
  SetOutPath "$INSTDIR" ; We have to set the OutPath back to the base install to get the shortcuts to have the right "Start in" property.
  CreateDirectory "$SMPROGRAMS\map3d"
  CreateShortCut "$SMPROGRAMS\map3d\map3d.lnk" "$INSTDIR\map3d.exe"
  CreateShortCut "$SMPROGRAMS\map3d\Uninstall map3d.lnk" "$INSTDIR\uninstall.exe"
  CreateShortCut "$SMPROGRAMS\map3d\Uninstall.lnk" "$INSTDIR\uninstall.exe"

  ;"Add/Remove Programs" entry
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\map3d" "DisplayName" "map3d"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\map3d" "UninstallString" "$INSTDIR\uninstall.exe"

SectionEnd


Section "Uninstall"

  ; Remove program executables:
  Delete "$INSTDIR\map3d.exe"
  Delete "$INSTDIR\uninstall.exe"

  ; dependent DLLs:
  Delete "$INSTDIR\*.dll"

  ; Potentially from previous installs
  RMDir /r "$INSTDIR\Microsoft.VC90.CRT"

  RMDir  "$INSTDIR"
  
  ; Remove the start menu and desktop shortcuts:
  Delete "$SMPROGRAMS\map3d\map3d.lnk"
  Delete "$SMPROGRAMS\map3d\Uninstall map3d.lnk"
  RMDir  "$SMPROGRAMS\map3d"

  ; Remove the registry key that stores our installation folder:
  DeleteRegKey /ifempty HKCU "Software\map3d"

  ; Remove the application from the "Add/Remove Programs" list:
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\map3d" \

SectionEnd

