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

// ConfigAlarmDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "AlarmClock.h"
#include "ConfigAlarmDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarmDlg dialog


CConfigAlarmDlg::CConfigAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigAlarmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigAlarmDlg)
	//}}AFX_DATA_INIT
	
	previousHour[0] = '\0';
	previousMinute[0] = '\0';

}

void CConfigAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigAlarmDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigAlarmDlg)
	ON_EN_CHANGE(IDC_PLAYLISTNAME, OnChangePlaylistname)
	ON_BN_CLICKED(IDC_ALARMON, OnAlarmon)
	ON_BN_CLICKED(IDC_SELECTPLAYLIST, OnSelectplaylist)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_ALARM_LEVEL_SLIDER, OnReleasedcaptureAlarmLevelSlider)
	ON_BN_CLICKED(IDC_FADEIN_STATUS, OnFadeinStatus)
	ON_BN_CLICKED(IDC_SNOOZE_STATUS, OnSnoozeStatus)
	ON_EN_CHANGE(IDC_SNOOZE_TIME, OnChangeSnoozeTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SNOOZE_TIME_SPIN, OnDeltaposSnoozeTimeSpin)
	ON_BN_CLICKED(IDABOUT, OnAbout)
	ON_CBN_SELCHANGE(IDC_HOURFORMAT_SELECTION, OnSelchangeHourformatSelection)
	ON_CBN_SELCHANGE(IDC_ALARM_SETTING, OnSelchangeAlarmSetting)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ALARM_LEVEL_SLIDER, OnCustomdrawAlarmLevelSlider)
	ON_BN_CLICKED(IDC_ALARM_ACTIVE, OnAlarmActive)
	ON_BN_CLICKED(IDC_ALARMCLOCK_ON, OnAlarmclockOn)
	ON_NOTIFY(NM_CLICK, IDC_WEEKDAYLIST, OnClickWeekdaylist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_WEEKDAYLIST, OnItemchangedWeekdaylist)
	ON_EN_CHANGE(IDC_HOUR, OnChangeHour)
	ON_EN_CHANGE(IDC_MINUTE, OnChangeMinute)
	ON_BN_CLICKED(IDC_REPEAT, OnRepeat)
	ON_BN_CLICKED(IDC_SHUFFLE, OnShuffle)
	ON_CBN_SELCHANGE(IDC_AMPM_SELECTOR, OnSelchangeAmpmSelector)
	ON_NOTIFY(UDN_DELTAPOS, IDC_FADE_TIME_SPIN, OnDeltaposFadeTimeSpin)
	ON_BN_CLICKED(IDC_PLAYLIST_TOGGLE, OnPlaylistToggle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarmDlg message handlers

BOOL CConfigAlarmDlg::OnInitDialog() 
{
	char	buffer[32];

	m_suppressEvents = 0;

	/* Get pointer for CGenericConfig */
	m_config = configuration->getConfig();

	/* Initialize control wrappers */
	m_hourFormatSelector = (CComboBox*)this->GetDlgItem( IDC_HOURFORMAT_SELECTION );
	m_alarmSetting = (CComboBox*)this->GetDlgItem( IDC_ALARM_SETTING );
	m_playListName = (CEdit*)this->GetDlgItem(IDC_PLAYLISTNAME);
	m_playListSelect = (CButton*)this->GetDlgItem( IDC_SELECTPLAYLIST );
	m_hourFormat = (CComboBox*)this->GetDlgItem( IDC_AMPM_SELECTOR );
	m_dayList = (CListCtrl*)this->GetDlgItem( IDC_WEEKDAYLIST );
	m_fadeInStatus = (CButton*)this->GetDlgItem(IDC_FADEIN_STATUS);
	m_snoozeStatus = (CButton*)this->GetDlgItem(IDC_SNOOZE_STATUS);
	m_alarmClockStatus = (CButton*)this->GetDlgItem(IDC_ALARMCLOCK_ON);
	m_playlistStatus = (CButton*)this->GetDlgItem(IDC_PLAYLIST_TOGGLE);
	m_repeatStatus = (CButton*)this->GetDlgItem(IDC_REPEAT);
	m_shuffleStatus	=	(CButton*)this->GetDlgItem(IDC_SHUFFLE);
	m_hourEdit = (CEdit*)this->GetDlgItem( IDC_HOUR );
	m_minuteEdit = (CEdit*)this->GetDlgItem( IDC_MINUTE );
	m_alarmActive = (CButton*)this->GetDlgItem(IDC_ALARM_ACTIVE );
	m_fadeInLevel = (CSliderCtrl*)this->GetDlgItem(IDC_ALARM_LEVEL_SLIDER);
	m_ampmSelector = (CComboBox*)this->GetDlgItem( IDC_AMPM_SELECTOR );

	m_weekdayLabel = (CStatic*)this->GetDlgItem( IDC_WEEKDAY_LABEL );

	// Set daily alarm status
	int index = configuration->beginAlarmList(DAILY_ALARM_TAG);
	CAlarmTime* alarm = configuration->getAlarmAt(DAILY_ALARM_TAG, 0);
	
	// Set playlist name
	m_config->getPlaylistName(playlistname);
	m_playListName->LimitText(PLAYLIST_NAME);
	SetDlgItemText(IDC_PLAYLISTNAME, playlistname);

	// Add selections to hourformat combo
	m_hourFormatSelector->AddString( "24h" );
	m_hourFormatSelector->AddString( "AM/PM" );
	
	// Set appropriate timeformat to combo
	m_config->getTimeformat24h() == true ? m_hourFormatSelector->SetCurSel( 0 ) : m_hourFormatSelector->SetCurSel( 1 );

	// Set appropriate alarm type value
	m_alarmSetting->AddString( ALARM_DAILY_COMBOTEXT );
	m_alarmSetting->AddString( ALARM_WEEKLY_COMBOTEXT );
	// Set appropriate setting
	m_config->getActiveMode() == DAILY_MODE ? m_alarmSetting->SetCurSel( ALARM_DAILY_NUMBER ) : m_alarmSetting->SetCurSel( ALARM_WEEKLY_NUMBER );

	/* Add AM and PM strings */
	m_hourFormat->AddString( "AM" );
	m_hourFormat->AddString( "PM" );
	m_hourFormat->SetCurSel( 0 );

	/* Hide AM/PM selector if we use 24 hour format */
	m_config->getTimeformat24h() == true ? m_hourFormat->ShowWindow( SW_HIDE ) : m_hourFormat->ShowWindow( SW_NORMAL );

	/* Add items to weekday selector */
	m_dayList->InsertItem( 0, "Monday");
	m_dayList->InsertItem( 1, "Tuesday");
	m_dayList->InsertItem( 2, "Wednesday");
	m_dayList->InsertItem( 3, "Thursday");
	m_dayList->InsertItem( 4, "Friday");
	m_dayList->InsertItem( 5, "Saturday");
	m_dayList->InsertItem( 6, "Sunday");

	/* Disable weekdaylist if DAILY_MODE is active */
	m_config->getActiveMode() == DAILY_MODE ? m_dayList->EnableWindow( FALSE ) : m_dayList->EnableWindow( TRUE );

	/* Set generic config settings */
	m_fadeInStatus->SetCheck(m_config->getFadeInStatus());
	m_snoozeStatus->SetCheck(m_config->getSnoozeStatus());
	m_alarmClockStatus->SetCheck(m_config->getAlarmOn());
	m_repeatStatus->SetCheck(configuration->getConfig()->getRepeatStatus());
	m_shuffleStatus->SetCheck(configuration->getConfig()->getShuffleStatus());

	m_playlistStatus->SetCheck(m_config->getPlaylistStatus());
	m_config->getPlaylistStatus() == true ? m_playListName->EnableWindow( false ) : m_playListName->EnableWindow( true );
	m_config->getPlaylistStatus() == true ? m_playListSelect->EnableWindow( false ) : m_playListSelect->EnableWindow( true );

	/* Set time edit-box limits */
	m_hourEdit->LimitText( 2 );
	this->loadHourValue();
	m_minuteEdit->LimitText( 2 );
	this->loadMinuteValue();
	this->loadAlarmStatus();

	if( configuration->getConfig()->getActiveMode() == WEEKLY_MODE )
	{
		this->clearHourValue();
		this->clearMinuteValue();
		m_hourEdit->EnableWindow( FALSE );
		m_minuteEdit->EnableWindow( FALSE );
		m_alarmActive->EnableWindow( FALSE );
		m_alarmActive->ShowWindow( SW_SHOW );
		m_weekdayLabel->ShowWindow( SW_SHOW );
		m_hourFormat->EnableWindow( FALSE );
	}
	else
	{
		m_alarmActive->EnableWindow( FALSE );
		m_alarmActive->ShowWindow( SW_HIDE );
		m_weekdayLabel->ShowWindow( SW_HIDE );
		m_dayList->ShowWindow( SW_HIDE );
	}

	/* Set Alarm level */
	m_fadeInLevel->SetPageSize( 25 );
	m_fadeInLevel->SetLineSize( 25 );
	m_fadeInLevel->SetTicFreq( 25 );
	m_fadeInLevel->SetTic( 25 );
	int level = m_config->getAlarmLevel();
	m_fadeInLevel->SetRange(0, 255);
	m_fadeInLevel->SetPos( 255 - level );
	int levelPercent = ( (255 - level) * 100 / 255);
	itoa(levelPercent, buffer, 10);
	SetDlgItemText(IDC_ALARM_LEVEL_VIEW, buffer);
	buffer[0] = '\0';
 
	/* Set snooze time */
	itoa( m_config->getSnoozeTime(), buffer, 10);
	SetDlgItemText(IDC_SNOOZE_TIME, buffer);
	
	/* Set fade in time */
	int fadeTime = m_config->getFadeInTime();
	itoa( m_config->getFadeInTime(), buffer, 10);
	SetDlgItemText(IDC_FADE_IN_TIME, buffer);

	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigAlarmDlg::init(CConfiguration *config, HWND winampHwnd)
{
	SYSTEMTIME	timeVar;
	CAlarmTime* time;

	GetLocalTime(&timeVar);

	ampHwnd	= winampHwnd;
	configuration = config;

	int i = config->beginAlarmList(DAILY_ALARM_TAG);
	
	/* Init with single daily alarm if no alarms exist */
	if(i == 0)
	{
		timeVar.wHour	=	8;
		timeVar.wMinute	=	0;
		time = new CAlarmTime(&timeVar, DAILY_ALARM, FALSE );
		config->addAlarm(DAILY_ALARM_TAG, time);
	}

	i	=	0;
	
	/* Init weekly alarms if they don't exist */
	i	=	config->beginAlarmList(WEEKLY_ALARM_TAG);
	if(i != 7)
	{
		if(i != 0)
		{		
			/* Malfunction -> remove existing and add 7 new */
			for(int index = 0; index < i; index++)
			{
				config->removeAlarmAt(WEEKLY_ALARM_TAG, index);
			}
		}
		
		timeVar.wHour	=	8;
		timeVar.wMinute	=	0;

		// Add monday
		timeVar.wDayOfWeek	=	1;
		time = new CAlarmTime(&timeVar, WEEKLY_ALARM, FALSE);
		config->addAlarm(WEEKLY_ALARM_TAG, time);

		// Add tuesday
		timeVar.wDayOfWeek	=	2;
		time	=	new CAlarmTime(&timeVar, WEEKLY_ALARM, FALSE);
		config->addAlarm(WEEKLY_ALARM_TAG, time);

		// Add wednesday
		timeVar.wDayOfWeek	=	3;
		time	=	new CAlarmTime(&timeVar, WEEKLY_ALARM, FALSE);
		config->addAlarm(WEEKLY_ALARM_TAG, time);
		
		// Add thursday
		timeVar.wDayOfWeek	=	4;
		time	=	new CAlarmTime(&timeVar, WEEKLY_ALARM, FALSE);
		config->addAlarm(WEEKLY_ALARM_TAG, time);
		
		// Add friday
		timeVar.wDayOfWeek	=	5;
		time	=	new CAlarmTime(&timeVar, WEEKLY_ALARM, FALSE);
		config->addAlarm(WEEKLY_ALARM_TAG, time);

		// Add saturday
		timeVar.wDayOfWeek	=	6;
		time	=	new CAlarmTime(&timeVar, WEEKLY_ALARM, FALSE);
		config->addAlarm(WEEKLY_ALARM_TAG, time);

		// Add sunday
		timeVar.wDayOfWeek	=	0;
		time	=	new CAlarmTime(&timeVar, WEEKLY_ALARM, FALSE);
		config->addAlarm(WEEKLY_ALARM_TAG, time);
	}
}

void CConfigAlarmDlg::OnChangePlaylistname() 
{
	GetDlgItemText(IDC_PLAYLISTNAME, playlistname, PLAYLIST_NAME);
	m_config->setPlaylistName(playlistname);
}

void CConfigAlarmDlg::OnAlarmon() 
{
	int index = configuration->beginAlarmList(DAILY_ALARM_TAG);
	CAlarmTime* alarm = configuration->getAlarmAt(DAILY_ALARM_TAG, 0);

	// Toggle alarm on/off
	alarm->getAlarmOn()	==	TRUE ? alarm->setAlarmStatus(FALSE) : alarm->setAlarmStatus(TRUE);
	
	m_alarmActive->SetCheck(alarm->getAlarmOn());

}

void CConfigAlarmDlg::OnSelectplaylist() 
{
	CFileDialog	*playlistDlg = new CFileDialog(TRUE, "m3u", NULL, 0, "All supported formats (*.m3u,*.mp3,*.ogg)|*.m3u;*.mp3;*.ogg|Winamp playlists (*.m3u)|*.m3u|Mp3 files (*.mp3)|*.mp3|Ogg Vorbis files (*.ogg)|*.ogg|All Files (*.*)|*.*||", this);

	if(playlistDlg->DoModal() == IDOK)
	{
		strcpy(playlistname, playlistDlg->GetPathName());
		SetDlgItemText(IDC_PLAYLISTNAME, playlistname);
	}
	
}

void CConfigAlarmDlg::OnReleasedcaptureAlarmLevelSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	char	levelString[16];

	int level = m_fadeInLevel->GetPos();
	
	/* Invert slider */
	level	=	255 - level;

	int percentageLevel	=	(100 * level) / 255;

	itoa(percentageLevel, levelString, 10);

	m_config->setAlarmLevel(level);
	SetDlgItemText(IDC_ALARM_LEVEL_VIEW, levelString);

	*pResult = 0;
}

void CConfigAlarmDlg::OnFadeinStatus() 
{
	// Toggle fade in on/off
	m_config->getFadeInStatus() ==	TRUE ? m_config->setFadeInStatus(FALSE) : m_config->setFadeInStatus(TRUE);
	
	m_fadeInStatus->SetCheck( m_config->getFadeInStatus() );
	
}

void CConfigAlarmDlg::OnSnoozeStatus() 
{
	// Toggle snooze in on/off
	m_config->getSnoozeStatus() ==	TRUE ? m_config->setSnoozeStatus(FALSE) : m_config->setSnoozeStatus(TRUE);
	m_snoozeStatus->SetCheck( m_config->getSnoozeStatus());		
}

void CConfigAlarmDlg::OnChangeSnoozeTime() 
{
	char	buffer[10];

	GetDlgItemText(IDC_SNOOZE_TIME, buffer, 10);

	int	i	=	atoi(buffer);

	if(i == 0 || i > 30)
	{
		itoa(m_config->getSnoozeTime(), buffer, 10);
		SetDlgItemText(IDC_SNOOZE_TIME, buffer);
	}
	else
	{
		m_config->setSnoozeTime(i);
	}
}

void CConfigAlarmDlg::OnDeltaposSnoozeTimeSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	char	buffer[10];
		
	int i =	m_config->getSnoozeTime();
	
	if(pNMUpDown->iDelta < 0)
	{
		if(i < 30)
		{
			i++;
		}
	}
	else
	{
		if(i > 1)
		{
			i--;
		}
	}

	m_config->setSnoozeTime(i);
	itoa(i, buffer, 10);
	SetDlgItemText(IDC_SNOOZE_TIME, buffer);

	*pResult = 0;
}

