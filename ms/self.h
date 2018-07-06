#pragma once
#include "stdafx.h"
#include "HPClient.h"
#include "MainDlg.h"
#include "Message.h"

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
public:
	HMODULE hDll;//模块句柄

	bool bUiThread;
	HANDLE hUIThread;
};