// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ms.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// CMainDlg �Ի���

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
END_MESSAGE_MAP()


// CMainDlg ��Ϣ��������


void CMainDlg::OnBnClickedBtn1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
}

LRESULT CMainDlg::OnMyStyleMessage(WPARAM wParam, LPARAM lParam)
{
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);//��ʾ��������
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();

	//SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	return 0;
}