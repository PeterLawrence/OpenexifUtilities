///////////////////////////////////////////////////////////////////////////////////
//
// JPEGRename.cpp 
//
// By Peter J Lawrence Jan 2007 Email P.J.Lawrence@gre.ac.uk
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
// v1.0.0 first release (PJL 14/01/07)
//
// Minor modifications to user interface (PJL 16/01/07)
// The ability to cope with repeated/already existing filenames. (PJL 16/01/07)
// If a repeated/existing filename then assigns a new filename as Filename(X).jpg where X is a unique number. (PJL 16/01/07)
// v1.0.1 release (PJL 16/01/07)
//
// Changed HHhMMs to HHhMMm (PJL 24/01/07)
// Included more date formats (PJL 24/01/07)
// fixed haveJPEGData flag so that it will be false on each loop around the do while loop (PJL 24/01/07)
// v1.0.2 released (PJL 24/01/07)
//
// Fixed min sizing of dialogue box (26/01/07)
// Included more time formats (29/01/07)
// v1.0.3 released (PJL 29/01/07)
//
// Updated registry code (PJL 01/02/07)
// Include extra data in registry (PJL 02/02/07)
// v1.0.4 released (PJL 02/02/07)
//
// Improved text control text output (PJL 12/02/07) 
// Added abort functionality (PJL 12/02/07)
// Fixed problem with Iconized Control Dialogue being closed and saving of registry (PJL 19/02/07)
// v1.05 release (PJL 20/02/07)
//
// Fixed problem relating to daylight saving and file time (PJL 23/08/07) 
// v1.06 release (PJL 23/08/07)
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
#include "dlgtxtctrl.h"
#include "resource.h"
#include "stdio.h"
#include "math.h"
#include "commctrl.h"
#include "commdlg.h"
#include <sys/stat.h>
#include <time.h>
#include <direct.h>
#include "cderr.h"
///////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
///////////////////////////////////////////////////////////////////////////////////
#define MinXValDlg 387
#define MinYValDlg 246
///////////////////////////////////////////////////////////////////////////////////
// Foward declarations of functions included in this code module:
LRESULT CALLBACK	RenameControlDlg(HWND, UINT, WPARAM, LPARAM);
///////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// Perform application initialization:
    DialogBox(hInstance, (LPCTSTR)IDD_MAIN_DIALOG, NULL, (DLGPROC)RenameControlDlg);
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////
#define FileDateAttributeToUseSize 3
const char *g_FileDateAttributeToUse[FileDateAttributeToUseSize] = { "Photo Taken","File Creation","File Modification" };
#define PhotoTaken 0
#define FileCreation 1
#define FileModification 2
//////////////////////////////////////////////////////////////////////////////////
#define FieldSpacingSize 4
const char *g_FieldSpacing[FieldSpacingSize] = { "None","Space","Dash (-)","Underscore (_)" };
#define SpacingNone 0
#define SpacingSpace 1
#define SpacingDash 2
#define SpacingUnderscore 3
//////////////////////////////////////////////////////////////////////////////////
#define DateFormatSize 18
const char *g_DateFormat[DateFormatSize] = {"YYYYMMDD","YYYYMM","YYYY-MM-DD","YYYY-MM","DDMMMYEAR","DDMMM",
                                            "DDMMYY",  "DD-MM-YY",  "DDdMMmYYy"  ,"MMDDYY",  "MM-DD-YY",  "MMmDDdYYy",
                                            "DDMMYYYY","DD-MM-YYYY","DDdMMmYYYYy","MMDDYYYY","MM-DD-YYYY","MMmDDdYYYYy" };
