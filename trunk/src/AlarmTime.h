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

// AlarmTime.h: interface for the CAlarmTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARMTIME_H__6FA49EE6_696F_4F1F_AFA1_2A5AA3AC81FD__INCLUDED_)
#define AFX_ALARMTIME_H__6FA49EE6_696F_4F1F_AFA1_2A5AA3AC81FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "fstream.h"

// variable length defines
#define SERIALIZE_BUFFER_SIZE 256

// Define alarm types
#define	WEEKLY_ALARM 0
#define DAILY_ALARM 1
#define	UNIQUE_ALARM 2

// Define ini-file tags
#define	WEEKLY_ALARM_TAG "WEEKLY"
#define DAILY_ALARM_TAG "DAILY"
#define	UNIQUE_ALARM_TAG "UNIQUE"

#define ALARM_ITEM_TAG "[ALARM]"

// format-strings for sprintf
#define TIME_FORMAT "ALARM_TIME=%d:%d:%d:%d:%d:%d"
#define ON_FORMAT "ALARM_ON=%s"
#define TYPE_FORMAT "ALARM_TYPE=%s"

class CAlarmTime  
{
public:
	void setWeekDay(int weekDay);
	int getWeekDay();
	void setMinute(int minute);
	void setHour(int hour);
	int getMinute();
	int getHour();
	bool getAlarmOn();
	bool serialize(fstream* outstream);
	bool isStateValid();
	bool deserialize(fstream* instream, char* key);
	SYSTEMTIME* getTime();
	void setAlarmStatus(bool on);
	void setTime(SYSTEMTIME* time);
	CAlarmTime(SYSTEMTIME* time, int alarmType, bool alarmOn);
	CAlarmTime();	// For deserialization purposes only!!
	virtual ~CAlarmTime();
	bool compare(SYSTEMTIME* time);

private:
	int m_dayOfWeek;
	int m_minute;
	int m_hour;
	int m_day;
	int m_month;
	int m_year;
	int m_alarmType;
	bool m_alarmOn;
	bool m_stateValid;
};

#endif // !defined(AFX_ALARMTIME_H__6FA49EE6_696F_4F1F_AFA1_2A5AA3AC81FD__INCLUDED_)
