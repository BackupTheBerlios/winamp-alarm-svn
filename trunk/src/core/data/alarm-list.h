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