void CConfigAlarmDlg::OnOK() 
{
	
	char	playList[PLAYLIST_NAME];
	int		retVal	=	0;

	if( m_config->getPlaylistStatus() == false )
	{
		m_config->getPlaylistName(playList);

		fstream*	playliststream	=	new fstream(playList, ios::in | ios::nocreate, filebuf::sh_read);
		
		// Check if file was opened successfully
		if(playliststream->is_open() == TRUE)
		{
			::SendMessage(ampHwnd, WM_CONFIGDIALOG_KILLED, IDOK, 0l);
		}
		else
		{
			retVal	=	this->MessageBox(	"The given playlist does not exist! Exit anyway? \n(Alarm will not work)",
											"Invalid playlist",
											MB_ICONEXCLAMATION | MB_ICONWARNING | MB_OKCANCEL);
		
			if( retVal == IDOK)
			{
				::SendMessage(ampHwnd, WM_CONFIGDIALOG_KILLED, IDOK, 0l);
			}
		}
	}
	else
	{
		::SendMessage(ampHwnd, WM_CONFIGDIALOG_KILLED, IDOK, 0l);
	}
}

void CConfigAlarmDlg::OnCancel() 
{
	::SendMessage(ampHwnd, WM_CONFIGDIALOG_KILLED, IDCANCEL, 0l);
}

void CConfigAlarmDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg	*about	=	new CAboutDlg();
	about->DoModal();

}

void CConfigAlarmDlg::OnSelchangeHourformatSelection() 
{
	int		selection	=	0;

	selection = m_hourFormatSelector->GetCurSel();

	selection == 0 ? m_config->setTimeformat24h( true ) : m_config->setTimeformat24h( false );

	if( selection == 0 )
	{
		m_hourFormat->ShowWindow( SW_HIDE );
	}
	else
	{
		m_hourFormat->ShowWindow( SW_SHOW );
	}

	this->loadHourValue();
}

void CConfigAlarmDlg::OnSelchangeAlarmSetting() 
{

	int selection = 0;

	selection = m_alarmSetting->GetCurSel();

	if( selection == ALARM_DAILY_NUMBER )
	{
		m_config->setActiveMode( DAILY_MODE );
		m_hourEdit->EnableWindow( TRUE );
		m_minuteEdit->EnableWindow( TRUE );
		m_alarmActive->EnableWindow( FALSE );
		m_alarmActive->ShowWindow( SW_HIDE );
		m_weekdayLabel->ShowWindow( SW_HIDE );
		m_hourFormat->EnableWindow( TRUE );
		m_dayList->ShowWindow( SW_HIDE );
		this->loadHourValue();
		this->loadMinuteValue();
		m_alarmActive->SetCheck( TRUE );
	}
	else if ( selection == ALARM_WEEKLY_NUMBER )
	{
		m_config->setActiveMode( WEEKLY_MODE );
		m_hourEdit->EnableWindow( FALSE );
		m_minuteEdit->EnableWindow( FALSE );
		m_alarmActive->EnableWindow( FALSE );
		m_alarmActive->ShowWindow( SW_SHOW );
		m_hourFormat->EnableWindow( FALSE );
		m_weekdayLabel->ShowWindow( SW_SHOW );
		m_dayList->SetSelectionMark( 1 );
		m_dayList->ShowWindow( SW_SHOW );
		this->clearHourValue();
		this->clearMinuteValue();
		this->loadAlarmStatus();
	}

	/* Disable weekdaylist if selection is daily alarm */
	m_config->getActiveMode() == DAILY_MODE ? m_dayList->EnableWindow( FALSE ) : m_dayList->EnableWindow( TRUE );
	
}

