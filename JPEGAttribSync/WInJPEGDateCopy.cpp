///////////////////////////////////////////////////////////////////////////////////
//
// JPEGAttribSync util.
//
// WinJPEGDateCopy.cpp
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
// v1.0.0 first release (PJL 10/1/07)
//
// Changed some of the Radio buttons to check boxes (PJL 23/01/07)
// v1.0.1 second release  (PJL 23/1/07)
//
// Change Exif creation to Photo taken
// Improved error message for when missing Exif information
// v1.0.2 Third release  (PJL 23/1/07)
//
// Updated registry code (PJL 01/02/07)
// Improved text control text output (PJL 12/02/07) 
// Added abort functionality (PJL 12/02/07)
// v1.0.3 released (12/02/07)
//
// Fixed problem with Iconized Control Dialogue being closed and saving of registry (PJL 19/02/07)
// v1.0.4  12/02/07 
//
// Fixed problem relating to daylight saving and file time (PJL 23/08/07) 
// v1.0.5 release (PJL 23/08/07)
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
#include "cderr.h"
#include "direct.h"
///////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
///////////////////////////////////////////////////////////////////////////////////
#define MinXValDlg 346
#define MinYValDlg 210
///////////////////////////////////////////////////////////////////////////////////
// Global Variables:
HINSTANCE g_hInst;	             							// current instance
#define MAX_LOADSTRING 100
TCHAR g_szWindowClass[MAX_LOADSTRING];						// The title bar text
///////////////////////////////////////////////////////////////////////////////////
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DateControlDlg(HWND, UINT, WPARAM, LPARAM);
///////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    TCHAR szTitle[MAX_LOADSTRING];								// The title bar text

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TIMESTAMPWIN, g_szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
    DialogBox(hInstance, (LPCTSTR)IDD_MAIN_DIALOG, NULL, (DLGPROC)DateControlDlg);

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_TIMESTAMPWIN);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_TIMESTAMPWIN;
	wcex.lpszClassName	= g_szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}
