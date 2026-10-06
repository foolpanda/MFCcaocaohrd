
// MFCcaocaohrd.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include "QZ.h"
#include "WNDChess.h"
#include "TStage.h"
// CMFCcaocaohrdApp:
// 有关此类的实现，请参阅 MFCcaocaohrd.cpp
//

class CMFCcaocaohrdApp : public CWinApp
{
public:
	//TQZ  m_ch[12];
	WNDChess ch[12];
	TBoardMAP cb;
	bool flag=false;
	TGame game;
	UINT   DeviceID=0;
public:
	CString m_strBinPath;
	CMFCcaocaohrdApp();
	void getbinpath();

	void playMp3(BOOL bopen);
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

};

extern CMFCcaocaohrdApp theApp;
