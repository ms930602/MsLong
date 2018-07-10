#pragma once


typedef int(*Glua_dostring)(int, const char *);//do_string
typedef int(*Glua_pushstring)(int, const char *);//pushstring
typedef void(*Glua_gettable)(int, int);//gettable
typedef double(*Glua_tonumber)(int, double);//tonumber
typedef int(*Glua_settop)(int, int);//settop
typedef const char*(*Glua_tostring)(int, int);//tostring
typedef int(*Glua_pushcclosure)(int, int, int);//
typedef void(*Glua_settable)(int, int);
typedef int(*Glua_loadfile)(int, const char*);
typedef int(*Gplua_call)(int, int, int, int);
typedef int(*Glua_type)(int, int);

class CMessage
{
public:
	CMessage();
	~CMessage();

	void Init() {//初始化游戏lua函数，lua状态机，子类化游戏窗口过程
		GetGameWindow();//获取窗口句柄
		subclass_game_wndproc();//子类化窗口过程

		wchar_t lpBuffer[MAX_PATH] = { 0 };
		GetSystemDirectory(lpBuffer, MAX_PATH);
		CString strPAth(lpBuffer);
		CString strPAth2;
		strPAth2.Format(_T("\\Client%x.cfg"), GetCurrentProcessId());
		strPAth += strPAth2;

		TRACE(strPAth);
	};
	void Release() {//卸载子类化
		un_subclass_game_wndproc();
	};
public:
	HWND GamehWnd = nullptr;//游戏的窗口句柄
	WNDPROC funWndProc = nullptr;

	CString GetWindowTitle(HWND hwnd);//获取天龙标题前的文字
private:
	static LRESULT CALLBACK our_wndproc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);//窗口消息钩子
private:
	/************************************************************************/
	/* 游戏的lua函数指针定义                                                                     */
	/************************************************************************/
	Glua_dostring GLua_Dostring = nullptr;
	Glua_pushstring GLua_Pushstring = nullptr;
	Glua_gettable GLua_Gettable = nullptr;
	Glua_tonumber GLua_Tonumber = nullptr;
	Glua_settop   GLua_Settop = nullptr;
	Glua_tostring GLua_Tostring = nullptr;
	Glua_pushcclosure GLua_Pushcclosure = nullptr;
	Glua_settable	GLua_Settable = nullptr;
	Glua_loadfile	GLua_Loadfile = nullptr;
	Gplua_call	  GpLua_Call = nullptr;
	Glua_type   Gplua_type = nullptr;
	int lua_state = 0;//lua状态机指针
private:
	HWND GetGameWindow();
	CString MyGetClassName(HWND hwnd);
	void subclass_game_wndproc();//子类化窗口过程函数
	void un_subclass_game_wndproc();	//卸载子类化窗口过程
	int InitLuaFun();//获取lua库函数
	int GetLuaState();//获取游戏中lua状态指针
};