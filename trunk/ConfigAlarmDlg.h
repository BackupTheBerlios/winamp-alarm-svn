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

#if !defined(AFX_CONFIGALARMDLG1_H__31801FBF_5552_4896_A707_A0CF1259600F__INCLUDED_)
#define AFX_CONFIGALARMDLG1_H__31801FBF_5552_4896_A707_A0CF1259600F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigAlarmDlg1.h : header file
//

#include "AlarmTime.h"

#define ALARM_DAILY_COMBOTEXT	"Every day same time"
#define ALARM_WEEKLY_COMBOTEXT	"Each day different time"
#define ALARM_WEEKLY_NUMBER 0
#define ALARM_DAILY_NUMBER 1

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarmDlg dialog
class CConfigAlarmDlg : public CDialog
{
// Construction
public:
	void loadAlarmStatus();
	void clearHourValue();
	void clearMinuteValue();
	void commitMinuteValue( int minute );
	void revertMinuteValue();
	void loadHourValue();
	bool checkDigits( char* buffer );
	void commitHourValue( int hour );
	void revertHourValue( );
	void setWeeklyAlarmTime(int controlID, int weekday);
	bool alarmOn;
	char playlistname[PLAYLIST_NAME];
	void init(CConfiguration* config, HWND winampHwnd);
	WORD alarmMinute;
	WORD alarmHour;
	HWND ampHwnd;
	CView*	m_pView;
	CConfigAlarmDlg(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CConfigAlarmDlg)
	enum { IDD = IDD_CONFIGALARMDLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CConfiguration* configuration;
	// Generated message map functions
	//{{AFX_MSG(CConfigAlarmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDatetimechangeAlarmtime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangePlaylistname();
	afx_msg void OnAlarmon();
	afx_msg void OnSelectplaylist();
	afx_msg void OnReleasedcaptureAlarmLevelSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFadeinStatus();
	afx_msg void OnSnoozeStatus();
	afx_msg void OnChangeSnoozeTime();
	afx_msg void OnDeltaposSnoozeTimeSpin(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAbout();
	afx_msg void OnSelchangeHourformatSelection();
	afx_msg void OnSelchangeAlarmSetting();
	afx_msg void OnCustomdrawAlarmLevelSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAlarmActive();
	afx_msg void OnAlarmclockOn();
	afx_msg void OnClickWeekdaylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedWeekdaylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeHour();
	afx_msg void OnChangeMinute();
	afx_msg void OnRepeat();
	afx_msg void OnShuffle();
	afx_msg void OnSelchangeAmpmSelector();
	afx_msg void OnDeltaposFadeTimeSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPlaylistToggle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CComboBox* m_ampmSelector;
	CSliderCtrl* m_fadeInLevel;
	CButton* m_alarmActive;
	CEdit* m_minuteEdit;
	CEdit* m_hourEdit;
	CButton* m_shuffleStatus;
	CButton* m_repeatStatus;
	CButton* m_alarmClockStatus;
	CButton* m_snoozeStatus;
	CButton* m_fadeInStatus;
	CButton* m_playlistStatus;
	CButton* m_playListSelect;
	CListCtrl* m_dayList;
	CComboBox* m_hourFormat;
	CEdit* m_playListName;
	CGenericConfig* m_config;
	CComboBox* m_alarmSetting;
	CComboBox* m_hourFormatSelector;
	CStatic* m_weekdayLabel;
	void loadMinuteValue();
	char previousMinute[5];
	char previousHour[5];
	int m_suppressEvents;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGALARMDLG1_H__31801FBF_5552_4896_A707_A0CF1259600F__INCLUDED_)
