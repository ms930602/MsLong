#pragma once
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
public:
	HMODULE hDll;//模块句柄

	bool bInitLoadThread;//是否创建循环发包主控线程
	bool bUiThread;//是否创建UI线程
	HANDLE hUIThread;
public:
	atomic_int atomic_int_work_thread;//线程计数
};