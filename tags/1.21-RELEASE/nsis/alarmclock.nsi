Name "AlarmClock v1.2"
ComponentText "This will install Winamp AlarmClock v1.21 plugin (23.1.2004)"

CrcCheck on

DirText "This will install Winamp AlarmClock v1.21 plugin (23.1.2004)."
OutFile AlarmClock-1.21.exe

InstallDir $PROGRAMFILES\Winamp
SetOutPath $INSTDIR\Plugins

File ..\release\Gen_AlarmClock.dll
File ..\Alarmclock-README.txt

;Delete $INSTDIR\Plugins\alarmconfig.ini
Exec wait "Notepad.exe $INSTDIR\Plugins\Alarmclock-README.txt"

MessageBox  MB_OK "Install successfull!"

; end
