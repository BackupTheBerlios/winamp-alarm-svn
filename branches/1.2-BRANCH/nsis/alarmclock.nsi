Name "AlarmClock v1.22-dev"
ComponentText "This will install Winamp AlarmClock plugin version v1.22dev-20050220"

CrcCheck on

DirText "This will install Winamp AlarmClock plugin version v1.22dev-20050220"
OutFile AlarmClock-1.22dev-20050220.exe

InstallDir $PROGRAMFILES\Winamp
SetOutPath $INSTDIR\Plugins

File ..\release\Gen_AlarmClock.dll
File ..\Alarmclock-README.txt

;Delete $INSTDIR\Plugins\alarmconfig.ini
Exec wait "Notepad.exe $INSTDIR\Plugins\Alarmclock-README.txt"

MessageBox  MB_OK "Install successfull!"

; end
