Name Winamp
ComponentText "This will install Winamp 2.63."
DirText "Setup has determined the optimal location to install. If you would like to change the directory, do so now."
LicenseText "Winamp is a freeware product. Please read the license terms below before installing."
LicenseData misc\license.txt
OutFile winamp263_new.exe
InstallDir $PROGRAMFILES\Winamp
EnabledBitmap checked.bmp
DisabledBitmap unchecked.bmp

InstType Standard
InstType Lite
InstType Minimal

Section "Winamp (required)"

FindWindow close WinampAgentMain ""
FindWindow prompt "Winamp v1.x" "Winamp is running. Please close Winamp and hit Retry, or hit Cancel to abort installation."

SetOutPath $INSTDIR
SetOverwrite off
File Winamp\winamp.m3u
SetOverwrite on
File Winamp\winamp.exe
File Winamp\demo.mp3
File Winamp\whatsnew.txt
File Winamp\winampa.exe
File Winamp\winampmb.htm
SetOutPath $INSTDIR\Skins
SetOutPath $INSTDIR\Plugins
File Winamp\plugins\in_mp3.dll
File Winamp\plugins\out_wave.dll

Section "Winamp Visualization Studio"
SectionIn 1
File Winamp\plugins\vis_avs.dll
SetOverwrite off
File Winamp\plugins\vis_avs.dat
SetOverwrite on
SetOutPath $INSTDIR\Plugins\avs
File Winamp\Plugins\avs\*.avs
File Winamp\Plugins\avs\fyrewurx.ape
SetOutPath $INSTDIR\Plugins\avs\justin
File Winamp\Plugins\avs\justin\*.avs
SetOutPath $INSTDIR\Plugins\avs\lone
File Winamp\Plugins\avs\lone\*.avs
SetOutPath $INSTDIR\Plugins
WriteINIStr $INSTDIR\Winamp.ini Winamp visplugin_name vis_avs.dll
WriteINIStr $INSTDIR\Winamp.ini Winamp visplugin_num 0

Section "Support for Windows Media Audio (WMA)"
SectionIn 1
SetOutPath $TEMP
File Misc\wmaudioredist.exe
Exec wait "$TEMP\wmaudioredist.exe /Q /R:N"
Delete $TEMP\wmaudioredist.exe
SetOutPath $INSTDIR\Plugins
File Winamp\plugins\in_wm.dll
File Winamp\plugins\out_wm.dll
; fuck wma. 

Section "Support for MJuice (MJF)"
SectionIn 1
File mjuice\in_mjf.dll
SetOutPath "$PROGRAMFILES\Mjuice Media Player"
File mjuice\mjuninst.exe
File mjuice\mjsecurity.exe
File mjuice\mjsecurityclient.dll
File mjuice\mjagent.exe
SetOutPath $SYSDIR
SetOverwrite off
File mjuice\atl.dll
SetOverwrite on
RegDLL $SYSDIR\atl.dll
RegDLL - $SYSDIR\audioexctl.dll
File mjuice\audioexctl.dll
RegDLL $SYSDIR\audioexctl.dll
InstNSPlug mjuice\npaxdlpi.dll
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\App Paths\MJAgent.exe" "" "$PROGRAMFILES\Mjuice Media Player\MJAgent.exe"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\App Paths\MJAgent.exe" "Path" "$PROGRAMFILES\Mjuice Media Player"
SetOutPath $INSTDIR\Plugins


Section "Support for Audiosoft (ASFS)"
SectionIn 1
RegDLL - $INSTDIR\Plugins\in_asfs.dll
File Winamp\plugins\in_asfs.dll
RegDLL $INSTDIR\Plugins\in_asfs.dll


Section "Support for WAV files"
SectionIn 12
File Winamp\plugins\in_wave.dll

Section "Support for CD audio"
SectionIn 12
File Winamp\plugins\in_cdda.dll

Section "Support for MOD/XM/IT files"
SectionIn 12
File Winamp\plugins\in_mod.dll
 
Section "Support for MIDI files"
SectionIn 12
File Winamp\plugins\in_midi.dll

Section "Support for writing WAV files"
SectionIn 12
File Winamp\plugins\out_disk.dll

Section "DirectSound output support"
SectionIn 12
File Winamp\plugins\out_ds.dll

Section -PostInstall
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Winamp" "DisplayName" "Winamp (remove only)"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Winamp" "UninstallString" '"$INSTDIR\Winamp.exe" /UNINSTALL'
Exec "$INSTDIR\Winamp.exe /INSTALL"
