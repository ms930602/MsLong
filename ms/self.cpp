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


	TRACE("����UI");
	pMainUI->DoModal();

	TRACE("��ʼ����Ϣ����");
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

	if (nType == ע��ģ��)
	{
		m_HPClient.HPInit();
		Initial();
		dbgPrint("ע��ģ��");
		return 0;
	}

	dbgPrint("ж��ģ��");
	return 0;
}