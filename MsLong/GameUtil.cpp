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