#include "pch.h"
#include "CDemoThread.h"
#include "MFCcaocaohrdDlg.h"
#include "resource.h"
BOOL CDemoThread::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	while (bdemo) {
		Sleep(this->xspeed);
		pdlg->PostMessage(QZ_AUTO, pdlg->m_index, 0);

	}
	return CWinThread::InitInstance();
}


int CDemoThread::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CWinThread::ExitInstance();
}
