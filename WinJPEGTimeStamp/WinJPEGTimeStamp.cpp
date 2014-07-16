///////////////////////////////////////////////////////////////////////////////////
//
// WinJPEGTimeStampWin.cpp 
//
// By Peter J Lawrence Email P.J.Lawrence@gre.ac.uk
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose
// and to alter it and redistribute it freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
// Modification History
//
// v1.0.0 first release (10/1/07)
// Changed Radio buttons to check boxes (PJL 23/1/07)
// 
// v1.0.1 second release  (29/1/07)
//
// Updated registry code (PJL 01/02/07)
// Included extra data in registry  (PJL 05/02/07)
// Improved text control text output (PJL 05/02/07)
// Fixed bug where application locked if it can't access a given file (PJL 05/02/07)
// Added abort functionality (PJL 06/02/07)
// v1.0.2 released (06/02/07)
//
// Fixed problem with Iconized Control Dialogue being closed and saving of registry (PJL 19/02/07)
// v1.0.3 released  (XX/02/07) 
//
// Notes:
// 
//
///////////////////////////////////////////////////////////////////////////////////
#include "ExifImageFile.h"
#include "ExifTagEntry.h"
///////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "stdio.h"
#include "math.h"
#include "commctrl.h"
#include "commdlg.h"
#include <sys/stat.h>
#include <time.h>
#include "cderr.h"
#include "direct.h"
#include "dlgtxtctrl.h"
///////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
///////////////////////////////////////////////////////////////////////////////////
#define DlgMinXVal 366
#define DlgMinYVal 200
///////////////////////////////////////////////////////////////////////////////////
// Foward declarations of functions included in this code module:
LRESULT CALLBACK	DateControlDlg(HWND, UINT, WPARAM, LPARAM);
void EnableEditBoxes(HWND hDlg, BOOL Status);
///////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// Perform application initialization:
    DialogBox(hInstance, (LPCTSTR)IDD_DATE_DIALOG, NULL, (DLGPROC)DateControlDlg);

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////
BOOL SaveCurrentStatus(HWND hWnd,const std::string aWorkingFolder)
{
    RECT TheRect;
    GetWindowRect(hWnd,&TheRect);

    LONG            lRetVal;
    HKEY            hkResult;
    lRetVal = RegCreateKeyEx( HKEY_CURRENT_USER, 
                        _T("SOFTWARE\\WinJPEGTimeStamp"), 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hkResult, NULL );
    if( lRetVal == ERROR_SUCCESS )
    {
        if (!IsIconic(hWnd) && !IsZoomed(hWnd))
        { 
            TheRect.right-=TheRect.left;
            TheRect.bottom-=TheRect.top;
            RegSetValueEx( hkResult, _T("WinLeftPos"),NULL, REG_DWORD, (PBYTE) &TheRect.left, sizeof(TheRect.left) );
            RegSetValueEx( hkResult, _T("WinTopPos"), NULL, REG_DWORD, (PBYTE) &TheRect.top, sizeof(TheRect.top) );
            RegSetValueEx( hkResult, _T("WinWidth"),  NULL, REG_DWORD, (PBYTE) &TheRect.right, sizeof(TheRect.right) );
            RegSetValueEx( hkResult, _T("WinHeight"), NULL, REG_DWORD, (PBYTE) &TheRect.bottom, sizeof(TheRect.bottom) );
        }

        if (aWorkingFolder.length()>0)
        {
            RegSetValueEx( hkResult, _T("WorkingFolder"), NULL, REG_EXPAND_SZ, (PBYTE)aWorkingFolder.c_str(), aWorkingFolder.length()+1 );
        }

        LONG aState=SendDlgItemMessage( hWnd, IDC_Accessed,BM_GETSTATE,0,0);
        BYTE IsChk=(BYTE) 0;
        if ((aState & BST_CHECKED)) IsChk=(BYTE) 1;
        RegSetValueEx( hkResult, _T("AccessedChk"),NULL, REG_BINARY, (PBYTE) &IsChk, sizeof(IsChk) );

        aState=SendDlgItemMessage( hWnd, IDC_Modified,BM_GETSTATE,0,0);
        IsChk=(BYTE) 0;
        if ((aState & BST_CHECKED)) IsChk=(BYTE) 1;
        RegSetValueEx( hkResult, _T("ModifiedChk"),NULL, REG_BINARY, (PBYTE) &IsChk, sizeof(IsChk) );

        aState=SendDlgItemMessage( hWnd, IDC_Creation,BM_GETSTATE,0,0);
        IsChk=(BYTE) 0;
        if ((aState & BST_CHECKED)) IsChk=(BYTE) 1;
        RegSetValueEx( hkResult, _T("CreationChk"),NULL, REG_BINARY, (PBYTE) &IsChk, sizeof(IsChk) );

        aState=SendDlgItemMessage( hWnd, IDC_CurrentTime,BM_GETSTATE,0,0);
        IsChk=(BYTE) 0;
        if ((aState & BST_CHECKED)) IsChk=(BYTE) 1;
        RegSetValueEx( hkResult, _T("CurrentTimeChk"),NULL, REG_BINARY, (PBYTE) &IsChk, sizeof(IsChk) );

        RegCloseKey( hkResult );
        return(TRUE);
    }
    return (FALSE);
}
//////////////////////////////////////////////////////////////////////////////////
BOOL LoadCurrentStatus(HWND hWnd,bool RetoreWindowStatus,std::string &aWorkingFolder)
{
    LONG            lRetVal;
    HKEY            hkResult;
    DWORD size;

    lRetVal = RegCreateKeyEx( HKEY_CURRENT_USER, 
                        _T("SOFTWARE\\WinJPEGTimeStamp"), 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hkResult, NULL );
    if( lRetVal == ERROR_SUCCESS )
    {
        RECT TheRect;
        GetWindowRect(hWnd,&TheRect);
        TheRect.right-=TheRect.left;
        TheRect.bottom-=TheRect.top;

        size = sizeof(TheRect.left);
        lRetVal = RegQueryValueEx( hkResult, _T("WinLeftPos"),NULL, NULL, (PBYTE) &TheRect.left, &size );
        if (lRetVal == ERROR_SUCCESS)
            lRetVal = RegQueryValueEx( hkResult, _T("WinTopPos"), NULL, NULL, (PBYTE) &TheRect.top,  &size);
        if (lRetVal == ERROR_SUCCESS)
            lRetVal = RegQueryValueEx( hkResult, _T("WinWidth"),  NULL, NULL, (PBYTE) &TheRect.right, &size );
        if (lRetVal == ERROR_SUCCESS)
            lRetVal = RegQueryValueEx( hkResult, _T("WinHeight"), NULL, NULL, (PBYTE) &TheRect.bottom, &size );

        if (RetoreWindowStatus && lRetVal == ERROR_SUCCESS)
        {
            if (TheRect.left<0)
            {
                TheRect.left=0;
            }
            if (TheRect.top<0)
            {
                TheRect.top=0;
            }
            if (TheRect.right<DlgMinXVal)
            {
                TheRect.right=DlgMinXVal;
            }
            if (TheRect.bottom<DlgMinYVal)
            {
                TheRect.bottom=DlgMinYVal;
            }
            SetWindowPos(hWnd,HWND_TOP,TheRect.left,TheRect.top,TheRect.right,TheRect.bottom,SWP_SHOWWINDOW);
        }

        DWORD MaxSubKeyLen,ValuesCount,MaxValueNameLen,MaxValueLen;
        lRetVal= RegQueryInfoKey(hkResult, NULL, NULL, NULL, NULL, &MaxSubKeyLen, NULL, 
                           &ValuesCount, &MaxValueNameLen, &MaxValueLen, NULL, NULL);

        if( lRetVal == ERROR_SUCCESS )
        {
            if (MaxValueLen>0)
            {
                MaxValueLen++;
                char *DataStr=new char[MaxValueLen];
                if (DataStr)
                {
                    lRetVal = RegQueryValueEx( hkResult, _T("WorkingFolder"), NULL, NULL, (PBYTE) DataStr, &MaxValueLen );
                    if (lRetVal == ERROR_SUCCESS)
                    {
                        aWorkingFolder.assign(DataStr);
                    }
                    delete [] DataStr;
                }
            }
        }
        BYTE IsChk=(BYTE) 0;
        size = sizeof(IsChk);
        lRetVal= RegQueryValueEx(hkResult, _T("AccessedChk"),NULL, NULL, (PBYTE) &IsChk, &size );
        if( lRetVal == ERROR_SUCCESS )
        {
            if (IsChk==0)
            {
                SendDlgItemMessage( hWnd, IDC_Accessed,BM_SETCHECK,FALSE,NULL);
            }
            else
            {
                SendDlgItemMessage( hWnd, IDC_Accessed,BM_SETCHECK,TRUE,NULL);
            }
        }

        lRetVal= RegQueryValueEx(hkResult, _T("ModifiedChk"),NULL, NULL, (PBYTE) &IsChk, &size );
        if( lRetVal == ERROR_SUCCESS )
        {
            if (IsChk==0)
            {
                SendDlgItemMessage( hWnd, IDC_Modified,BM_SETCHECK,FALSE,NULL);
            }
            else
            {
                SendDlgItemMessage( hWnd, IDC_Modified,BM_SETCHECK,TRUE,NULL);
            }
        }

        lRetVal= RegQueryValueEx(hkResult, _T("CreationChk"),NULL, NULL, (PBYTE) &IsChk, &size );
        if( lRetVal == ERROR_SUCCESS )
        {
            if (IsChk==0)
            {
                SendDlgItemMessage( hWnd, IDC_Creation,BM_SETCHECK,FALSE,NULL);
            }
            else
            {
                SendDlgItemMessage( hWnd, IDC_Creation,BM_SETCHECK,TRUE,NULL);
            }
        }

        lRetVal= RegQueryValueEx(hkResult, _T("CurrentTimeChk"),NULL, NULL, (PBYTE) &IsChk, &size );
        if( lRetVal == ERROR_SUCCESS )
        {
            if (IsChk==0)
            {
                SendDlgItemMessage( hWnd, IDC_CurrentTime,BM_SETCHECK,FALSE,NULL);
                EnableEditBoxes(hWnd,TRUE);
            }
            else
            {
                SendDlgItemMessage( hWnd, IDC_CurrentTime,BM_SETCHECK,TRUE,NULL);
                EnableEditBoxes(hWnd,FALSE);
            }
        }
        RegCloseKey( hkResult );
        return(TRUE);
    }
    return (FALSE);
}
//////////////////////////////////////////////////////////////////////////////////
// options
#define OPT_MODIFY_DIG_TIME       (1 << 0)
#define OPT_MODIFY_MOD_TIME       (1 << 1)
#define OPT_MODIFY_CRT_TIME       (1 << 2)
/////////////////////////////////////////////////////////////////////////////
// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
//  Calculate modules the MS Excel way 
//  MOD(n, d) = n - d*INT(n/d)
//
int DateModules(int aNum, int aModVal)
{
    return ( (int) (aNum- aModVal*(int) floor( (double) aNum/ (double) aModVal) ) );
}
//////////////////////////////////////////////////////////////////////////////////
//
// Calculates whether the year specified is a leap year
//
bool isLeapYear(const int aYear)
{
    if ( (aYear % 4) == 0) // Almost every year which is divisible by 4 is a leap year.
    {
        if ( (aYear % 100) == 0) 
        {
            // however, may not be since almost ever year that is divisible by 100 is not
            if ( (aYear % 400) == 0)
            {
                // in this case it is a leap year since also divisible by 400,
                return (true);
            }
            return (false);
        }
        return (true);
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
bool AddDays(int &TheDay, int &TheMonth, int &TheYear, int DaysToAdd, int MonthsToAdd,int YearsToAdd,int &TotalDaysAdded)
{
    int OrgDay=TheDay;
    int OrgMonth=TheMonth;
    int OrgYear=TheYear;

    TotalDaysAdded=0;

    if (TheMonth<0 || TheMonth > 12)
    {
        // not a valid month
        return (false);
    }
    const int MonthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // Update Months
    int xYear=0;
    TheMonth+=MonthsToAdd;

    if (TheMonth<1)
    {
        xYear = TheMonth / 12 - 1;
        TheMonth = TheMonth - 1; // 0 skipped
        TheMonth = DateModules(TheMonth,12)+1; // range 1 to 12
    }
    else
    {
        xYear = (TheMonth-1) / 12; // range 1 to 12
        TheMonth = (TheMonth-1) % 12 + 1;
    }

    // Add any extra year
    YearsToAdd+=xYear;

    // Update Years
    TheYear += YearsToAdd;

    // Correct day of the month for the current year
    int DaysInMonth = MonthDays[TheMonth-1];
    if (TheMonth==2) // Feb
    {
        if (isLeapYear(TheYear))
        {
            DaysInMonth++;
        }
    }
    if (TheDay>DaysInMonth)
    {
        TheDay=DaysInMonth;
    }

    // Add Days
    int IncDay=1;
    if (DaysToAdd<0)
    {
        IncDay=-1;
    }

    int aDay;
    for (aDay=0;aDay<abs(DaysToAdd);aDay++)
    {
        TheDay+=IncDay;

        DaysInMonth = MonthDays[TheMonth-1];
        if (TheMonth==2) // Feb
        {
            if (isLeapYear(TheYear))
            {
                DaysInMonth++;
            }
        }
        if (TheDay<1 || TheDay > DaysInMonth)
        {
            if (IncDay<0)
            {
                TheMonth--;
                if (TheMonth<1)
                {
                    TheMonth=12;
                    TheYear--;
                }
                DaysInMonth = MonthDays[TheMonth-1];
                if (TheMonth==2) // Feb
                {
                    if (isLeapYear(TheYear))
                    {
                        DaysInMonth++;
                    }
                }
                TheDay=DaysInMonth;
            }
            else
            {
                TheMonth++;
                if (TheMonth>12)
                {
                    TheMonth=1;
                    TheYear++;
                }
                TheDay=1;
            }
        }
    }

    // now calculate total number of days added/removed
    IncDay=1;
    if (OrgYear>TheYear)
    {
        IncDay=-1;
    }
    else if (OrgYear==TheYear)
    {
        if (OrgMonth>TheMonth)
        {
            IncDay=-1;
        }
        else if (OrgMonth==TheMonth)
        {
            if (OrgDay>TheDay)
            {
                IncDay=-1;
            }
        }
    }

    // now count the days between  original and updated date

    TotalDaysAdded=0;
    while (OrgYear!=TheYear || OrgMonth!=TheMonth || OrgDay!=TheDay)
    {
        OrgDay+=IncDay;
        TotalDaysAdded+=IncDay;

        if (IncDay<0)
        {
            if (OrgYear<TheYear)
            {
                // problem found with date (Abort!)
                return (false);
            }
        }
        else
        {
            if (OrgYear>TheYear)
            {
                // problem found with date (Abort!)
                return (false);
            }
        }

        DaysInMonth = MonthDays[OrgMonth-1];
        if (OrgMonth==2) // Feb
        {
            if (isLeapYear(OrgYear))
            {
                DaysInMonth++;
            }
        }
        if (OrgDay<1 || OrgDay > DaysInMonth)
        {
            if (IncDay<0)
            {
                OrgMonth--;
                if (OrgMonth<1)
                {
                    OrgMonth=12;
                    OrgYear--;
                }
                DaysInMonth = MonthDays[OrgMonth-1];
                if (OrgMonth==2) // Feb
                {
                    if (isLeapYear(OrgYear))
                    {
                        DaysInMonth++;
                    }
                }
                OrgDay=DaysInMonth;
            }
            else
            {
                OrgMonth++;
                if (OrgMonth>12)
                {
                    OrgMonth=1;
                    OrgYear++;
                }
                OrgDay=1;
            }
        }
    }
    return (true);
}
//////////////////////////////////////////////////////////////////////////////////
//
//  Add specified time to atime
//
bool AddTime(SYSTEMTIME  &atime,
             int wMilliseconds,int wSecond,int wMinute,int wHour,int wDay, int wMonth,int wYear)
{
    // Milliseconds
    int xSecond=0;
    wMilliseconds+=atime.wMilliseconds;
    if (wMilliseconds<0)
    {
        xSecond = wMilliseconds / 1000 - 1;
        wMilliseconds = DateModules(wMilliseconds,1000);
    }
    else
    {
        xSecond=wMilliseconds / 1000; // range (0 to 999)
        wMilliseconds = wMilliseconds % 1000;
    }
    wSecond+=xSecond;
    atime.wMilliseconds=wMilliseconds;

    // Seconds
    int xMinute=0;
    wSecond+=atime.wSecond;
    if (wSecond<0)
    {
        xMinute = wSecond / 60 - 1;
        wSecond = DateModules(wSecond,60);
    }
    else
    {
        xMinute = wSecond / 60; // range (0 to 59)
        wSecond = wSecond % 60;
    }

    // ass extra minutes 
    wMinute+=xMinute;

    atime.wSecond=wSecond;

    // Minutes
    int xHour = 0;
    wMinute+=atime.wMinute;

    if (wMinute<0)
    {
         xHour = wMinute / 60 -1;
         wMinute = DateModules(wMinute,60);
    }
    else
    {
        xHour = wMinute / 60; // range (0 to 59)
        wMinute = wMinute % 60;
    }

    // add extra hours
    wHour+=xHour;

    atime.wMinute=wMinute;

    // Hours
    int xDay=0;
    wHour+=atime.wHour;
    if (wHour<0)
    {
        xDay = wHour / 24 - 1;
        wHour = DateModules(wHour,24);
    }
    else
    {
        xDay = wHour / 24; // range (0 to 23)
        wHour = wHour % 24;
    }

    // add extra days
    wDay+=xDay;

    atime.wHour=wHour;

    // Days, Month and Year

    // This is a bit problematic since number of days in each month or year is variable

    int TheDay=atime.wDay;
    int TheMonth=atime.wMonth;
    int TheYear=atime.wYear;
    int TotalDaysAdded;
    
    if (AddDays(TheDay, TheMonth, TheYear, wDay, wMonth,wYear,TotalDaysAdded))
    {
        atime.wDay=TheDay;
        atime.wMonth=TheMonth;
        atime.wYear=TheYear;

        // find new day of the week
        TotalDaysAdded+=atime.wDayOfWeek;
        TotalDaysAdded=DateModules(TotalDaysAdded,7);
        atime.wDayOfWeek = TotalDaysAdded; // range 0 to 6
        
        return (true);
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
bool MakeCTime(SYSTEMTIME &atime,char *TimeStr,int TimeStrSize)
{
    char *Months[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char *Days[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

    if (atime.wDayOfWeek<7 && atime.wMonth>0 && atime.wMonth<13)
    {
        _snprintf(TimeStr,TimeStrSize,"%03s %03s %02i %02i:%02i:%02i %04i",
            Days[atime.wDayOfWeek],Months[atime.wMonth-1],atime.wDay,atime.wHour,atime.wMinute,atime.wSecond,atime.wYear);
        return (true);
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
//
//  Generates a JPEG time string  "YYYY:MM:DD HH:MM:SS" e.g "2006:08:16 12:33:50"
//  20 characters long
//
bool MakeJPEGTime(SYSTEMTIME &atime,char *TimeStr,int TimeStrSize)
{
    _snprintf(TimeStr,TimeStrSize,"%04i:%02i:%02i %02i:%02i:%02i",
                                    atime.wYear,atime.wMonth,atime.wDay,atime.wHour,atime.wMinute,atime.wSecond);
    return (true);
}
//////////////////////////////////////////////////////////////////////////////////
//
//  reads a JPEG time string  "YYYY:MM:DD HH:MM:SS" e.g "2006:08:16 12:33:50"
//  20 characters long
//
bool GetJPEGTime(SYSTEMTIME &atime,const char *TimeStr,int TimeStrSize)
{
    int FieldsRead = sscanf(TimeStr,"%04u:%02u:%02u %02u:%02u:%02u",
                            &atime.wYear,&atime.wMonth,&atime.wDay,&atime.wHour,&atime.wMinute,&atime.wSecond);
    if (FieldsRead==6)
    {
        return (true);
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
//
//  Given a filename with a directory and extension this routine removes
//  the directory from the filename.
//  The directory is returned in the string directory.
//
bool ExtractFilenameAndDirectory(char *filename, char *directory)
{
    if (!filename) return false;
    const char DirectorySty='\\';
    char* TheLoc=strrchr(filename,DirectorySty);
    if (TheLoc>0)
    {
        int result = TheLoc - filename + 1;
        int i;
        for (i=0;i<result;i++)
        {
            directory[i]=filename[i];
        }
        directory[result]='\0';
        int j=0;
        for (i=result;i<(int) strlen(filename);i++)
        {
            filename[j]=filename[i];
            j++;
        }
        filename[j]='\0';
    }
    return(true);
}
//////////////////////////////////////////////////////////////////////////////////
void winBeep()
{
    MessageBeep(MB_ICONEXCLAMATION);
}
//////////////////////////////////////////////////////////////////////////////////
//
// this routine test to see if the input string is a number
//
// if isFloat then a floating point number is required
//
void check_for_number(HWND TheControl, BOOL isFloat, BOOL CanBeNeg)
{
    int i;

    #define SZ_NAME         20
    char buf[BUFSIZ];
    
    GetWindowText(TheControl,buf,BUFSIZ);
    if ((int)strlen(buf) > SZ_NAME)
    {
        buf[SZ_NAME] = '\0';
        SetWindowText(TheControl,buf);
        winBeep();
        MessageBox(TheControl,"Field too long","Error",MB_OK|MB_ICONINFORMATION);
    }
    buf[SZ_NAME] = '\0';
    int dp,spaces;
    dp=1;spaces=0;
    if (isFloat) dp=0;

    int MoveBack=0;
    for (i = 0; buf[i] != '\0'; i++)
    {
        if (MoveBack>0)
        {
            buf[i-MoveBack]=buf[i];
        }
        if ( !(buf[i] >= '0' && buf[i] <='9') )
        {
            if (!(CanBeNeg && spaces == 0 && buf[i] == '-'))
                if (buf[i]!=' ') spaces=1;
                
            if (!(buf[i] == '.' && dp==0) && 
                !(buf[i] == '-' && spaces==0 && CanBeNeg) &&
                !(buf[i] == ' ' && spaces==0) )
            {
                // remove this character
                MoveBack++;
            }
            if (buf[i]=='.')  dp=1; 
            if (CanBeNeg && spaces == 0 && buf[i] == '-') spaces=1;              
        } else spaces=1;
    }
    if (MoveBack>0)
    {
        // update control if charactors have been removed
        buf[i-MoveBack]='\0';
        SetWindowText(TheControl,buf);
        SetFocus(TheControl);
        SendMessage(TheControl, EM_SETSEL,i, i);
    }
}
//////////////////////////////////////////////////////////////////////////////////
#define LEFTSTICKY         0xFF000000UL
#define TOPSTICKY          0x00FF0000UL
#define RIGHTSTICKY        0x0000FF00UL
#define BOTTOMSTICKY       0x000000FFUL
#define SAMESTICKY         0xF0F0F0F0UL
#define ALLSTICKY          0xFFFFFFFFUL
#define TOPLEFTSTICKY      0xFFFF0000UL
#define TOPRIGHTSTICKY     0x00FFFF00UL
#define BOTTOMLEFTSTICKY   0xFF0000FFUL
#define BOTTOMRIGHTSTICKY  0x0000FFFFUL
#define NULLSTICKY         0x00000000UL
//////////////////////////////////////////////////////////////////////////////////
void MoveDlgItem(HWND DlgWin,unsigned long TheID,int XOffset,int YOffset, unsigned int GlueType)
{
    RECT TheRect;
    HWND aWin=GetDlgItem(DlgWin,TheID);
    GetWindowRect(aWin,&TheRect);
    POINT TheLocation;

    TheLocation.x=TheRect.left;
    TheLocation.y=TheRect.top;
    ScreenToClient(DlgWin,&TheLocation);
    TheRect.left=TheLocation.x;
    TheRect.top=TheLocation.y;
    TheLocation.x=TheRect.right;
    TheLocation.y=TheRect.bottom;
    ScreenToClient(DlgWin,&TheLocation);
    TheRect.right=TheLocation.x;
    TheRect.bottom=TheLocation.y;

    if (GlueType==TOPLEFTSTICKY)
    {
        TheRect.bottom=TheRect.bottom+YOffset;
    }
    else if (GlueType==BOTTOMRIGHTSTICKY)
    {
        TheRect.right=TheRect.right+XOffset;
        TheRect.top=TheRect.top+YOffset;
        TheRect.bottom=TheRect.bottom+YOffset;
    }
    else if (GlueType==ALLSTICKY)
    {
        TheRect.right=TheRect.right+XOffset;
        TheRect.bottom=TheRect.bottom+YOffset;
    }
    else
    {
        if ((GlueType & RIGHTSTICKY)==RIGHTSTICKY)
        {
            TheRect.right=TheRect.right+XOffset;
            TheRect.left=TheRect.left+XOffset;
        }
        if ((GlueType & BOTTOMSTICKY)==BOTTOMSTICKY)
        {
            TheRect.top=TheRect.top+YOffset;
            TheRect.bottom=TheRect.bottom+YOffset;
        }
        if ((GlueType & LEFTSTICKY)==LEFTSTICKY)
        {
        }
        if ((GlueType & TOPSTICKY)==TOPSTICKY)
        {
        }
    }
    MoveWindow(aWin,TheRect.left,TheRect.top,TheRect.right-TheRect.left,TheRect.bottom-TheRect.top,TRUE);
}
//////////////////////////////////////////////////////////////////////////////////
bool HandleSize(HWND DlgWin,int theWidth, int theHeight, int &oldWidth, int &oldHeight)
{ 
    if (IsIconic(DlgWin)) return(true);

    RECT ClientRect;
    GetClientRect(DlgWin,&ClientRect);
  
    // difference in size
    int XOffset=theWidth-oldWidth;
    int YOffset=theHeight-oldHeight;

    // ratios
    float ExpandX=theWidth/float(oldWidth);
    float ExpandY=theHeight/float(oldHeight);

    MoveDlgItem(DlgWin,IDC_EDITBOX,XOffset,YOffset,ALLSTICKY);

    MoveDlgItem(DlgWin,IDCANCEL,XOffset,YOffset,BOTTOMSTICKY);
    MoveDlgItem(DlgWin,IDUNDOABORT,XOffset,YOffset,BOTTOMSTICKY);
    MoveDlgItem(DlgWin,IDOK,XOffset,YOffset,BOTTOMSTICKY);

    oldWidth=ClientRect.right;
    oldHeight=ClientRect.bottom;
 
    InvalidateRect( DlgWin, NULL, FALSE );
    return(true);
}
//////////////////////////////////////////////////////////////////////////////////
//
// Class used to store undo information
//
class FileDateClass
{
private:
    std::string m_FileName;
    std::string m_Dtime; // image digitized
    std::string m_Mtime; // image modified
    std::string m_Ctime; // image created (photo taken)
    WORD m_wOpts;

public:

    FileDateClass() { m_wOpts=0;m_FileName.assign("NULL"); }

    FileDateClass(const FileDateClass &SrcClass)
    {
        m_FileName.assign(SrcClass.m_FileName);
        m_wOpts=SrcClass.m_wOpts;
        m_Dtime=SrcClass.m_Dtime;
        m_Mtime=SrcClass.m_Mtime;
        m_Ctime=SrcClass.m_Ctime;
    }

    FileDateClass(const char* aFileName,WORD a_wOpts,std::string &a_Dtime,std::string &a_Mtime,std::string &a_Ctime)
    {
        m_FileName.assign(aFileName);
        m_wOpts=a_wOpts;
        m_Dtime=a_Dtime;
        m_Mtime=a_Mtime;
        m_Ctime=a_Ctime;
    }

    bool GetFileName(std::string &aFileName)
    {
        aFileName=m_FileName;
        return (true);
    }

    bool GetFileName(char* aFileName,int aFileNameSize)
    {
        strncpy(aFileName,m_FileName.c_str(),aFileNameSize);
        return (true);
    }

    bool GetFileTimes(std::string &a_Dtime,std::string &a_Mtime,std::string &a_Ctime)
    {
        a_Dtime=m_Dtime;
        a_Mtime=m_Mtime;
        a_Ctime=m_Ctime;
        return (true);
    }

    WORD GetwOpts() { return (m_wOpts); }
};
//////////////////////////////////////////////////////////////////////////////////
void ProcessPendingEvents()
{
    MSG msg;         // address of structure with message
    if (PeekMessage (&msg, NULL, 0, 0,PM_REMOVE))
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
}
//////////////////////////////////////////////////////////////////////////////////
void EnableEditBoxes(HWND hDlg, BOOL Status)
{
    EnableWindow(GetDlgItem(hDlg,IDC_HoursEdit), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_MinsEdit), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_SecsEdit), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_DaysEdit), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_MonthsEdit), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_YearsEdit), Status);

    EnableWindow(GetDlgItem(hDlg,IDC_SPIN_HOURS), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_SPIN_MINS), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_SPIN_SECS), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_SPIN_DAYS), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_SPIN_MONTHS), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_SPIN_YEARS), Status);
}
//////////////////////////////////////////////////////////////////////////////////
void EnableInputControls(HWND hDlg, BOOL Status)
{
    if (Status)
    {
        LONG aState=SendDlgItemMessage( hDlg, IDC_CurrentTime,BM_GETSTATE,0,0);
        if ( (aState & BST_CHECKED))
        {
            EnableEditBoxes(hDlg,FALSE);
        }
        else
        {
            EnableEditBoxes(hDlg,TRUE);
        }
    }
    else
    {
        EnableEditBoxes(hDlg,FALSE);

    }
    EnableWindow(GetDlgItem(hDlg,IDC_Digitized), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_Modified), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_Creation), Status);
    EnableWindow(GetDlgItem(hDlg,IDC_CurrentTime), Status);

    EnableWindow(GetDlgItem(hDlg,IDOK), Status);
    EnableWindow(GetDlgItem(hDlg,IDCANCEL), Status);
    if (Status)
    {
        SetWindowText(GetDlgItem(hDlg,IDUNDOABORT),"Undo");
    }
    else
    {
        SetWindowText(GetDlgItem(hDlg,IDUNDOABORT),"Abort");
        EnableWindow(GetDlgItem(hDlg,IDUNDOABORT), TRUE);
    }
}
//////////////////////////////////////////////////////////////////////////////////
//
// Mesage handler for about box.
//
LRESULT CALLBACK DateControlDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int aVal;
    static int oldWidth=0,oldHeight=0;
    static std::vector<FileDateClass> Undolist;
    static std::string WorkingFolder;
    static DlgTxtControl TxtWindow(hDlg,IDC_EDITBOX);
    static bool ContinueOperation=false;

	switch (message)
	{
		case WM_INITDIALOG:
            // set date for controls
            
            SendDlgItemMessage(hDlg, IDC_HoursEdit, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) "0");
            SendMessage(GetDlgItem(hDlg,IDC_SPIN_HOURS), UDM_SETRANGE, 0, MAKELPARAM(48, -48));

            SendDlgItemMessage(hDlg, IDC_MinsEdit, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) "0");
            SendMessage(GetDlgItem(hDlg,IDC_SPIN_MINS), UDM_SETRANGE, 0, MAKELPARAM(120, -120));

            SendDlgItemMessage(hDlg, IDC_SecsEdit, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) "0");
            SendMessage(GetDlgItem(hDlg,IDC_SPIN_SECS), UDM_SETRANGE, 0, MAKELPARAM(120, -120));

            SendDlgItemMessage(hDlg, IDC_DaysEdit, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) "0");
            SendMessage(GetDlgItem(hDlg,IDC_SPIN_DAYS), UDM_SETRANGE, 0, MAKELPARAM(50, -50));

            SendDlgItemMessage(hDlg, IDC_MonthsEdit, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) "0");
            SendMessage(GetDlgItem(hDlg,IDC_SPIN_MONTHS), UDM_SETRANGE, 0, MAKELPARAM(24, -24));

            SendDlgItemMessage(hDlg, IDC_YearsEdit, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) "0");
            SendMessage(GetDlgItem(hDlg,IDC_SPIN_YEARS), UDM_SETRANGE, 0, MAKELPARAM(9999, -9999));

            TxtWindow.AppendText( _T("Status Window....\r\n"));
            TxtWindow.AppendText( _T("Version: 1.0.3 Feb 2007 (Freeware)\r\n"));
            TxtWindow.AppendText( _T("\r\n"));
            TxtWindow.AppendText( _T("Author: Peter J.Lawrence\r\n"));
            TxtWindow.AppendText( _T("email P.J.Lawrence@gre.ac.uk\r\n\r\n"));

            TxtWindow.AppendText( _T("This software is provided \"as is\", without any guarantee made as to its suitability or fitness for any particular use.\r\nThe Author takes no responsibility for any damage that may unintentionally be caused through its use.\r\n"));

            TxtWindow.AppendText( _T("\r\n"));
            TxtWindow.AppendText( _T("Incorporates the following third party libraries/applications/source code:-\r\n"));
            TxtWindow.AppendText( _T("      IJG library Release 6b\r\n"));
            TxtWindow.AppendText( _T("      OpenExif Version: 1.8\r\n"));

            SendDlgItemMessage( hDlg, IDC_Creation,BM_SETCHECK,TRUE,NULL);

            EnableWindow(GetDlgItem(hDlg,IDUNDOABORT), FALSE);

            {
                HINSTANCE hInstance=(HINSTANCE) GetWindowLong(hDlg, GWL_HINSTANCE);
                HICON hIcon = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_TIMESTAMPWIN));
                HICON hIconSmall = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_SMALL));
                PostMessage (hDlg, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
                PostMessage (hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIconSmall);
                DestroyIcon(hIcon);
                DestroyIcon(hIconSmall);

                RECT ClientRect;
                GetClientRect(hDlg,&ClientRect);
                oldWidth=ClientRect.right;
                oldHeight=ClientRect.bottom;
            }

            if (LoadCurrentStatus(hDlg,true,WorkingFolder))
            {
                if (!WorkingFolder.empty())
                {
                    if (_chdir(WorkingFolder.c_str())!=0)
                    {
                        WorkingFolder.erase();
                    }
                }
                if (WorkingFolder.empty())
                {
                    // assign working folder
                    char *Buffer;
                    if ( (Buffer=_getcwd(NULL,0)) )
                    {
                        WorkingFolder.assign(Buffer);
                        free(Buffer);
                    } 
                }
            }
            return TRUE;

        case WM_SIZING:
            {
                RECT* ClientRect = (LPRECT) lParam;
                if ( (ClientRect->right-ClientRect->left)<DlgMinXVal ||
                     (ClientRect->bottom-ClientRect->top)<DlgMinYVal )
                {
                    if ((ClientRect->right-ClientRect->left)<DlgMinXVal)
                    {
                        ClientRect->right=ClientRect->left+DlgMinXVal;
                    }
                    if ((ClientRect->bottom-ClientRect->top)<DlgMinYVal)
                    {
                        ClientRect->bottom=ClientRect->top+DlgMinYVal;
                    }
                    return (TRUE);
                }
            }
            break;

        case WM_SIZE:
        {
            int nWidth = LOWORD(lParam);  // width of client area 
            int nHeight = HIWORD(lParam); // height of client area
            return (HandleSize(hDlg,nWidth,nHeight,oldWidth,oldHeight));
        }

        case WM_CLOSE:
            SaveCurrentStatus(hDlg,WorkingFolder);
            EndDialog(hDlg, LOWORD(wParam));
            return (TRUE);
        
        case WM_COMMAND:
            switch (LOWORD(wParam))
			{
            case IDCANCEL:
                SaveCurrentStatus(hDlg,WorkingFolder);
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;

            case IDC_Accessed:
            case IDC_Modified:
            case IDC_Creation:
                {
                    LONG aState=SendDlgItemMessage( hDlg, LOWORD(wParam),BM_GETSTATE,0,0);
                    if ( (aState & BST_CHECKED))
                    {
                        SendDlgItemMessage( hDlg, LOWORD(wParam),BM_SETCHECK,FALSE,NULL);
                    }
                    else
                    {
                        SendDlgItemMessage( hDlg, LOWORD(wParam),BM_SETCHECK,TRUE,NULL);
                    }
                }
                return TRUE;

            case IDC_CurrentTime:
                {
                    LONG aState=SendDlgItemMessage( hDlg, LOWORD(wParam),BM_GETSTATE,0,0);
                    if ( (aState & BST_CHECKED))
                    {
                        SendDlgItemMessage( hDlg, LOWORD(wParam),BM_SETCHECK,FALSE,NULL);
                        EnableEditBoxes(hDlg,TRUE);
                     }
                    else
                    {
                        SendDlgItemMessage( hDlg, LOWORD(wParam),BM_SETCHECK,TRUE,NULL);
                        EnableEditBoxes(hDlg,FALSE);
                    }
                }
                break;

            case IDC_HoursEdit:
            case IDC_MinsEdit:
            case IDC_SecsEdit:
            case IDC_DaysEdit:
            case IDC_MonthsEdit:
            case IDC_YearsEdit:
                    check_for_number((HWND) lParam,FALSE,TRUE);
                    break;

            case IDOK:
            {
                #define TheTextSize 200
                char TheText[TheTextSize];

                BOOL UseCurrentTime=FALSE;
                LONG aState=SendDlgItemMessage( hDlg, IDC_CurrentTime,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
                    UseCurrentTime=TRUE;
                }

                WORD wOpts = (WORD) 0;
                aState=SendDlgItemMessage( hDlg, IDC_Accessed,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
                    wOpts = wOpts | (WORD) OPT_MODIFY_DIG_TIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_Modified,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    wOpts = wOpts | (WORD) OPT_MODIFY_MOD_TIME;
                }

                aState=SendDlgItemMessage( hDlg, IDC_Creation,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    wOpts = wOpts | (WORD) OPT_MODIFY_CRT_TIME;
                }

                #define FileNameStrSize 5000
                #define DirectoryStrSize 1000

                int sizeofFileName= FileNameStrSize;
                char TheFileName[FileNameStrSize];
                char aDirectory[DirectoryStrSize];

                const char *Filter = "All JPEG\0";
                const char *FilterExt = "*.jpg;*.jpeg\0";

                ZeroMemory(TheFileName,FileNameStrSize);                
                ZeroMemory(aDirectory,DirectoryStrSize);

                OPENFILENAME ofn;

                char szFileTitle[FileNameStrSize];
                #define FilterStrSize 30
                char  szFilter[FilterStrSize];
                strcpy(szFilter,Filter);
                strcpy(&szFilter[strlen(Filter)+1],FilterExt);
                szFilter[strlen(szFilter)+strlen(FilterExt)+2] ='\0';

                szFileTitle[0] ='\0';

                /* Set all structure members to zero. */

                memset(&ofn, 0, sizeof(OPENFILENAME));

                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.hwndOwner = GetFocus();
                ofn.lpstrFilter = szFilter;
                ofn.nFilterIndex = 1;
                ofn.lpstrFile= TheFileName;
                ofn.nMaxFile = sizeofFileName;
                ofn.lpstrFileTitle = szFileTitle;
                ofn.nMaxFileTitle = sizeof(szFileTitle);
                if (WorkingFolder.length()>0)
                {
                    ofn.lpstrInitialDir=WorkingFolder.c_str();
                }
                else
                {
                    ofn.lpstrInitialDir = aDirectory;
                }

                ofn.Flags = OFN_EXPLORER| OFN_ALLOWMULTISELECT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
                if (GetOpenFileName(&ofn)) 
                { 
                    TxtWindow.Clear();
                    TxtWindow.AppendText( _T("Status....\r\n"));

                    int NextFilePos=0;
                    // test to see how many files selected
                    int StrLen=strlen(TheFileName);
                    if (TheFileName[StrLen+1]!=0)
                    {
                        //multiple files
                        NextFilePos=StrLen+1;
                    }

                    if (NextFilePos==0)
                    {
                        if (ExtractFilenameAndDirectory(TheFileName,aDirectory))
                        {
                            WorkingFolder.assign(aDirectory);
                        }
                        else
                        {
                            WorkingFolder.erase();
                        }
                    }
                    else
                    {
                        // first entry is Directorty others are file name
                        WorkingFolder.assign(TheFileName);

                        StrLen=strlen(&TheFileName[NextFilePos]);
                        strcpy(TheFileName,&TheFileName[NextFilePos]);

                        if (TheFileName[NextFilePos+StrLen+1]!=0)
                        {
                            // another file
                            NextFilePos=NextFilePos+StrLen+1;
                        }
                        else
                        {
                            NextFilePos=0;
                        }
                        
                    }

                    int hours,mins,secs,days,months,years;
                    if (!UseCurrentTime)
                    {
                        SendDlgItemMessage(hDlg, IDC_HoursEdit, WM_GETTEXT, (WPARAM) TheTextSize, (LPARAM)TheText);
                        hours=atoi(TheText);

                        SendDlgItemMessage(hDlg, IDC_MinsEdit, WM_GETTEXT, (WPARAM) TheTextSize, (LPARAM)TheText);
                        mins=atoi(TheText);

                        SendDlgItemMessage(hDlg, IDC_SecsEdit, WM_GETTEXT, (WPARAM) TheTextSize, (LPARAM)TheText);
                        secs=atoi(TheText);

                        SendDlgItemMessage(hDlg, IDC_DaysEdit, WM_GETTEXT, (WPARAM) TheTextSize, (LPARAM)TheText);
                        days=atoi(TheText);

                        SendDlgItemMessage(hDlg, IDC_MonthsEdit, WM_GETTEXT, (WPARAM) TheTextSize, (LPARAM)TheText);
                        months=atoi(TheText);
    
                        SendDlgItemMessage(hDlg, IDC_YearsEdit, WM_GETTEXT, (WPARAM) TheTextSize, (LPARAM)TheText);
                        years=atoi(TheText);
                    }

                    Undolist.clear();
                    EnableInputControls(hDlg,FALSE);
                    ContinueOperation=true;
                    do 
                    {
                        _snprintf(TheText,TheTextSize,"=========================\r\n");
                        TxtWindow.AppendText( TheText);

                        ExifImageFile inImageFile;
                        std::string inImageFileNaem;
                        inImageFileNaem.assign(TheFileName);

                        char *ModOptions="r+";
                        if (wOpts==0)
                        {
                            ModOptions="r";
                        }

                        if (inImageFile.open(inImageFileNaem.c_str(), ModOptions) == EXIF_OK)
                        {
                            ExifStatus aErr;

                            SYSTEMTIME  SysTime;
                            std::string JPEGDateStr;
                            
                            #define DateStrSize 30
                            char DateStr[DateStrSize];

                            _snprintf(TheText,TheTextSize, "Accessing attributes for \"%s\"\r\n",TheFileName);
                            TxtWindow.AppendText( TheText);                                
 
                            bool ModifiedValues=false;

                            std::string JPGDtime;
                            // EXIFTAG_DALETIMEDIGITIZED Date/Time of image digitized
                            ExifTagEntry* entryTag=NULL;
                            entryTag = inImageFile.getGenericTag(EXIFTAG_DALETIMEDIGITIZED,EXIF_APP1_EXIFIFD,aErr);
                            if (entryTag)
                            {
                                JPGDtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                _snprintf(TheText,TheTextSize,"Digitized : %s\r\n", JPGDtime.c_str() );
                                TxtWindow.AppendText( TheText);

                                if (wOpts & OPT_MODIFY_DIG_TIME)
                                {
                                    if (UseCurrentTime || GetJPEGTime(SysTime,JPGDtime.c_str(),JPGDtime.length()))
                                    {
                                        if (UseCurrentTime)
                                        {
                                            GetLocalTime(&SysTime);
                                        }
                                        else
                                        {
                                            AddTime(SysTime,0,secs,mins,hours,days,months,years);
                                        }
                                        
                                        if (MakeJPEGTime(SysTime,DateStr,DateStrSize))
                                        {
                                            JPEGDateStr.assign(DateStr);
                                            (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPEGDateStr);
                                            ModifiedValues=true;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                TxtWindow.AppendText( "No EXIF Digitized time information\r\n");
                            }

                            std::string JPGMtime;
                            // EXIFTAG_DATETIME Date/Time of image was last modified
                            entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIME,EXIF_APP1_IFD0,aErr);
                            if (entryTag)
                            {
                                JPGMtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                _snprintf(TheText,TheTextSize,"Modified : %s\r\n", JPGMtime.c_str() );
                                TxtWindow.AppendText( TheText);
                                
                                if (wOpts & OPT_MODIFY_MOD_TIME)
                                {
                                    if (UseCurrentTime || GetJPEGTime(SysTime,JPGMtime.c_str(),JPGMtime.length()))
                                    {
                                        if (UseCurrentTime)
                                        {
                                            GetLocalTime(&SysTime);
                                        }
                                        else
                                        {
                                            AddTime(SysTime,0,secs,mins,hours,days,months,years);
                                        }
                                        
                                        if (MakeJPEGTime(SysTime,DateStr,DateStrSize))
                                        {
                                            JPEGDateStr.assign(DateStr);
                                            (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPEGDateStr);
                                            ModifiedValues=true;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                TxtWindow.AppendText( "No EXIF Modified time information\r\n");
                            }

                            std::string JPGCtime;
                            // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                            entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                            if (entryTag)
                            {
                                JPGCtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                _snprintf(TheText,TheTextSize,"Created : %s\r\n", JPGCtime.c_str() );
                                TxtWindow.AppendText( TheText);
                                if (wOpts & OPT_MODIFY_CRT_TIME)
                                {
                                    if (UseCurrentTime || GetJPEGTime(SysTime,JPGCtime.c_str(),JPGCtime.length()))
                                    {
                                        if (UseCurrentTime)
                                        {
                                            GetLocalTime(&SysTime);
                                        }
                                        else
                                        {
                                            AddTime(SysTime,0,secs,mins,hours,days,months,years);
                                        }
                                        
                                        if (MakeJPEGTime(SysTime,DateStr,DateStrSize))
                                        {
                                            JPEGDateStr.assign(DateStr);
                                            (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPEGDateStr);
                                            ModifiedValues=true;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                TxtWindow.AppendText( "No EXIF Original image time information\r\n");
                            }			               

                            if (ModifiedValues)
                            {
                                Undolist.push_back(FileDateClass(TheFileName,wOpts,JPGDtime,JPGMtime,JPGCtime));
                            }

                            if (wOpts>0)
                            {
                                // Output updated values

                                _snprintf(TheText,TheTextSize,"Updated Values....\r\n");
                                TxtWindow.AppendText( TheText);
                                if (ModifiedValues)
                                {
                                    bool UpdatedInfo=false;
                                    if (wOpts & OPT_MODIFY_DIG_TIME)
                                    {
                                        // EXIFTAG_DALETIMEDIGITIZED Date/Time of image digitized
                                        entryTag = inImageFile.getGenericTag(EXIFTAG_DALETIMEDIGITIZED,EXIF_APP1_EXIFIFD,aErr);
                                        if (entryTag)
                                        {
                                            JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                            _snprintf(TheText,TheTextSize,"Digitized : %s\r\n", JPEGDateStr.c_str() );
                                            TxtWindow.AppendText( TheText);
                                            UpdatedInfo=true;
                                        }
                                    }
                                    if (wOpts & OPT_MODIFY_MOD_TIME)
                                    {
                                        // EXIFTAG_DATETIME Date/Time of image was last modified
                                        entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIME,EXIF_APP1_IFD0,aErr);
                                        if (entryTag)
                                        {
                                            JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                            _snprintf(TheText,TheTextSize,"Modified : %s\r\n", JPEGDateStr.c_str() );
                                            TxtWindow.AppendText( TheText);
                                            UpdatedInfo=true;
                                        }
                                    }
                                    if (wOpts & OPT_MODIFY_CRT_TIME)
                                    {
                                        // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                                        entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                                        if (entryTag)
                                        {
                                            JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                            _snprintf(TheText,TheTextSize,"Created : %s\r\n", JPEGDateStr.c_str() );
                                            TxtWindow.AppendText( TheText);
                                            UpdatedInfo=true;
                                        }
                                    }

                                    if (!UpdatedInfo)
                                    {
                                        TxtWindow.AppendText( "Problems with updated values!\r\n");
                                    }
                                }
                                else
                                {
                                     TxtWindow.AppendText( "None\r\n");
                                }
                            }
                            // Close the file
                            if (ModifiedValues)
                            {
                                if( inImageFile.close() != EXIF_OK )
                                {
                                    _snprintf(TheText,TheTextSize,"Error: Could not close JPEG file : %s\r\n", TheFileName );
                                }
                            }
                            else
                            {
                                if( inImageFile.closeDoNotSave() != EXIF_OK )
                                {
                                    _snprintf(TheText,TheTextSize,"Error: Could not close JPEG file : %s\r\n", TheFileName );
                                }
                            }
                        }
                        else
                        {
                            _snprintf(TheText,TheTextSize, "FAILED to access EXIF attributes for \"%s\"\r\n",TheFileName);
                            TxtWindow.AppendText( TheText);
                        }

                        // get next file name
                        if (NextFilePos>0)
                        {
                            StrLen=strlen(&TheFileName[NextFilePos]);
                            if (StrLen>0)
                            {
                                strcpy(TheFileName,&TheFileName[NextFilePos]);
                                NextFilePos=NextFilePos+StrLen+1;
                            }
                            else
                            {
                                NextFilePos=0;
                            }
                        }

                        // Update window messages
                        ProcessPendingEvents();
                    } while (NextFilePos>0 && ContinueOperation);

                    _snprintf(TheText,TheTextSize,"=========================\r\n");
                    TxtWindow.AppendText( TheText);
                    if (ContinueOperation)
                    {
                        TxtWindow.AppendText( _T("Operation Complete"));
                    }
                    else
                    {
                        TxtWindow.AppendText( _T("Aborted!"));
                    }
                }
                else
                {
                    // failed to open all files
                    DWORD WinErrorCode=CommDlgExtendedError();
                    switch (WinErrorCode)
                    {
                    case 0:
                        // Cancel pressed
                        break;
                    case FNERR_BUFFERTOOSMALL:
                        winBeep();
                        MessageBox(hDlg,"Too many files selected.\n Please select fewer files and try again.","Error",MB_OK|MB_ICONINFORMATION);
                        break;
                    default:
                        MessageBox(hDlg,"Problem selecting files.\n Please select fewer files and try again.","Error",MB_OK|MB_ICONINFORMATION);
                        break;
                    }
                }
                ContinueOperation=false;
                EnableInputControls(hDlg,TRUE);
                if (Undolist.empty())
                {
                    EnableWindow(GetDlgItem(hDlg,IDUNDOABORT), FALSE);
                }
                else
                {
                    EnableWindow(GetDlgItem(hDlg,IDUNDOABORT), TRUE);
                }
            }
            break;

            case IDUNDOABORT: // this button is used for both undo can cancel operation
                if (ContinueOperation)
                {
                    // already processing so cancel current operation
                    ContinueOperation=false;
                    EnableWindow(GetDlgItem(hDlg,IDUNDOABORT), FALSE);
                }
                else if (!Undolist.empty())
                {
                    if (MessageBox(hDlg,"Undo previous changes?","Error",MB_YESNO|MB_ICONQUESTION)==IDYES)
                    {
                        char TheText[TheTextSize];
                        EnableInputControls(hDlg,FALSE);
                        TxtWindow.Clear();
                        TxtWindow.AppendText( _T("Undo Status....\r\n"));

                        std::string JPEGDateStr;
                        std::string JPGDtime,JPGMtime,JPGCtime;
                        std::vector<FileDateClass>::iterator UndoIterator;
                        ContinueOperation=true;
                        unsigned int UndoCount=0;
                        for (UndoIterator =  Undolist.begin(); (UndoIterator != Undolist.end() && ContinueOperation); ++UndoIterator)
                        {
                            WORD wOpts = (*UndoIterator).GetwOpts();

                            _snprintf(TheText,TheTextSize, "=========================\r\n");
                            TxtWindow.AppendText( TheText);

                            (*UndoIterator).GetFileTimes(JPGDtime,JPGMtime,JPGCtime);

                            std::string TheFileName;
                            (*UndoIterator).GetFileName(TheFileName);
                            UndoCount++;

                            ExifImageFile inImageFile;
                            if (inImageFile.open(TheFileName.c_str(), "r+") == EXIF_OK)
                            {
                                ExifStatus aErr;

                                _snprintf(TheText,TheTextSize, "Accessing attributes for \"%s\"\r\n",TheFileName.c_str());
                                TxtWindow.AppendText( TheText);                                
 
                                // EXIFTAG_DALETIMEDIGITIZED Date/Time of image digitized
                                ExifTagEntry* entryTag=NULL;
                                entryTag = inImageFile.getGenericTag(EXIFTAG_DALETIMEDIGITIZED,EXIF_APP1_EXIFIFD,aErr);
                                if (entryTag)
                                {
                                    JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                    _snprintf(TheText,TheTextSize,"Digitized : %s\r\n", JPEGDateStr.c_str() );
                                    TxtWindow.AppendText( TheText);

                                    if (wOpts & OPT_MODIFY_DIG_TIME)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPGDtime);
                                    }
                                }
                                else
                                {
                                    TxtWindow.AppendText( "No EXIF Digitized time information\r\n");
                                }

                                // EXIFTAG_DATETIME Date/Time of image was last modified
                                entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIME,EXIF_APP1_IFD0,aErr);
                                if (entryTag)
                                {
                                    JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                    _snprintf(TheText,TheTextSize,"Modified : %s\r\n", JPEGDateStr.c_str() );
                                    TxtWindow.AppendText( TheText);
                                
                                    if ( wOpts & OPT_MODIFY_MOD_TIME)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPGMtime);
                                    }
                                }
                                else
                                {
                                    TxtWindow.AppendText( "No EXIF Modified time information\r\n");
                                }

                                // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                                entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                                if (entryTag)
                                {
                                    JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                    _snprintf(TheText,TheTextSize,"Created : %s\r\n", JPEGDateStr.c_str() );
                                    TxtWindow.AppendText( TheText);
                                    if ( wOpts & OPT_MODIFY_CRT_TIME)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPGCtime);
                                    }
                                }
                                else
                                {
                                    TxtWindow.AppendText( "No EXIF Original image time information\r\n");
                                }
			                   
                                _snprintf(TheText,TheTextSize,"Updated Values....\r\n");
                                TxtWindow.AppendText( TheText);

                                // Output updated values

                                bool UpdatedInfo=false;
                                if (wOpts & OPT_MODIFY_DIG_TIME)
                                {
                                    // EXIFTAG_DALETIMEDIGITIZED Date/Time of image digitized
                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DALETIMEDIGITIZED,EXIF_APP1_EXIFIFD,aErr);
                                    if (entryTag)
                                    {
                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Digitized : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText( TheText);
                                        UpdatedInfo=true;
                                    }
                                }
                                if (wOpts & OPT_MODIFY_MOD_TIME)
                                {
                                    // EXIFTAG_DATETIME Date/Time of image was last modified
                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIME,EXIF_APP1_IFD0,aErr);
                                    if (entryTag)
                                    {
                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Modified : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText( TheText);
                                        UpdatedInfo=true;
                                    }
                                }
                                if (wOpts & OPT_MODIFY_CRT_TIME)
                                {
                                    // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                                    if (entryTag)
                                    {
                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Created : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText( TheText);
                                        UpdatedInfo=true;
                                    }
                                }

                                if (!UpdatedInfo)
                                {
                                    TxtWindow.AppendText( "None\r\n");
                                }
                            
                                // Close the file
                                if( inImageFile.close() != EXIF_OK )
                                {
                                    _snprintf(TheText,TheTextSize,"Error: Could not close JPEG file : %s\r\n", TheFileName.c_str());
                                    TxtWindow.AppendText( TheText);
                                }
                            }
                            else
                            {
                                _snprintf(TheText,TheTextSize, "FAILED to access EXIF attributes for \"%s\"\r\n",TheFileName.c_str());
                                TxtWindow.AppendText( TheText);
                            }

                            // Update window messages
                            ProcessPendingEvents();
                        }
                        _snprintf(TheText,TheTextSize,"=========================\r\n");
                        TxtWindow.AppendText( TheText);
                        if (ContinueOperation)
                        {
                            Undolist.clear();
                            TxtWindow.AppendText( _T("Undo Complete"));;
                        }
                        else
                        {
                            // remove any operations from the undo list were processed
                            if (UndoCount>0)
                            {
                                UndoIterator = Undolist.begin()+(UndoCount-1);
                                Undolist.erase(Undolist.begin(),UndoIterator);
                            }
                            TxtWindow.AppendText( _T("Undo Aborted!"));
                        }
                        
                        EnableInputControls(hDlg,TRUE);
                        ContinueOperation=false;
                        if (Undolist.size()>0)
                        {
                            EnableWindow(GetDlgItem(hDlg,IDUNDOABORT), TRUE);
                        }
                        else
                        {
                            EnableWindow(GetDlgItem(hDlg,IDUNDOABORT), FALSE);
                        }
                    }
                }
                break;

            case IDC_SPIN_HOURS:
                {
                    char TheText[TheTextSize];
                    SendDlgItemMessage(hDlg, IDC_HoursEdit, WM_GETTEXT, (WPARAM) TheTextSize, (LPARAM) TheText);
                    aVal=atoi(TheText);
                    aVal++;
                    _snprintf(TheText,TheTextSize,"%i",aVal);
                    SendDlgItemMessage(hDlg, IDC_HoursEdit, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) TheText);
                }
                return TRUE;

            default:
                return TRUE;
			}
			break;
	}
    return FALSE;
}