// ms.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "ms.h"
#include "self.h"

CSelf* pSelf;

// CmsApp

BEGIN_MESSAGE_MAP(CmsApp, CWinApp)
END_MESSAGE_MAP()


// CmsApp ����

CmsApp::CmsApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CmsApp ����

CmsApp theApp;


// CmsApp ��ʼ��

BOOL CmsApp::InitInstance()
{
	CWinApp::InitInstance();
	TRACE("��ʼ��DLL");
	pSelf = new CSelf;
	pSelf->hDll = theApp.m_hInstance;
	pSelf->InitLoadDLL((void*)1);
	return TRUE;
}

int CmsApp::ExitInstance()
{
	delete pSelf;
	TRACE("------client------->�ͷ�Self");
	return CWinApp::ExitInstance();
}
