
// MFCcaocaohrd.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFCcaocaohrd.h"
#include "MFCcaocaohrdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "Digitalv.h"
#include <IO.h>
//#include <DbgHelp.h>  
//#pragma comment(lib,"DbgHelp.lib")

//创建dump文件
/*
void CreateDumpFile(CString lpstrDumpFilePathName, EXCEPTION_POINTERS* pException)
{
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Dump信息
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;
	// 写入dump文件
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
	CloseHandle(hDumpFile);
}

// 处理Unhandled Excepiton 的回调函数
LONG ApplicationCrashHandler(EXCEPTION_POINTERS* pException)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString strDmpName;
	strDmpName.Format("%02d%02d_%02d%02d%02d.dmp", time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	CreateDumpFile(strDmpName, pException);
	return EXCEPTION_EXECUTE_HANDLER;
}
*/
//原文链接：https ://blog.csdn.net/muyangjun/article/details/106423714
// CMFCcaocaohrdApp

BEGIN_MESSAGE_MAP(CMFCcaocaohrdApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCcaocaohrdApp 构造

CMFCcaocaohrdApp::CMFCcaocaohrdApp()
{
	
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
/*	m_ch[0] = TQZ(TGPoint(0, 0), 0, 2);
	m_ch[1] = TQZ(TGPoint(0, 1), 1,4);
	m_ch[2] = TQZ(TGPoint(0, 3), 2,2);
	m_ch[3] = TQZ(TGPoint(2, 0),3,2);
	m_ch[4] = TQZ(TGPoint(2, 1), 4,3);
	m_ch[5] = TQZ(TGPoint(2, 3), 5,2);
	m_ch[6] = TQZ(TGPoint(3, 1), 6,1);
	m_ch[7] = TQZ(TGPoint(3, 2), 7,1);
	m_ch[8] = TQZ(TGPoint(4, 0), 8,1);
	m_ch[9] = TQZ(TGPoint(4, 3), 9,1);
	m_ch[10] = TQZ(TGPoint(4, 1), 10,1);
	m_ch[11] = TQZ(TGPoint(4, 2), 11,1); */
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCcaocaohrdApp 对象

CMFCcaocaohrdApp theApp;


// CMFCcaocaohrdApp 初始化

BOOL CMFCcaocaohrdApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	getbinpath();
	game.ReadFromFile(m_strBinPath + "\\sanguohrd.txt");
	//game.WriteMapFile(m_strBinPath + "\\hrd-strmap.log");
	//调用捕捉函数
	//SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
	CMFCcaocaohrdDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
void CMFCcaocaohrdApp::getbinpath()
{
	CString strExeFullPath;
	char* pChar = strExeFullPath.GetBuffer(MAX_PATH);
	GetModuleFileName(NULL, pChar, MAX_PATH);
	strExeFullPath.ReleaseBuffer();
	int i = strExeFullPath.ReverseFind('\\');
	// strExeFullPath=strExeFullPath.Left(i);
	// i=strExeFullPath.ReverseFind('\\');
	// strExeFullPath=strExeFullPath.Left(i);
	//ASSERT(i != -1);  // not find path
	m_strBinPath = strExeFullPath.Left(i);
}
#define MCI_DGV_PLAY_REPEAT                 0x00010000L
#define MCI_DGV_PLAY_REVERSE                0x00020000L

/*
* 函数原型：int _access(const char *pathname, int mode);
参数：pathname 为文件路径或目录路径 mode 为访问权限（在不同系统中可能用不能的宏定义重新定义）
返回值：如果文件具有指定的访问权限，则函数返回0；如果文件不存在或者不能访问指定的权限，则返回-1.
备注：当pathname为文件时，_access函数判断文件是否存在，并判断文件是否可以用mode值指定的模式进行访问。当pathname为目录时，_access只判断指定目录是否存在，在Windows NT和Windows 2000中，所有的目录都只有读写权限。

原文链接：https://blog.csdn.net/u014740628/article/details/128717324
*/

void CMFCcaocaohrdApp::playMp3(BOOL bopen)
{
	// TODO: 在此处添加实现代码.
	char   buf[128];
	//use   mciSendString()   
	//mciSendString("play   e:\\songs\\把根留住.mp3",buf,sizeof(buf),NULL);   
	//mciSendString("play   e:\\songs\\zhj.mp3",buf,sizeof(buf),NULL);   
	//char   str[128]   =   {0};   
	//int   i   =   0;   

	//use   mciSendCommand   
	CString mpg = m_strBinPath + "\\bk.mp3";
	if ((_access(mpg, 0)) == -1)
	{
		//文件no存在；
		return;
	}
	MCI_OPEN_PARMS   mciOpen;
	MCIERROR   mciError;
	//mciOpen.lpstrDeviceType   =   (LPCTSTR)MCI_ALL_DEVICE_ID;   
	//mciOpen.lpstrDeviceType   =   "waveaudio";   //只能播放.wav文件   
	//mciOpen.lpstrDeviceType   =   "avivideo";     //*.avi   
	mciOpen.lpstrDeviceType = _T("mpegvideo");
	//mciOpen.lpstrDeviceType   =   "sequencer";   
	mciOpen.lpstrElementName = mpg; //_T("e:\\music\\forever.mp3");
	//mciOpen.lpstrElementName   =   "e:\\movie\\first.avi";   
	//mciOpen.lpstrElementName   =   "c:\\winnt\\media\\Windows   登录音.wav";   
	if(!bopen) {
			mciSendCommand(DeviceID, MCI_PAUSE, NULL, (DWORD_PTR)&mciOpen);
			if (DeviceID != 0)
			{
				
				mciSendCommand(DeviceID, MCI_CLOSE, NULL, (DWORD_PTR)&mciOpen);
					DeviceID = 0;
			}
			return;
	}
	if(DeviceID==0){
		mciError = mciSendCommand(DeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT , (DWORD_PTR)&mciOpen);
		if (mciError)
		{
			mciGetErrorString(mciError, buf, 128);
			MessageBox(NULL,_T(buf), _T("open ERROR"),MB_OK);
			return;
		}
		DeviceID = mciOpen.wDeviceID;
	}
 	  
	MCI_PLAY_PARMS   mciPlay;    //mciError   =   mciSendCommand(DeviceID,MCI_PLAY,0   ,(DWORD)&mciPlay);  
	//MCI_FROM | MCI_TO |  MCI_WAIT
	mciError = mciSendCommand(DeviceID, MCI_PLAY,   MCI_DGV_PLAY_REPEAT,
		(DWORD_PTR)(LPMCI_PLAY_PARMS)&mciPlay);  //MCI_DGV_PLAY_REPEAT, 要 #include "Digitalv.h"
	if (mciError)
	{
		mciGetErrorString(mciError, buf, 128);
		MessageBox(NULL, _T("send MCI_PLAY command failed"), _T("play ERROR"), MB_OK);
		return;
	} 
}
