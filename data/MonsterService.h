#pragma once
#include <vector>
#include <string>
#include "default.h"

using namespace std;

class CMsEnvTree   //周围环境二叉树父类Environment
{
public:
	CMsEnvTree() {};
	~CMsEnvTree() {};

protected:
	DWORD GetEnvTreeBase();//获取周围环境二叉树基址
	BOOL TreeObjectType(DWORD Object, char*  szObjectName);//怪物对象 
};

struct TMsMonster
{

	DWORD dwTree;    //怪物二叉树节点
	DWORD dwObject;  //怪物对象
	int   nMonsterId;//怪物对象+34是怪物的ID
	float fMonsterX;//怪物对象+48怪物的x坐标
	float fMonsterY;//怪物对象+50怪物的y坐标
	DWORD dwOffset;    //偏移怪物的名称，血值，等级所在的偏移基址
	float fMonsterHp;   //怪物的属性属性偏移+8怪物的血值百分比
	int   nWhoHave;    //怪物的属性属性偏移+24怪物是否有拥有者
	PCHAR szName;     //怪物的属性属性偏移+3C怪物的名字
	int   nLevel;    //怪物的属性属性偏移+6C等级
	int   nType;//这个是怪物归属，区分，-1绿怪，角色对象里的一个值-红怪，不是我们角色对象的里的值-白怪
	int   nNpcType;//这个区分npc的类型
	TMsMonster()
	{
		dwTree = 0;
		nMonsterId = -1;
		nLevel = 0;
		dwObject = 0;
		fMonsterX = 0.0f;
		fMonsterY = 0.0f;
		fMonsterHp = 0.0f;
		szName = "";
		nWhoHave = 0;
		dwOffset = 0;
		nType = 0;
		nNpcType = -1;
	};
};

typedef 	vector<TMsMonster> VMsMonster;

class CMsMonster :
	public CMsEnvTree
{
public:
	CMsMonster() {};
	~CMsMonster() {};
public:
	VMsMonster GetMonsterData();
	int OpenNpcDlg(int nID);
private:
	void MonsterTraverse(TMsTree* Tree, VMsMonster& vm_Monster, DWORD* pCount);//先序遍历二叉树
	void GetMonsterInfo(TMsTree* Tree, VMsMonster& vm_Monster);//取怪物的属性信息
	int  GetMonsterType(DWORD MonsterOb, DWORD RoleOb);//区分怪物 宠物 NPC
};