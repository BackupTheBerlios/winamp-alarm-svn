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

#ifndef PLAYSETTINGS_H
#define PLAYSETTINGS_H

#include <string.h>

// Using standard library namespace (for strings)
using namespace std;

//! This class contains playback settings
class PlaybackSettings  
{
public:

	//! Returns default alarm volume (in percents)
	int GetVolume();

	//! Returns the fade time (in seconds)
	int GetFadeTime();

	//! Returns the state of the repeat flag.
	/*!
	 * If true, repeat is on.
	 */
	bool IsRepeatOn();
	
	//! Returns the state of the shuffle flag
	/*!
		If true, shuffle is on.
	 */
	bool IsShuffleOn();
	
	//! Returns the snooze time in seconds
	int GetSnoozeTime();
	
	//! Returns the state of the snooze flag.
	/*!
		If true, snoozing is on.
	 */
	bool IsSnoozeOn();

	//! Returns the state of the fade flag.
	/*!
		If true, music is faded in.
	 */
	bool IsFadeOn();

	//! Enables or disables repeat
	void SetIsRepeatOn( bool isRepeatOn_ );
	
	//! Enables or disables shuffle
	void SetIsShuffleOn( bool isShuffleOn_ );
	
	//! Enables or disables snoozing
	void SetIsSnoozeOn(bool snooze);
	
	//! Sets the snooze time in seconds
	void SetSnoozeTime( int snoozeSeconds_ );
	
	//! Sets alarm volume
	void SetVolume(int level);

	//! Enables or disables fade
	/*
		Fade is done from 0% -> volume%
	*/
	void SetIsFadeOn(bool fadeInOn);
	
	//! Sets fade time in seconds
	void SetFadeTime( int fadeInTime );
	
	//! Returns playlist filename
	string& GetPlaylistFilename();
	
	//! Sets playlist filename
	void SetPlaylistFilename( string& playlistFilename_ );

	//! Constructor	
	PlaybackSettings();
	
	//! Destructor
	virtual ~PlaybackSettings();

private:
	//! This flag determines if shuffle is used in playback
	bool _isShuffleOn;

	//! This flag determines if repeat is used in playback
	bool _isRepeatOn;
	
	//! This flag determines if 24h time format should be used
	bool _isTimeformat24h;
	
	//! This field specifies the snooze time in seconds
	int _snoozeTime;
	
	//! This flag determines if snoozing is on
	bool _isSnoozeOn;
	
	//! This flag determines if fade is on
	bool _isFadeOn;
	
	//! This field specifies the fade time in seconds
	int _fadeTime;
	
	//! This field contains the playlist filename
	string _playlistFileName;
};

#endif PLAYSETTINGS_H

