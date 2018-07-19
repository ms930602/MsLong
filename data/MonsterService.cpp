#include "MonsterService.h"
#include "MsBase.h"

DWORD K_LUASTATE_BASE = V_LUA_STATE;       //lua状态L指针
DWORD K_MAP_BASE = V_MAP_BASE;//地图坐标基址

DWORD CMsEnvTree::GetEnvTreeBase()
{
	return 0;
}

BOOL CMsEnvTree::TreeObjectType(DWORD Object, char * szObjectName)
{
	return 0;
}

VMsMonster CMsMonster::GetMonsterData()
{
	return VMsMonster();
}

int CMsMonster::OpenNpcDlg(int nID)
{
	return 0;
}

void CMsMonster::MonsterTraverse(TMsTree * Tree, VMsMonster & vm_Monster, DWORD * pCount)
{
}

void CMsMonster::GetMonsterInfo(TMsTree * Tree, VMsMonster & vm_Monster)
{
}

int CMsMonster::GetMonsterType(DWORD MonsterOb, DWORD RoleOb)
{
	return 0;
}
