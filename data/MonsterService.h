#pragma once
#include <vector>
#include <string>
#include "default.h"

using namespace std;

class CMsEnvTree   //��Χ��������������Environment
{
public:
	CMsEnvTree() {};
	~CMsEnvTree() {};

protected:
	DWORD GetEnvTreeBase();//��ȡ��Χ������������ַ
	BOOL TreeObjectType(DWORD Object, char*  szObjectName);//������� 
};

struct TMsMonster
{

	DWORD dwTree;    //����������ڵ�
	DWORD dwObject;  //�������
	int   nMonsterId;//�������+34�ǹ����ID
	float fMonsterX;//�������+48�����x����
	float fMonsterY;//�������+50�����y����
	DWORD dwOffset;    //ƫ�ƹ�������ƣ�Ѫֵ���ȼ����ڵ�ƫ�ƻ�ַ
	float fMonsterHp;   //�������������ƫ��+8�����Ѫֵ�ٷֱ�
	int   nWhoHave;    //�������������ƫ��+24�����Ƿ���ӵ����
	PCHAR szName;     //�������������ƫ��+3C���������
	int   nLevel;    //�������������ƫ��+6C�ȼ�
	int   nType;//����ǹ�����������֣�-1�̹֣���ɫ�������һ��ֵ-��֣��������ǽ�ɫ��������ֵ-�׹�
	int   nNpcType;//�������npc������
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
	void MonsterTraverse(TMsTree* Tree, VMsMonster& vm_Monster, DWORD* pCount);//�������������
	void GetMonsterInfo(TMsTree* Tree, VMsMonster& vm_Monster);//ȡ�����������Ϣ
	int  GetMonsterType(DWORD MonsterOb, DWORD RoleOb);//���ֹ��� ���� NPC
};