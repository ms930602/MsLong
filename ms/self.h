#pragma once
#include "stdafx.h"
#include "HPClient.h"

class CSelf
{
public:
	CSelf();
	~CSelf();
public:
	UINT __stdcall InitLoadDLL(void* p);
private:
	CHPClient m_HPClient;

public:
	HMODULE hDll;//Ä£¿é¾ä±ú
};