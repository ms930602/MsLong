#include "stdafx.h"
#include "GameUtil.h"
#include <TlHelp32.h>

CString tget_curpath(BOOL slash)
{
	/************************************************************************
	获取路径
	************************************************************************/
	TCHAR lpBuffer[MAX_PATH] = { 0 };
	if (GetModuleFileName(
		NULL,
		lpBuffer,
		MAX_PATH
	) == NULL)
	{
		return CString();
	}

	CString CStrPath(lpBuffer);
	int npos = CStrPath.ReverseFind(_T('\\'));//逆向查找
	if (npos != -1)
	{
		if (slash == TRUE)
			CStrPath = CStrPath.Mid(0, npos + 1);//截取从0开始的字符串保留斜杠
		else
			CStrPath = CStrPath.Mid(0, npos);//截取从0开始的字符串不要斜杠
											 //dbgPrint(_T("%s::\t\t %s\n"), CString(__FUNCTION__), CStrPath);
	}

	return CStrPath;
}

unsigned int __stdcall InJect_thread(void * p)
{
	CString* pCStrPath = (CString*)p;
	CString CStrPath = *pCStrPath;
	delete pCStrPath;
	if (!CStrPath.IsEmpty())
	{
		//注入游戏
		InJectDll(CStrPath, _T("ms.dll"));
	}
	return 0;
}

BOOL InJectDll(CString PID, CString DllName) {

	DWORD ProcessId = _tcstoul(PID, NULL, 10);
	if (ProcessId == -1)
	{
		return FALSE;
	}
	
	//EnablePrivilege(TRUE);

	HANDLE hProcess =
		OpenProcess(
			PROCESS_ALL_ACCESS,
			FALSE,
			ProcessId
		);

	if (!hProcess)
	{
		return FALSE;
	}
	//目标程序中申请一片内存
	LPVOID lpBaseAddress =
		VirtualAllocEx(
			hProcess,
			NULL,
			4096,
			MEM_COMMIT,
			PAGE_EXECUTE_READWRITE
		);

	if (!lpBaseAddress)
	{
		CloseHandle(hProcess);
		return FALSE;
	}

	CString _CStrPath = tget_curpath(TRUE);
	if (_CStrPath.IsEmpty())
		return FALSE;

	_CStrPath += DllName;
	//DLL路径写到目标进程
	BOOL bWrite =

		WriteProcessMemory(
			hProcess,
			lpBaseAddress,
			_CStrPath,//DLL路径
			MAX_PATH,
			NULL
		);

	if (!bWrite)
	{
		CloseHandle(hProcess);
		return FALSE;
	}

	//开启远程线程执行加载DLL的函数
	HANDLE hThread =

		CreateRemoteThread(
			hProcess,
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)LoadLibrary,
			lpBaseAddress,
			0,
			NULL
		);

	if (!hThread)
	{
		CloseHandle(hProcess);
		return FALSE;
	}


	WaitForSingleObject(
		hThread,
		INFINITE
	);

	//清理在目标程序中申请的那一片内存
	VirtualFreeEx(
		hProcess,
		lpBaseAddress,
		4096,
		MEM_DECOMMIT
	);

	CloseHandle(hProcess);

	TRACE("注入完毕");

	//EnablePrivilege(FALSE);
	return TRUE;
}

int EnablePrivilege(bool isStart)
{
	return 0;
}

vector<DWORD> GetGameProcessId(CString ProcessNmae) {
	vector<DWORD> ProcessId;

	HANDLE hSnapshot =
		CreateToolhelp32Snapshot(
			TH32CS_SNAPPROCESS,
			0
		);

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);

	BOOL bOk =
		Process32First(
			hSnapshot,
			&pe
		);

	for (; bOk; bOk = Process32Next(hSnapshot, &pe))
	{
		if (ProcessNmae == pe.szExeFile)
		{
			ProcessId.push_back(pe.th32ProcessID);
		}
	}

	::CloseHandle(hSnapshot);

	return ProcessId;
}


CString GetRoleState(INT nState)
{
	CString CstrText;
	if (nState == 0)
	{
		CstrText = "不动";
	}
	else if (nState == 2)
	{
		CstrText = "移动";
	}
	else if (nState == 5)
	{
		CstrText = "回城";
	}
	else if (nState == 6)
	{
		CstrText = "打坐或吃药";
	}
	else if (nState == 7)
	{
		CstrText = "杀怪";
	}
	else if (nState == 8)
	{
		CstrText = "采集";
	}
	else if (nState == 9)
	{
		CstrText = "死亡";
	}
	else if (nState == 10)
	{
		CstrText = " 摆摊";
	}

	return CstrText;
}

CString GetRoleMenPai(INT nMenpai)
{
	CString Cstr;
	if (nMenpai == 0)
		Cstr = "少林";
	else if (nMenpai == 1)
		Cstr = "明教";
	else if (nMenpai == 2)
		Cstr = "丐帮";
	else if (nMenpai == 3)
		Cstr = "武当";
	else if (nMenpai == 4)
		Cstr = "峨嵋";
	else if (nMenpai == 5)
		Cstr = "星宿";
	else if (nMenpai == 6)
		Cstr = "天龙";
	else if (nMenpai == 7)
		Cstr = "天山";
	else if (nMenpai == 8)
		Cstr = "逍遥";
	else if (nMenpai == 10)
		Cstr = "慕容";
	else if (nMenpai == 11)
		Cstr = "唐门";
	else
		Cstr = "无门派";

	return Cstr;
}