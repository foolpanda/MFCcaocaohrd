#pragma once
#include <afxwin.h>
class CMFCcaocaohrdDlg;
class CDemoThread :
    public CWinThread
{
public:
    CMFCcaocaohrdDlg* pdlg;
    int& xspeed;
    BOOL bdemo = true;
    CDemoThread(int& speed, CMFCcaocaohrdDlg* dlg):xspeed(speed),pdlg(dlg) {

    }
    virtual BOOL InitInstance();
    virtual int ExitInstance();
};

