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

// Configuration.cpp: implementation of the CConfiguration class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AlarmClock.h"
#include "Configuration.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define iniFileSeparator	'&'

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfiguration::CConfiguration()
{
//	alarmOn	=	false;
//	hour	=	0;
//	minute	=	0;
	
	// Create map for storing alarm time information
	map		=	new alarmMap();
	conf	=	new CGenericConfig();
	
}

CConfiguration::~CConfiguration()
{
	// Delete all items in map
	alarmMapIterator iter	=	map->begin();
	while (iter != map->end())
	{
		delete((*iter).first);
		delete((*iter).second);
		map->erase(iter);
		iter++;
	}

}

bool CConfiguration::readConfiguration(char* iniFile)
{
	bool	retVal	=	false;
	bool	status	=	true;
	char	buffer[SERIALIZE_BUFFER_SIZE];

	// Index is used as map keys
	int		index	=	0;
	CAlarmTime*	time	=	0;
		
	// Copy ini file name to internal variable
	strcpy(iniFileName, iniFile);

	alarmMapIterator iter(map->begin());

	map->erase( map->begin(), map->end() );

	iter	=	map->begin();
	
	delete	conf;
	conf	=	new CGenericConfig();

	fstream*	instream	=	new fstream(iniFile, ios::in | ios::nocreate, filebuf::sh_read);
	
	// Check if file was opened successfully
	if(instream->is_open() == TRUE)
	{
		// TODO: Read basic config
		
		// Read all alarms
		while(status != false && !instream->eof())
		{
			instream->getline(buffer, SERIALIZE_BUFFER_SIZE, '\n');

			// Read generic config
			if(strcmp(GENERIC_SETTINGS_TAG, buffer) == 0)
			{
				conf->deserialize(instream);
			}
		
			if(strcmp(ALARM_ITEM_TAG, buffer) == 0)
			{
				char*	key	=	new char[32];
				index++;
				time	=	new CAlarmTime();
				status	=	time->deserialize(instream, key);
				if(status == false)
				{
					// Prevent memory leak
					delete time;
				}
				else
				{
					addAlarm(key, time);
				}
			}
		}
	}
	
	// Close filestream
	instream->close();
	instream->flush();

	return retVal;
}

bool CConfiguration::saveConfiguration()
{
	
	fstream*	outstream	=	new fstream(iniFileName, ios::out, filebuf::sh_write);
	
	if(outstream->is_open() == TRUE)
	{

		*outstream << GENERIC_SETTINGS_TAG << '\n';
		// Serialize config
		conf->serialize(outstream);

		// Serialize alarms
		alarmMapIterator iter	=	map->begin();

		while(iter != map->end())
		{
			// Only those objects with valid states will be serialized
			if(((*iter).second)->isStateValid() == TRUE)
			{
				*outstream << ALARM_ITEM_TAG << '\n';
				((*iter).second)->serialize(outstream);
				iter++;
			}
		}
	}

	// Close outstream
	outstream->flush();
	outstream->close();
	
	return true;
}

int CConfiguration::beginAlarmList(char* key)
{
	int		count	=	0;

	// Count items with weekly tag in map
	alarmMapIterator i	=	map->begin();
	
	while(i != map->end())
	{
		using namespace std;
	
		while(i != map->end() && strcmp((*i).first, key) != 0)
		{
			i++;
		}
				
		if(i != map->end() && strcmp((*i).first, key) == 0)
		{
			count++;
			i++;
		}
	}

	return count;
}

CAlarmTime* CConfiguration::getAlarmAt(char* key, int index)
{
	CAlarmTime*	alarm	=	0;
	int			count	=	0;
	
	// Count items with weekly tag in map
	alarmMapIterator i	=	map->begin();
	
	while(count <= index && i != map->end())
	{
		using namespace std;
	
		while(i != map->end() && strcmp((*i).first, key) != 0)
		{
			i++;
		}
		if(i == map->end())
		{
			return 0;
		}
		
		if(i != map->end() && count == index && strcmp((*i).first, key) == 0)
		{
			alarm = (*i).second;
			break;
		}
		i++;
		count++;
	}

	return alarm;
}

void CConfiguration::addAlarm(char *key, CAlarmTime *alarm)
{
	if(alarm != 0)
	{
		map->insert(alarmMap::value_type(key, alarm));
	}
}

bool CConfiguration::removeAlarmAt(char *key, int index)
{
	bool	retVal	=	false;
	
	// Count items with weekly tag in map
	alarmMapIterator i	=	map->begin();
	for(int count = 0; count <= index; count++)
	{
		i	=	map->find(key);
		// If map ends before we reach our index -> break and return fail
		if(i == map->end()) break;
		// if match is found -> erase item
		if(count == index)
		{
			//delete((*i).first);
			delete((*i).second);
			map->erase(i);
			retVal	=	true;
			break;
		}
	}

	return retVal;
}

CGenericConfig* CConfiguration::getConfig()
{
	return conf;
}
