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
	PCHAR szName;//��ɫ����
	int nLevel;//�ȼ�
	int nTeamFollow;//��Ӹ���״̬
	int nMenpai;//����
	int nRoleID;//����ID
	int nPetID;//����ID
	int nState;//����״̬
	int nMoney;//
	int nJiaoZI;//
	int nYuanBao;//
	int nZengDian;//
	int nBindYuanBao;//
	int nHongLI;
	int nFanQuan;
	////////
	int nHuoLi;//���� 2748
	int nJingLi;//���� 2750
	int nHuoYue;//��Ծ 29F0
	int nShanE;//�ƶ� 2760
	int nMenGong;//�Ź� 30
	int nShaGuaiShu;//ɱ���� 29E8
	int nNuQi;//ŭ�� 70
	int nBangGong;//�ﹱ 287c


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
		nMoney = -1;//��Ǯ
		nJiaoZI = -1;//����
		nYuanBao = -1;//Ԫ��
		nZengDian = -1;//����
		nBindYuanBao = -1;//��Ԫ��
		nHongLI = -1;//����
		nFanQuan = -1;//��ȯ
		nHuoLi = -1;//���� 2748
		nJingLi = -1;//���� 2750
		nHuoYue = -1;//��Ծ 29F0
		nShanE = -1;//�ƶ� 2760
		nMenGong = -1;//�Ź� 30
		nShaGuaiShu = -1;//ɱ���� 29E8
		nNuQi = -1;//ŭ�� 70
		nBangGong = -1;//�ﹱ 287c
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

	TMsHPMP GetHPMP();//����ĵ�ǰHPMP���HPMP
	TMsRolePos GetPos();
	TMsRoleInfo GetRoleInfo();
	TMsRoleExp GetRoleExp();
	ULONG getobject();  //�������
	DWORD pass_map();//��ͼ״̬
	int GetMonsterTypeFlag();
	//	TMsMap role_curmap();

	TMsRoleInfo roleInfo;
public:
	void Ms_RunToTargetCall(float fx, float fy);//����Ѱ·CALL
	void Ms_RunToTargetExCall(int nTgtMapId, int nCurMapId, float fx, float fy);//��ͼѰ·CALL
};