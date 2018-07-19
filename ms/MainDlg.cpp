// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ms.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "self.h"

extern CSelf* pSelf;

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
	DDX_Control(pDX, IDC_TAB_MAIN, m_Tab);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_MESSAGE(WM_MY_MESSAGE, OnMyMessage)
	ON_MESSAGE(WM_MYSTYLEEX_MESSAGE, OnMyStyleMessage)
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CMainDlg::OnTcnSelchangeTabMain)
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������


BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_Tab.InsertItem(0, _T("����̨"));
	m_Tab.InsertItem(1, _T("������Ϣ"));
	m_pageA.Create(IDD_DLG_TAB_A, &m_Tab);
	m_pageB.Create(IDD_DLG_TAB_B, &m_Tab);
	//�趨��Tab����ʾ�ķ�Χ  
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

	//���浱ǰѡ��  
	m_CurSelTab = 0;
	return TRUE;
}

LRESULT CMainDlg::OnMyStyleMessage(WPARAM wParam, LPARAM lParam)
{
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);//��ʾ��������
	ShowWindow(SW_RESTORE);
	SetForegroundWindow();

	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	return 0;
}

LRESULT CMainDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	switch ((int)lParam)
	{
	case 0://��ʼ��ť����
		TRACE("OnMyMessage --> 0");
		break;
	case 1://�޸Ŀ�ʼ��ť��Ϣ
		TRACE("OnMyMessage --> 1");
		break;
	case 2://ȡ����ʼ��ť����״̬
		TRACE("OnMyMessage --> 2");
		break;
	case 3://�������ڼ�������
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
