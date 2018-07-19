#include "stdafx.h"
#include "self.h"
#include "Message.h"
#include "MainDlg.h"
#include "MsBase.h"

extern CSelf* pSelf;
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

const char * CMessage::telua_tostring(int n)
{
	__try {
		return GLua_Tostring(lua_state, n);
	}
	__except (1) {
		TRACE(__FUNCTION__);
		return "ERROR :lua_Tostring";
	}
}

int myluaregstertogame(int a)
{
	pSelf->CreatAgainLogin();

	return 0;
}

int myluadbgprint(int a)
{
	
	TRACE(pMsg->telua_tostring(-1));

	return 0;
}

LRESULT CMessage::our_wndproc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	if (wMsg == LUA_MEASSAGE)
	{
		pMsg->telua_dostring((char*)lParam);
	}
	else if (wMsg == LUA_GETVALUE)
	{
		pMsg->telua_getnumber((char*)lParam, (PVOID)wParam);
	}
	else if (wMsg == LUA_GETSTRING)
	{
		pMsg->telua_getstring((char*)lParam, (char*)wParam);
	}
	else if (wMsg == LUA_REGISTEREX)//加载lua lib文件
	{
		pMsg->telua_loadfile((char*)lParam);
		pMsg->telua_register("GMsLuaRegsterToGame", (int)myluaregstertogame);
		pMsg->telua_register("GMsLuaDugPrint", (int)myluadbgprint);
	}
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

int CMessage::telua_loadfile(const char * file)
{
	__try {
		if (GLua_Loadfile(lua_state, file) || GpLua_Call(lua_state, 0, 0, 0))
		{
			return 1;
		}
		return 0;
	}
	__except (1) {
		TRACE(__FUNCTION__);
		return -1;
	}
}

bool CMessage::telua_register(const char * FuncName, int pFun)
{
	__try {
		GLua_Pushstring(lua_state, FuncName);
		GLua_Pushcclosure(lua_state, pFun, 0);
		GLua_Settable(lua_state, -10001);
		return true;
	}
	__except (1) {
		TRACE(__FUNCTION__);
		return false;
	}
}

bool CMessage::telua_dostring(const char * args)
{
	__try {
		GLua_Dostring(lua_state, args);
		return true;
	}
	__except (1) { TRACE(__FUNCTION__); return false; }
}

bool CMessage::telua_getglobal(const char * name)
{
	__try {
		GLua_Pushstring(lua_state, name);
		GLua_Gettable(lua_state, -10001);
		return true;
	}
	__except (1) { TRACE(__FUNCTION__); return false; }
}

double CMessage::telua_tonumber(int n)
{
	__try {
		return GLua_Tonumber(lua_state, n);
	}
	__except (1) {
		TRACE(__FUNCTION__);
		return 1.234567;
	}
}

void CMessage::telua_pop(int n)
{
	__try {
		GLua_Settop(lua_state, -(n)-1);
	}
	__except (1) {
		dbgPrint(__FUNCTION__);
	}
}

bool CMessage::telua_getnumber(const char * buf, PVOID out)
{
	__try {
		if (telua_dostring(buf))
		{
			if (telua_getglobal("g_GetValue"))
			{
				*(int*)out = (int)telua_tonumber(-1);
				telua_pop(1);
				return true;
			}
			else
			{
				TRACE("%s telua_getglobal erro", __FUNCTION__);
				return false;
			}
		}
		else
		{
			TRACE("%s telua_dostring erro", __FUNCTION__);
			return false;
		}
	}
	__except (1) {
		TRACE(__FUNCTION__); return false;
	}
}

bool CMessage::telua_getstring(const char * buf, const char * want_get_string)
{
	__try {
		if (telua_dostring(buf))
		{
			if (telua_getglobal(want_get_string))
			{
				const char* str = telua_tostring(-1);
				sprintf((char*)buf, str);
				telua_pop(1);
				return true;
			}
			else
			{
				TRACE("%s telua_getglobal erro", __FUNCTION__);
				return false;
			}
		}
		else
		{
			TRACE("%s telua_getglobal erro", __FUNCTION__);
			return false;
		}
	}
	__except (1) {
		TRACE(__FUNCTION__); return false;
	}
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
		TRACE(_T("卸载子类化窗口"));
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
			TRACE("获取lua函数成功");
			return 1;//获取lua函数地址成功
		}
		else
		{
			TRACE("获取lua函数失败");
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
				__asm
				{
					mov  ecx, K_LUASTATE_BASE;
					mov  ecx, [ecx];
					mov  edx, [ecx];
					call [edx + 0x3c];
					mov  eax, [eax];
					mov  L, eax;
				}
				TRACE("L  %x", L);
				return L;
			}
			Sleep(500);
		}
	}
	catch (...)
	{
		L = -1;
		TRACE(__FUNCTION__);
	}

	return L;
}

