; This script shows how to make your applicaton uninstallable 

;--------------------------------

; The name of the installer
Name "PCB Helper"

; The file to write
OutFile "setup.exe"

; The default installation directory
InstallDir $PROGRAMFILES\PCBHelper

; The text to prompt the user to enter a directory
DirText "This will install PCB Helper on your computer. Choose a directory"

;--------------------------------

; The stuff to install
Section "" ;No components page, name is not important

; Set output path to the installation directory.
SetOutPath $INSTDIR

; Put file there
File PCBHelper.exe

; Also get the Qt dependent DLLs
File D3Dcompiler_47.dll
File libEGL.dll
File libgcc_s_dw2-1.dll
File libGLESV2.dll
File libstdc++-6.dll
File libwinpthread-1.dll
File opengl32sw.dll
File Qt5Core.dll
File Qt5Gui.dll
File Qt5Svg.dll
File Qt5Widgets.dll
CreateDirectory "$INSTDIR\platforms"
SetOutPath "$INSTDIR\platforms"
File /r "platforms\"
SetOutPath $INSTDIR

; Create Start Menu Objects
CreateDirectory "$SMPROGRAMS\MarkTaylor"
CreateShortCut "$SMPROGRAMS\MarkTaylor\PCBHelper.lnk" "$INSTDIR\PCBHelper.exe"


; Tell the compiler to write an uninstaller and to look for a "Uninstall" section 
WriteUninstaller $INSTDIR\Uninstall.exe

SectionEnd ; end the section

; The uninstall section
Section "Uninstall"

Delete $INSTDIR\Uninstall.exe
Delete $INSTDIR\PCBHelper.exe

Delete $INSTDIR\D3Dcompiler_47.dll
Delete $INSTDIR\libEGL.dll
Delete $INSTDIR\libgcc_s_dw2-1.dll
Delete $INSTDIR\libGLESV2.dll
Delete $INSTDIR\libstdc++-6.dll
Delete $INSTDIR\libwinpthread-1.dll
Delete $INSTDIR\opengl32sw.dll
Delete $INSTDIR\Qt5Core.dll
Delete $INSTDIR\Qt5Gui.dll
Delete $INSTDIR\Qt5Svg.dll
Delete $INSTDIR\Qt5Widgets.dll
Delete $INSTDIR\platforms\qwindows.dll
RMDir $INSTDIR\platforms

RMDir $INSTDIR

Delete "$SMPROGRAMS\MarkTaylor\PCBHelper.lnk"
RMDir "$SMPROGRAMS\MarkTaylor"

SectionEnd
