// ms.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "ms.h"
#include "self.h"

CSelf* pSelf;

// CmsApp

BEGIN_MESSAGE_MAP(CmsApp, CWinApp)
END_MESSAGE_MAP()


// CmsApp 构造

CmsApp::CmsApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CmsApp 对象

CmsApp theApp;


// CmsApp 初始化

BOOL CmsApp::InitInstance()
{
	CWinApp::InitInstance();
	TRACE("初始化DLL");
	pSelf = new CSelf;
	pSelf->hDll = theApp.m_hInstance;
	pSelf->InitLoadDLL((void*)1);
	return TRUE;
}

int CmsApp::ExitInstance()
{
	delete pSelf;
	TRACE("------client------->释放Self");
	return CWinApp::ExitInstance();
}
