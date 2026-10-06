
// MFCcaocaohrdDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCcaocaohrd.h"
#include "MFCcaocaohrdDlg.h"
#include "afxdialogex.h"
#include "CDemoThread.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCcaocaohrdDlg 对话框



CMFCcaocaohrdDlg::CMFCcaocaohrdDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HRD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCcaocaohrdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_steps);
	DDX_Control(pDX, IDC_SLIDER1, m_speed);
	DDX_Check(pDX, IDC_SILENT, m_bsilent);
}

BEGIN_MESSAGE_MAP(CMFCcaocaohrdDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_RUNSOL, &CMFCcaocaohrdDlg::OnBnClickedRunsol)
	
	ON_MESSAGE(QZ_AUTO, &CMFCcaocaohrdDlg::OnQzAuto)
	ON_MESSAGE(QZ_MOVE, &CMFCcaocaohrdDlg::OnQzMove)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCcaocaohrdDlg::OnSelchangeCombo1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SOLVER, &CMFCcaocaohrdDlg::OnBnClickedSolver)
	ON_BN_CLICKED(IDOK, &CMFCcaocaohrdDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SILENT, &CMFCcaocaohrdDlg::OnBnClickedSilent)
END_MESSAGE_MAP()


// CMFCcaocaohrdDlg 消息处理程序

BOOL CMFCcaocaohrdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	CComboBox* pcomb = (CComboBox*)GetDlgItem(IDC_COMBO1);
	for (TStage st: app->game.m_stages) {
		CString sname = st.name.c_str();
		pcomb->AddString(sname);
	}
	/*((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("横刀立马");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("四路进兵");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("五将逼宫");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("巧过五关");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("兵临曹营");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("层层设防");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("前呼后拥");
	*/
	//	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("守口如瓶");
	//	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("守口如瓶1");
	//	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("三军联防");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	setstage(app->game.m_stages[0]);
	m_bsilent = 0;
	app->playMp3(!m_bsilent);
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
int CMFCcaocaohrdDlg::setstage(TStage& st)
{
	// TODO: 在此处添加实现代码.
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	vector<TQZ> Qzs;
	for (int vi = 0; vi < 12; vi++)
	{
		TRole &rl=st.roles[vi];
		TQZ  mqz = TQZ(TGPoint(rl.l,rl.c),rl.id,rl.type);// st->m_ch[vi];
		//TQZ  mqz = TQZ::fromRole(rl);
		TGPoint p = mqz.p;
		int t = rl.type;
		app->ch[vi].Set(p.c, p.l, t);
		app->ch[vi].NO = vi;
		Qzs.push_back(mqz);
	}

	for (int i = 0; i < 10; i++)
	{
		if (app->ch[i].GetSafeHwnd() != NULL) {
			app->ch[i].DestroyWindow();
		}
		app->ch[i].Create(NULL, WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON | WS_VISIBLE,
			app->ch[i].GetRect(), this, i+20);
		if (app->ch[i].type == 2 || app->ch[i].type == 3 || app->ch[i].type == 4)
		{
			app->ch[i].LoadBitmaps(10 * i + app->ch[i].type);
		}
		else
			app->ch[i].LoadBitmaps(IDB_S);
		app->ch[i].RedrawWindow();
		app->ch[i].ShowWindow(SW_SHOW);
	}
	// TODO: 在此添加额外的初始化代码
	Qzs.resize(10);
	string strmap = TBoardMAP::getMapString(Qzs);
	string strmap2 = TBoardMAP::getMapBString(Qzs);
	app->cb = TBoardMAP(strmap2, Qzs, 0);
	return 0;
}
void CMFCcaocaohrdDlg::OnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox* pcomb = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int m_gamei = pcomb->GetCurSel();
	CString gamename;
	pcomb->GetLBText(m_gamei, gamename);
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	for (TStage st : app->game.m_stages) {
		if (gamename.CompareNoCase(st.name.c_str()) == 0) {
			setstage(st);
			break;
		}
	}
}
void CMFCcaocaohrdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCcaocaohrdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCcaocaohrdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


vector<Move> x_resPath;

void  CMFCcaocaohrdDlg::getSpeed() {
	UINT  speed = m_speed.GetPos();
	xspeed = 100 + speed * 50;
}
void CMFCcaocaohrdDlg::OnBnClickedRunsol()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int ix = 0;
	m_index = 0;
