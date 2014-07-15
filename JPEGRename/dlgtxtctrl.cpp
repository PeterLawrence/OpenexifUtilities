//////////////////////////////////////////////////////////////////////////////////
//
// Dialog Text Control Class
//
// Author P.J.Lawrence Jan 2007 Email P.J.Lawrence@gre.ac.uk
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
//////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <tchar.h>
#include <string>
#include "dlgtxtctrl.h"
//////////////////////////////////////////////////////////////////////////////////
bool DlgTxtControl::AppendText(const char* TheText)
{
    if (TheText)
    {
        size_t NewTxtLen=strlen(TheText);
        if (NewTxtLen>0)
        {
            if (m_TxtLimit==0)
            {
                LONG TxtLimit=SendDlgItemMessage( m_hDlg, m_ControlID,EM_GETLIMITTEXT,(WPARAM) 0,(LPARAM) 0);
                if (TxtLimit>0)
                {
                    m_TxtLimit = (UINT) TxtLimit;
                }
            }

            if (m_TxtLimit>0)
            {
                LONG TxtLength=SendDlgItemMessage( m_hDlg, m_ControlID,WM_GETTEXTLENGTH,(WPARAM) 0,(LPARAM) 0);
                m_TxtLength=(TxtLength+NewTxtLen);
                if (TxtLength>0)
                {
                    if ( m_TxtLength>m_TxtLimit)
                    {
                        // increase limit
                        m_TxtLimit = ( (20*(NewTxtLen+2))+m_TxtLimit);
                        SendDlgItemMessage( m_hDlg, m_ControlID,EM_SETLIMITTEXT,(WPARAM) m_TxtLimit,(LPARAM) 0);
                    }
                }
                // add text to edit control
                SendDlgItemMessage( m_hDlg, m_ControlID,EM_REPLACESEL,TRUE,(LPARAM) TheText);
                return (true);
            }
        }
    }
    return (false);
}
//////////////////////////////////////////////////////////////////////////////////
bool DlgTxtControl::AppendText(const std::string &TheText)
{
    return (AppendText(TheText.c_str()));
}
//////////////////////////////////////////////////////////////////////////////////
bool DlgTxtControl::Clear()
{
    SetDlgItemText( m_hDlg, m_ControlID, _T("") );
    m_TxtLength=0;
    return (true);
}