#define DateFormatYYYYMMDD        0
#define DateFormatYYYYMM          1
#define DateFormatYYYYMMDDDash    2
#define DateFormatYYYYMMDash      3
#define DateFormatDDMMMYEAR       4
#define DateFormatDDMMM           5
#define DateFormatDDMMYY          6
#define DateFormatDDMMYYDash      7
#define DateFormatDDMMYYLetter    8
#define DateFormatMMDDYY          9
#define DateFormatMMDDYYDash     10
#define DateFormatMMDDYYLetter   11
#define DateFormatDDMMYYYY       12
#define DateFormatDDMMYYYYDash   13
#define DateFormatDDMMYYYYLetter 14
#define DateFormatMMDDYYYY       15
#define DateFormatMMDDYYYYDash   16
#define DateFormatMMDDYYYYLetter 17
//////////////////////////////////////////////////////////////////////////////////
#define TimeFormatSize 11
const char *g_TimeFormat[TimeFormatSize] = {"HHhMMmSSs","HHhMMm","HH-MM-SS","HH-MM","HH.MM.SS","HH.MM","HH MM SS","HH MM","H-Mxm (12 hour)","H.Mxm (12 hour)","H Mxm (12 hour)" };
#define TimeFormatHHhMMmSSs   0
#define TimeFormatHHhMMm      1
#define TimeFormatHHMMSSDash  2
#define TimeFormatHHMMDash    3
#define TimeFormatHHMMSSDot   4
#define TimeFormatHHMMDot     5
#define TimeFormatHHMMSSSpace 6
#define TimeFormatHHMMSpace   7
#define TimeFormatHMxmDash    8
#define TimeFormatHMxmDot     9
#define TimeFormatHMxmSpace  10
//////////////////////////////////////////////////////////////////////////////////
#define FieldFormatSize 6
const char *g_FieldFormat[FieldFormatSize] = {"Date","Time","Filename","User Text","Count","None" };
#define FileFormatDate     0
#define FileFormatTime     1
#define FileFormatFileName 2
#define FileFormatUserText 3
#define FileFormatCount    4
#define FileFormatNone     5
//////////////////////////////////////////////////////////////////////////////////
//
// Read a Dialogue Text control
//
bool ReadDlgTextCtrl(HWND hDlg,unsigned int TextID,std::string &StrContents)
{
    int StrLen=SendDlgItemMessage(hDlg,TextID,EM_LINELENGTH,0,0);
    if (StrLen>0)
    {
        char*  STempStr=new char[StrLen+1];
        if (STempStr)
        {
            SendDlgItemMessage(hDlg,TextID, WM_GETTEXT, (WPARAM) StrLen+1, (LPARAM) STempStr);
            StrContents.assign(STempStr);
            delete [] STempStr;
            return (true);
        }
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
//
// Read a Dialogue Text control which contains numbers
//
bool ReadDlgTextCtrl(HWND hDlg,unsigned int TextID,int &TheValue)
{
    TheValue=0;
    std::string aString;
    if (ReadDlgTextCtrl(hDlg,TextID,aString))
    { 
        if (sscanf(aString.c_str(),"%i",&TheValue)==1)
        {
            return(true);
        }
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
BOOL SaveCurrentStatus(HWND hWnd,const std::string aWorkingFolder)
{
    RECT TheRect;
    GetWindowRect(hWnd,&TheRect);

    LONG            lRetVal;
    HKEY            hkResult;
    lRetVal = RegCreateKeyEx( HKEY_CURRENT_USER, 
                        _T("SOFTWARE\\WinJPEGRename"), 0, NULL, 0,
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

        int FileDateAttribute=SendDlgItemMessage(hWnd,IDC_FileDateAttribute, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("FileDateAttribute"),NULL, REG_DWORD, (PBYTE) &FileDateAttribute, sizeof(FileDateAttribute) );
        int FieldSpacing=SendDlgItemMessage(hWnd,IDC_FieldSpacing, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("FieldSpacing"),NULL, REG_DWORD, (PBYTE) &FieldSpacing, sizeof(FieldSpacing) );
        int DateFormat=SendDlgItemMessage(hWnd,IDC_DateFormat, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("DateFormat"),NULL, REG_DWORD, (PBYTE) &DateFormat, sizeof(DateFormat) );
        int TimeFormat=SendDlgItemMessage(hWnd,IDC_TimeFormat, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("TimeFormat"),NULL, REG_DWORD, (PBYTE) &TimeFormat, sizeof(TimeFormat) );
        
        std::string aString;
        if (ReadDlgTextCtrl(hWnd,IDC_UserText,aString))
        {
             RegSetValueEx(hkResult, _T("UserString"), NULL, REG_EXPAND_SZ, (PBYTE)aString.c_str(), aString.length()+1 );
        }
        int Counter=0;
        if (ReadDlgTextCtrl(hWnd,IDC_Counter,Counter))
        {
            RegSetValueEx( hkResult, _T("CounterVal"),NULL, REG_DWORD, (PBYTE) &Counter, sizeof(Counter) );
        }
        int FieldOptions1=SendDlgItemMessage(hWnd,IDC_Field1, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("FieldOptions1"),NULL, REG_DWORD, (PBYTE) &FieldOptions1, sizeof(FieldOptions1) );
        int FieldOptions2=SendDlgItemMessage(hWnd,IDC_Field2, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("FieldOptions2"),NULL, REG_DWORD, (PBYTE) &FieldOptions2, sizeof(FieldOptions2) );
        int FieldOptions3=SendDlgItemMessage(hWnd,IDC_Field3, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("FieldOptions3"),NULL, REG_DWORD, (PBYTE) &FieldOptions3, sizeof(FieldOptions3) );
        int FieldOptions4=SendDlgItemMessage(hWnd,IDC_Field4, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("FieldOptions4"),NULL, REG_DWORD, (PBYTE) &FieldOptions4, sizeof(FieldOptions4) );
        int FieldOptions5=SendDlgItemMessage(hWnd,IDC_Field5, CB_GETCURSEL ,0,0);
        RegSetValueEx( hkResult, _T("FieldOptions5"),NULL, REG_DWORD, (PBYTE) &FieldOptions5, sizeof(FieldOptions5) );

        if (aWorkingFolder.length()>0)
        {
            RegSetValueEx( hkResult, _T("WorkingFolder"), NULL, REG_EXPAND_SZ, (PBYTE)aWorkingFolder.c_str(), aWorkingFolder.length()+1 );
        }

        RegCloseKey( hkResult );
    }
    return(true);
}
//////////////////////////////////////////////////////////////////////////////////
bool SelectItem(HWND hWnd,int TheItem,int TheIndex)
{
    HWND hwndList = GetDlgItem(hWnd, TheItem);
    if (hwndList)
    {
        SendMessage(hwndList, CB_SETCURSEL, TheIndex, (LPARAM) 0);
        return (true);
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
BOOL LoadCurrentStatus(HWND hWnd,bool RetoreWindowStatus,std::string &aWorkingFolder)
{
    LONG            lRetVal;
    HKEY            hkResult;
    DWORD size;

    lRetVal = RegCreateKeyEx( HKEY_CURRENT_USER, 
                        _T("SOFTWARE\\WinJPEGRename"), 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hkResult, NULL );
    if( lRetVal == ERROR_SUCCESS )
    {
        RECT TheRect;
        GetWindowRect(hWnd,&TheRect);
        TheRect.right-=TheRect.left;
        TheRect.bottom-=TheRect.top;

        size = sizeof(TheRect.left);
        RegQueryValueEx( hkResult, _T("WinLeftPos"),NULL, NULL, (PBYTE) &TheRect.left, &size );
        RegQueryValueEx( hkResult, _T("WinTopPos"), NULL, NULL, (PBYTE) &TheRect.top,  &size);
        RegQueryValueEx( hkResult, _T("WinWidth"),  NULL, NULL, (PBYTE) &TheRect.right, &size );
        RegQueryValueEx( hkResult, _T("WinHeight"), NULL, NULL, (PBYTE) &TheRect.bottom, &size );

        int FileDateAttribute;
        size = sizeof(FileDateAttribute);
        if (RegQueryValueEx( hkResult, _T("FileDateAttribute"),NULL, NULL, (PBYTE) &FileDateAttribute, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_FileDateAttribute,FileDateAttribute);
        }

        DWORD MaxSubKeyLen,ValuesCount,MaxValueNameLen,MaxValueLen;
        lRetVal= RegQueryInfoKey(hkResult, NULL, NULL, NULL, NULL, &MaxSubKeyLen, NULL, 
                                 &ValuesCount, &MaxValueNameLen, &MaxValueLen, NULL, NULL);
        char *DataStr=NULL;

        if( lRetVal == ERROR_SUCCESS )
        {
            if (MaxValueLen>0)
            {
                MaxValueLen++;
                DataStr=new char[MaxValueLen];
            }
        }

        int FieldSpacing;
        size = sizeof(FieldSpacing);
        if (RegQueryValueEx( hkResult, _T("FieldSpacing"),NULL, NULL, (PBYTE) &FieldSpacing, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_FieldSpacing,FieldSpacing);
        }
        int DateFormat;
        if (RegQueryValueEx( hkResult, _T("DateFormat"),NULL, NULL, (PBYTE) &DateFormat, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_DateFormat,DateFormat);
        }
        int TimeFormat;
        if (RegQueryValueEx( hkResult, _T("TimeFormat"),NULL, NULL, (PBYTE) &TimeFormat, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_TimeFormat,TimeFormat);
        }

        if (DataStr)
        {
            DWORD DataLength=MaxValueLen;
            lRetVal = RegQueryValueEx( hkResult, _T("UserString"), NULL, NULL, (PBYTE) DataStr, &DataLength );
            if (lRetVal == ERROR_SUCCESS)
            {
                SendDlgItemMessage( hWnd,IDC_UserText, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) DataStr);
            }
        }
        int UseCounter;
        if (RegQueryValueEx( hkResult, _T("CounterVal"),NULL, NULL, (PBYTE) &UseCounter, &size )==ERROR_SUCCESS)
        {
            char TextBuff[10];
            _snprintf(TextBuff,9,"%-i",UseCounter);
            SendDlgItemMessage( hWnd,IDC_Counter, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) TextBuff);
        }

        int FieldOptions;
        if (RegQueryValueEx( hkResult, _T("FieldOptions1"),NULL, NULL, (PBYTE) &FieldOptions, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_Field1,FieldOptions);
        }
        if (RegQueryValueEx( hkResult, _T("FieldOptions2"),NULL, NULL, (PBYTE) &FieldOptions, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_Field2,FieldOptions);
        }
        if (RegQueryValueEx( hkResult, _T("FieldOptions3"),NULL, NULL, (PBYTE) &FieldOptions, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_Field3,FieldOptions);
        }
        if (RegQueryValueEx( hkResult, _T("FieldOptions4"),NULL, NULL, (PBYTE) &FieldOptions, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_Field4,FieldOptions);
        }
        if (RegQueryValueEx( hkResult, _T("FieldOptions5"),NULL, NULL, (PBYTE) &FieldOptions, &size )==ERROR_SUCCESS)
        {
            SelectItem(hWnd,IDC_Field5,FieldOptions);
        }

        if (RetoreWindowStatus)
        {
            if (TheRect.left<0)
            {
                TheRect.left=0;
            }
            if (TheRect.top<0)
            {
                TheRect.top=0;
            }
            if (TheRect.right<MinXValDlg)
            {
                TheRect.right=MinXValDlg;
            }
            if (TheRect.bottom<MinYValDlg)
            {
                TheRect.bottom=MinYValDlg;
            }
            SetWindowPos(hWnd,HWND_TOP,TheRect.left,TheRect.top,TheRect.right,TheRect.bottom,SWP_SHOWWINDOW);
        }

        if (DataStr)
        {
            lRetVal = RegQueryValueEx( hkResult, _T("WorkingFolder"), NULL, NULL, (PBYTE) DataStr, &MaxValueLen );
            if (lRetVal == ERROR_SUCCESS)
            {
                aWorkingFolder.assign(DataStr);
            }
            delete [] DataStr;
        }
        RegCloseKey( hkResult );
    }
    return(true);
}
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
/////////////////////////////////////////////////////////////////////////////
//
// Gets file times from a file
//
static bool GetFileTimes(LPCTSTR    lpszTemplateFileName,
						 FILETIME*  tsAtime,
						 FILETIME*  tsMtime,
						 FILETIME*  tsCtime) 
{
	HANDLE hFile = CreateFile(
		lpszTemplateFileName, 
		GENERIC_READ, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		0);

	if(INVALID_HANDLE_VALUE == hFile)
    {
		return false;
	}

	if(!GetFileTime(hFile, tsCtime, tsAtime, tsMtime))
    {
		CloseHandle(hFile);
		return false;
	}
	CloseHandle(hFile);

    // Convert times to local time
    FILETIME LocTime;
    if (!FileTimeToLocalFileTime(tsAtime,&LocTime))
    {    
        return false;
    }
    *tsAtime=LocTime;
    if (!FileTimeToLocalFileTime(tsMtime,&LocTime))
    {   
        return false;
    }
    *tsMtime=LocTime;
    if (!FileTimeToLocalFileTime(tsCtime,&LocTime))
    {
        return false;
    }
    *tsCtime=LocTime;

	return true;
}
//////////////////////////////////////////////////////////////////////////////////
//
//  Remove all characters which are not allowed in a window's filename
//
bool RemoveNonStandardCharacters(std::string &TheString)
{
    int pos;
    bool RemovedChar=false;
    for (pos=0;pos<TheString.length();pos++)
    {
        switch (TheString.at(pos))
        {
        case '\\':
        case '/':
        case ':':
        case '*':
        case '?':
        case '\"':
        case '<':
        case '>':
        case '|':
            TheString.erase(pos,1);
            RemovedChar=true;
            pos--;
            break;
        }
    }
    return (RemovedChar);
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
//  Generates a file date string 
//
bool MakeDateStr(SYSTEMTIME &atime,int StrFormat,char *DateStr,int DateStrSize)
{
    char *Months[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    switch (StrFormat)
    {
    case DateFormatYYYYMMDD:
        _snprintf(DateStr,DateStrSize,"%04i%02i%02i",
                                        atime.wYear,atime.wMonth,atime.wDay);
        break;
    case DateFormatYYYYMM:
        _snprintf(DateStr,DateStrSize,"%04i%02i",
                                        atime.wYear,atime.wMonth);
        break;
    case DateFormatYYYYMMDDDash:
        _snprintf(DateStr,DateStrSize,"%04i-%02i-%02i",
                                        atime.wYear,atime.wMonth,atime.wDay);
        break;
    case DateFormatYYYYMMDash:
        _snprintf(DateStr,DateStrSize,"%04i-%02i",
                                        atime.wYear,atime.wMonth);
        break;
    case DateFormatDDMMMYEAR:
        _snprintf(DateStr,DateStrSize,"%02i%3s%04i",
                                        atime.wDay,Months[atime.wMonth-1],atime.wYear);
        break;
    case DateFormatDDMMM:
        _snprintf(DateStr,DateStrSize,"%02i%3s%",
                                        atime.wDay,Months[atime.wMonth-1]);
        break;
    case DateFormatDDMMYY:
        {
            int YY=atime.wYear % 1000;
            _snprintf(DateStr,DateStrSize,"%02i%02i%02i",
                                         atime.wDay,atime.wMonth,YY);
        }
        break;
    case DateFormatDDMMYYDash:
        {
            int YY=atime.wYear % 1000;
            _snprintf(DateStr,DateStrSize,"%02i-%02i-%02i",
                                         atime.wDay,atime.wMonth,YY);
        }
        break;
    case DateFormatDDMMYYLetter:
        {
            int YY=atime.wYear % 1000;
            _snprintf(DateStr,DateStrSize,"%02id%02im%02iy",
                                         atime.wDay,atime.wMonth,YY);
        }
        break;
    case DateFormatMMDDYY:
        {
            int YY=atime.wYear % 1000;
            _snprintf(DateStr,DateStrSize,"%02i%02i%02i",
                                         atime.wMonth,atime.wDay,YY);
        }
        break;
    case DateFormatMMDDYYDash:
        {
            int YY=atime.wYear % 1000;
            _snprintf(DateStr,DateStrSize,"%02i-%02i-%02i",
                                         atime.wMonth,atime.wDay,YY);
        }
        break;
    case DateFormatMMDDYYLetter:
        {
            int YY=atime.wYear % 1000;
            _snprintf(DateStr,DateStrSize,"%02im%02id%02iy",
                                         atime.wMonth,atime.wDay,YY);
        }
        break;
    case DateFormatDDMMYYYY:
        _snprintf(DateStr,DateStrSize,"%02i%02i%04i",
                                         atime.wDay,atime.wMonth,atime.wYear);
        break;
    case DateFormatDDMMYYYYDash:
            _snprintf(DateStr,DateStrSize,"%02i-%02i-%04i",
                                         atime.wDay,atime.wMonth,atime.wYear);
        break;
    case DateFormatDDMMYYYYLetter:
            _snprintf(DateStr,DateStrSize,"%02id%02im%04iy",
                                         atime.wDay,atime.wMonth,atime.wYear);
        break;
    case DateFormatMMDDYYYY:
            _snprintf(DateStr,DateStrSize,"%02i%02i%04i",
                                         atime.wMonth,atime.wDay,atime.wYear);
        break;
    case DateFormatMMDDYYYYDash:
            _snprintf(DateStr,DateStrSize,"%02i-%02i-%04i",
                                         atime.wMonth,atime.wDay,atime.wYear);
        break;
    case DateFormatMMDDYYYYLetter:
            _snprintf(DateStr,DateStrSize,"%02im%02id%04iy",
                                         atime.wMonth,atime.wDay,atime.wYear);
        break;
    }

    return (true);
}
//////////////////////////////////////////////////////////////////////////////////
//
//  Generates a file time string  
//
bool MakeTimeStr(SYSTEMTIME &atime,int StrFormat,char *TimeStr,int TimeStrSize)
{
    switch (StrFormat)
    {
    case TimeFormatHHhMMmSSs:
        _snprintf(TimeStr,TimeStrSize,"%02ih%02im%02is",atime.wHour,atime.wMinute,atime.wSecond);
        break;
    case TimeFormatHHhMMm:
        _snprintf(TimeStr,TimeStrSize,"%02ih%02im",atime.wHour,atime.wMinute);
        break;
    case TimeFormatHHMMSSDash:
        _snprintf(TimeStr,TimeStrSize,"%02i-%02i-%02i",atime.wHour,atime.wMinute,atime.wSecond);
        break;
    case TimeFormatHHMMDash:
        _snprintf(TimeStr,TimeStrSize,"%02i-%02i",atime.wHour,atime.wMinute);
        break;
    case TimeFormatHHMMSSDot:
        _snprintf(TimeStr,TimeStrSize,"%02i.%02i.%02i",atime.wHour,atime.wMinute,atime.wSecond);
        break;
    case TimeFormatHHMMDot:
        _snprintf(TimeStr,TimeStrSize,"%02i.%02i",atime.wHour,atime.wMinute);
        break;
    case TimeFormatHHMMSSSpace:
        _snprintf(TimeStr,TimeStrSize,"%02i %02i %02i",atime.wHour,atime.wMinute,atime.wSecond);
        break;
    case TimeFormatHHMMSpace:
        _snprintf(TimeStr,TimeStrSize,"%02i %02i",atime.wHour,atime.wMinute);
        break;
    case TimeFormatHMxmDash:
        if (atime.wHour>12)
        {
            int aTime=atime.wHour % 12;
            _snprintf(TimeStr,TimeStrSize,"%02i-%02ipm",aTime,atime.wMinute);
        }
        else
        {
            _snprintf(TimeStr,TimeStrSize,"%02i-%02iam",atime.wHour,atime.wMinute);
        }
        break;
    case TimeFormatHMxmDot:
        if (atime.wHour>12)
        {
            int aTime=atime.wHour % 12;
            _snprintf(TimeStr,TimeStrSize,"%02i.%02ipm",aTime,atime.wMinute);
        }
        else
        {
            _snprintf(TimeStr,TimeStrSize,"%02i.%02iam",atime.wHour,atime.wMinute);
        }
        break;
    case TimeFormatHMxmSpace:
        if (atime.wHour>12)
        {
            int aTime=atime.wHour % 12;
            _snprintf(TimeStr,TimeStrSize,"%02i %02ipm",aTime,atime.wMinute);
        }
        else
        {
            _snprintf(TimeStr,TimeStrSize,"%02i %02iam",atime.wHour,atime.wMinute);
        }
        break;

    }
    return (true);
}
//////////////////////////////////////////////////////////////////////////////////
//
// removes the extension from a filename by replacing "." with 
// terminate sringe code (zero)
// theExtension is a pointer to the start of the Extension in the filename
//
//  returns true if extension removed
//
bool RemoveExtension(char *filename, char *&theExtension)
{
    if (!filename) return false;
    int StrLen=(strlen(filename)-2); // start at least one character in.
    if (StrLen>0)
    {
        int i=0;
        for (i=StrLen;i>0;--i)
        {
            if (filename[i]=='.')
            {
                theExtension=&filename[i+1];
                filename[i]=0;
                return (true);
            }
        }
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

    MoveDlgItem(DlgWin,IDRENAME,XOffset,YOffset,BOTTOMSTICKY);
    MoveDlgItem(DlgWin,IDTEST,XOffset,YOffset,BOTTOMSTICKY);
    MoveDlgItem(DlgWin,IDUNDOABORT,XOffset,YOffset,BOTTOMSTICKY);
    MoveDlgItem(DlgWin,IDCANCEL,XOffset,YOffset,BOTTOMSTICKY);

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
    std::string m_OrgFileName;
    std::string m_NewFileName;
public:

    FileDateClass() { m_OrgFileName.assign("NULL"); m_NewFileName.assign("NULL");}

    FileDateClass(const FileDateClass &SrcClass)
    {
        m_OrgFileName.assign(SrcClass.m_OrgFileName);
        m_NewFileName.assign(SrcClass.m_NewFileName);
    }

    FileDateClass(const char* aOrgFileName,const char* aNewFileName)
    {
        m_OrgFileName.assign(aOrgFileName);
        m_NewFileName.assign(aNewFileName);
    }

    bool GetOrgFileName(std::string &aFileName)
    {
        aFileName=m_OrgFileName;
        return (true);
    }

    bool GetOrgFileName(char* aFileName,int aFileNameSize)
    {
        strncpy(aFileName,m_OrgFileName.c_str(),aFileNameSize);
        return (true);
    }

    bool GetNewFileName(std::string &aFileName)
    {
        aFileName=m_NewFileName;
        return (true);
    }

    bool GetNewFileName(char* aFileName,int aFileNameSize)
    {
        strncpy(aFileName,m_NewFileName.c_str(),aFileNameSize);
        return (true);
    }
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
void EnableInputControls(HWND hDlg, BOOL Status)
{
    EnableWindow(GetDlgItem(hDlg,IDRENAME), Status);
    EnableWindow(GetDlgItem(hDlg,IDTEST), Status);
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
bool FillSelectionBox(HWND aDlg,int SelectionId,int FileSize,const char* FileList[],int Select=0)
{
    HWND hwndList = GetDlgItem(aDlg, SelectionId);
    if (hwndList)
    {
        int i;
        for (i = 0; i < FileSize; i++) 
        { 
            SendMessage(hwndList, CB_INSERTSTRING , i,  (LPARAM) FileList[i]); 

        }
        SendMessage(hwndList, CB_SETCURSEL, Select, (LPARAM) 0);
        return (true);
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
bool InsertSeparator(std::string &TheString, int FieldSpacing)
{
    if (TheString.length()>0)
    {
        switch (FieldSpacing)
        {
        case SpacingSpace:
            TheString.append(" ");
            return (true);
            break;
        case SpacingDash:
            TheString.append("-");
            return (true);
            break;
        case SpacingUnderscore:
            TheString.append("_");
            return (true);
            break;
        case SpacingNone:
        default:
            break;
        }
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
//
//  returns true if aFileName is in the list of already used names
//
bool FileNameAlreadyUsed(const std::string &aFileName,const std::vector<std::string> &FileList)
{
    for (int i=0;i<FileList.size();i++)
    {
        if (aFileName.length()==FileList[i].length())
        {
            // same length
            bool SameString=true;;
            int j;
            for (j=0;(j<aFileName.length() && SameString);j++)
            {
                if (tolower(aFileName.at(j)) !=tolower(FileList[i].at(j)))
                {
                    SameString=false;
                }
            }
            if (SameString)
                return (true);
        }
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
//
// Finds starting location of file extension
//
bool FindExtension(const std::string &aFileName,int &ThePos)
{
    int StrLen=aFileName.length()-2; // start at least one character in.
    if (StrLen>0)
    {
        int i=0;
        for (i=StrLen;i>0;--i)
        {
            if (aFileName.at(i)=='.')
            {
                ThePos=i;
                return (true);
            }
        }
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
//
// make a unique filename
//
bool MakeUniqueFileName(std::string &aFileName,std::vector<std::string> &FileList,bool TestFileSystem)
{
    int anID=1;
    std::string NewName;
    NewName.assign(aFileName);

    bool RemoveExt=false;
    char TempChar[5];

    int ExtPos=0;
    if (FindExtension(aFileName,ExtPos))
    {
        if (ExtPos>2) // must be at least of a certain length
        {
            RemoveExt=true;
        }
    }

    while (anID<1000)
    {
        anID++;
        if (RemoveExt)
        {
            NewName.assign(aFileName,0,ExtPos-1);
        }
        else
        {
            NewName.assign(aFileName);
        }
        NewName.append("(");
        _snprintf(TempChar,5,"%i",anID);
        NewName.append(TempChar);
        NewName.append(")");
        if (RemoveExt)
        {
            NewName.append(aFileName,ExtPos,aFileName.length());
        }

        if (!FileNameAlreadyUsed(NewName,FileList))
        {
            if (TestFileSystem)
            {
                FILE *aFile=fopen(NewName.c_str(),"r");
                if (aFile)
                {
                    fclose(aFile);
                    FileList.push_back(NewName.c_str());
                    // file already exists
                    // generate new filename and try again
                }
                else
                {
                    aFileName.assign(NewName);
                    return (true);
                }
            }
            else
            {
                aFileName.assign(NewName);
                return (true);
            }
        }
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
//
// Mesage handler for about box.
//
LRESULT CALLBACK RenameControlDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int oldWidth=0,oldHeight=0;
    static std::vector<FileDateClass> Undolist;
    static std::string TheUndoDirectory;
    static std::string WorkingFolder;
    static std::vector<std::string> FileList;
    static DlgTxtControl TxtWindow(hDlg,IDC_EDITBOX);
    static bool ContinueOperation=false;

	switch (message)
	{
		case WM_INITDIALOG:  
            FillSelectionBox(hDlg,IDC_FileDateAttribute,FileDateAttributeToUseSize,g_FileDateAttributeToUse);
            FillSelectionBox(hDlg,IDC_FieldSpacing,FieldSpacingSize,g_FieldSpacing);
            FillSelectionBox(hDlg,IDC_DateFormat,DateFormatSize,g_DateFormat);
            FillSelectionBox(hDlg,IDC_TimeFormat,TimeFormatSize,g_TimeFormat);
            FillSelectionBox(hDlg,IDC_Field1,FieldFormatSize-1,g_FieldFormat);
            FillSelectionBox(hDlg,IDC_Field2,FieldFormatSize,g_FieldFormat,FileFormatTime);
            FillSelectionBox(hDlg,IDC_Field3,FieldFormatSize,g_FieldFormat,FieldFormatSize-1);
            FillSelectionBox(hDlg,IDC_Field4,FieldFormatSize,g_FieldFormat,FieldFormatSize-1);
            FillSelectionBox(hDlg,IDC_Field5,FieldFormatSize,g_FieldFormat,FieldFormatSize-1);

            SendDlgItemMessage( hDlg,IDC_UserText, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) "MyPhotos");
            SendDlgItemMessage( hDlg,IDC_Counter, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) "1");

            TxtWindow.Clear();
            TxtWindow.AppendText(_T("Status Window....\r\n"));
            TxtWindow.AppendText(_T("Version: 1.0.6 Aug 2007 (Freeware)\r\n"));
            TxtWindow.AppendText(_T("\r\n"));
            TxtWindow.AppendText(_T("Author: Peter J.Lawrence\r\n"));
            TxtWindow.AppendText(_T("email P.J.Lawrence@gre.ac.uk\r\n\r\n"));

            TxtWindow.AppendText(_T("This software is provided \"as is\", without any guarantee made as to its suitability or fitness for any particular use.\r\nThe Author takes no responsibility for any damage that may unintentionally be caused through its use.\r\n"));

            TxtWindow.AppendText(_T("\r\n"));
            TxtWindow.AppendText(_T("Incorporates the following third party libraries/applications/source code:-\r\n"));
            TxtWindow.AppendText(_T("      IJG library Release 6b\r\n"));
            TxtWindow.AppendText(_T("      OpenExif Version: 1.8\r\n"));

            SendDlgItemMessage( hDlg, IDC_SrcCreation,BM_SETCHECK,TRUE,NULL);
            SendDlgItemMessage( hDlg, IDC_SetFileModified,BM_SETCHECK,TRUE,NULL);

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
                if ( (ClientRect->right-ClientRect->left)<MinXValDlg ||
                     (ClientRect->bottom-ClientRect->top)<MinYValDlg )
                {
                    if ((ClientRect->right-ClientRect->left)<MinXValDlg)
                    {
                        ClientRect->right=ClientRect->left+MinXValDlg;
                    }
                    if ((ClientRect->bottom-ClientRect->top)<MinYValDlg)
                    {
                        ClientRect->bottom=ClientRect->top+MinYValDlg;
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
                {
                    SaveCurrentStatus(hDlg,WorkingFolder);
				    EndDialog(hDlg, LOWORD(wParam));
                }
				return TRUE;

            case IDC_SetDigitized:
            case IDC_SetModified:
            case IDC_SetCreation:
            case IDC_SetFileAccessed:
            case IDC_SetFileModified:
            case IDC_SetFileCreation:
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

            case IDTEST:
            case IDRENAME:
            {
                #define TheTextSize 200
                char TheText[TheTextSize];

                int FileDateAttribute=SendDlgItemMessage(hDlg,IDC_FileDateAttribute, CB_GETCURSEL ,0,0);
                if (FileDateAttribute==CB_ERR)
                {
                    TxtWindow.AppendText("ERROR: Can't set attributes\r\n");
                    // problem with selection
                    break;
                }
                int FieldSpacing=SendDlgItemMessage(hDlg,IDC_FieldSpacing, CB_GETCURSEL ,0,0);
                int DateFormat=SendDlgItemMessage(hDlg,IDC_DateFormat, CB_GETCURSEL ,0,0);
                int TimeFormat=SendDlgItemMessage(hDlg,IDC_TimeFormat, CB_GETCURSEL ,0,0);

                #define MaxFiles 5
                int FieldOptions[MaxFiles];
                FieldOptions[0]=SendDlgItemMessage(hDlg,IDC_Field1, CB_GETCURSEL ,0,0);
                FieldOptions[1]=SendDlgItemMessage(hDlg,IDC_Field2, CB_GETCURSEL ,0,0);
                FieldOptions[2]=SendDlgItemMessage(hDlg,IDC_Field3, CB_GETCURSEL ,0,0);
                FieldOptions[3]=SendDlgItemMessage(hDlg,IDC_Field4, CB_GETCURSEL ,0,0);
                FieldOptions[4]=SendDlgItemMessage(hDlg,IDC_Field5, CB_GETCURSEL ,0,0);

                std::string UserString;
                if (ReadDlgTextCtrl(hDlg,IDC_UserText,UserString))
                {
                    if (RemoveNonStandardCharacters(UserString))
                    {
                        SendDlgItemMessage(hDlg,IDC_UserText, WM_SETTEXT, (WPARAM) FALSE, (LPARAM) UserString.c_str());
                    }
                }
                
                int CounterStart=0;
                if (!ReadDlgTextCtrl(hDlg,IDC_Counter,CounterStart))
                {
                    CounterStart=0;
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
                    ofn.lpstrInitialDir=aDirectory;
                }

                ofn.Flags = OFN_EXPLORER| OFN_ALLOWMULTISELECT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
                if (GetOpenFileName(&ofn)) 
                { 
                    TxtWindow.Clear();
                    TxtWindow.AppendText(_T("Status....\r\n"));
                    TxtWindow.AppendText("=========================\r\n");
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
                        // first entry is Directorty others are filename
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

                    FILETIME tsAtime,tsMtime,tsCtime;
                    std::string JPGCtime;

                    if (LOWORD(wParam)==IDRENAME)
                    {
                        Undolist.clear();
                        TheUndoDirectory.assign(WorkingFolder);
                    }
                    FileList.clear();
                    EnableInputControls(hDlg,FALSE);
                    ContinueOperation=true;

                    bool haveJPEGData=false;
                    int FileCount=0;
                    do 
                    {
                        haveJPEGData=false;
                        SYSTEMTIME  SysFileTime;
                        switch (FileDateAttribute)
                        {
                        case PhotoTaken:
                            {
                                // get information from jpeg file
                                ExifImageFile inImageFile;
                                ExifStatus aErr;
                                if (inImageFile.open(TheFileName,"r") == EXIF_OK)
                                {
                                    // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                                    ExifTagEntry* entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                                    if (entryTag)
                                    {
                                        JPGCtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        if (GetJPEGTime(SysFileTime,JPGCtime.c_str(),JPGCtime.size()))
                                        {
                                            haveJPEGData=true;
                                        }
                                    }
                                    if( inImageFile.close() != EXIF_OK )
                                    {
                                        // problem with closing file
                                    }
                                }
                                if (haveJPEGData)
                                {
                                    break;
                                }
                                else
                                {
                                    _snprintf(TheText,TheTextSize,"Failed to obtain photo taken date for %s.\r\n",TheFileName);
                                    TxtWindow.AppendText(TheText );
                                    _snprintf(TheText,TheTextSize,"Will use file creation time instead for %s.\r\n",TheFileName);
                                    TxtWindow.AppendText(TheText);
                                }
                            }
                        case FileCreation:
                        case FileModification:
                            {
                                if (GetFileTimes(TheFileName,&tsAtime,&tsMtime,&tsCtime))
                                {
                                    switch (FileDateAttribute)
                                    {
                                    case PhotoTaken:
                                        FileTimeToSystemTime(&tsCtime,&SysFileTime);
                                        break;
                                    case FileCreation:
                                        FileTimeToSystemTime(&tsCtime,&SysFileTime);
                                        break;
                                    default:
                                        FileTimeToSystemTime(&tsMtime,&SysFileTime);
                                    }
                                }
                                else
                                {
                                    // just use current time
                                    GetLocalTime(&SysFileTime);
                                }
                            }
                            break;
                        }

                        // now build filename string
                        int i;
                        char *theExtension=NULL;
                        RemoveExtension(TheFileName, theExtension);

                        std::string NewFileName;
                        NewFileName.assign("");
                        for (i=0;i<MaxFiles;i++)
                        {
                            switch (FieldOptions[i])
                            {
                            case FileFormatDate:
                                MakeDateStr(SysFileTime,DateFormat,TheText,TheTextSize);
                                InsertSeparator(NewFileName,FieldSpacing);
                                NewFileName.append(TheText);
                                break;
                            case FileFormatTime:
                                MakeTimeStr(SysFileTime,TimeFormat,TheText,TheTextSize);
                                InsertSeparator(NewFileName,FieldSpacing);
                                NewFileName.append(TheText);
                                break;
                            case FileFormatFileName:
                                InsertSeparator(NewFileName,FieldSpacing);
                                NewFileName.append(TheFileName);
                                break;
                            case FileFormatUserText:
                                if (UserString.length()>0)
                                {
                                    InsertSeparator(NewFileName,FieldSpacing);
                                    NewFileName.append(UserString);
                                }
                                break;
                            case FileFormatCount:
                                InsertSeparator(NewFileName,FieldSpacing);
                                _snprintf(TheText,TheTextSize,"%1i", (CounterStart+FileCount));
                                NewFileName.append(TheText);
                                break;
                            case FileFormatNone:
                            default:
                                break;
                            }
                        }

                        if (theExtension)
                        {
                            NewFileName.append(".");
                            NewFileName.append(theExtension);
                            theExtension--;
                            *theExtension='.'; // put back the dot
                        }

                        // rename the file
                        if (LOWORD(wParam)==IDRENAME)
                        {
                            int result = rename(TheFileName, NewFileName.c_str() );
                            if( result != 0 )
                            {
                                // first see if file already exists
                                FILE *aFile=fopen(NewFileName.c_str(),"r");
                                if (aFile)
                                {
                                    fclose(aFile);
                                    // file already exists
                                    // generate new filename and try again

                                    if (FileNameAlreadyUsed(NewFileName,FileList)==false)
                                    {
                                        // add name to list if not already done so
                                        FileList.push_back(NewFileName);
                                    }
                                    if (MakeUniqueFileName(NewFileName,FileList,true))
                                    {
                                        // try to now rename file with new filename
                                        result = rename(TheFileName, NewFileName.c_str());
                                    }
                                }
                            }
                            if( result != 0 )
                            {
                                // output results
                                _snprintf(TheText,TheTextSize,"FAILED to rename %1s to %1s\r\n",TheFileName,NewFileName.c_str());
                                TxtWindow.AppendText(TheText);
                            }
                            else
                            {
                                // output results
                                _snprintf(TheText,TheTextSize,"Renamed %1s to %1s\r\n",TheFileName,NewFileName.c_str());
                                TxtWindow.AppendText(TheText);
                                Undolist.push_back(FileDateClass(TheFileName,NewFileName.c_str()));
                            }
                            FileList.push_back(NewFileName);
                        }
                        else
                        {
                            // see if filename is already on disk
                            FILE *aFile=fopen(NewFileName.c_str(),"r");
                            if (aFile || FileNameAlreadyUsed(NewFileName,FileList))
                            {
                                if (aFile)
                                {
                                    fclose(aFile);
                                }
                                // file already exists
                                // generate new filename and try again

                                if (FileNameAlreadyUsed(NewFileName,FileList)==false)
                                {
                                    // add name to list if not already done so
                                    FileList.push_back(NewFileName);
                                }
                                if (MakeUniqueFileName(NewFileName,FileList,true))
                                {
                                    _snprintf(TheText,TheTextSize,"Would rename %1s to %1s\r\n",TheFileName,NewFileName.c_str());
                                    TxtWindow.AppendText(TheText);
                                    FileList.push_back(NewFileName);
                                }
                                else
                                {
                                    // output results
                                    _snprintf(TheText,TheTextSize,"FAILED to rename %1s to %1s\r\n",TheFileName,NewFileName.c_str());
                                    TxtWindow.AppendText(TheText);
                                }
                            }
                            else
                            {
                                // output results
                                _snprintf(TheText,TheTextSize,"Would rename %1s to %1s\r\n",TheFileName,NewFileName.c_str());
                                TxtWindow.AppendText(TheText);
                                FileList.push_back(NewFileName);
                            }
                        }


                        // get next filename
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
                        FileCount++;
                    } while (NextFilePos>0 && ContinueOperation);

                    TxtWindow.AppendText(_T("=========================\r\n"));
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

            case IDUNDOABORT:
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
                        if (_chdir(TheUndoDirectory.c_str()))
                        {
                            // failed to change folder
                            // continue anyway and see if can application can rename file
                            TxtWindow.AppendText("Warning: failed to set correct folder\r\n");
                        }
                        char TheText[TheTextSize];
                        EnableInputControls(hDlg,FALSE);
                        
                        TxtWindow.Clear();
                        TxtWindow.AppendText(_T("Undo Status....\r\n"));
                        TxtWindow.AppendText("=========================\r\n");

                        ContinueOperation=true;
                        std::vector<FileDateClass>::iterator UndoIterator;
                        unsigned int UndoCount=0;

                        for (UndoIterator =  Undolist.begin();(UndoIterator != Undolist.end() && ContinueOperation); ++UndoIterator)
                        {
                            std::string TheOldFileName;
                            (*UndoIterator).GetOrgFileName(TheOldFileName);

                            // Get Undo values
                            std::string TheNewFileName;
                            (*UndoIterator).GetNewFileName(TheNewFileName);
                            UndoCount++;

                            // rename the file back to its old filename
                            int result = rename(TheNewFileName.c_str(), TheOldFileName.c_str() );
                            if( result != 0 )
                            {
                                // output results
                                _snprintf(TheText,TheTextSize,"FAILED to undo the renaming of %1s to %1s\r\n",TheNewFileName.c_str(),TheOldFileName.c_str());
                                TxtWindow.AppendText(TheText);
                            }
                            else
                            {
                                // output results
                                _snprintf(TheText,TheTextSize,"Renamed %1s back to %1s\r\n",TheNewFileName.c_str(),TheOldFileName.c_str());
                                TxtWindow.AppendText(TheText);
                            }

                            // Update window messages
                            ProcessPendingEvents();
                        }
                        
                        TxtWindow.AppendText(_T("=========================\r\n"));
                        if (ContinueOperation)
                        {
                            Undolist.clear();
                            TxtWindow.AppendText( _T("Undo Complete"));;
                        }
                        else
                        {
                            // remove any operations from the undo list which were processed
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

            default:
                return TRUE;
			}
			break;
	}
    return FALSE;
}