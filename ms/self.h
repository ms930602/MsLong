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
	friend UINT __stdcall Dll_threadFunc(void* p);//��ʼ���̺߳���

public:
	HMODULE hDll;//ģ����
};