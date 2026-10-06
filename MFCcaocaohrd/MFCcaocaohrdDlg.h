
// MFCcaocaohrdDlg.h: 头文件
//

#pragma once

#include "TStage.h"
class CDemoThread;
// CMFCcaocaohrdDlg 对话框
class CMFCcaocaohrdDlg : public CDialogEx
{
// 构造
public:
	CMFCcaocaohrdDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HRD_DIALOG};
#endif
	int m_index=0;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_steps;

	afx_msg void OnBnClickedRunsol();
protected:
	afx_msg LRESULT OnQzAuto(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnQzMove(WPARAM wParam, LPARAM lParam);
	int setstage(TStage& st);
public:
	afx_msg void OnSelchangeCombo1();
	CSliderCtrl m_speed;
#define	IDT_TIMER_0	WM_USER + 200
	UINT  StartTimer(UINT TimerDuration);
	BOOL StopTimer(UINT TimerVal);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	void getSpeed();
	int xspeed = 0;
	CDemoThread* m_pdemothread = NULL;
public:
	afx_msg void OnBnClickedSolver();
	afx_msg void OnBnClickedOk();

	
	BOOL m_bsilent;

	afx_msg void OnBnClickedSilent();
};