void CConfigAlarmDlg::OnCustomdrawAlarmLevelSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	/* Delegate */
	this->OnReleasedcaptureAlarmLevelSlider( pNMHDR, pResult );
	*pResult = 0;
}

void CConfigAlarmDlg::OnAlarmActive() 
{
	CAlarmTime* alarm = NULL;

	// Get active mode
	int mode = m_config->getActiveMode();

	if( mode == DAILY_MODE )
	{
		alarm = configuration->getAlarmAt( DAILY_MODE_TAG, 0 );
		alarm->getAlarmOn() == true ? alarm->setAlarmStatus( false ) : alarm->setAlarmStatus( true );
	}
	else if( mode == WEEKLY_MODE )
	{
		POSITION pos = m_dayList->GetFirstSelectedItemPosition();
		if( pos != NULL )
		{
			alarm = configuration->getAlarmAt( WEEKLY_ALARM_TAG, (int)pos - 1 );
			alarm->getAlarmOn() == true ? alarm->setAlarmStatus( false ) : alarm->setAlarmStatus( true );
		}
	}
}

void CConfigAlarmDlg::OnAlarmclockOn() 
{
	// Toggle global alarm on
	m_config->getAlarmOn() == true ? m_config->setAlarmOn( false ) : m_config->setAlarmOn( true );
}

