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
