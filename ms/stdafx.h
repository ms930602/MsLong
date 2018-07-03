// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcontrolbars.h>

#include <WinSock.h>  //һ��Ҫ�������������winsock2.h
#include <vector>
#include <string>
#include <thread>
using namespace std;

#pragma comment(lib,"wsock32.lib")

#ifdef _DEBUG
#pragma comment(lib,"..\\HPSocket\\bin\\HPSocket_UD.lib") 
#else
#pragma comment(lib,"..\\HPSocket\\bin\\HPSocket_U.lib") 
#endif // !_DEBUG

enum ELogin
{
	ע��ģ�� = 1,
	ж��ģ�� = 2,
	�л���ɫ = 3
};

template <typename TF, typename... TS>
void DPrint(IN  const TF Format, IN const TS... list)
{
	try
	{
		//CString Cstr;
		//Cstr.Format(Format, list...);
		//Cstr = _T("[WG][dll]") + Cstr;
		::OutputDebugString(CString(Format));//������������
		//WriteLog(Cstr);//д��־
}
	catch (...)
	{
		::OutputDebugStringA(__FUNCTION__);
	}
}

#define def__debug__dll 1
#undef  dbgPrint
#if     def__debug__dll
#define dbgPrint(_x_,...) DPrint(_x_,__VA_ARGS__)
#else
#define dbgPrint( _x_ ,...)
#endif