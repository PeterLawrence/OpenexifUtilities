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
#ifndef DlgTxtControl_H
#define DlgTxtControl_H
//////////////////////////////////////////////////////////////////////////////////
class DlgTxtControl
{
private:
    HWND m_hDlg;
    UINT m_ControlID;
    UINT m_TxtLimit;
    UINT m_TxtLength;
public:
    DlgTxtControl(HWND hDlg,UINT aControlID)
    {
        m_hDlg=hDlg;
        m_ControlID=aControlID;
        m_TxtLimit=0;
        m_TxtLength=0;
    }

    UINT GetControlID() { return(m_ControlID); }
    void SetTxtLimit(UINT aVal) { m_TxtLimit = aVal; }
    UINT GetTxtLimit() { return(m_TxtLimit); }
    void SetTxtLength(UINT aVal) { m_TxtLength = aVal; }
    UINT GetTxtLength() { return(m_TxtLength); }
    bool AppendText(const char* TheText);
    bool AppendText(const std::string &TheText);
    bool Clear();
};
#endif