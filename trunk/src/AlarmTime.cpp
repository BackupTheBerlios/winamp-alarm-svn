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

// AlarmTime.cpp: implementation of the CAlarmTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "alarmclock.h"
#include "AlarmTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlarmTime::CAlarmTime(SYSTEMTIME* time, int alarmType, bool alarmOn)
{
	m_year		=	time->wYear;
	m_month		=	time->wMonth;
	m_day		=	time->wDay;

	m_hour		=	time->wHour;
	m_minute	=	time->wMinute;
	m_dayOfWeek	=	time->wDayOfWeek;
	m_alarmType	=	alarmType;

	m_alarmOn	=	alarmOn;

	m_stateValid	=	true;
}

CAlarmTime::CAlarmTime()
{
	m_stateValid	=	false;
	m_hour		=	0;
	m_minute	=	0;
}

CAlarmTime::~CAlarmTime()
{
}

bool CAlarmTime::compare(SYSTEMTIME *time)
{
	bool	retVal	=	false;

	// Check if the alarm is on...
	if (m_alarmOn == true)
	{
		// Weekly alarm-> check weekday, hour and minute
		if(m_alarmType == WEEKLY_ALARM)
		{
			if( m_dayOfWeek == time->wDayOfWeek &&
				m_hour == time ->wHour &&
				m_minute == time->wMinute)
			{
				retVal	= true;
			}
		}
		
		// Daily alarm-> check hour and minute
		if(m_alarmType == DAILY_ALARM)
		{
			if( m_hour == time ->wHour &&
				m_minute == time->wMinute)
			{
				retVal	= true;
			}
		}

		// Unique alarm-> check all values
		if(m_alarmType == UNIQUE_ALARM)
		{
			if( m_year == time->wYear &&
				m_month == time->wMonth &&
				m_day == time->wDay &&
				m_hour == time ->wHour &&
				m_minute == time->wMinute)
			{
				retVal	= true;
			}
		}
	}

	return retVal;
}

// Set time for alarm
void CAlarmTime::setTime(SYSTEMTIME *time)
{
	m_year		=	time->wYear;
	m_month		=	time->wMonth;
	m_day		=	time->wDay;

	m_hour		=	time->wHour;
	m_minute	=	time->wMinute;
	m_dayOfWeek	=	time->wDayOfWeek;
}

void CAlarmTime::setAlarmStatus(bool on)
{
	if(on == true)
	{
		m_alarmOn = true;
	}
	else
	{
		m_alarmOn = false;
	}
}

// Return time as SYSTEMTIME struct
SYSTEMTIME* CAlarmTime::getTime()
{
	SYSTEMTIME*	time	=	new SYSTEMTIME;

	time->wDay			=	m_day;
	time->wDayOfWeek	=	m_dayOfWeek;
	time->wHour			=	m_hour;
	time->wMilliseconds	=	0;
	time->wMinute		=	m_minute;
	time->wMonth		=	m_month;
	time->wSecond		=	0;
	time->wYear			=	m_year;

	return time;
}

