Winamp Alarmclock (V1.21, 23.01.2004)
------------------------

DISCLAIMER: THIS PROGRAM COMES WITHOUT ANY WARRANTY, MEANING THAT AUTHOR OF THIS SOFTWARE
IS NOT IN ANY WAY RESPONSIBLE FOR ANY DIRECT OR INDIRECT DAMAGE CAUSED BY THIS PROGRAM. SO,
IF YOU DON'T WAKE UP FOR JOB INTERVIEW BECAUSE OF A BUG IN THE ALARM, TOUGH LUCK. USE AT
YOUR OWN RISK.

However, the plugin has been quite extensively tested, and there are no known fatal bugs.
Testers haven't reported any failures to trigger the alarm, so freak accidents aside, it
should work pretty reliably.

You're free to redistribute the program, preferably with the installer, as long as you also
distribute this README.

Changes
-------
v1.2 -> v1.21
- Config dialog complained about missing playlist if "Use current playlist" was checked. Fixed. Thanks
  to Perttu Immonen for spotting this.

v1.11 -> v1.2
- Added option for disabling the playlist loading. The alarm uses whatever playlist happens to be loaded
  in Winamp. NOTE! If the Winamp playlist is empty, then the alarm won't work! Thanks to Barry Weingart
  for suggestion.
- Fixed shuffle and repeat, which were broken. Non-fatal, but irritating. Thanks to Greg Nelson for
  pointing this out.

v1.1 -> v1.11
- Fixed a bug which caused the volume to jump to 100% when song was changed. Thanks to Josh Burnett (again)
- Clicking stop-button no longer sets volume to 100% since this caused the above problem.

v1.0 -> v1.1
- Sorry about the late update. I have been insanely busy with school lately, and I never got around
  updating the alarm.
- FATAL: Fixed problem with AM/PM times. 12:22 AM mapped to 12:22 and 12:22 PM mapped to 00:12, which
  is (of course) wrong. This one was a tough nut to crack, not because of the time format, but because
  of the general boneheadedness of MFC. Thanks to Josh Burnett for reporting this one.
- Disabled confusing "This alarm active" checkbox when mode is "Every day same time". Thanks to everyone
  for this suggestion. The alarm in this mode is now by default on.
- Added configurable fading. Fade duration can now be configured within range of 1 to 10 minutes.
- Added new filetypes to playlist selection dialog. Now it features "All supported" (mp3, m3u,ogg) and
  "Ogg Vorbis" (ogg)

v0.98 -> v1.0
- FATAL: Fixed crash when snooze was not on, and user stopped the alarm by clicking the stop-button on
  Winamp
- Fixed some AM/PM issues
- Made fade-in to respect the set alarm volume (fades only to set alarm volume, instead of 100%)
- Fade-in didn't reset the volume when the alarm was triggered second time
- Added a button to snooze dialog for closing the dialog without stopping playing
- Configuration dialog cleanups

Introduction
------------

This is an alarmclock plugin for Winamp 2. It has all the basic features an alarmclock should
need, and some nice advanced features. You can configure the alarm to wake you up every day at
the same time, or configure alarms differently for each weekday (in case you have an irregular
sleeping rhytm).

Features:
- Alarm volume, shuffling, repeat and fade-in can be easily configured
- You can supply different alarm times for each weekday, and disable alarms on daily basis, or set
  the alarm to wake you up same time every day.
- You can select a playlist to wake you up, or a single audio-file
- Alarm supports snoozing, which means that when enabled, you can postpone the alarm for certain
  amount of time by hitting enter, space bar or clicking on Snooze-button. Snooze delay is
  (of course) configurable (1-30 minutes)

Usage
-----

When you have installed the plugin using the installer (which should automatically install the plugin
to correct directory) you'll need to configure it.
- go to Winamp preferences (CTRL + p on keyboard)
- select "Plugins/General Purpose" -item in the tree
- select "Winamp alarm v1.2" in the list
- click "Configure"-button at the bottom

Alarm configuration dialog should now open.

First, you'll need to select the playlist. Click on the "Select playlist..." -button to open a file
selector. Note: You can also select a single audio file by changing "Files of type" -selection in file
selection dialog. New in 1.2: You can also check the "Use current playlist" if you want the alarm to use
whatever playlist you happen to have loaded in Winamp.

Next, select the time format. You can use AM/PM -format or 24h format.

Choose the alarm type. If you choose "Each day different time" option, you'll need to configure the
alarm times on daily basis by selecting the day on "Weekday" -list and setting time. You'll also need
to check the "Current alarm active" -checkbox to activate the alarm for the selected day. If you use
the "Every day same time" -type, then you'll need to set the time and enable the current alarm.

Depending on your needs, you can now set the alarm level, set repeat or shuffle, enable snoozing and
enable the fade in.

Finally, enable the "Alarm clock on" -checkbox. DO NOT FORGET THIS, this checkbox enables and disables
the alarmclock.

Now you are set to go! Please note: alarm will not be triggered if Winamp is already playing (wouldn't
make much sense)

Author
------
Harri Salokorpi
hsalokor@ee.oulu.fi

Feel free to send bug reports or feature suggestions. 

Known issues
------------

This plugin has been tested with Windows 2000 and Windows 98. There might be some problems with older
Windows versions. Tested Winamp versions are 2.6x, 2.7x and 2.8x.

- When fade-in is in progress, user cannot change volume. This is because the plugin cannot read the
  volume from Winamp, and therefore it cannot detect user-originated changes in volume. You can either
  wait for the fade to end (which releases the volume control) or click stop and play
- Closing configuration dialog when snoozing closes both dialogs and disables snooze. No idea about this
  one, I couldn't fix this, but it isn't a fatal bug
- If "Use current playlist" is selected and playlist is empty, the alarm will not work. I cannot think of
  any 100% reliable way of preventing this problem (what if the ghosted playlist is invalid and playlist is
  empty?).

Troubleshooting
---------------
- If you have problems updating from previous versions to this one, please remove alarmclock.ini
  from Winamp plugins directory. New configuration variables SHOULD be handled gracefully, but you
  never know.
  
