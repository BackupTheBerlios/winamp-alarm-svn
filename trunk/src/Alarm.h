/*
Copyright (c) 2004 Harri Salokorpi <hsalokor@iki.fi>

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

// Alarm.h: interface for the CAlarm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARM_H__7C8FE0E5_752D_4E48_90AB_D01E1C528046__INCLUDED_)
#define AFX_ALARM_H__7C8FE0E5_752D_4E48_90AB_D01E1C528046__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Configuration.h"

#define STATE_WAITING		0
#define STATE_ALARM_TRIGGER	1
#define	STATE_ALARMING		2
#define STATE_FADING_IN		3
#define STATE_SNOOZE		4

// A class that check is alarm is triggered
class CAlarm  
{
public:
	bool checkTime( SYSTEMTIME *alarm );
	void setState(int state);
	int getState();
	void enableAlarm();
	void disableAlarm();
	void snoozeAlarm();
	void init(CConfiguration* config);
	
	CAlarm();
	virtual ~CAlarm();

private:
	bool checkWeekdayAndTime( SYSTEMTIME *time );
	bool runCheckToList( char* tag );

	int internalState;
//	SYSTEMTIME latestAlarm;
	time_t	latestAlarm;
	time_t	currentTime;
	bool alarmDisabled;
	bool alarmActivated;
	WORD alarmMinute;
	WORD alarmHour;
	CConfiguration* configuration;
};

#endif // !defined(AFX_ALARM_H__7C8FE0E5_752D_4E48_90AB_D01E1C528046__INCLUDED_)
