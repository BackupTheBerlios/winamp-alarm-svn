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

// GenericConfig.h: interface for the CGenericConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERICCONFIG_H__12945957_E5FE_42B9_845E_B4F57F51FE0D__INCLUDED_)
#define AFX_GENERICCONFIG_H__12945957_E5FE_42B9_845E_B4F57F51FE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PLAYLIST_READ_NAME_FORMAT "PLAYLIST_NAME=\"%[^\"]\""
#define PLAYLIST_WRITE_NAME_FORMAT "PLAYLIST_NAME=\"%s\""

#define VOLUME_SLIDE_STATUS_FORMAT "VOLUME_SLIDE_STATUS=%s"
#define VOLUME_SLIDE_TIME_FORMAT "FADE_IN_TIME=%d"
#define VOLUME_SLIDE_LEVEL_FORMAT "FADE_IN_LEVEL=%d"
#define FADEIN_TIME_FORMAT "FADE_IN_TIME=%d"
#define SNOOZE_STATUS_FORMAT "SNOOZE_ON=%s"
#define SNOOZE_TIME_FORMAT "SNOOZE_TIME=%d"
#define ACTIVE_MODE_FORMAT "ACTIVE_MODE=%s"
#define SHUFFLE_STATUS_FORMAT "SHUFFLE_ON=%s"
#define REPEAT_STATUS_FORMAT "REPEAT_ON=%s"
#define TIMEFORMAT_STATUS_FORMAT "24H_FORMAT=%s"
#define ALARMON_STATUS_FORMAT "ALARM_ON=%s"
#define PLAYLIST_STATUS_FORMAT "LOAD_PLAYLIST=%s"


#define GENERIC_SETTINGS_TAG "[GENERIC]"
#define DAILY_MODE_TAG "DAILY"
#define WEEKLY_MODE_TAG "WEEKLY"

#define	DAILY_MODE	0
#define WEEKLY_MODE 1

class CGenericConfig  
{
public:
	bool getAlarmOn();
	void setAlarmOn( bool alarmOn );
	void setTimeformat24h( bool is24h );
	bool getTimeformat24h();
	bool repeatStatus;
	void setRepeatStatus( bool status );
	void setShuffleStatus( bool status );
	void setPlaylistStatus( bool status );
	bool getRepeatStatus();
	bool getShuffleStatus();
	bool getPlaylistStatus();
	int getActiveMode();
	void setActiveMode(int mode);
	void setSnoozeTime(int time);
	int getSnoozeTime();
	bool getSnoozeStatus();
	void setSnoozeStatus(bool snooze);
	int getAlarmLevel();
	void setAlarmLevel(int level);
	void setFadeInStatus(bool fadeInOn);
	bool getFadeInStatus();
	int getFadeInTime();
	void setFadeInTime( int fadeInTime );
	void getPlaylistName(char* playlist);
	void setPlaylistName(char* playlist);
	bool serialize(fstream* outstream);
	bool deserialize(fstream *instream);
	CGenericConfig();
	virtual ~CGenericConfig();

private:
	bool alarmOn;
	bool deserializeVariable( fstream* in, char* variable, char* deserializationMask);
	bool deserializeVariable( fstream* in, int* variable, char* deserializationMask);
	bool deserializeVariable( fstream* in, bool* variable, char* deserializationMask);
	void endSerialization( fstream* out );
	void serializeVariable( fstream* out, bool variable, char* serializationMask);
	void serializeVariable( fstream* out, char* variable, char* serializationMask);
	void serializeVariable( fstream* out, int variable, char *serializationMask );
	bool shuffleStatus;
	bool timeformat24h;
	int activeMode;
	int snoozeTime;
	bool snoozeOn;
	bool fadeInOn;
	bool playlistStatus;
	int fadeInTime;
	int volumeSlideLevel;
	int volumeSlideTime;
	char playlistName[PLAYLIST_NAME];
};

#endif // !defined(AFX_GENERICCONFIG_H__12945957_E5FE_42B9_845E_B4F57F51FE0D__INCLUDED_)