void CConfigAlarmDlg::OnClickWeekdaylist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CAlarmTime* alarm = NULL;

	POSITION pos = m_dayList->GetFirstSelectedItemPosition();
	if( pos != NULL )
	{
		alarm = configuration->getAlarmAt( WEEKLY_ALARM_TAG, (int)pos - 1);
		m_hourEdit->EnableWindow( TRUE );
		m_minuteEdit->EnableWindow( TRUE );
		m_alarmActive->EnableWindow( TRUE );
		m_hourFormat->EnableWindow( TRUE );
		this->loadHourValue();
		this->loadMinuteValue();
		this->loadAlarmStatus();
	}

	*pResult = 0;
}

void CConfigAlarmDlg::OnItemchangedWeekdaylist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	/* Delegate */
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	this->OnClickWeekdaylist( pNMHDR, pResult );	
	*pResult = 0;
}

void CConfigAlarmDlg::OnChangeHour() 
{
	if( m_suppressEvents == 1 ) return;

	m_suppressEvents = 1;

	char	buffer[5];
	int		hour = 0;
	
	m_hourEdit->GetWindowText( buffer, 4 );
	
	/* Allow empty buffer */
	if( strlen( buffer ) == 0 )
	{
		return;
	}

	if( this->checkDigits( buffer ) == false )
	{
		this->revertHourValue();
		return;
	}

	hour = atoi( buffer );
	
	// We use AM/PM format
	if( m_config->getTimeformat24h() == false )
	{
		if( hour > 12 || hour < 1 )
		{
			this->revertHourValue();
			return;
		}

		if( hour == 12 &&
			m_ampmSelector->GetCurSel() == 1 )
		{
			hour = 12;
		}

		if( hour == 12 &&
			m_ampmSelector->GetCurSel() == 0 )
		{
			hour = 0;
		}

		if ( m_ampmSelector->GetCurSel() == 1 )
		{
			/* If PM -> add 12 hours to hour (for internal data format which is 24h) */
			hour = hour + 12;
			if( hour == 24 ) hour = 0;
		}

		this->commitHourValue( hour );
	
		/* If 2 digits entered -> set focus to minute-field */
		if( strlen( buffer ) == 2 )
		{
			m_minuteEdit->SetFocus();
		}
	}
	else
	{
		if( hour < 24 &&
			hour >= 0 )
		{
			this->commitHourValue( hour );

			/* If 2 digits entered -> set focus to minute-field */
			if( strlen( buffer ) == 2 )
			{
				m_minuteEdit->SetFocus();
			}
		}
		else
		{
			this->revertHourValue();
			return;
		}
	}
	
	m_hourEdit->GetWindowText( buffer, 4 );
	strcpy( previousHour, buffer );

	m_suppressEvents = 0;
}

