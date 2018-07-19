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
	friend UINT __stdcall Dll_threadFunc(void* p);//��ʼ���̺߳���

	friend UINT __stdcall UI_ThreadFunc(LPVOID p);//UI�̺߳���
	void CreatUI();//����UI

	friend UINT __stdcall Login_AgainFunc(void* p);//��¼�� ������Ϸ����ʱ ��ʼ�����нű�ҳ������
	void CreatAgainLogin();//�����л���ɫ���߳�
public:
	HMODULE hDll;//ģ����

	bool bInitLoadThread;//�Ƿ񴴽�ѭ�����������߳�
	bool bUiThread;//�Ƿ񴴽�UI�߳�
	bool bLoginAgain;//�Ƿ�ִ�е�¼��ɫ��ʼ����
public:
	HANDLE hAgainLoginThread;
	HANDLE hUIThread;
public:
	atomic_int atomic_int_work_thread;//�̼߳���
};