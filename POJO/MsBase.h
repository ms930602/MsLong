#pragma once
#include <Windows.h>


#define     V_LUA_STATE           0xB58A1C       //lua指针基址
#define     V_ROLE_BASE		      0xB56BBC       //人物基址

DWORD      K_LUASTATE_BASE = V_LUA_STATE;       //lua状态L指针
DWORD      K_ROLE_BASE = V_ROLE_BASE;           //人物基址