// ms.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "ms.h"
#include "self.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSelf* self = nullptr;

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
	//self = new CSelf;
	//self->hDll = theApp.m_hInstance;
	//self->InitLoadDLL((void*)1);
	return TRUE;
}

int CmsApp::ExitInstance()
{
	//delete self;

	return CWinApp::ExitInstance();
}
