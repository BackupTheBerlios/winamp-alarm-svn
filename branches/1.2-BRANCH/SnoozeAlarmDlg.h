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

#if !defined(AFX_SNOOZEALARMDLG_H__DA205B82_21C4_45C3_A8D5_9B8F2BC483A1__INCLUDED_)
#define AFX_SNOOZEALARMDLG_H__DA205B82_21C4_45C3_A8D5_9B8F2BC483A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SnoozeAlarmDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSnoozeAlarmDlg dialog

class CSnoozeAlarmDlg : public CDialog
{
// Construction
public:
	void setTimer( int minute, int second );
	void enableSnooze();
	HWND	 ampHwnd;
	void init(HWND winampHwnd);
	CSnoozeAlarmDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSnoozeAlarmDlg)
	enum { IDD = IDD_SNOOZEDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnoozeAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSnoozeAlarmDlg)
	afx_msg void OnSnooze();
	afx_msg void OnStop();
	afx_msg void OnDestroy();
	afx_msg void OnCancelMode();
	afx_msg void OnClose();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex);
	afx_msg void OnCloseButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CButton* m_snoozeButton;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNOOZEALARMDLG_H__DA205B82_21C4_45C3_A8D5_9B8F2BC483A1__INCLUDED_)
