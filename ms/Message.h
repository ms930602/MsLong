#pragma once
class CMessage
{
public:
	CMessage();
	~CMessage();

	void Init() {//初始化游戏lua函数，lua状态机，子类化游戏窗口过程
		GetGameWindow();//获取窗口句柄
		subclass_game_wndproc();//子类化窗口过程
	};
	void Release() {//卸载子类化
		un_subclass_game_wndproc();
	};
public:
	HWND GamehWnd = nullptr;//游戏的窗口句柄
	WNDPROC funWndProc = nullptr;
private:
	static LRESULT CALLBACK our_wndproc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);//窗口消息钩子
private:
	HWND GetGameWindow();
	CString MyGetClassName(HWND hwnd);
	void subclass_game_wndproc();//子类化窗口过程函数
	void un_subclass_game_wndproc();	//卸载子类化窗口过程
};