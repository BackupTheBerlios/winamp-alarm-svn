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

// TimeFormat.h: interface for the TimeFormat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMEFORMAT_H__E8B44242_0332_4D0D_8007_312EFE4E1754__INCLUDED_)
#define AFX_TIMEFORMAT_H__E8B44242_0332_4D0D_8007_312EFE4E1754__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TimeFormat  
{
public:
	bool isHourValid( char* hour, bool ampmMode );
	TimeFormat();
	virtual ~TimeFormat();

};

#endif // !defined(AFX_TIMEFORMAT_H__E8B44242_0332_4D0D_8007_312EFE4E1754__INCLUDED_)
