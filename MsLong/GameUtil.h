#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;

unsigned int __stdcall InJect_thread(void *p);

BOOL InJectDll(CString ProcessId, CString DllName);

vector<DWORD> GetGameProcessId(CString ProcessNmae);

CString GetRoleState(INT nState);

CString GetRoleMenPai(INT nMenpai);