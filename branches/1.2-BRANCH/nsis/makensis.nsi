Name "Nullsoft Install System Development Kit"
OutFile nsis10h.exe
CRCCheck on
LicenseText "You must read the following license before installing."
LicenseData makensis-license.txt
ComponentText "This will install the Nullsoft Install System v1.0h on your computer."
InstType Normal
DirText "Please select a location to install NSIS (or use the default)."
UninstallText "This will uninstall NSIS from your system."
UninstallExeName uninst-nsis.exe

InstallDir $PROGRAMFILES\NSIS
InstallDirRegKey HKEY_LOCAL_MACHINE SOFTWARE\NSIS ""

Section "NSIS development files (required)"
SectionIn 1
SetOutPath $INSTDIR
File makensis.exe
File makensis.rtf

Section "Example NSI script files"
SectionIn 1
SetOutPath $INSTDIR
File spin.nsi
File makensis.nsi
File wafull.nsi

Section "Example License file"
SectionIn 1
SetOutPath $INSTDIR
File makensis-license.txt

Section "Example bitmaps and icons"
SectionIn 1
SetOutPath $INSTDIR
File bitmap1.bmp
File bitmap2.bmp
File main.ico
File uninst.ico

Section "NSI Development Shell Extensions"
SectionIn 1
WriteRegStr HKEY_CLASSES_ROOT ".nsi" "" "NSISFile"
WriteRegStr HKEY_CLASSES_ROOT "NSISFile" "" "NSI Script File"
WriteRegStr HKEY_CLASSES_ROOT "NSISFile\shell" "" "open"
WriteRegStr HKEY_CLASSES_ROOT "NSISFile\DefaultIcon" "" $INSTDIR\makensis.exe,0
WriteRegStr HKEY_CLASSES_ROOT "NSISFile\shell\open\command" "" 'notepad.exe "%1"'
WriteRegStr HKEY_CLASSES_ROOT "NSISFile\shell\compile" "" "Compile NSI"
WriteRegStr HKEY_CLASSES_ROOT "NSISFile\shell\compile\command" "" '"$INSTDIR\makensis.exe" "%1"'

Section "NSIS Complete Source Code"
SetOutPath $INSTDIR\Source\Makenssi
File Source\Makenssi\*.*
SetOutPath $INSTDIR\Source\Makenssi\zlib
File Source\Makenssi\zlib\*.*
SetOutPath $INSTDIR\Source\exehead
File Source\exehead\*.*
SetOutPath $INSTDIR\Source\exehead\zlib
File Source\exehead\zlib\*.*

Section -post
WriteRegStr HKEY_LOCAL_MACHINE SOFTWARE\NSIS "" $INSTDIR
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\NSIS" "DisplayName" "NSIS Development Kit (remove only)"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\NSIS" "UninstallString" '"$INSTDIR\uninst-nsis.exe"'
Exec '"write" "$INSTDIR\makensis.rtf"'
Exec '"explorer" "$INSTDIR\"'

Section Uninstall
DeleteRegKey HKEY_CLASSES_ROOT ".nsi"
DeleteRegKey HKEY_CLASSES_ROOT "NSISFile"
DeleteRegKey HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\NSIS"
DeleteRegKey HKEY_LOCAL_MACHINE SOFTWARE\NSIS
Delete $INSTDIR\makensis.exe
Delete $INSTDIR\makensis.rtf
Delete $INSTDIR\uninst-nsis.exe
Delete $INSTDIR\makensis.nsi
Delete $INSTDIR\spin.nsi
Delete $INSTDIR\wafull.nsi
Delete $INSTDIR\main.ico
Delete $INSTDIR\makensis-license.txt
Delete $INSTDIR\uninst.ico
Delete $INSTDIR\bitmap1.bmp
Delete $INSTDIR\bitmap2.bmp
Delete $INSTDIR\Source\Makenssi\zlib\*.*
Delete $INSTDIR\Source\Makenssi\*.*
Delete $INSTDIR\Source\exehead\zlib\*.*
Delete $INSTDIR\Source\exehead\*.*
RMDir $INSTDIR\Source\makenssi\zlib
RMDir $INSTDIR\Source\makenssi
RMDir $INSTDIR\Source\exehead\zlib
RMDir $INSTDIR\Source\exehead
RMDir $INSTDIR\Source
RMDir $INSTDIR
