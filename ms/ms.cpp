// ms.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "ms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

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

	return TRUE;
}
