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

// SnoozeAlarmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "alarmclock.h"
#include "SnoozeAlarmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnoozeAlarmDlg dialog


CSnoozeAlarmDlg::CSnoozeAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSnoozeAlarmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSnoozeAlarmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSnoozeAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnoozeAlarmDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnoozeAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CSnoozeAlarmDlg)
	ON_BN_CLICKED(IDSNOOZE, OnSnooze)
	ON_BN_CLICKED(IDSTOP, OnStop)
	ON_WM_DESTROY()
	ON_WM_CANCELMODE()
	ON_WM_CLOSE()
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_CHARTOITEM()
	ON_WM_CAPTURECHANGED()
	ON_BN_CLICKED(IDCLOSE, OnCloseButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnoozeAlarmDlg message handlers

void CSnoozeAlarmDlg::OnSnooze() 
{
	m_snoozeButton = (CButton*)this->GetDlgItem( IDSNOOZE );
	m_snoozeButton->EnableWindow( FALSE );
	::SendMessage( ampHwnd, WM_SNOOZING, IDSNOOZE, 0l);
}

void CSnoozeAlarmDlg::OnStop() 
{
	::SendMessage( ampHwnd, WM_SNOOZING, IDSTOP, 0l);
	//CDialog::OnDestroy();
}

void CSnoozeAlarmDlg::init(HWND winampHwnd)
{
	ampHwnd		=	winampHwnd;
}

void CSnoozeAlarmDlg::OnDestroy() 
{
	//::SendMessage( ampHwnd, WM_SNOOZING, IDSTOP, 0l);
//	CDialog::OnDestroy();
}

void CSnoozeAlarmDlg::OnCancelMode() 
{
	::SendMessage( ampHwnd, WM_SNOOZING, IDSTOP, 0l);
}

void CSnoozeAlarmDlg::enableSnooze()
{
	m_snoozeButton = (CButton*)this->GetDlgItem( IDSNOOZE );
	this->SetDlgItemText( IDC_TIME, "00:00" );
	m_snoozeButton->EnableWindow( TRUE );
}

void CSnoozeAlarmDlg::OnClose() 
{
	::SendMessage( ampHwnd, WM_SNOOZING, IDSTOP, 0l);
	//CDialog::OnClose();
	
}

void CSnoozeAlarmDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	::SendMessage( ampHwnd, WM_SNOOZING, IDSTOP, 0l);
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CSnoozeAlarmDlg::setTimer(int minute, int second)
{
	char title[9];
	char temp[4];

	temp[0] = '\0';
	title[0] = '\0';
	itoa( minute, temp, 10 );
	if( minute < 10 )
	{
		strcat( title, "0" );
	}
	strcat( title, temp );
	itoa( second, temp, 10 );
	strcat( title, ":" );
	if( second < 10 )
	{
		strcat( title, "0" );
	}
	strcat( title, temp );
	
	//CStatic* timer = (CStatic*)this->GetDlgItem( IDC_TIME );
	this->SetDlgItemText( IDC_TIME, title );
	//timer->SetWindowText( title );
}

void CSnoozeAlarmDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	::SendMessage( ampHwnd, WM_SNOOZING, IDSNOOZE, 0l);
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

int CSnoozeAlarmDlg::OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex) 
{
	return CDialog::OnCharToItem(nChar, pListBox, nIndex);
}

void CSnoozeAlarmDlg::OnCloseButton() 
{
	// TODO: Add your control notification handler code here
	::SendMessage( ampHwnd, WM_SNOOZING, IDCLOSESNOOZE, 0l);
}
