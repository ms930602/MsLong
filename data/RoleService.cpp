#include "RoleService.h"
#include "MsBase.h"
/*
#define  ROLEOFFSET(data)\
data = *(PULONG)Const_Role_Base;\
data = *(PULONG)(data + 0x74);\
data = *(PULONG)(data + 0x1EC);\
data = *(PULONG)(data + 0x4);\
*/

#define  MAPOBJECT(data)\
data = *(PULONG)K_MAP_BASE;\
data = *(PULONG)(data + 0xAC);\


TMsHPMP CRoleService::GetHPMP()
{
	return TMsHPMP();
}

TMsRolePos CRoleService::GetPos()
{
	TMsRolePos tRolePos;

	try
	{
		ULONG data = 0;
		MAPOBJECT(data)
			tRolePos.fx = *(float*)(data + 0x48);
		tRolePos.fy = *(float*)(data + 0x50);
		tRolePos.bool_ret = TRUE;
	}
	catch (...)
	{
		::OutputDebugString(__FUNCTION__);
	}

	return tRolePos;
}

TMsRoleInfo CRoleService::GetRoleInfo()
{
	return TMsRoleInfo();
}

TMsRoleExp CRoleService::GetRoleExp()
{
	return TMsRoleExp();
}

ULONG CRoleService::getobject()
{
	return 0;
}

DWORD CRoleService::pass_map()
{
	return 0;
}

int CRoleService::GetMonsterTypeFlag()
{
	return 0;
}

void CRoleService::Ms_RunToTargetCall(float fx, float fy)
{
}

void CRoleService::Ms_RunToTargetExCall(int nTgtMapId, int nCurMapId, float fx, float fy)
{
}
