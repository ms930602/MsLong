#pragma once
#include "resource.h"
#include "stdafx.h"
#include "HPClient.h"
#include "MainDlg.h"
#include "Message.h"
#include <atomic>

class CSelf
{
public:
	CSelf();
	~CSelf();
public:
	void InitLoadDLL(void* p);
	friend UINT __stdcall Dll_threadFunc(void* p);//初始化线程函数

	friend UINT __stdcall UI_ThreadFunc(LPVOID p);//UI线程函数
	void CreatUI();//创建UI

	friend UINT __stdcall Login_AgainFunc(void* p);//登录后 进入游戏界面时 初始化所有脚本页面数据
	void CreatAgainLogin();//创建切换角色的线程
public:
	HMODULE hDll;//模块句柄

	bool bInitLoadThread;//是否创建循环发包主控线程
	bool bUiThread;//是否创建UI线程
	bool bLoginAgain;//是否执行登录角色初始化绑定
public:
	HANDLE hAgainLoginThread;
	HANDLE hUIThread;
public:
	atomic_int atomic_int_work_thread;//线程计数
};