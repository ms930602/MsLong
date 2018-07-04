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
	TRACE("消息进入");
	TRACE("进入home判断 WM_KEYDOWN %d", wMsg == WM_KEYDOWN);
	TRACE("进入home判断 VK_HOME %d", wParam == VK_HOME);
	if (wMsg == WM_KEYDOWN&&wParam == VK_HOME//判断热键键值
		&&pMainUI&&pMainUI->m_hWnd&&::IsWindow(pMainUI->m_hWnd))//判断窗口是否创建好了
	{
		TRACE("进入home判断");
		if (::IsWindowVisible(pMainUI->m_hWnd))//判断窗口状态可见就隐藏这个窗口
		{
			TRACE("隐藏");
			::ShowWindow(pMainUI->m_hWnd, SW_HIDE);
		}
		else
		{
			TRACE("显示");
			::SendMessage(pMainUI->m_hWnd, WM_MYSTYLEEX_MESSAGE, 0, 0);//弹出辅助窗口，并置顶
		}
	}
	TRACE("消息结束");
	//////////////////////////////////////////////////////////////////////////

	return ::CallWindowProc(pMsg->funWndProc, hWnd, wMsg, wParam, lParam);
}

HWND CMessage::GetGameWindow()
{
	TRACE("获取当前游戏窗口句柄");
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
					if (MyGetClassName(hwnd) == "WindowsForms10.Window.8.app.0.141b42a_r14_ad1")//对比窗口类名是不是游戏的类 TianLongBaBu WndClass
					{
						GamehWnd = hwnd;
						TRACE("获取当前游戏窗口句柄 : 成功 %d", GamehWnd);
						return GamehWnd;
					}
				}
			}
			hwnd = ::GetNextWindow(hwnd, GW_HWNDNEXT);//获取下个窗口句柄
		}
	}
	TRACE("获取当前游戏窗口句柄 : 失败");
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
		TRACE(_T("安装子类化窗口"));
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
