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
	bInitLoadThread = true;
	HANDLE	hlg = (HANDLE)_beginthreadex(NULL, 0, &Dll_threadFunc, (void*)p, 0, NULL);
	::CloseHandle(hlg);
	TRACE("����init load dll");
	--atomic_int_work_thread;
}

UINT __stdcall UI_ThreadFunc(LPVOID p)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	pMainUI = new CMainDlg();
	pMainUI->DoModal();
	return 0;
}

void CSelf::CreatUI()//����UI�߳�
{
	bUiThread = true;
	hUIThread = (HANDLE)_beginthreadex(NULL, 0, &UI_ThreadFunc, this, 0, NULL);
}
