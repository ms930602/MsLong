
// TestLuaGUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestLuaGUIApp: 
// �йش����ʵ�֣������ TestLuaGUI.cpp
//

class CTestLuaGUIApp : public CWinApp
{
public:
	CTestLuaGUIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestLuaGUIApp theApp;