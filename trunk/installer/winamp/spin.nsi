Name "Spinner Plus"
LicenseText "Please read and agree to this license before continuing."
LicenseData license.txt
ComponentText "This will install Spinner Plus 3.0 on your system. Select which options you want set up."
DirText "Select a directory to install Spinner Plus in."
UninstallText "This will uninstall Spinner Plus. Hit Next to uninstall, or Cancel to cancel."
UninstallExeName uninstall-spinner.exe
OutFile spinplus.exe
Icon icon.ico
EnabledBitmap bitmap1.bmp
DisabledBitmap bitmap2.bmp
InstType Typical

InstallDir "$PROGRAMFILES\Spinner Plus"
InstallDirRegKey HKEY_LOCAL_MACHINE "Software\Spinner Plus" "instpath"
SetOverwrite on

Section "Spinner Plus 3.0 (required)"
FindWindow prompt "SpinnerWClass" "Spinner Plus is currently running. Please close before installing."
SetOutPath $INSTDIR\Program
File Program\*.*
SetOutPath $INSTDIR\Program\Res\3.0_maxi_player
File Program\Res\3.0_maxi_player\*.*
SetOutPath $INSTDIR\Program\Res\3.0_toolbar_player
File Program\Res\3.0_toolbar_player\*.*
SetOutPath $INSTDIR\Program\Res\prefsart
File Program\Res\prefsart\*.*
WriteRegDword HKEY_CURRENT_USER "Software\Spinner Plus\spinner" "Registered" 0
WriteRegStr HKEY_CURRENT_USER "Software\Spinner Plus\spinner\Options" "SpinnerInstallSuccessful" "1"
WriteRegStr HKEY_CURRENT_USER "Software\Spinner Plus\spinner\Options" "application/vnd.spinnerplus" "$INSTDIR\Program\spinner.exe"
WriteRegStr HKEY_CLASSES_ROOT ".spn" "" "spnFile"
WriteRegStr HKEY_CLASSES_ROOT ".spn" "Content Type" "application/vnd.spinnerplus"
WriteRegStr HKEY_CLASSES_ROOT "spnFile" "" "spnFile"
WriteRegBin HKEY_CLASSES_ROOT "spnFile" "EditFlags" 00000100
WriteRegStr HKEY_CLASSES_ROOT "spnFile\Shell\open\command" "" '"$INSTDIR\Program\spinner.exe" %1'
WriteRegStr HKEY_CURRENT_USER "Software\Netscape\Netscape Navigator\Viewers" "application/vnd.spinnerplus" "$INSTDIR\Program\spinner.exe"

WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Spinner Plus 3.0" "DisplayName" "Spinner Plus (remove only)"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Spinner Plus 3.0" "UninstallString" '"$INSTDIR\uninstall-spinner.EXE"'
WriteRegStr HKEY_LOCAL_MACHINE "Software\Spinner Plus" "instpath" $INSTDIR

Section "Start Menu and Desktop Icons"
SectionIn 1
CreateShortCut "$DESKTOP\Spinner Plus.lnk" "$INSTDIR\Program\spinner.exe" "" "" 0
CreateShortCut "$STARTMENU\Programs\Spinner Plus.lnk" "$INSTDIR\Program\spinner.exe" "" "" 0
CreateShortCut "$QUICKLAUNCH\Spinner Plus.lnk" "$INSTDIR\Program\spinner.exe" "" "" 0

Section "Launch Spinner Plus"
SectionIn 1
Exec '"$INSTDIR\Program\spinner.exe"'

Section "Launch Spinner Plus on Startup"
WriteRegStr HKEY_CURRENT_USER "Software\Microsoft\Windows\CurrentVersion\Run" "Spinner Plus" '"$INSTDIR\Program\spinner.exe"'


Section "View Readme.txt"
Exec '"$WINDIR\notepad.exe" "$INSTDIR\Program\spinner-readme.txt"'

Section Uninstall
DeleteRegKey HKEY_CURRENT_USER "Software\Spinner Plus"
DeleteRegKey HKEY_CLASSES_ROOT "spnFile"
DeleteRegKey HKEY_CLASSES_ROOT ".spn"
DeleteRegValue HKEY_CURRENT_USER "Software\Netscape\Netscape Navigator\Viewers" "application/vnd.spinnerplus"
DeleteRegValue HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Spinner Plus 3.0" "UninstallString"
DeleteRegValue HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Spinner Plus 3.0" "DisplayName"
DeleteRegKey HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Spinner Plus 3.0"
DeleteRegValue HKEY_CURRENT_USER "Software\Microsoft\Windows\CurrentVersion\Run" "Spinner Plus"

Delete $INSTDIR\Program\Res\3.0_maxi_player\*.*
RMDir $INSTDIR\Program\Res\3.0_maxi_player
Delete $INSTDIR\Program\Res\3.0_toolbar_player\*.*
RMDir $INSTDIR\Program\Res\3.0_toolbar_player
Delete $INSTDIR\Program\Res\prefsart\*.*
RMDir $INSTDIR\Program\Res\prefsart

RMDir $INSTDIR\Program\Res
Delete $INSTDIR\Program\*.*
RMDir $INSTDIR\Program
Delete $INSTDIR\*.*
RMDir $INSTDIR

Delete "$STARTMENU\Programs\spinner plus.lnk"
Delete "$DESKTOP\spinner plus.lnk"
Delete "$QUICKLAUNCH\spinner plus.lnk"
