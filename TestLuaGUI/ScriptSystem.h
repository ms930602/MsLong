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
	LuaStateOwner* pState;//初始化lua的基本库，才能调用lua函数
};