// instream is a filestream, key is retVal that contains a key for map
bool CAlarmTime::deserialize(fstream *instream, char* key)
{
	bool	retVal	=	false;

	bool	objectBreak	=	false;

	char	buffer[SERIALIZE_BUFFER_SIZE];
	char	onStatus[32];
	char	type[32];

	// Get time
	if(!instream->eof() && objectBreak == false)
	{
		instream->getline(buffer, SERIALIZE_BUFFER_SIZE, '\n');

		if(strcmp(buffer, INIFILE_OBJECT_SEPARATOR) != 0)
		{
			sscanf(buffer, TIME_FORMAT, &m_year, &m_month, &m_day, &m_hour, &m_minute, &m_dayOfWeek);
		}
		else
		{
			objectBreak	=	true;
		}
	}

	// Get on-status
	if(!instream->eof() && objectBreak == false)
	{
		instream->getline(buffer, SERIALIZE_BUFFER_SIZE, '\n');
		if(strcmp(buffer, INIFILE_OBJECT_SEPARATOR) != 0)
		{
			sscanf(buffer, ON_FORMAT, &onStatus);
			if(strcmp(onStatus, "ON") == 0) m_alarmOn = true;
			if(strcmp(onStatus, "OFF") == 0) m_alarmOn = false;
		}
		else
		{
			objectBreak	=	true;
		}
	}

	// Get alarm type
	if(!instream->eof() && objectBreak == false)
	{
		instream->getline(buffer, SERIALIZE_BUFFER_SIZE, '\n');

		if(strcmp(buffer, INIFILE_OBJECT_SEPARATOR) != 0)
		{
			sscanf(buffer, TYPE_FORMAT, &type);
			
			if(strcmp(type, WEEKLY_ALARM_TAG ) == 0)
			{
				m_alarmType = WEEKLY_ALARM;
				strcpy(key, type);
				m_stateValid	=	true;
			}
			if(strcmp(type, DAILY_ALARM_TAG ) == 0)
			{
				m_alarmType = DAILY_ALARM;
				strcpy(key, type);
				m_stateValid	=	true;
			}

			if(strcmp(type, UNIQUE_ALARM_TAG ) == 0)
			{
				m_alarmType = UNIQUE_ALARM;
				strcpy(key, type);
				m_stateValid	=	true;
			}	
		}
		else
		{
			objectBreak	=	true;
		}
	}

	retVal	=	m_stateValid;

	return	retVal;

}

bool CAlarmTime::isStateValid()
{
	return m_stateValid;
}

bool CAlarmTime::serialize(fstream *outstream)
{
	bool	retVal	=	false;
	char	buffer[SERIALIZE_BUFFER_SIZE];
	char	onStatus[32];
	char	alarmType[16];
	
	// If object state is valid -> serialize
	if (m_stateValid == true)
	{
		// Write time
		sprintf(buffer, TIME_FORMAT, m_year, m_month, m_day, m_hour, m_minute, m_dayOfWeek);
		*outstream << buffer << "\n";
		buffer[0] = '\0';	// Null buffer
	
		// Write on-status
		m_alarmOn	==	true ? strcpy(onStatus, "ON") : strcpy(onStatus, "OFF");
		sprintf(buffer, ON_FORMAT, onStatus);
		*outstream << buffer << "\n";
		buffer[0] = '\0';	// Null buffer

		// Write alarm type
		if(m_alarmType == WEEKLY_ALARM) strcpy(alarmType, WEEKLY_ALARM_TAG);
		if(m_alarmType == DAILY_ALARM) strcpy(alarmType, DAILY_ALARM_TAG);
		if(m_alarmType == UNIQUE_ALARM) strcpy(alarmType, UNIQUE_ALARM_TAG);
		sprintf(buffer, TYPE_FORMAT, alarmType);
		*outstream << buffer << "\n";
		buffer[0] = '\0';	// Null buffer

		strcpy(buffer, INIFILE_OBJECT_SEPARATOR);
		*outstream << buffer << "\n";
		
	}
	
	return	retVal;
}

bool CAlarmTime::getAlarmOn()
{
	if( m_alarmType == DAILY_ALARM )
	{
		return true;
	}
	else
	{
		return m_alarmOn;
	}
}

int CAlarmTime::getHour()
{
	return m_hour;
}

int CAlarmTime::getMinute()
{
	return m_minute;
}

void CAlarmTime::setHour(int hour)
{
	m_hour	=	hour;
}

void CAlarmTime::setMinute(int minute)
{
	m_minute = minute;
}

int CAlarmTime::getWeekDay()
{
	return m_dayOfWeek;
}

void CAlarmTime::setWeekDay(int weekDay)
{
	m_dayOfWeek = weekDay;
}