BOOL CMessage::LUAInitialize()
{
	CHAR lpBuffer[MAX_PATH] = { 0 };
	HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, lpBuffer);
	CString strPAth(lpBuffer);
	CString strPAth2;
	strPAth2.Format(_T("\\Client%x.cfg"), GetCurrentProcessId());
	strPAth += strPAth2;

	HRSRC hResc = ::FindResource(pSelf->hDll, MAKEINTRESOURCE(IDR_RCDATA1), RT_RCDATA);
	if (hResc == NULL)
	{
		TRACE("LUAInitialize GetLastError  ==   %d", ::GetLastError());
		return FALSE;
	}

	DWORD dwImageSize = SizeofResource(pSelf->hDll, hResc);

	HGLOBAL hResourceImage = ::LoadResource(pSelf->hDll, hResc);
	if (hResourceImage == NULL)
	{
		TRACE("LUAInitialize ERROR %s", __FUNCTION__);
		return FALSE;
	}
	PVOID pMemory = ::LockResource(hResourceImage);
	if (pMemory == NULL)
	{
		TRACE("LUAInitialize ERROR %s", __FUNCTION__);
		return FALSE;
	}

	HANDLE hFile = CreateFile(strPAth, GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		TRACE("LUAInitialize ERROR %s", __FUNCTION__);
		return FALSE;
	}

	DWORD dwByteWrite;
	if (!WriteFile(hFile, pMemory, dwImageSize, &dwByteWrite, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	if (dwByteWrite != dwImageSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	::CloseHandle(hFile);
	Sleep(1000);
	::SendMessage(GamehWnd, LUA_REGISTEREX, 0, (LPARAM)strPAth.GetString());//注册lua，加载lua_lib
	DeleteFile(strPAth);
	return TRUE;
}

void CMessage::msg_dostring(const char * _Format, ...)
{
	CriticalSectionLock lock(&m_State);

	try
	{
		char do_stringBuf[2048] = { 0 };//用于存放do_string的字符串缓冲区
		va_list list;
		va_start(list, _Format);
		vsprintf(do_stringBuf, _Format, list);
		va_end(list);
		::SendMessage(GamehWnd, LUA_MEASSAGE, 0, (LPARAM)do_stringBuf);
	}
	catch ( ... )
	{
		TRACE(__FUNCTION__);
	}
}

int CMessage::msg_getnumber(char * _Format, ...)
{
	CriticalSectionLock lock(&m_State);

	int nValue = 0;
	try
	{
		char getnumberBuf[2048] = { 0 };//用于存放getnumber的字符串缓冲区
		va_list list;
		va_start(list, _Format);
		vsprintf(getnumberBuf, _Format, list);
		va_end(list);
		::SendMessage(GamehWnd, LUA_GETVALUE, (WPARAM)&nValue, (LPARAM)getnumberBuf);
	}
	catch (...)
	{
		TRACE(__FUNCTION__);
	}

	return nValue;
}

string CMessage::msg_getstring(const char * str_arg, char * _Format, ...)
{
	CriticalSectionLock lock(&m_State);
	string str;
	try
	{
		char getstringBuf[2048] = { 0 };//用于存放getstring的字符串缓冲区
		va_list list;
		va_start(list, _Format);
		vsprintf(getstringBuf, _Format, list);
		va_end(list);
		::SendMessage(GamehWnd, LUA_GETSTRING, (WPARAM)str_arg, (LPARAM)getstringBuf);
		str = getstringBuf;
	}
	catch (...)
	{
		TRACE(__FUNCTION__);
	}

	return str;
}

int CMessage::GetData(const char * str)
{
	return	msg_getnumber("g_GetValue = Player:GetData(\"%s\");", str);
}

RolePos CMessage::GetRolePos()
{
	
	return RolePos();
}

int CMessage::GetCurMountID()
{
	return 0;
}