//	this->PostMessageA(QZ_AUTO, m_index, 0);
	int nMin = 0, nMax = 10;
	m_speed.GetRange(nMin, nMax);
	getSpeed();
	if (m_pdemothread == NULL) {
		GetDlgItem(IDC_RUNSOL)->EnableWindow(FALSE);
		m_pdemothread = new CDemoThread(xspeed, this);
		m_pdemothread->CreateThread();
		
	}
	//Sleep();
	//StartTimer(xspeed);
	/*for (Move m : x_resPath) {
		WNDChess& mch = app->ch[m.qzIdx];
		switch (m.dir)
		{
		case 0:   mch.moveself(-10,0);  break;
			case 1: mch.moveself(0, -10);    break;
			case 2: mch.moveself(10, 0);     break;
			case 3: mch.moveself(0,  10);	break;
			default:ix++;
				break;
		}
		Sleep(1000);

	}*/
}
afx_msg LRESULT CMFCcaocaohrdDlg::OnQzMove(WPARAM wParam, LPARAM lParam) {
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	int qzid = (int)wParam;
	int dir =(int) lParam;
	ASSERT(qzid < 12 && qzid >= 0);
	ASSERT(dir < 4 && dir >= 0);
	WNDChess& mch = app->ch[qzid];
	switch (dir)
	{
	case 0: mch.moveself(-10, 0);  break;
	case 1: mch.moveself(0, -10);    break;
	case 2: mch.moveself(10, 0);     break;
	case 3: mch.moveself(0, 10);	break;
	default:
		return 1;
		break;
	}
	if(m_pdemothread==NULL)
	if (app->cb.ifEnd()) {
		MessageBox("恭喜你过关了! 好样的. (^0^)");
	}
	return 0;
}

afx_msg LRESULT CMFCcaocaohrdDlg::OnQzAuto(WPARAM wParam, LPARAM lParam)
{
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	if (m_index < x_resPath.size()) {
		Move& m = x_resPath[m_index];
		OnQzMove(m.qzIdx, m.dir);
		++m_index;
		getSpeed();
		//this->PostMessageA(QZ_AUTO, m_index, 0);
		

	}
	else {
		//for (int i = 0;i < 10;i++) {
			//app->ch[i].RedrawWindow();
		//}
		//StopTimer(IDT_TIMER_0);
		if (m_index > 800) return 0;
		m_index = 1000;
		if (m_pdemothread) {
			m_pdemothread->bdemo = false;
			Sleep(200);
			//delete m_pdemothread;
			m_pdemothread = NULL;
		}
		
		MessageBox("演示完成");
		GetDlgItem(IDC_RUNSOL)->EnableWindow(TRUE);
		
	}
	return 0;
}

UINT  CMFCcaocaohrdDlg::StartTimer(UINT TimerDuration)
{

	UINT    TimerVal;

	TimerVal = SetTimer(IDT_TIMER_0, TimerDuration, NULL);
	if (TimerVal == 0)
	{
		MessageBox(_T("Unable to obtain timer"),_T("IDT_TIMER_0"),	MB_OK | MB_SYSTEMMODAL);
	}
	return TimerVal;


}// end
BOOL CMFCcaocaohrdDlg::StopTimer(UINT TimerVal)
{
	if (!KillTimer(TimerVal))
	{
		return FALSE;
	}
	return TRUE;
} // end StopTimer

void CMFCcaocaohrdDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OnQzAuto(0, 0);
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCcaocaohrdDlg::OnBnClickedSolver()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pdemothread) {
		MessageBox("正在演示过程中，无法求解!!!");
		return;
	}
	TAutoSolver sol;
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	vector<TQZ> Qzs;
	for (int vi = 0; vi < 10; vi++)
	{
		if (app->cb.QZs.size() < 10) {
			break;
		}
		TQZ& mqz = app->cb.QZs[vi];
		Qzs.push_back(mqz);
	}
	sol.solveNew(app->cb.QZs);
	string res = sol.cout2.str();
	CString res2 = res.c_str();
	x_resPath = sol.m_resPath;
	res2.Replace("\n", "\r\n");
	m_steps.SetWindowTextA(res2);
}


void CMFCcaocaohrdDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}




void CMFCcaocaohrdDlg::OnBnClickedSilent()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CMFCcaocaohrdApp* app = (CMFCcaocaohrdApp*)AfxGetApp();
	app->playMp3(!m_bsilent);
	
}
