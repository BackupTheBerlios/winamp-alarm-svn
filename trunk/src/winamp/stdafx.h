// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__71F5DE83_CAA9_4339_ADEB_4F30C0592C6A__INCLUDED_)
#define AFX_STDAFX_H__71F5DE83_CAA9_4339_ADEB_4F30C0592C6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Own Defines
#define PLAYLIST_NAME 512
#define INIFILE_OBJECT_SEPARATOR ""

#define WM_CONFIGDIALOG_KILLED	WM_USER + 3105
#define WM_SNOOZING				WM_USER + 3006


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <map>
#include <vector>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__71F5DE83_CAA9_4339_ADEB_4F30C0592C6A__INCLUDED_)
