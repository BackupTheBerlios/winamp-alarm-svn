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
