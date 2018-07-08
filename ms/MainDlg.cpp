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
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_1, &CMainDlg::OnBnClickedBtn1)
	ON_MESSAGE(WM_MYSTYLEEX_MESSAGE, OnMyStyleMessage)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMainDlg 消息处理程序


BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

void CMainDlg::OnBnClickedBtn1()
{
}

LRESULT CMainDlg::OnMyStyleMessage(WPARAM wParam, LPARAM lParam)
{
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);//显示在任务栏
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();

	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

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
