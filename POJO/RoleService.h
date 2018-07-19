#pragma once
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

struct TMsHPMP
{
	BOOL bool_ret;
	int nCurhp;
	int nMaxhp;
	int nCurmp;
	int nMaxmp;

	TMsHPMP()
	{
		bool_ret = FALSE;
		nCurhp = -1;
		nMaxhp = -1;
		nCurmp = -1;
		nMaxmp = -1;
	};
};


struct TMsRolePos
{
	BOOL bool_ret;
	float fx;
	float fy;

	TMsRolePos()
	{
		bool_ret = FALSE;
		fx = -1;
		fy = -1;
	};
};


struct TMsRoleInfo
{

	BOOL bool_ret;
	PCHAR szName;//角色名字
	int nLevel;//等级
	int nTeamFollow;//组队跟随状态
	int nMenpai;//门派
	int nRoleID;//人物ID
	int nPetID;//宠物ID
	int nState;//人物状态
	int nMoney;//
	int nJiaoZI;//
	int nYuanBao;//
	int nZengDian;//
	int nBindYuanBao;//
	int nHongLI;
	int nFanQuan;
	////////
	int nHuoLi;//活力 2748
	int nJingLi;//精力 2750
	int nHuoYue;//活跃 29F0
	int nShanE;//善恶 2760
	int nMenGong;//门贡 30
	int nShaGuaiShu;//杀怪数 29E8
	int nNuQi;//怒气 70
	int nBangGong;//帮贡 287c


	TMsRoleInfo()
	{
		bool_ret = FALSE;
		nLevel = -1;
		nMenpai = -1;
		szName = "";
		nRoleID = -1;
		nPetID = -1;
		nState = -1;
		nTeamFollow = -1;
		nMoney = -1;//金钱
		nJiaoZI = -1;//交子
		nYuanBao = -1;//元宝
		nZengDian = -1;//赠点
		nBindYuanBao = -1;//绑定元宝
		nHongLI = -1;//红利
		nFanQuan = -1;//返券
		nHuoLi = -1;//活力 2748
		nJingLi = -1;//精力 2750
		nHuoYue = -1;//活跃 29F0
		nShanE = -1;//善恶 2760
		nMenGong = -1;//门贡 30
		nShaGuaiShu = -1;//杀怪数 29E8
		nNuQi = -1;//怒气 70
		nBangGong = -1;//帮贡 287c
	};
};

struct TMsRoleExp
{
	BOOL bool_ret;
	int nCurExp;
	int nMaxExp;


	TMsRoleExp()
	{
		bool_ret = FALSE;
		nCurExp = -1;
		nMaxExp = -1;
	};
};

class CRoleService
{
public:
	CRoleService() {};
	~CRoleService() {};

	TMsHPMP GetHPMP();//人物的当前HPMP最大HPMP
	TMsRolePos GetPos();
	TMsRoleInfo GetRoleInfo();
	TMsRoleExp GetRoleExp();
	ULONG getobject();  //人物对象
	DWORD pass_map();//过图状态
	int GetMonsterTypeFlag();
	//	TMsMap role_curmap();

	TMsRoleInfo roleInfo;
public:
	void Ms_RunToTargetCall(float fx, float fy);//本地寻路CALL
	void Ms_RunToTargetExCall(int nTgtMapId, int nCurMapId, float fx, float fy);//跨图寻路CALL
};