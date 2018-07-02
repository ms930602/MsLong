#include "stdafx.h"
#include "GameUtil.h"
#include <TlHelp32.h>

CString tget_curpath(BOOL slash)
{
	/************************************************************************
	��ȡ·��
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
	int npos = CStrPath.ReverseFind(_T('\\'));//�������
	if (npos != -1)
	{
		if (slash == TRUE)
			CStrPath = CStrPath.Mid(0, npos + 1);//��ȡ��0��ʼ���ַ�������б��
		else
			CStrPath = CStrPath.Mid(0, npos);//��ȡ��0��ʼ���ַ�����Ҫб��
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

	//Ŀ�����������һƬ�ڴ�
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
	//DLL·��д��Ŀ�����
	BOOL bWrite =

		WriteProcessMemory(
			hProcess,
			lpBaseAddress,
			_CStrPath,//DLL·��
			MAX_PATH,
			NULL
		);

	if (!bWrite)
	{
		CloseHandle(hProcess);
		return FALSE;
	}

	//����Զ���߳�ִ�м���DLL�ĺ���
	HANDLE hThread =

		CreateRemoteThread(
			hProcess,
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)LoadLibraryA,
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

	//������Ŀ��������������һƬ�ڴ�
	VirtualFreeEx(
		hProcess,
		lpBaseAddress,
		4096,
		MEM_DECOMMIT
	);

	CloseHandle(hProcess);



	return TRUE;
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