#pragma once
#include "MsLua.h"

class CScriptSystem
{
public:
	CScriptSystem() {};
	~CScriptSystem()
	{
		delete pState;
		delete m_pMsLua;
	};
public:
	void Initial();
	void LUA_DoFile(const char* fileName)
	{
		(*pState)->DoFile(fileName);
	}
private:
	CMsLua* m_pMsLua;
	LuaStateOwner* pState;//��ʼ��lua�Ļ����⣬���ܵ���lua����
};