/*
Copyright (c) 2004 Harri Salokorpi <hsalokor@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject
to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// AlarmClock.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "AlarmClock.h"
#include "ConfigAlarmDlg.h"
#include "Alarm.h"
#include "Configuration.h"
#include "SnoozeAlarmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	iniFileName "alarmConfig.ini"

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" bool PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmClockApp

BEGIN_MESSAGE_MAP(CAlarmClockApp, CWinApp)
	//{{AFX_MSG_MAP(CAlarmClockApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmClockApp construction

#define TICK_COUNT 3

CAlarm			*alarm = 0;
CConfiguration	*configuration = 0;
CConfigAlarmDlg	*cfg = 0;
CSnoozeAlarmDlg	*snooze = 0;
time_t			lastAlarm;
time_t			currentTime;
time_t			fadeStarted;

char			plugindir[512];
char			winampdir[128];
char			buffer[PLAYLIST_NAME];
char			shellplaycommand[512];
bool			alarmExecuted	=	false;
bool			cfgWindowOpen	=	false;
bool			snoozeWindowOpen	=	false;
int				tickCounter		=	0;
int				fadeVol			=	0;
bool			fadeIn			=	false;
bool			shuffleSet;
bool			repeatSet;

CAlarmClockApp::CAlarmClockApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
};

/////////////////////////////////////////////////////////////////////////////
// The one and only CAlarmClockApp object

CAlarmClockApp theApp;

/////////////////////////////////////////////////////////////////////////////
// Below are method/struct declarations required by WinAmp

WNDPROC lpWndProcOld;

extern "C" int init();
extern "C" void quit();
extern "C" void config();

winampGeneralPurposePlugin plugin =
{
	GPPHDR_VER,
	"Winamp alarm v1.21",
	init,
	config,
	quit,
};

// This wndproc is hooked to winamps message loop
extern "C" LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int state	=	0;
	int ret		=	0;

	// Here we deal with the configuration window closing
	if(message == WM_CONFIGDIALOG_KILLED)
	{
		if(wParam == IDOK)
		{
			configuration->saveConfiguration();
			alarm->enableAlarm();
		}
		if(wParam == IDCANCEL)
		{
			configuration->readConfiguration(plugindir);
			alarm->enableAlarm();
		}
		cfg->DestroyWindow();
		delete cfg;
		cfgWindowOpen = false;
	}

	if(message == WM_SNOOZING)
	{
		if( wParam == IDSNOOZE )
		{
			// Stop playing
			::SendMessage(plugin.hwndParent, WM_COMMAND, 40046, 0l );	
			time( &lastAlarm );
			alarm->setState(STATE_SNOOZE);
			//snooze->ShowWindow( SW_HIDE );
		}
		if( wParam == IDSTOP )
		{
			// Stop playing
			::SendMessage(plugin.hwndParent, WM_COMMAND, 40047, 0l );	
			alarm->setState(STATE_WAITING);
			if( snoozeWindowOpen == true )
			{
				snoozeWindowOpen	=	false;
				snooze->DestroyWindow();
				delete snooze;
			}

			// Set full volume
			ret	=	SendMessage( plugin.hwndParent, WM_USER , 255 , 122 );
			repeatSet == true ? SendMessage( plugin.hwndParent, WM_USER , 1 , 253 ) : SendMessage( plugin.hwndParent, WM_USER , 0 , 253 );
			shuffleSet == true ? SendMessage( plugin.hwndParent, WM_USER , 1 , 252 ) : SendMessage( plugin.hwndParent, WM_USER , 0 , 252 );
		}
		if( wParam == IDCLOSESNOOZE )
		{
			if( snoozeWindowOpen == true )
			{
				snoozeWindowOpen	=	false;
				snooze->DestroyWindow();
				delete snooze;
			}
			alarm->setState(STATE_WAITING);
		}
	}

	// Timer triggered checks... idles 10 ticks, currently
	if(message == WM_TIMER)
	{
		if(tickCounter > 0)
		{
			tickCounter--;
		}
		else
		{
			// Get current alarm state
			state =	alarm->getState();
			tickCounter = TICK_COUNT;
			if (configuration->getConfig()->getFadeInStatus() == true &&
				state == STATE_ALARMING )
			{
				if(fadeVol < configuration->getConfig()->getAlarmLevel())
				{
					time( &currentTime );
					int timediff = currentTime - fadeStarted;
					int fadingTime = configuration->getConfig()->getFadeInTime() * 60;
					if( timediff != 0 )
					{
						fadeVol = ( configuration->getConfig()->getAlarmLevel() * timediff ) / fadingTime;
					}
				}
			}
		}
	}

	if( state == STATE_SNOOZE )
	{
		int minuteDiff	=	0;
		int minutes = 0;
		int seconds = 0;

		time( &currentTime );

		minuteDiff = ( currentTime - lastAlarm ) / (60);
		
		minutes = configuration->getConfig()->getSnoozeTime() - minuteDiff - 1;
		seconds = 60 - ( currentTime - lastAlarm ) % 60;
		
		if( minutes < 0 )
		{
			minutes = 0;
			seconds = 0;
		}

		if( seconds == 60 )
		{
			minutes += 1;
			seconds = 0;
		}
		
		snooze->setTimer( minutes, seconds );

		if( minuteDiff >= configuration->getConfig()->getSnoozeTime() )
		{
			time( &lastAlarm );
			alarm->setState( STATE_ALARMING );
			//snooze->ShowWindow( SW_NORMAL );
			snooze->enableSnooze();
			
			ret	=	SendMessage(plugin.hwndParent, WM_USER , 0l , 102);

			// No fade in -> we set volume HERE
			if(configuration->getConfig()->getFadeInStatus() == false)
			{
				ret	=	SendMessage(plugin.hwndParent, WM_USER , configuration->getConfig()->getAlarmLevel() , 122);
			}
			else
			{
				fadeVol	=	0;
				ret	=	SendMessage(plugin.hwndParent, WM_USER , 0 , 122);	// Fade in
			}
		}
	}

	// NOP
	if(state == STATE_WAITING)
	{
	}

	// Alarm is triggered -> load playlist etc.
	if(state == STATE_ALARM_TRIGGER)
	{

		// Check if winamp is already playing .>
		ret = SendMessage( plugin.hwndParent, WM_USER, 0, 104 );

		time( &fadeStarted );
		fadeVol = 0;

		if( ret != 1 )
		{
			if( configuration->getConfig()->getPlaylistStatus() == false )
			{
				configuration->getConfig()->getPlaylistName( buffer );

				fstream*	playliststream	=	new fstream(buffer, ios::in | ios::nocreate, filebuf::sh_read);
				
				// Check if file was opened successfully
				if(playliststream->is_open() == TRUE)
				{
					ret		=	SendMessage(plugin.hwndParent, WM_USER , 0 , 101);	// Clear playlist
					shellplaycommand[0] = '\0';
					strcat( shellplaycommand, winampdir );
					strcat( shellplaycommand, "winamp.exe /ADD " );
					strcat( shellplaycommand, "\"" );
					strcat( shellplaycommand, buffer );
					strcat( shellplaycommand, "\"" );

					// Tell winamp to load our playlist
					::WinExec( shellplaycommand, false);
				}
			}

			configuration->getConfig()->getRepeatStatus() ? SendMessage( plugin.hwndParent, WM_USER , 1 , 253 ) : SendMessage( plugin.hwndParent, WM_USER , 0 , 253 );
			configuration->getConfig()->getShuffleStatus() ? SendMessage( plugin.hwndParent, WM_USER , 1 , 252 ) : SendMessage( plugin.hwndParent, WM_USER , 0 , 252 );

			// Trigger acknowledged -> alarming... NOTE: MUST BE TRIGGERED BEFORE WinExec() OR KABOOM! Recursion and stack overflow 8)
			alarm->setState(STATE_ALARMING);	

			// Set volume to 0
			SendMessage(plugin.hwndParent, WM_USER , 0 , 122);

			alarmExecuted	=	false;			// Mark alarm not yet executed (needed by the STATE_ALARMING)

			if( configuration->getConfig()->getSnoozeStatus() == true )
			{
				if( snoozeWindowOpen == false)
				{
					snooze	=	new CSnoozeAlarmDlg();
					snooze->init( plugin.hwndParent );
					snooze->Create( IDD_SNOOZEDIALOG );
					snooze->CenterWindow( CWnd::GetDesktopWindow() );
					snooze->ShowWindow( SW_SHOW );
					snoozeWindowOpen = true;
				}
			}
		}
		else
		{
			alarm->setState( STATE_WAITING );
		}
	}

	if(state == STATE_ALARMING)
	{
		// Executed once after alarm trigger
		if(alarmExecuted == false)
		{
			// Reset the fade volume
			fadeVol = 0;
			
			// Check if winamp is already playing .>
			ret = SendMessage( plugin.hwndParent, WM_USER, 0, 104 );

			// Play it, Sam
			ret	= SendMessage(plugin.hwndParent, WM_COMMAND, 0l , 100 );

			// No fade in -> we set volume HERE
			if(configuration->getConfig()->getFadeInStatus() == false)
			{
				// Set alarm volume
				ret		=	SendMessage(plugin.hwndParent, WM_USER , configuration->getConfig()->getAlarmLevel() , 122);
			}
			else
			{
				ret		=	SendMessage(plugin.hwndParent, WM_USER , 0 , 122);	// Fade in
			}

			alarmExecuted = true;
		}

		// Here we do fade in etc.
		if(message != WM_USER)
		{
			if(configuration->getConfig()->getFadeInStatus() == true)
			{
				if( fadeVol < configuration->getConfig()->getAlarmLevel() )
				{
					ret	=	SendMessage( plugin.hwndParent, WM_USER , fadeVol , 122 );
				}
			}

			ret = SendMessage(plugin.hwndParent,WM_USER, 0l, 104);	// Check whether we are playing

			// if WinAmp is stopped -> we go to wait-state
			if(ret != 1)
			{
				if( snoozeWindowOpen == true )
				{
					snoozeWindowOpen	=	false;
					snooze->DestroyWindow();
					delete snooze;
				}

				repeatSet == true ? SendMessage( plugin.hwndParent, WM_USER , 1 , 253 ) : SendMessage( plugin.hwndParent, WM_USER , 0 , 253 );
				shuffleSet == true ? SendMessage( plugin.hwndParent, WM_USER , 1 , 252 ) : SendMessage( plugin.hwndParent, WM_USER , 0 , 252 );
				
				alarm->setState(STATE_WAITING);
			}
		}
	}

	return CallWindowProc(lpWndProcOld,hwnd,message,wParam,lParam);
}


extern "C" void config()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Open configuration dialog if it is not already open
	if( cfgWindowOpen != true)
	{
		// Set correct values for configuration dialog
		alarm->disableAlarm();

		cfg		=	new CConfigAlarmDlg();
		cfg->init(configuration, plugin.hwndParent);
		cfg->Create( IDD_CONFIGALARMDLG );
		cfg->ShowWindow( SW_SHOWNORMAL );
		cfgWindowOpen = true;
	}
	else
	{
		cfg->SetFocus();
	}
}

extern "C" int init()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	char*	charIndex;
	int		index;

	alarmExecuted = false;

	// Get the winamp plugin directory
	GetModuleFileName(plugin.hDllInstance,plugindir,sizeof(plugindir));
	charIndex = plugindir+lstrlen(plugindir);	// Go to the end of string
	while (charIndex >= plugindir && *charIndex != '\\') charIndex--;   // Go back until we hit the directory separator

	index	=	charIndex - plugindir;
	plugindir[index + 1]	=	'\0';	// Cut the relevant part by placing a null-mark

	// Get the Winamp-directory
	strcpy(winampdir, plugindir);
	charIndex = (winampdir + lstrlen(winampdir) - 2); // Go to the end of string
	while (charIndex >= winampdir && *charIndex != '\\') charIndex--;   // Go back until we hit the directory separator
	
	index	=	charIndex - winampdir;
	winampdir[index + 1]	=	'\0';	// Cut the relevant part by placing a null-mark

	strcat(plugindir, iniFileName);

	configuration	=	new CConfiguration();
	alarm			=	new CAlarm();
	configuration->readConfiguration(plugindir);

	alarm->init(configuration);		// Pass CConfiguration to Alarm for settings

	lpWndProcOld = (WNDPROC)GetWindowLong(plugin.hwndParent,GWL_WNDPROC);
	SetWindowLong(plugin.hwndParent,GWL_WNDPROC,(long)WndProc);

	return 0;
}

extern "C" void quit()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Add exit preparations
}

extern "C" {
	_declspec(dllexport) winampGeneralPurposePlugin * winampGetGeneralPurposePlugin()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		return &plugin;
	}
}