void CConfigAlarmDlg::revertHourValue()
{
	m_hourEdit->SetWindowText( previousHour );
}

void CConfigAlarmDlg::commitHourValue(int hour)
{

	if( m_config->getActiveMode() == DAILY_MODE )
	{
		CAlarmTime* alarm = configuration->getAlarmAt( DAILY_ALARM_TAG, 0);
		alarm->setHour( hour );
	}
	else if( configuration->getConfig()->getActiveMode() == WEEKLY_MODE )
	{
		POSITION pos = m_dayList->GetFirstSelectedItemPosition();
		if( pos != NULL )
		{
			CAlarmTime* alarm = configuration->getAlarmAt( WEEKLY_ALARM_TAG, (int)pos - 1);
			alarm->setHour( hour );
		}
	}
}

bool CConfigAlarmDlg::checkDigits(char *buffer)
{
	bool	retVal	=	true;
	int		i		=	0;

	for( i = 0; i < strlen(buffer); i++ )
	{
		if( isdigit( (int)buffer[i] ) == 0 )
		{
			retVal = false;
		}
	}
	return retVal;
}

void CConfigAlarmDlg::loadHourValue()
{
	//if( m_suppressEvents == 1 ) return;

	int hour = 0;
	char buffer[4] = "";
	char temp[4] = "";

	m_suppressEvents = 1;

	if( m_config->getActiveMode() == DAILY_MODE )
	{
		CAlarmTime* alarm = configuration->getAlarmAt( DAILY_ALARM_TAG, 0);

		hour = alarm->getHour();

		// AM/PM workaround
		if( m_config->getTimeformat24h() == false )
		{
			if( hour == 12 	)
			{
				hour = 12;
				m_ampmSelector->SetCurSel( 1 );
			}

			if( hour == 0 )
			{
				hour = 12;
				m_ampmSelector->SetCurSel( 0 );
			}

			if( hour > 1 && hour < 12 )
			{
				m_ampmSelector->SetCurSel( 0 );
			}

			if( hour > 12 && hour < 24 )
			{
				m_ampmSelector->SetCurSel( 1 );
				hour -= 12;
			}
		}

		itoa(hour, buffer, 10);

		if( hour < 10 )
		{
			strcat( temp, "0" );
			strcat( temp, buffer );
			strcpy( buffer, temp );
		}
		
		m_hourEdit->SetWindowText( buffer );
	}
	else if( m_config->getActiveMode() == WEEKLY_MODE )
	{
		POSITION pos = m_dayList->GetFirstSelectedItemPosition();
		if( pos != NULL )
		{
			CAlarmTime* alarm = configuration->getAlarmAt( WEEKLY_ALARM_TAG, (int)pos - 1);

			hour = alarm->getHour();

			// AM/PM workaround
			if( m_config->getTimeformat24h() == false )
			{
				if( hour == 12 	)
				{
					hour = 12;
					m_ampmSelector->SetCurSel( 1 );
				}

				if( hour == 0 )
				{
					hour = 12;
					m_ampmSelector->SetCurSel( 0 );
				}

				if( hour > 1 && hour < 12 )
				{
					m_ampmSelector->SetCurSel( 0 );
				}

				if( hour > 12 && hour < 24 )
				{
					m_ampmSelector->SetCurSel( 1 );
					hour -= 12;
				}
			}

			itoa(hour, buffer, 10);

			if( hour < 10 )
			{
				strcat( temp, "0" );
				strcat( temp, buffer );
				strcpy( buffer, temp );
			}

			m_hourEdit->SetWindowText( buffer );
		}
	}

	m_suppressEvents = 0;
}

