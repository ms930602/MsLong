#pragma once
#include "stdafx.h"
#include "../LuaPlus/LuaPlus.h"
using namespace LuaPlus;

class CMsLua
{
public:
	CMsLua() {};
	~CMsLua() {};

public:
	int LUA_Sleep(LuaState* pState);

	int LUA_LoadScript(LuaState* pState);

	int LUA_GetTickCount(LuaState* pState);

	int LUA_Stop(LuaState* pState);

	int LUA_ShowMessage(LuaState* pState);

	//
	//��������
	int LUA_PlaySound(LuaState* pState);

	int LUA_MessageBox(LuaState* pState);

	int LUA_GetDebugMessage(LuaState* pState);//��ȡ������Ϣ

	int LUA_Script(LuaState* pState);
};