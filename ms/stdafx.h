// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 数据库类
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcontrolbars.h>

#include <WinSock.h>  //一定要包含这个，或者winsock2.h
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
	注入模块 = 1,
	卸载模块 = 2,
	切换角色 = 3
};

template <typename TF, typename... TS>
void DPrint(IN  const TF Format, IN const TS... list)
{
	try
	{
		//CString Cstr;
		//Cstr.Format(Format, list...);
		//Cstr = _T("[WG][dll]") + Cstr;
		::OutputDebugString(CString(Format));//调试输出到软件
		//WriteLog(Cstr);//写日志
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