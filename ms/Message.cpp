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
	/////////////////////////////辅助窗口的显示相关//////////////////////////

	if (wMsg == WM_KEYDOWN&&wParam == VK_HOME//判断热键键值
		&&pMainUI&&pMainUI->m_hWnd&&::IsWindow(pMainUI->m_hWnd))//判断窗口是否创建好了
	{
		if (::IsWindowVisible(pMainUI->m_hWnd))//判断窗口状态可见就隐藏这个窗口
		{
			::ShowWindow(pMainUI->m_hWnd, SW_HIDE);
		}
		else
		{
			::SendMessage(pMainUI->m_hWnd, WM_MYSTYLEEX_MESSAGE, 0, 0);//弹出辅助窗口，并置顶
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
		HWND  hwnd = ::GetTopWindow(NULL);//获取顶层窗口句柄
		while (hwnd)
		{
			DWORD dwPId = 0;
			::GetWindowThreadProcessId(hwnd, &dwPId);//找出某个窗口的创建者线程或进程返回创建者的标志
			if (dwCurPId == dwPId)
			{
				if (::GetParent(hwnd) == 0)//GetParent检查这个窗口是否有父窗口
				{
					if (MyGetClassName(hwnd) == "TianLongBaBu WndClass")//对比窗口类名是不是游戏的类
					{
						GamehWnd = hwnd;
						return GamehWnd;
					}
				}
			}
			hwnd = ::GetNextWindow(hwnd, GW_HWNDNEXT);//获取下个窗口句柄
		}
		Sleep(1000);
	}

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
		dbgPrint(_T("安装子类化窗口"));
	}
}

void CMessage::un_subclass_game_wndproc()
{
	if (GamehWnd && funWndProc)
	{
		dbgPrint(_T("卸载子类化窗口"));
		::SetWindowLong(GamehWnd, GWL_WNDPROC, (LONG)funWndProc);
	}
}
