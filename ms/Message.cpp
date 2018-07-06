#include "stdafx.h"
#include "Message.h"
#include "MainDlg.h"

extern CMessage * pMsg;
extern CMainDlg * pMainUI;

CString className = _T("WindowsForms10.Window.8.app.0.141b42a_r14_ad1");// TianLongBaBu WndClass | WindowsForms10.Window.8.app.0.141b42a_r14_ad1

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
	if (wMsg == WM_KEYDOWN&&wParam == VK_HOME//�ж��ȼ���ֵ
		)//�жϴ����Ƿ񴴽�����
	{
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
	//////////////////////////////////////////////////////////////////////////

	return ::CallWindowProc(pMsg->funWndProc, hWnd, wMsg, wParam, lParam);
}

HWND CMessage::GetGameWindow()
{
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
					CString cName = className;
					if (MyGetClassName(hwnd) == cName)//�Աȴ��������ǲ�����Ϸ����
					{
						GamehWnd = hwnd;
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
