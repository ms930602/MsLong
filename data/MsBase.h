#pragma once
#include "default.h"

#define     V_LUA_STATE           0xB58A1C       //lua指针基址
#define     V_MAP_BASE            0xB56BBC      //小地图基址
#define     V_ROLE_BASE		      0xB56580       //人物基址

extern DWORD K_LUASTATE_BASE;       //lua状态L指针
extern DWORD K_MAP_BASE;//地图坐标基址
//DWORD      K_ROLE_BASE = V_ROLE_BASE;           //人物基址