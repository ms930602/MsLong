#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;

BOOL InJectDll(CString ProcessId, CString DllName);

vector<DWORD> GetGameProcessId(CString ProcessNmae);