void CConfigAlarmDlg::revertMinuteValue()
{
	m_minuteEdit->SetWindowText( previousMinute );
}


void CConfigAlarmDlg::loadMinuteValue()
{
	int minute = 0;
	char buffer[5] = "";
	char temp[5] = "";

	if( m_config->getActiveMode() == DAILY_MODE )
	{
		CAlarmTime* alarm = configuration->getAlarmAt( DAILY_ALARM_TAG, 0);

		minute = alarm->getMinute();
		itoa(minute, buffer, 10);

		if( minute < 10 )
		{
			strcat( temp, "0" );
			strcat( temp, buffer );
			strcpy( buffer, temp );
		}

		m_minuteEdit->SetWindowText( buffer );
	}
	else if( m_config->getActiveMode() == WEEKLY_MODE )
	{
		POSITION pos = m_dayList->GetFirstSelectedItemPosition();
		if( pos != NULL )
		{
			CAlarmTime* alarm = configuration->getAlarmAt( WEEKLY_ALARM_TAG, (int)pos - 1);

			minute = alarm->getMinute();
			itoa(minute, buffer, 10);

			if( minute < 10 )
			{
				strcat( temp, "0" );
				strcat( temp, buffer );
				strcpy( buffer, temp );
			}

			m_minuteEdit->SetWindowText( buffer );
		}
	}
}

