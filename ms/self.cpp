#include "stdafx.h"
#include "self.h"
#include "MainDlg.h"
#include "Message.h"

CMainDlg * pMainUI;
CMessage * pMsg;

void Initial()
{
	pMainUI = new CMainDlg;
	pMsg = new CMessage;


	TRACE("创建UI");
	pMainUI->DoModal();

	TRACE("初始化消息函数");
	pMsg->Init();


}

CSelf::CSelf()
{
	pMainUI = nullptr;
	pMsg = nullptr;
}

CSelf::~CSelf()
{
	delete pMainUI;
	delete pMsg;
}

UINT CSelf::InitLoadDLL(void* p)
{
	int nType = (int)p;

	if (nType == 注入模块)
	{
		m_HPClient.HPInit();
		Initial();
		dbgPrint("注入模块");
		return 0;
	}

	dbgPrint("卸载模块");
	return 0;
}