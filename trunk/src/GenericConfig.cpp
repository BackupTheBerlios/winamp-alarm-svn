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

// GenericConfig.cpp: implementation of the CGenericConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "alarmclock.h"
#include "GenericConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenericConfig::CGenericConfig()
{
	strcpy(playlistName, " ");
	volumeSlideLevel	=	255;
	volumeSlideTime		=	0;
	fadeInOn			=	false;
	activeMode			=	DAILY_MODE;
	snoozeTime			=	5;
	snoozeOn			=	false;
	timeformat24h		=	true;
	alarmOn				=	false;
	fadeInTime			=	2;
	playlistStatus		=	false;
}

CGenericConfig::~CGenericConfig()
{
}

bool CGenericConfig::serialize(fstream *outstream)
{
	bool	retVal	=	false;
	
	retVal	=	true;

	// Write playlist
	this->serializeVariable( outstream, playlistName, PLAYLIST_WRITE_NAME_FORMAT );

	// Write snooze status
	this->serializeVariable( outstream, fadeInOn, VOLUME_SLIDE_STATUS_FORMAT );

	// Write volume slide time
	this->serializeVariable( outstream, volumeSlideLevel, VOLUME_SLIDE_LEVEL_FORMAT );

	// Write snooze status
	this->serializeVariable( outstream, snoozeOn, SNOOZE_STATUS_FORMAT );
	
	// Write snooze time
	this->serializeVariable( outstream, snoozeTime, SNOOZE_TIME_FORMAT );

	// Write shuffle status
	this->serializeVariable( outstream, shuffleStatus, SHUFFLE_STATUS_FORMAT );

	// Write repeat status
	this->serializeVariable( outstream, repeatStatus, REPEAT_STATUS_FORMAT );

	// Write current timeformat status
	this->serializeVariable( outstream, timeformat24h, TIMEFORMAT_STATUS_FORMAT );

	this->serializeVariable( outstream, alarmOn, ALARMON_STATUS_FORMAT );

	// Write active mode status
	if(activeMode == DAILY_MODE)
	{
		this->serializeVariable( outstream, DAILY_MODE_TAG, ACTIVE_MODE_FORMAT);
	}
	else if(activeMode == WEEKLY_MODE) 
	{
		this->serializeVariable( outstream, WEEKLY_MODE_TAG, ACTIVE_MODE_FORMAT);
	}

	this->serializeVariable( outstream, fadeInTime, FADEIN_TIME_FORMAT );

	this->serializeVariable( outstream, playlistStatus, PLAYLIST_STATUS_FORMAT );

	this->endSerialization( outstream );
		
	return	retVal;
}

bool CGenericConfig::deserialize(fstream *instream)
{
	bool	retVal	=	false;
	bool	objectBreak	=	true;
	char	buffer[SERIALIZE_BUFFER_SIZE];

	// Get playlist
	retVal	=	this->deserializeVariable( instream, playlistName, PLAYLIST_READ_NAME_FORMAT );

	// Get volume slide status
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, &fadeInOn, VOLUME_SLIDE_STATUS_FORMAT );
	}

	// Get volume slide level
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, &volumeSlideLevel, VOLUME_SLIDE_LEVEL_FORMAT );
	}

	// Get snooze status
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, &snoozeOn, SNOOZE_STATUS_FORMAT );
	}

	// Get snooze time
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, &snoozeTime, SNOOZE_TIME_FORMAT );
	}

	// Get shuffle status
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, &shuffleStatus, SHUFFLE_STATUS_FORMAT );
	}

	// Get repeat status
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, &repeatStatus, REPEAT_STATUS_FORMAT );
	}

	// Get timeformat status
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, &timeformat24h, TIMEFORMAT_STATUS_FORMAT );
	}

	// Get alarm on status
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, &alarmOn, ALARMON_STATUS_FORMAT );
	}

	// Get active mode time
	if( retVal == true )
	{
		retVal	=	this->deserializeVariable( instream, buffer, ACTIVE_MODE_FORMAT );
		if(strcmp( buffer, DAILY_MODE_TAG ) == 0) activeMode = DAILY_MODE;
		if(strcmp( buffer, WEEKLY_MODE_TAG ) == 0) activeMode = WEEKLY_MODE;
	}

	if( retVal == true )
	{
		objectBreak = false;
		retVal = this->deserializeVariable( instream, &fadeInTime, FADEIN_TIME_FORMAT );
		if( fadeInTime == 0 ) fadeInTime = 2;
	}

	if( retVal == true )
	{
		objectBreak = false;
		retVal = this->deserializeVariable( instream, &playlistStatus, PLAYLIST_STATUS_FORMAT );
	}

	if(objectBreak == false)
	{
		retVal	=	true;
	}
	
	return	retVal;
}

void CGenericConfig::setPlaylistName(char *playlist)
{
	strcpy(playlistName, playlist);
}

void CGenericConfig::getPlaylistName(char *playlist)
{
	strcpy(playlist, playlistName);
}

bool CGenericConfig::getFadeInStatus()
{
	return fadeInOn;
}

