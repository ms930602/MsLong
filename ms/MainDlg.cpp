// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ms.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "self.h"

extern CSelf* pSelf;

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_Tab);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_MESSAGE(WM_MY_MESSAGE, OnMyMessage)
	ON_MESSAGE(WM_MYSTYLEEX_MESSAGE, OnMyStyleMessage)
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CMainDlg::OnTcnSelchangeTabMain)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序


BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	m_Tab.InsertItem(0, _T("控制台"));
	m_Tab.InsertItem(1, _T("基础信息"));
	m_pageA.Create(IDD_DLG_TAB_A, &m_Tab);
	m_pageB.Create(IDD_DLG_TAB_B, &m_Tab);
	//设定在Tab内显示的范围  
	CRect rc;
	m_Tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_pageA.MoveWindow(&rc);
	m_pageB.MoveWindow(&rc);

	m_pageA.ShowWindow(SW_HIDE);

	m_pageA.ShowWindow(SW_SHOW);

	//保存当前选择  
	m_CurSelTab = 0;
	return TRUE;
}

LRESULT CMainDlg::OnMyStyleMessage(WPARAM wParam, LPARAM lParam)
{
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);//显示在任务栏
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();

	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	return 0;
}

LRESULT CMainDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	switch ((int)lParam)
	{
	case 0://开始按钮禁用
		TRACE("OnMyMessage --> 0");
		break;
	case 1://修改开始按钮信息
		TRACE("OnMyMessage --> 1");
		break;
	case 2://取消开始按钮禁用状态
		TRACE("OnMyMessage --> 2");
		break;
	case 3://各个窗口加载数据
		TRACE("OnMyMessage --> 3");
		break;
	case 4:
		TRACE("OnMyMessage --> 4");
		break;
	}
	return 0;
}


void CMainDlg::OnClose()
{
	if (pSelf->bUiThread)
	{
		this->ShowWindow(SW_HIDE);
		return;
	}
	CDialogEx::OnClose();
}


void CMainDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	int index = m_CurSelTab;
	m_CurSelTab = m_Tab.GetCurSel();
	if (m_CurSelTab != index) {
		switch (m_CurSelTab)
		{
		case 0:
			m_pageB.ShowWindow(SW_HIDE);

			m_pageA.ShowWindow(SW_SHOW);
			break;
		case 1:
			m_pageA.ShowWindow(SW_HIDE);

			m_pageB.ShowWindow(SW_SHOW);
			break;
		}
	}
	*pResult = 0;
}
