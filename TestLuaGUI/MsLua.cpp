#include "stdafx.h"
#include "MsLua.h"
#include <string>
//#include <MMSYSTEM.H>

int CMsLua::LUA_Sleep(LuaState * pState)
{
	LuaStack args(pState);
	
	int nNum = args[2].GetInteger();
	Sleep(nNum);

	return 0;
}

int CMsLua::LUA_LoadScript(LuaState * pState)
{
	LuaStack args(pState);

	std::string strScriptName = args[2].GetString();
	pState->DoFile(strScriptName.c_str());

	return 0;
}

int CMsLua::LUA_GetTickCount(LuaState * pState)
{
	DWORD nVal = GetTickCount();
	pState->PushNumber(nVal);

	return 0;
}

int CMsLua::LUA_Stop(LuaState * pState)
{
	pState->PushBoolean(true);

	return 0;
}

int CMsLua::LUA_ShowMessage(LuaState * pState)
{
	LuaStack args(pState);

	const char* str = args[1].GetString();
	TRACE("使用游戏中的lua打印输出调试信息:-> %s", str);

	return 0;
}

int CMsLua::LUA_PlaySound(LuaState * pState)
{
	LuaStack args(pState);

	const char* str = args[2].GetString();
	//::PlaySound(str, NULL, SND_ALIAS | SND_ASYNC);
	return 0;
}

int CMsLua::LUA_MessageBox(LuaState * pState)
{
	LuaStack args(pState);

	const char* str = args[2].GetString();
	AfxMessageBox(CString(str));
	return 0;
}

int CMsLua::LUA_GetDebugMessage(LuaState * pState)
{
	
	return 0;
}

int CMsLua::LUA_Script(LuaState * pState)
{
	LuaStack args(pState);

	int nScript = args[1].GetInteger();


	return 0;
}
