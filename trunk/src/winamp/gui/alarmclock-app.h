// AlarmClock.h : main header file for the ALARMCLOCK DLL
//

#if !defined(AFX_ALARMCLOCK_H__B8DA71A1_554E_4DF7_A977_B4F179B92922__INCLUDED_)
#define AFX_ALARMCLOCK_H__B8DA71A1_554E_4DF7_A977_B4F179B92922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "gen.h"
#include "WinAmpMessages.h"
#include "alarm.h"

/////////////////////////////////////////////////////////////////////////////
// CAlarmClockApp
// See AlarmClock.cpp for the implementation of this class
//

class CAlarmClockApp : public CWinApp
{
public:
	CAlarmClockApp();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmClockApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAlarmClockApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMCLOCK_H__B8DA71A1_554E_4DF7_A977_B4F179B92922__INCLUDED_)