void CGenericConfig::setFadeInStatus(bool fadeInOn)
{
	this->fadeInOn	=	fadeInOn;
}

int CGenericConfig::getFadeInTime()
{
	return fadeInTime;
}

void CGenericConfig::setFadeInTime( int fadeInTime )
{
	this->fadeInTime = fadeInTime;
}

void CGenericConfig::setAlarmLevel(int level)
{
	volumeSlideLevel	=	level;
}

int CGenericConfig::getAlarmLevel()
{
	return volumeSlideLevel;
}

void CGenericConfig::setSnoozeStatus(bool snooze)
{
	this->snoozeOn	=	snooze;
}

bool CGenericConfig::getSnoozeStatus()
{
	return snoozeOn;
}

int CGenericConfig::getSnoozeTime()
{
	return this->snoozeTime;
}

void CGenericConfig::setSnoozeTime(int snoozeTime)
{
	this->snoozeTime	=	snoozeTime;
}

void CGenericConfig::setActiveMode(int mode)
{
	activeMode	=	mode;
}

int CGenericConfig::getActiveMode()
{
	return activeMode;
}

bool CGenericConfig::getShuffleStatus()
{
	return shuffleStatus;
}

bool CGenericConfig::getRepeatStatus()
{
	return repeatStatus;
}

bool CGenericConfig::getPlaylistStatus()
{
	return playlistStatus;
}

void CGenericConfig::setShuffleStatus(bool status)
{
	shuffleStatus	=	status;
}

void CGenericConfig::setRepeatStatus(bool status)
{
	repeatStatus	=	status;
}

void CGenericConfig::setPlaylistStatus(bool status)
{
	playlistStatus	=	status;
}

void CGenericConfig::serializeVariable(fstream *out, char *variable, char *serializationMask)
{
	char		buffer[256];

	// Write variable
	sprintf(buffer, serializationMask, variable);
	*out << buffer << "\n";
	buffer[0] = '\0';	// Null buffer
}

void CGenericConfig::serializeVariable(fstream *out, bool variable, char *serializationMask)
{
	char		buffer[256];

	// Write boolean variable
	if(variable == true) sprintf(buffer, serializationMask, "ON");
	else sprintf(buffer, serializationMask, "OFF");
	*out << buffer << "\n";
	buffer[0] = '\0';	// Null buffer

}

void CGenericConfig::serializeVariable(fstream *out, int variable, char *serializationMask)
{
	char		buffer[256];

	// Write variable
	sprintf(buffer, serializationMask, variable);
	*out << buffer << "\n";
	buffer[0] = '\0';	// Null buffer
}

void CGenericConfig::endSerialization( fstream* out )
{
	char		buffer[256];

	strcpy(buffer, INIFILE_OBJECT_SEPARATOR);
	*out << buffer << "\n";
}

// Load character variable from file
bool CGenericConfig::deserializeVariable(fstream *in, char *variable, char *deserializationMask)
{
	bool	retVal	=	false;
	char	buffer[SERIALIZE_BUFFER_SIZE];

	// Get char variable
	if(!in->eof() )
	{
		in->getline(buffer, SERIALIZE_BUFFER_SIZE, '\n');

		if(strcmp(buffer, INIFILE_OBJECT_SEPARATOR) != 0)
		{
			sscanf(buffer, deserializationMask, variable);
			retVal	=	true;
		}
	}
	return retVal;
}

bool CGenericConfig::deserializeVariable(fstream *in, bool *variable, char *deserializationMask)
{
	bool	retVal	=	false;
	char	buffer[SERIALIZE_BUFFER_SIZE];

	if(!in->eof() )
	{
		in->getline(buffer, SERIALIZE_BUFFER_SIZE, '\n');
		
		if(strcmp(buffer, INIFILE_OBJECT_SEPARATOR) != 0)
		{
			char	status[16];
			sscanf(buffer, deserializationMask, &status);

			retVal	=	true;

			if (strcmp(status, "ON") == 0)
			{
				*variable	=	true;
			}
			else
			{
				*variable	=	false;
			}
		}
	}
	return retVal;
}

bool CGenericConfig::deserializeVariable(fstream *in, int *variable, char *deserializationMask)
{
	bool	retVal	=	false;
	char	buffer[SERIALIZE_BUFFER_SIZE];

	if(!in->eof() )
	{
		in->getline(buffer, SERIALIZE_BUFFER_SIZE, '\n');
		
		if(strcmp(buffer, INIFILE_OBJECT_SEPARATOR) != 0)
		{
			sscanf(buffer, deserializationMask, variable);
			retVal	=	true;
		}
	}
	return retVal;
}

bool CGenericConfig::getTimeformat24h()
{
	return this->timeformat24h;
}

void CGenericConfig::setTimeformat24h(bool is24h)
{
	this->timeformat24h = is24h;
}

void CGenericConfig::setAlarmOn( bool alarmOn_ )
{
	this->alarmOn = alarmOn_;
}

bool CGenericConfig::getAlarmOn()
{
	return this->alarmOn;
}
