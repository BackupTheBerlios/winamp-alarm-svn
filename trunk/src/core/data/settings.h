// Configuration.h: interface for the CConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGURATION_H__CDC40C81_A130_43B3_9460_96DF3715F5D8__INCLUDED_)
#define AFX_CONFIGURATION_H__CDC40C81_A130_43B3_9460_96DF3715F5D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AlarmTime.h"
#include "GenericConfig.h"
#include "fstream.h"

// STL comparator
class compare
{
public:
	operator()(const char* s, const char* t) const
	{
		return (strcmp(s,t) < 0);
	}
};

// Typedef STL's map and iterator
typedef std::multimap< char*, CAlarmTime*, compare> alarmMap;
typedef alarmMap::iterator alarmMapIterator;

class CConfiguration  
{
public:
	CGenericConfig* getConfig();
	bool removeAlarmAt(char* key, int index);
	void addAlarm(char* key, CAlarmTime* alarm);
	CAlarmTime* getAlarmAt(char* key, int index);
	int beginAlarmList(char* key);
	char playlist[PLAYLIST_NAME];
	bool saveConfiguration();
	bool readConfiguration(char* iniFile);
	CConfiguration();
	virtual ~CConfiguration();

protected:
	char iniFileName[256];
	
	// Map for all alarm objects
	alarmMap*			map;
private:
	CGenericConfig* conf;
};

#endif // !defined(AFX_CONFIGURATION_H__CDC40C81_A130_43B3_9460_96DF3715F5D8__INCLUDED_)
