#include "stdafx.h"
#include "self.h"


extern CMainDlg* pMainUI;
extern CSelf* pSelf;
extern CMessage* pMsg;

CSelf::CSelf()
{
	pMainUI = nullptr;
	pMsg = nullptr;
}

CSelf::~CSelf()
{
}

void CSelf::InitLoadDLL(void* p)
{
	HANDLE	hlg = (HANDLE)_beginthreadex(NULL, 0, &Dll_threadFunc, (void*)p, 0, NULL);
	::CloseHandle(hlg);
}