void CConfigAlarmDlg::commitMinuteValue(int minute)
{

	if( m_config->getActiveMode() == DAILY_MODE )
	{
		CAlarmTime* alarm = configuration->getAlarmAt( DAILY_ALARM_TAG, 0);
		alarm->setMinute( minute );
	}
	else if( m_config->getActiveMode() == WEEKLY_MODE )
	{
		POSITION pos = m_dayList->GetFirstSelectedItemPosition();
		if( pos != NULL )
		{
			CAlarmTime* alarm = configuration->getAlarmAt( WEEKLY_ALARM_TAG, (int)pos - 1);
			alarm->setMinute( minute );
		}
	}
}

void CConfigAlarmDlg::OnChangeMinute() 
{
	if( m_suppressEvents == 1 ) return;

	char	buffer[5];
	int		minute = 0;
	
	m_minuteEdit->GetWindowText( buffer, 4 );
	
	/* Allow empty buffer */
	if( strlen( buffer ) == 0 )
	{
		return;
	}

	if( this->checkDigits( buffer ) == false )
	{
		this->revertMinuteValue();
		return;
	}

	minute = atoi( buffer );
	
	if( minute != 0 ||
		buffer[0] == '0' )
	{
		if( minute >= 0 &&
			minute < 60 )
		{
			this->commitMinuteValue( minute );
		}
		else
		{
			this->revertMinuteValue();
		}
	}
	else
	{
		this->revertHourValue();
	}

	m_minuteEdit->GetWindowText( buffer, 4 );
	strcpy( previousMinute, buffer );
}

void CConfigAlarmDlg::clearMinuteValue()
{
	m_minuteEdit->SetWindowText( "" );
}

void CConfigAlarmDlg::clearHourValue()
{
	m_hourEdit->SetWindowText( "" );
}

void CConfigAlarmDlg::loadAlarmStatus()
{
	int minute = 0;
	char buffer[5] = "";
	char temp[5] = "";

	if( m_config->getActiveMode() == DAILY_MODE )
	{
		CAlarmTime* alarm = configuration->getAlarmAt( DAILY_ALARM_TAG, 0);
		alarm->getAlarmOn() == true ? m_alarmActive->SetCheck( TRUE ) : m_alarmActive->SetCheck( FALSE );
	}
	else if( m_config->getActiveMode() == WEEKLY_MODE )
	{
		POSITION pos = m_dayList->GetFirstSelectedItemPosition();
		if( pos != NULL )
		{
			CAlarmTime* alarm = configuration->getAlarmAt( WEEKLY_ALARM_TAG, (int)pos - 1);

			alarm->getAlarmOn() == true ? m_alarmActive->SetCheck( TRUE ) : m_alarmActive->SetCheck( FALSE );
		}
	}
}

void CConfigAlarmDlg::OnRepeat() 
{
	m_config->getRepeatStatus() == true ? m_config->setRepeatStatus( false ) : m_config->setRepeatStatus( true );
}

void CConfigAlarmDlg::OnShuffle() 
{
	m_config->getShuffleStatus() == true ? m_config->setShuffleStatus( false ) : m_config->setShuffleStatus( true );
}


void CConfigAlarmDlg::OnSelchangeAmpmSelector() 
{
	if( m_suppressEvents == 1 ) return;
	this->OnChangeHour();
}

void CConfigAlarmDlg::OnDeltaposFadeTimeSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	char	buffer[10];
		
	int i =	m_config->getFadeInTime();
	
	if(pNMUpDown->iDelta < 0)
	{
		if(i < 10)
		{
			i++;
		}
	}
	else
	{
		if(i > 1)
		{
			i--;
		}
	}

	m_config->setFadeInTime(i);
	itoa(i, buffer, 10);
	SetDlgItemText(IDC_FADE_IN_TIME, buffer);

	*pResult = 0;
}

void CConfigAlarmDlg::OnPlaylistToggle() 
{
	m_config->getPlaylistStatus() == true ? m_config->setPlaylistStatus( false ) : m_config->setPlaylistStatus( true );
	m_config->getPlaylistStatus() == true ? m_playListName->EnableWindow( false ) : m_playListName->EnableWindow( true );
	m_config->getPlaylistStatus() == true ? m_playListSelect->EnableWindow( false ) : m_playListSelect->EnableWindow( true );
}
