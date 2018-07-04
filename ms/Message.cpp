#include "stdafx.h"
#include "Message.h"
#include "MainDlg.h"

extern CMessage * pMsg;
extern CMainDlg * pMainUI;

CMessage::CMessage()
{
}

CMessage::~CMessage()
{
}

LRESULT CMessage::our_wndproc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	//////////////////////////////////////////////////////////////////////////
	/////////////////////////////�������ڵ���ʾ���//////////////////////////
	TRACE("��Ϣ����");
	TRACE("����home�ж� WM_KEYDOWN %d", wMsg == WM_KEYDOWN);
	TRACE("����home�ж� VK_HOME %d", wParam == VK_HOME);
	if (wMsg == WM_KEYDOWN&&wParam == VK_HOME//�ж��ȼ���ֵ
		&&pMainUI&&pMainUI->m_hWnd&&::IsWindow(pMainUI->m_hWnd))//�жϴ����Ƿ񴴽�����
	{
		TRACE("����home�ж�");
		if (::IsWindowVisible(pMainUI->m_hWnd))//�жϴ���״̬�ɼ��������������
		{
			TRACE("����");
			::ShowWindow(pMainUI->m_hWnd, SW_HIDE);
		}
		else
		{
			TRACE("��ʾ");
			::SendMessage(pMainUI->m_hWnd, WM_MYSTYLEEX_MESSAGE, 0, 0);//�����������ڣ����ö�
		}
	}
	TRACE("��Ϣ����");
	//////////////////////////////////////////////////////////////////////////

	return ::CallWindowProc(pMsg->funWndProc, hWnd, wMsg, wParam, lParam);
}

HWND CMessage::GetGameWindow()
{
	TRACE("��ȡ��ǰ��Ϸ���ھ��");
	while (true)
	{
		DWORD dwCurPId = ::GetCurrentProcessId();
		HWND  hwnd = ::GetTopWindow(NULL);//��ȡ���㴰�ھ��
		while (hwnd)
		{
			DWORD dwPId = 0;
			::GetWindowThreadProcessId(hwnd, &dwPId);//�ҳ�ĳ�����ڵĴ������̻߳���̷��ش����ߵı�־
			if (dwCurPId == dwPId)
			{
				if (::GetParent(hwnd) == 0)//GetParent�����������Ƿ��и�����
				{
					if (MyGetClassName(hwnd) == "WindowsForms10.Window.8.app.0.141b42a_r14_ad1")//�Աȴ��������ǲ�����Ϸ���� TianLongBaBu WndClass
					{
						GamehWnd = hwnd;
						TRACE("��ȡ��ǰ��Ϸ���ھ�� : �ɹ� %d", GamehWnd);
						return GamehWnd;
					}
				}
			}
			hwnd = ::GetNextWindow(hwnd, GW_HWNDNEXT);//��ȡ�¸����ھ��
		}
	}
	TRACE("��ȡ��ǰ��Ϸ���ھ�� : ʧ��");
	return NULL;
}

CString CMessage::MyGetClassName(HWND hwnd)
{
	CString strname;
	GetClassName(hwnd, strname.GetBuffer(MAX_PATH), MAX_PATH);
	strname.ReleaseBuffer();

	return strname;
}

void CMessage::subclass_game_wndproc()
{
	if (GamehWnd)
	{
		funWndProc = (WNDPROC)::SetWindowLong(GamehWnd, GWL_WNDPROC, (LONG)our_wndproc);
		TRACE(_T("��װ���໯����"));
	}
}

void CMessage::un_subclass_game_wndproc()
{
	if (GamehWnd && funWndProc)
	{
		dbgPrint(_T("ж�����໯����"));
		::SetWindowLong(GamehWnd, GWL_WNDPROC, (LONG)funWndProc);
	}
}
