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
File libgcc_s_dw2-1.dll
File libstdc++-6.dll
File libwinpthread-1.dll
File Qt5Cored.dll
File Qt5Guid.dll
File Qt5Widgetsd.dll

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
Delete $INSTDIR\libgcc_s_dw2-1.dll
Delete $INSTDIR\libstdc++-6.dll
Delete $INSTDIR\libwinpthread-1.dll
Delete $INSTDIR\Qt5Cored.dll
Delete $INSTDIR\Qt5Guid.dll
Delete $INSTDIR\Qt5Widgetsd.dll

RMDir $INSTDIR

Delete "$SMPROGRAMS\MarkTaylor\PCBHelper.lnk"
RMDir "$SMPROGRAMS\MarkTaylor"

SectionEnd
