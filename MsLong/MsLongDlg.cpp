
// MsLongDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MsLong.h"
#include "MsLongDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


HWND g_MyHwnd = nullptr;
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


// CMsLongDlg 对话框



CMsLongDlg::CMsLongDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MSLONG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMsLongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CMsLongDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMsLongDlg::OnTcnSelchangeTabMain)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_USER_NOTIFYICON, OnNotifyMsg)
END_MESSAGE_MAP()


// CMsLongDlg 消息处理程序

BOOL CMsLongDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO: 在此添加额外的初始化代码
	m_tab.InsertItem(0, _T("控制台"));
	m_tab.InsertItem(1, _T("基础信息"));
	m_pageA.Create(IDD_DIALOG1, &m_tab);
	m_pageB.Create(IDD_DIALOG2, &m_tab);
	//设定在Tab内显示的范围  
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_pageA.MoveWindow(&rc);
	m_pageB.MoveWindow(&rc);
	//把对话框对象指针保存起来  
	pDialog[0] = &m_pageA;
	pDialog[1] = &m_pageB;
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//保存当前选择  
	m_CurSelTab = 0;

	/***** Start *****
	托盘图标
	*/
	m_notify.cbSize = sizeof(NOTIFYICONDATA);//结构体大小
	m_notify.hWnd = m_hWnd;//对应窗口
	m_notify.uID = IDR_MAINFRAME;//托盘id
	m_notify.hIcon = m_hIcon;//图标

	lstrcpy(m_notify.szTip, _T("B数控制台"));

	m_notify.uCallbackMessage = WM_USER_NOTIFYICON;//处理消息
	m_notify.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; //有效标志
	Shell_NotifyIcon(NIM_ADD, &m_notify);//添加托盘
	/***** End *****/
	g_MyHwnd = m_hWnd;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMsLongDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMsLongDlg::OnPaint()
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
HCURSOR CMsLongDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMsLongDlg::OnNotifyMsg(WPARAM wparam, LPARAM lparam)

//wParam接收的是图标的ID，而lParam接收的是鼠标的行为   
{
	if (wparam != IDR_MAINFRAME)
		return    1;
	switch (lparam)
	{
	case  WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”     
	{
		LPPOINT    lpoint = new    tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置
		CMenu    menu;
		menu.CreatePopupMenu();//声明一个弹出式菜单     
							   //增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已     
							   //隐藏），将程序结束。    
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭"));
		//确定弹出式菜单的位置     
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		//资源回收
		HMENU    hmenu = menu.Detach();
		menu.DestroyMenu();
		delete    lpoint;
	}
	break;
	case    WM_LBUTTONDBLCLK://双击左键的处理     
	{
		if (IsWindowVisible())
			ShowWindow(SW_HIDE);
		else
			ShowWindow(SW_SHOW);//简单的显示主窗口完事儿 
	}
	break;
	}
	return 0;

}



void CMsLongDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//得到新的页面索引  
	int index = m_CurSelTab;
	m_CurSelTab = m_tab.GetCurSel();
	if (m_CurSelTab != index) {
		//把当前的页面隐藏起来  
		pDialog[index]->ShowWindow(SW_HIDE);
		//把新的页面显示出来  
		pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}


void CMsLongDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (IDNO == ::MessageBox(this->m_hWnd, _T("退出程序将无法执行脚本，退出吗?"), _T("警告"),

		MB_ICONEXCLAMATION | MB_YESNO))
	{
		return;
	}
	else {
		::Shell_NotifyIcon(NIM_DELETE, &m_notify); //关闭时删除系统托盘图标  
		CDialog::OnClose();
	}
}


LRESULT CMsLongDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch (message) //判断消息类型  
	{
	case WM_SYSCOMMAND:
		//如果是系统消息   
		if (wParam == SC_MINIMIZE)
		{
			//接收到最小化消息时主窗口隐藏   
			AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);
			return 0;
		}
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}