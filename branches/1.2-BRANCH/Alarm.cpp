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

// Alarm.cpp: implementation of the CAlarm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AlarmClock.h"
#include "Alarm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlarm::CAlarm()
{
	// Init latestAlarm to sane value
//	GetLocalTime(&latestAlarm);
	time( &latestAlarm );
	alarmHour	=	0;
	alarmMinute	=	0;
	alarmActivated = FALSE;
}

CAlarm::~CAlarm()
{
}

void CAlarm::init(CConfiguration *config)
{
	configuration	=	config;
}

void CAlarm::snoozeAlarm()
{

}

bool CAlarm::runCheckToList( char *tag )
{
	bool	retVal	=	false;

	int index	=	configuration->beginAlarmList(tag);

	for(int i = 0; i < index; i++)
	{
		CAlarmTime* alarmTime = configuration->getAlarmAt(tag, i);

		if(alarmTime == 0) return false;
		
		// Check if time is ok
		if(strcmp(tag, DAILY_ALARM_TAG) == 0)
		{
			if( checkTime( alarmTime->getTime() ) == true &&
				configuration->getConfig()->getAlarmOn() == true )
			{
				retVal	=	true;
			}
		}
		else
		{
			if(	checkWeekdayAndTime( alarmTime->getTime() ) == true &&
				alarmTime->getAlarmOn() == true &&
				configuration->getConfig()->getAlarmOn() == true )
			{
				retVal	=	true;
			}
		}
	}

	return retVal;
}

void CAlarm::disableAlarm()
{
	alarmDisabled = TRUE;
}

void CAlarm::enableAlarm()
{
	alarmDisabled = FALSE;
}

int CAlarm::getState()
{
	bool		retVal	=	false;

	time( &currentTime );

	// Do trigger only once a day
	if(alarmActivated == false && alarmDisabled != true)
	{
		// Run daily mode check
		if(configuration->getConfig()->getActiveMode() == DAILY_MODE)
		{
			retVal	=	runCheckToList( DAILY_ALARM_TAG );
			
			if(retVal == true)
			{
				internalState	=	STATE_ALARM_TRIGGER;
				time( &latestAlarm );
			}
		}

		// run weekly mode check
		if(configuration->getConfig()->getActiveMode() == WEEKLY_MODE)
		{	
			retVal	=	runCheckToList( WEEKLY_ALARM_TAG );

			if(retVal == TRUE)
			{
				internalState	=	STATE_ALARM_TRIGGER;
				time( &latestAlarm );
			}
		}

		alarmActivated	=	retVal;
	}
	else
	{
		if( currentTime - latestAlarm > 61 )
		{
			alarmActivated = false;
		}
	}

	return internalState;
}

void CAlarm::setState(int state)
{
	internalState	=	state;
}

bool CAlarm::checkWeekdayAndTime(SYSTEMTIME *time)
{
	SYSTEMTIME		current;
	bool			retVal	=	false;


	GetLocalTime( &current );

	if( current.wDayOfWeek == time->wDayOfWeek &&
		current.wHour == time->wHour &&
		current.wMinute == time->wMinute )
	{
		retVal	=	true;
	}

	return retVal;
}

bool CAlarm::checkTime(SYSTEMTIME *time )
{
	SYSTEMTIME		current;
	bool			retVal	=	false;


	GetLocalTime( &current );

	if( current.wHour == time->wHour &&
		current.wMinute == time->wMinute )
	{
		retVal	=	true;
	}

	return retVal;
}