///////////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(g_hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
                case IDM_SETDATE:
				   DialogBox(g_hInst, (LPCTSTR)IDD_DATE_DIALOG, NULL, (DLGPROC)DateControlDlg);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
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
                        _T("SOFTWARE\\WinJPEGAttribSync"), 0, NULL, 0,
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

        RegCloseKey( hkResult );
        return (TRUE);
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
                        _T("SOFTWARE\\WinJPEGAttribSync"), 0, NULL, 0,
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
        RegCloseKey( hkResult );
        return (TRUE);
    }
    return(FALSE);
}
//////////////////////////////////////////////////////////////////////////////////
// options
#define OPT_MODIFY_ATIME       (1 << 0)
#define OPT_MODIFY_MTIME       (1 << 1)
#define OPT_MODIFY_CTIME       (1 << 2)
#define OPT_NO_CREATE	       (1 << 3)
#define OPT_MODIFY_DIG_TIME    (1 << 4)
#define OPT_MODIFY_MOD_TIME    (1 << 5)
#define OPT_MODIFY_CRT_TIME    (1 << 6)
//////////////////////////////////////////////////////////////////////////////////
//
// The function that does all the file attribute updating
//
// This function comes from the Touch for Windows code developed by Joergen Sigvardsson.
//
static DWORD touch(LPCTSTR lpszFile, FILETIME* atime, FILETIME* mtime, FILETIME* ctime, WORD wOpts)
{
	SetLastError(ERROR_SUCCESS);

	HANDLE hFile = CreateFile(
		lpszFile, 
		GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		(wOpts & OPT_NO_CREATE) ? OPEN_EXISTING : OPEN_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		0);

	DWORD dwRetVal = GetLastError();

	// Check for CreateFile() special cases
	if(dwRetVal != ERROR_SUCCESS)
    {
		if((wOpts & OPT_NO_CREATE) && dwRetVal == ERROR_FILE_NOT_FOUND)
        {
			return ERROR_SUCCESS; // not an error
        }
		else if(hFile != INVALID_HANDLE_VALUE && dwRetVal == ERROR_ALREADY_EXISTS)
        {
			dwRetVal = ERROR_SUCCESS; // not an error according to MSDN docs
        }
	}

	if(dwRetVal != ERROR_SUCCESS)
    {
		return dwRetVal;
    }

	// Is there any template timestamp?  
	if(atime || mtime || ctime)
    {
		SetLastError(ERROR_SUCCESS);
		SetFileTime(
			hFile, 
			(wOpts & OPT_MODIFY_CTIME) ? ctime : NULL,
			(wOpts & OPT_MODIFY_ATIME) ? atime : NULL,
			(wOpts & OPT_MODIFY_MTIME) ? mtime : NULL);
		dwRetVal = GetLastError();
	}

	CloseHandle(hFile);

	return dwRetVal;
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
int DifferenceInDays(int SrtDay, int SrtMonth, int SrtYear,
                      const int EndDay, const int const EndMonth, const int EndYear)
{
    const int MonthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};

    // see if start is before or after end date
    int IncDay=1;
    if (SrtYear>EndYear)
    {
        IncDay=-1;
    }
    else if (SrtYear==EndYear)
    {
        if (SrtMonth>EndMonth)
        {
            IncDay=-1;
        }
        else if (SrtMonth==EndMonth)
        {
            if (SrtDay>EndDay)
            {
                IncDay=-1;
            }
        }
    }

    // count the days between start and end dates

    int TotalDaysBetween=0;
    while (SrtYear!=EndYear || SrtMonth!=EndMonth || SrtDay!=EndDay)
    {
        SrtDay+=IncDay;
        TotalDaysBetween+=IncDay;

        if (IncDay<0)
        {
            if (SrtYear<EndYear)
            {
                // problem found with date (Abort!)
                return (false);
            }
        }
        else
        {
            if (SrtYear>EndYear)
            {
                // problem found with date (Abort!)
                return (false);
            }
        }

        int DaysInMonth = MonthDays[SrtMonth-1];
        if (SrtMonth==2) // Feb
        {
            if (isLeapYear(SrtYear))
            {
                DaysInMonth++;
            }
        }
        if (SrtDay<1 || SrtDay > DaysInMonth)
        {
            if (IncDay<0)
            {
                SrtMonth--;
                if (SrtMonth<1)
                {
                    SrtMonth=12;
                    SrtYear--;
                }
                DaysInMonth = MonthDays[SrtMonth-1];
                if (SrtMonth==2) // Feb
                {
                    if (isLeapYear(SrtYear))
                    {
                        DaysInMonth++;
                    }
                }
                SrtDay=DaysInMonth;
            }
            else
            {
                SrtMonth++;
                if (SrtMonth>12)
                {
                    SrtMonth=1;
                    SrtYear++;
                }
                SrtDay=1;
            }
        }
    }
    return (TotalDaysBetween);
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
//  Assign day of week to a date given a known weekday day and date 
//
bool SetDayOfWeek(SYSTEMTIME &TheDate,SYSTEMTIME &RefDate)
{
    int DaysDiff=DifferenceInDays((int) RefDate.wDay, (int) RefDate.wMonth, (int) RefDate.wYear,
                                  (int) TheDate.wDay, (int) TheDate.wMonth, (int) TheDate.wYear);

    // find new day of the week
    DaysDiff+=RefDate.wDayOfWeek;
    DaysDiff=DateModules(DaysDiff,7);
    TheDate.wDayOfWeek = DaysDiff; // range 0 to 6
    return (true);
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
    FILETIME m_tsAtime;  // file attributes time
    FILETIME m_tsMtime;  // file modify time
    FILETIME m_tsCtime;  // file creation time
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

        m_tsAtime=SrcClass.m_tsAtime;
        m_tsMtime=SrcClass.m_tsMtime;
        m_tsCtime=SrcClass.m_tsCtime;
    }

    FileDateClass(const char* aFileName,WORD a_wOpts,FILETIME &a_tsAtime,FILETIME &a_tsMtime,FILETIME &a_tsCtime,std::string &a_Dtime,std::string &a_Mtime,std::string &a_Ctime)
    {
        m_FileName.assign(aFileName);
        m_wOpts=a_wOpts;
        m_Dtime=a_Dtime;
        m_Mtime=a_Mtime;
        m_Ctime=a_Ctime;

        m_tsAtime=a_tsAtime;
        m_tsMtime=a_tsMtime;
        m_tsCtime=a_tsCtime;
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

    bool GetJPGTimeTimes(std::string &a_Dtime,std::string &a_Mtime,std::string &a_Ctime)
    {
        a_Dtime=m_Dtime;
        a_Mtime=m_Mtime;
        a_Ctime=m_Ctime;
        return (true);
    }

    bool GetFileTimes(FILETIME &a_tsAtime,FILETIME &a_tsMtime,FILETIME &a_tsCtime)
    {
        a_tsAtime=m_tsAtime;
        a_tsMtime=m_tsMtime;
        a_tsCtime=m_tsCtime;
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
void EnableInputControls(HWND hDlg, BOOL Status)
{
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
    static int oldWidth=0,oldHeight=0;
    static std::vector<FileDateClass> Undolist;
    static std::string WorkingFolder;
    static DlgTxtControl TxtWindow(hDlg,IDC_EDITBOX);
    static bool ContinueOperation=false;

	switch (message)
	{
		case WM_INITDIALOG:
            // set date for controls
            TxtWindow.Clear();
            TxtWindow.AppendText(_T("Status Window....\r\n"));
            TxtWindow.AppendText(_T("Version: 1.0.5 Aug 2007 (Freeware)\r\n"));
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
                SaveCurrentStatus(hDlg,WorkingFolder);
				EndDialog(hDlg, LOWORD(wParam));
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

            case IDOK:
            {
                BOOL UseCurrentTime=FALSE;
                LONG aState=SendDlgItemMessage( hDlg, IDC_CurrentTime,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
                    UseCurrentTime=TRUE;
                }

                // source options
                WORD srcOpts = (WORD) 0;
                aState=SendDlgItemMessage( hDlg, IDC_SrcFileAccessed,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
                    srcOpts = srcOpts | (WORD) OPT_MODIFY_ATIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_SrcFileModified,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    srcOpts = srcOpts | (WORD) OPT_MODIFY_MTIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_SrcFileCreation,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    srcOpts = srcOpts | (WORD) OPT_MODIFY_CTIME;
                }

                // JPEG Exif src attributes
                aState=SendDlgItemMessage( hDlg, IDC_SrcDigitized,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
                    srcOpts = srcOpts | (WORD) OPT_MODIFY_DIG_TIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_SrcModified,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    srcOpts = srcOpts | (WORD) OPT_MODIFY_MOD_TIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_SrcCreation,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    srcOpts = srcOpts | (WORD) OPT_MODIFY_CRT_TIME;
                }
                // set options
                WORD wOpts = (WORD) 0;

                // file attributes
                aState=SendDlgItemMessage( hDlg, IDC_SetFileAccessed,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
                    wOpts = wOpts | (WORD) OPT_MODIFY_ATIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_SetFileModified,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    wOpts = wOpts | (WORD) OPT_MODIFY_MTIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_SetFileCreation,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    wOpts = wOpts | (WORD) OPT_MODIFY_CTIME;
                }

                // JPEG Exif attributes
                aState=SendDlgItemMessage( hDlg, IDC_SetDigitized,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
                    wOpts = wOpts | (WORD) OPT_MODIFY_DIG_TIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_SetModified,BM_GETSTATE,0,0);
                if ((aState & BST_CHECKED))
                {
				    wOpts = wOpts | (WORD) OPT_MODIFY_MOD_TIME;
                }
                aState=SendDlgItemMessage( hDlg, IDC_SetCreation,BM_GETSTATE,0,0);
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
                    TxtWindow.AppendText(_T("Status....\r\n"));

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

                    Undolist.clear();
                    EnableInputControls(hDlg,FALSE);
                    ContinueOperation=true;

                    #define TheTextSize 200
                    char TheText[TheTextSize];

                    do 
                    {
                        TxtWindow.AppendText(_T("=========================\r\n"));

                        ExifImageFile inImageFile;
                        bool UpdateValues=true;

                        char *ModOptions="r";
                        if ( (wOpts & OPT_MODIFY_DIG_TIME) ||
                             (wOpts & OPT_MODIFY_MOD_TIME) ||
                             (wOpts & OPT_MODIFY_CRT_TIME)  )
                        {
                            ModOptions="r+";
                        }
                        
                        ExifStatus aErr;

                        #define DateStrSize 30
                        char DateStr[DateStrSize];

                        FILETIME tsAtime, tsMtime,tsCtime;
                        std::string JPGDtime;
                        std::string JPGMtime;
                        std::string JPGCtime;

                        bool imgFileOpen=(inImageFile.open(TheFileName, ModOptions) == EXIF_OK);
                        bool AttrFileData = GetFileTimes(TheFileName,&tsAtime,&tsMtime,&tsCtime);

                        if (imgFileOpen || AttrFileData)
                        {
                            _snprintf(TheText,TheTextSize, "Accessing attributes for \"%s\"\r\n",TheFileName);
                            TxtWindow.AppendText(TheText);
                        }

                        ExifTagEntry* entryTag=NULL;

                        if (imgFileOpen)
                        {                            
                            // EXIFTAG_DALETIMEDIGITIZED Date/Time of image digitized

                            entryTag = inImageFile.getGenericTag(EXIFTAG_DALETIMEDIGITIZED,EXIF_APP1_EXIFIFD,aErr);
                            if (entryTag)
                            {
                                JPGDtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                _snprintf(TheText,TheTextSize,"Exif Digitized : %s\r\n", JPGDtime.c_str() );
                                TxtWindow.AppendText(TheText); 
                            }
                            else
                            {
                                TxtWindow.AppendText("No EXIF Digitized time information\r\n");
                                if ( (srcOpts & OPT_MODIFY_DIG_TIME) )
                                {
                                    UpdateValues=false;
                                }
                            }

                            // EXIFTAG_DATETIME Date/Time of image was last modified
                            entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIME,EXIF_APP1_IFD0,aErr);
                            if (entryTag)
                            {
                                JPGMtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                _snprintf(TheText,TheTextSize,"Exif Modified : %s\r\n", JPGMtime.c_str() );
                                TxtWindow.AppendText(TheText);
                            }
                            else
                            {
                                TxtWindow.AppendText(_T("No EXIF Modified time information\r\n"));
                                if ( (srcOpts & OPT_MODIFY_MOD_TIME) )
                                {
                                    UpdateValues=false;
                                }
                            }
                            
                            // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                            entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                            if (entryTag)
                            {
                                JPGCtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                _snprintf(TheText,TheTextSize,"Exif Photo taken : %s\r\n", JPGCtime.c_str() );
                                TxtWindow.AppendText(TheText);
                            }
                            else
                            {
                                TxtWindow.AppendText("No EXIF Original image time information\r\n");
                                if ( (srcOpts & OPT_MODIFY_CRT_TIME) )
                                {
                                    UpdateValues=false;
                                }
                            }			               
                        }
                        else
                        {
                            if ( (srcOpts & OPT_MODIFY_DIG_TIME) ||
                                 (srcOpts & OPT_MODIFY_MOD_TIME) ||
                                 (srcOpts & OPT_MODIFY_CRT_TIME)  )
                            {
                                // can't continue since can't access JPEG options
                                UpdateValues=false;
                            }
                        }

                        if (!UpdateValues)
                        {
                            TxtWindow.AppendText("This image does not have the required EXIF information for selected operation.\r\n");
                        }

                        SYSTEMTIME  SysCtime,SysMtime,SysAtime;
                        if (AttrFileData)
                        {
                            FileTimeToSystemTime(&tsCtime,&SysCtime);
                            FileTimeToSystemTime(&tsMtime,&SysMtime);
                            FileTimeToSystemTime(&tsAtime,&SysAtime);

                            if (MakeCTime(SysAtime,DateStr,DateStrSize))
                            {
                                _snprintf(TheText,TheTextSize,"File Accessed : %s\r\n", DateStr );
                                TxtWindow.AppendText(TheText);
                            }

                            if (MakeCTime(SysMtime,DateStr,DateStrSize))
                            {
                                _snprintf(TheText,TheTextSize,"File Modified : %s\r\n", DateStr );
                                TxtWindow.AppendText(TheText);
                            }

                            if (MakeCTime(SysCtime,DateStr,DateStrSize))
                            {
                                _snprintf(TheText,TheTextSize,"File Created  : %s\r\n", DateStr );
                                TxtWindow.AppendText(TheText);
                            } 
                        }
                        else
                        {
                            // just use current time
                            GetLocalTime(&SysCtime);
                            tsMtime=tsCtime;
                            tsAtime=tsCtime;
                            SystemTimeToFileTime(&SysCtime,&tsCtime);
                            SysMtime=SysCtime;
                            SysAtime=SysCtime;
                        }

                        if (UpdateValues)
                        {
                            // now have all data make modification file time and jpeg string
                            SYSTEMTIME  ModificationSysTime;
                            std::string ModificationDateStr;
                        
                            switch (srcOpts)
                            {
                            case OPT_MODIFY_ATIME:
                                    ModificationSysTime=SysAtime;
                                    if (MakeJPEGTime(ModificationSysTime,DateStr,DateStrSize))
                                    {
                                        ModificationDateStr.assign(DateStr);
                                    }
                                    break;
                            case OPT_MODIFY_MTIME:
                                    ModificationSysTime=SysMtime;
                                    if (MakeJPEGTime(ModificationSysTime,DateStr,DateStrSize))
                                    {
                                        ModificationDateStr.assign(DateStr);
                                    }
                                    break;
                            case OPT_MODIFY_CTIME:
                                    ModificationSysTime=SysCtime;
                                    if (MakeJPEGTime(ModificationSysTime,DateStr,DateStrSize))
                                    {
                                        ModificationDateStr.assign(DateStr);
                                    }
                                    break;
                            case OPT_MODIFY_DIG_TIME:
                                    ModificationDateStr=JPGDtime;
                                    GetJPEGTime(ModificationSysTime,ModificationDateStr.c_str(),ModificationDateStr.size());
                                    // since JPEG date has no day of the week need to calculate it.
                                    SetDayOfWeek(ModificationSysTime,SysMtime); 
                                    break;
                            case OPT_MODIFY_MOD_TIME:
                                    ModificationDateStr=JPGMtime;
                                    GetJPEGTime(ModificationSysTime,ModificationDateStr.c_str(),ModificationDateStr.size());
                                    // since JPEG date has no day of the week need to calculate it.
                                    SetDayOfWeek(ModificationSysTime,SysMtime);
                                    break;
                            case OPT_MODIFY_CRT_TIME:
                                    ModificationDateStr=JPGCtime;
                                    GetJPEGTime(ModificationSysTime,ModificationDateStr.c_str(),ModificationDateStr.size());
                                    // since JPEG date has no day of the week need to calculate it.
                                    SetDayOfWeek(ModificationSysTime,SysMtime);
                                    break;
                            }

                            bool ModifiedValues=false;
                            bool ModifiedJPGValues=false;
                            bool UpdatedInfo=false;

                            _snprintf(TheText,TheTextSize,"Updated Values....\r\n");
                            TxtWindow.AppendText(TheText);

                            if (imgFileOpen && 
                                 ( (wOpts & OPT_MODIFY_DIG_TIME) ||
                                   (wOpts & OPT_MODIFY_MOD_TIME) ||
                                   (wOpts & OPT_MODIFY_CRT_TIME) ) )
                            {
                                // Output and updated values

                                std::string JPEGDateStr;

                                if (wOpts & OPT_MODIFY_DIG_TIME)
                                {
                                    // EXIFTAG_DALETIMEDIGITIZED Date/Time of image digitized

                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DALETIMEDIGITIZED,EXIF_APP1_EXIFIFD,aErr);
                                    if (entryTag)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(ModificationDateStr);
                                        ModifiedValues=true;
                                        ModifiedJPGValues=true;

                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Exif Digitized : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText(TheText);
                                        UpdatedInfo=true;
                                    }
                                }
                                if (wOpts & OPT_MODIFY_MOD_TIME)
                                {
                                    // EXIFTAG_DATETIME Date/Time of image was last modified
                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIME,EXIF_APP1_IFD0,aErr);
                                    if (entryTag)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(ModificationDateStr);
                                        ModifiedValues=true;
                                        ModifiedJPGValues=true;

                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Exif Modified : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText(TheText);
                                        UpdatedInfo=true;
                                    }
                                }
                                if (wOpts & OPT_MODIFY_CRT_TIME)
                                {
                                    // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                                    if (entryTag)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(ModificationDateStr);
                                        ModifiedValues=true;
                                        ModifiedJPGValues=true;

                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Exif Photo taken : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText(TheText);
                                        UpdatedInfo=true;
                                    }
                                }
                            }
                            // close image file first
                            if (imgFileOpen)
                            {
                                // Close the file
                                if( inImageFile.close() != EXIF_OK )
                                {
                                    _snprintf(TheText,TheTextSize,"Error: Could not close JPEG file : %s\r\n", TheFileName );
                                }
                            
                            }

                            // now update values
                            
                            FILETIME ModificationLocalFileTime;
                            SystemTimeToFileTime(&ModificationSysTime,&ModificationLocalFileTime);

                            FILETIME ModificationFileTime;
                            LocalFileTimeToFileTime(&ModificationLocalFileTime,&ModificationFileTime);

                            DWORD dwResult = touch(
				                TheFileName,
				                (wOpts & OPT_MODIFY_ATIME) ? &ModificationFileTime : NULL,
				                (wOpts & OPT_MODIFY_MTIME) ? &ModificationFileTime : NULL,
				                (wOpts & OPT_MODIFY_CTIME) ? &ModificationFileTime : NULL,
				                wOpts
			                );

			                if(ERROR_SUCCESS != dwResult) 
                            {
                                TxtWindow.AppendText("FAILED to set file attributes\r\n");
			                }
                            else
                            {
                                FILETIME UtsAtime,UtsMtime,UtsCtime;
                                if (GetFileTimes(TheFileName,&UtsAtime,&UtsMtime,&UtsCtime) )
                                {
                                    FileTimeToSystemTime(&UtsCtime,&SysCtime);
                                    FileTimeToSystemTime(&UtsMtime,&SysMtime);
                                    FileTimeToSystemTime(&UtsAtime,&SysAtime);

                                    if (wOpts & OPT_MODIFY_ATIME)
                                    {
                                        ModifiedValues=true;
                                        if (MakeCTime(SysAtime,DateStr,DateStrSize))
                                        {
                                            _snprintf(TheText,TheTextSize,"File Accessed : %s\r\n", DateStr );
                                            TxtWindow.AppendText(TheText);
                                            UpdatedInfo=true;
                                        }
                                    }
                                    if (wOpts & OPT_MODIFY_MTIME)
                                    {
                                        ModifiedValues=true;
                                        if (MakeCTime(SysMtime,DateStr,DateStrSize))
                                        {
                                            sprintf(TheText,"File Modified : %s\r\n", DateStr );
                                            TxtWindow.AppendText(TheText);
                                            UpdatedInfo=true;
                                        }
                                    }
                                    if (wOpts & OPT_MODIFY_CTIME)
                                    {
                                        ModifiedValues=true;
                                        if (MakeCTime(SysCtime,DateStr,DateStrSize))
                                        {
                                            _snprintf(TheText,TheTextSize,"File Created  : %s\r\n", DateStr );
                                            TxtWindow.AppendText(TheText);
                                            UpdatedInfo=true;
                                        } 
                                    }
                                }
                            }

                            if (ModifiedValues && !UpdatedInfo)
                            {
                                TxtWindow.AppendText("Problem outputting updated values\r\n");
                            }

                            if (ModifiedValues)
                            {
                                Undolist.push_back(FileDateClass(TheFileName,wOpts,tsAtime,tsMtime,tsCtime,JPGDtime,JPGMtime,JPGCtime));
                            }
                            else
                            {
                                TxtWindow.AppendText("None\r\n");
                            }
                        }
                        else
                        {
                            TxtWindow.AppendText("FAILED to set file attributes\r\n");
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
                        char TheText[TheTextSize];

                        EnableInputControls(hDlg,FALSE);
                        TxtWindow.Clear();
                        TxtWindow.AppendText(_T("Undo Status....\r\n"));

                        std::string JPEGDateStr;
                        std::string JPGDtime,JPGMtime,JPGCtime;
                        FILETIME tsAtime, tsMtime,tsCtime;
                        ContinueOperation=true;
                        std::vector<FileDateClass>::iterator UndoIterator;
                        unsigned int UndoCount=0;
                        for (UndoIterator =  Undolist.begin();(UndoIterator != Undolist.end() && ContinueOperation); ++UndoIterator)
                        {
                            WORD wOpts = (*UndoIterator).GetwOpts();

                            TxtWindow.AppendText(_T("=========================\r\n"));

                            std::string TheFileName;
                            (*UndoIterator).GetFileName(TheFileName);
                            UndoCount++;

                            char *ModOptions="r";
                            if ( (wOpts & OPT_MODIFY_DIG_TIME) ||
                                 (wOpts & OPT_MODIFY_MOD_TIME) ||
                                 (wOpts & OPT_MODIFY_CRT_TIME)  )
                            {
                                ModOptions="r+";
                            }
                        
                            ExifStatus aErr;

                            #define DateStrSize 30
                            char DateStr[DateStrSize];

                            ExifImageFile inImageFile;
                            bool imgFileOpen=(inImageFile.open(TheFileName.c_str(), ModOptions) == EXIF_OK);
                            bool AttrFileData = GetFileTimes(TheFileName.c_str(),&tsAtime,&tsMtime,&tsCtime);

                            if (imgFileOpen || AttrFileData)
                            {
                                _snprintf(TheText,TheTextSize, "Accessing attributes for \"%s\"\r\n",TheFileName.c_str());
                                TxtWindow.AppendText(TheText);
                            }

                            ExifTagEntry* entryTag=NULL;

                            if (imgFileOpen)
                            {                            
                                // EXIFTAG_DALETIMEDIGITIZED Date/Time of image digitized

                                entryTag = inImageFile.getGenericTag(EXIFTAG_DALETIMEDIGITIZED,EXIF_APP1_EXIFIFD,aErr);
                                if (entryTag)
                                {
                                    JPGDtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                    _snprintf(TheText,TheTextSize,"Exif Digitized : %s\r\n", JPGDtime.c_str() );
                                    TxtWindow.AppendText(TheText); 
                                }
                                else
                                {
                                    TxtWindow.AppendText("No EXIF Digitized time information\r\n");
                                }

                                // EXIFTAG_DATETIME Date/Time of image was last modified
                                entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIME,EXIF_APP1_IFD0,aErr);
                                if (entryTag)
                                {
                                    JPGMtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                    _snprintf(TheText,TheTextSize,"Exif Modified : %s\r\n", JPGMtime.c_str() );
                                    TxtWindow.AppendText(TheText);
                                }
                                else
                                {
                                    TxtWindow.AppendText("No EXIF Modified time information\r\n");
                                }
                            
                                // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                                entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                                if (entryTag)
                                {
                                    JPGCtime = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                    _snprintf(TheText,TheTextSize,"Exif Photo taken : %s\r\n", JPGCtime.c_str() );
                                    TxtWindow.AppendText(TheText);
                                }
                                else
                                {
                                    TxtWindow.AppendText("No EXIF Original image time information\r\n");
                                }			               
                            }

                            SYSTEMTIME  SysCtime,SysMtime,SysAtime;
                            if (AttrFileData)
                            {
                                FileTimeToSystemTime(&tsCtime,&SysCtime);
                                FileTimeToSystemTime(&tsMtime,&SysMtime);
                                FileTimeToSystemTime(&tsAtime,&SysAtime);

                                if (MakeCTime(SysAtime,DateStr,DateStrSize))
                                {
                                    _snprintf(TheText,TheTextSize,"File Accessed : %s\r\n", DateStr );
                                    TxtWindow.AppendText(TheText);
                                }

                                if (MakeCTime(SysMtime,DateStr,DateStrSize))
                                {
                                    _snprintf(TheText,TheTextSize,"File Modified : %s\r\n", DateStr );
                                    TxtWindow.AppendText(TheText);
                                }

                                if (MakeCTime(SysCtime,DateStr,DateStrSize))
                                {
                                    _snprintf(TheText,TheTextSize,"File Created  : %s\r\n", DateStr );
                                    TxtWindow.AppendText(TheText);
                                } 
                            }
                            else
                            {
                                // just use current time
                                GetLocalTime(&SysCtime);
                                tsMtime=tsCtime;
                                tsAtime=tsCtime;
                                SystemTimeToFileTime(&SysCtime,&tsCtime);
                                SysMtime=SysCtime;
                                SysAtime=SysCtime;
                            }

                            // Get Undo values
                            (*UndoIterator).GetJPGTimeTimes(JPGDtime,JPGMtime,JPGCtime);
                            (*UndoIterator).GetFileTimes(tsAtime,tsMtime,tsCtime);

                            // Assign old values back to file
                            bool ModifiedValues=false;
                            bool ModifiedJPGValues=false;

                            TxtWindow.AppendText(_T("Updated Values....\r\n"));

                            if (imgFileOpen && 
                                 ( (wOpts & OPT_MODIFY_DIG_TIME) ||
                                   (wOpts & OPT_MODIFY_MOD_TIME) ||
                                   (wOpts & OPT_MODIFY_CRT_TIME) ) )
                            {
                                // Output and updated values

                                std::string JPEGDateStr;

                                if (wOpts & OPT_MODIFY_DIG_TIME)
                                {
                                    // EXIFTAG_DATETIMEDIGITIZED Date/Time of image digitized

                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DALETIMEDIGITIZED,EXIF_APP1_EXIFIFD,aErr);
                                    if (entryTag)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPGDtime);
                                        ModifiedValues=true;
                                        ModifiedJPGValues=true;

                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Exif Digitized : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText(TheText);
                                    }
                                }
                                if (wOpts & OPT_MODIFY_MOD_TIME)
                                {
                                    // EXIFTAG_DATETIME Date/Time of image was last modified
                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIME,EXIF_APP1_IFD0,aErr);
                                    if (entryTag)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPGMtime);
                                        ModifiedValues=true;
                                        ModifiedJPGValues=true;

                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Exif Modified : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText(TheText);
                                    }
                                }
                                if (wOpts & OPT_MODIFY_CRT_TIME)
                                {
                                    // EXIFTAG_DATETIMEORIGINAL Date/Time of original image taken
                                    entryTag = inImageFile.getGenericTag(EXIFTAG_DATETIMEORIGINAL,EXIF_APP1_EXIFIFD,aErr);
                                    if (entryTag)
                                    {
                                        (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->setValue(JPGCtime);
                                        ModifiedValues=true;
                                        ModifiedJPGValues=true;

                                        JPEGDateStr = (dynamic_cast < ExifTagEntryT<std::string> *> (entryTag))->getValue();
                                        _snprintf(TheText,TheTextSize,"Exif Photo taken : %s\r\n", JPEGDateStr.c_str() );
                                        TxtWindow.AppendText(TheText);
                                    }
                                }
                            }

                            // close image file first
                            if (imgFileOpen)
                            {
                                // Close the file
                                if( inImageFile.close() != EXIF_OK )
                                {
                                    _snprintf(TheText,TheTextSize,"Error: Could not close JPEG file : %s\r\n", TheFileName.c_str());
                                }
                            }

                            // Convert back to file times
                            FILETIME tsAFileTime;
                            LocalFileTimeToFileTime(&tsAtime,&tsAFileTime);
                            FILETIME tsMFileTime;
                            LocalFileTimeToFileTime(&tsMtime,&tsMFileTime);
                            FILETIME tsCFileTime;
                            LocalFileTimeToFileTime(&tsCtime,&tsCFileTime);

                            // now update values
                            DWORD dwResult = touch(
				                TheFileName.c_str(),
				                (wOpts & OPT_MODIFY_ATIME) ? &tsAFileTime : NULL,
				                (wOpts & OPT_MODIFY_MTIME) ? &tsMFileTime : NULL,
				                (wOpts & OPT_MODIFY_CTIME) ? &tsCFileTime : NULL,
				                wOpts
			                );

			                if(ERROR_SUCCESS != dwResult) 
                            {
                                TxtWindow.AppendText(_T("FAILED to set file Attributes\r\n"));
			                }
                            else
                            {
                                if (GetFileTimes(TheFileName.c_str(),&tsAtime,&tsMtime,&tsCtime) )
                                {
                                    FileTimeToSystemTime(&tsCtime,&SysCtime);
                                    FileTimeToSystemTime(&tsMtime,&SysMtime);
                                    FileTimeToSystemTime(&tsAtime,&SysAtime);

                                    if (wOpts & OPT_MODIFY_ATIME)
                                    {
                                        ModifiedValues=true;
                                        if (MakeCTime(SysAtime,DateStr,DateStrSize))
                                        {
                                            _snprintf(TheText,TheTextSize,"File Accessed : %s\r\n", DateStr );
                                            TxtWindow.AppendText(TheText);
                                        }
                                    }
                                    if (wOpts & OPT_MODIFY_MTIME)
                                    {
                                        ModifiedValues=true;
                                        if (MakeCTime(SysMtime,DateStr,DateStrSize))
                                        {
                                            sprintf(TheText,"File Modified : %s\r\n", DateStr );
                                            TxtWindow.AppendText(TheText);
                                        }
                                    }
                                    if (wOpts & OPT_MODIFY_CTIME)
                                    {
                                        ModifiedValues=true;
                                        if (MakeCTime(SysCtime,DateStr,DateStrSize))
                                        {
                                            _snprintf(TheText,TheTextSize,"File Created  : %s\r\n", DateStr );
                                            TxtWindow.AppendText(TheText);
                                        } 
                                    }
                                }
                            }

                            if (!ModifiedValues)
                            {
                                TxtWindow.AppendText("None\r\n");
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