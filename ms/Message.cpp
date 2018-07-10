#include "stdafx.h"
#include "Message.h"
#include "MainDlg.h"

extern CMessage * pMsg;
extern CMainDlg * pMainUI;

CString className = _T("TianLongBaBu WndClass");

CMessage::CMessage()
{
}

CMessage::~CMessage()
{
}

CString CMessage::GetWindowTitle(HWND hwnd)
{
	CString CStitle;
	::GetWindowText(hwnd, CStitle.GetBuffer(MAX_PATH), MAX_PATH);
	CStitle.ReleaseBuffer();
	CStitle = CStitle.Left(14);

	return CStitle;
}

LRESULT CMessage::our_wndproc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	//////////////////////////////////////////////////////////////////////////
	/////////////////////////////辅助窗口的显示相关//////////////////////////
	if (wMsg == WM_KEYDOWN&&wParam == VK_HOME//判断热键键值
		)//判断窗口是否创建好了
	{
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
					CString cName = className;
					if (MyGetClassName(hwnd) == cName)//对比窗口类名是不是游戏的类
					{
						GamehWnd = hwnd;
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

int CMessage::InitLuaFun()
{
	HMODULE LuaPlus = GetModuleHandleA("LuaPlus.dll");
	if (LuaPlus)
	{
		GLua_Dostring = (Glua_dostring)GetProcAddress(LuaPlus, "lua_dostring");
		GLua_Gettable = (Glua_gettable)GetProcAddress(LuaPlus, "lua_gettable");
		GLua_Pushstring = (Glua_pushstring)GetProcAddress(LuaPlus, "lua_pushstring");
		GLua_Tonumber = (Glua_tonumber)GetProcAddress(LuaPlus, "lua_tonumber");
		GLua_Tostring = (Glua_tostring)GetProcAddress(LuaPlus, "lua_tostring");
		GLua_Settop = (Glua_settop)GetProcAddress(LuaPlus, "lua_settop");
		GpLua_Call = (Gplua_call)GetProcAddress(LuaPlus, "lua_pcall");
		GLua_Settable = (Glua_settable)GetProcAddress(LuaPlus, "lua_settable");
		GLua_Pushcclosure = (Glua_pushcclosure)GetProcAddress(LuaPlus, "lua_pushcclosure");
		GLua_Loadfile = (Glua_loadfile)GetProcAddress(LuaPlus, "luaL_loadfile");
		Gplua_type = (Glua_type)GetProcAddress(LuaPlus, "lua_type");
		if (GLua_Dostring && GLua_Gettable && GLua_Pushstring
			&& GLua_Tonumber && GLua_Tostring &&GLua_Settop)
		{
			return 1;//获取lua函数地址成功
		}
		else
		{
			return 0;//获取地址失败，模块句柄获取成功
		}
	}
	return -1;//无效模块句柄
}

int CMessage::GetLuaState()
{
	int L = 0;
	try
	{
		while (!L)
		{
			CString CStitle = GetWindowTitle(GamehWnd);
			if (CStitle.Find(_T("《新天龙八部》"), 0) != -1)
			{
				DWORD LUASTATE_BASE = 0x0;
				__asm
				{
					mov ecx, LUASTATE_BASE;
					mov ecx, [ecx];
					mov edx, [ecx];
					call[edx + 0x3c];
					mov eax, [eax];
					mov  L, eax;
				}
				dbgPrint("L  %x", L);
			}
			Sleep(500);
		}
	}
	catch (...)
	{
		L = -1;
		dbgPrint(__FUNCTION__);
	}

	return L;
}
