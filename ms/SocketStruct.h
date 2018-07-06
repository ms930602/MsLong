#pragma once
#ifndef _STRURCT_SOCKET
#define _STRURCT_SOCKET
#include "stdafx.h"

#define SOCKET_GAME_������Ϸ 1
#define SOCKET_GAME_������¼ 2
#define SOCKET_GAME_������½ 3
#define SOCKET_GAME_UNINSTALL 4

#define SOCKET_LINK 10 //���ӷ������Ϣ
#define SOCKET_USERINFO 11 //�ͻ���->����� ���ͽ�ɫ��Ϣ
#define SOCEKT_LOGIN_INFO 16 //��¼��Ϣ
#define SOCKET_LOGIN_ACTION 18 //��¼��Ϸ����
#define SOCKET_GAME_INFO	19 //��Ϸ��Ϣ
#define SOCKET_GAME_SCRIPT_INFO	20 //ִ����Ϸ�ű�
#define SOCKET_GAME_PAUSE_SCRIPT 22 //�ݶ���ǰ�ű�
#define SOCKET_GAME_LOGIN_INI_OK 23 //��Ϸ֪ͨ�����˺��������
#define SOCKET_GAME_START_SCRIPT 24 //������ǰ�ű�
#define SOCKET_GAME_VALIDATE 25 //��֤��
#define SOCKET_GAME_VALIDATE_RESULT 26 //��֤����
#define SOCKET_GAME_SECURITY 27 //�ܱ�
#define SOCKET_LINK_���� 28 //���ӷ������Ϣ
#define SOCKET_GAME_STOP_SCRIPT 29 //ֹͣ�ű�


#define SOCKET_�ͻ��˽�������_������ 49
#define SOCKET_�ͻ��˷�������_������Ϣ 50
//----------------------------------------------------------------------
//����ͨѶ�ṹ��
//----------------------------------------------------------------------
#pragma pack(push)//�����ֽڶ��뷽ʽΪ1�ֽ�
#pragma pack(1)

struct TPkgHeader
{
	DWORD seq;
	int body_len;
};

struct TPkgBody
{
	char name[30];
	short age;
	char desc[1];
};

struct TPkgInfo
{
	bool is_header;
	int length;
	DWORD  seq;				//����ID

	TPkgInfo(bool header = true, int nID = 0, int len = sizeof(TPkgHeader)) : is_header(header), seq(nID), length(len) {}
	void Reset() { is_header = true, seq = 0, length = sizeof(TPkgHeader); }
	~TPkgInfo() {}
};

/*
*���ӳɹ��󣬷��������û���������
*/
struct SocketLoginInfo
{
	char GameName[30];//�˺�
	char GameNameHouZhui[20];//�˺ź�׺
	char GamePWD[50];//����
	char GameServerName[15];//С��(������)����
	char RoleName[20];//��ɫ��
	char MiBao[98];//��ɫ��
	int IsLoginIndex;//��¼����
	int isCreateRole;//�޽�ɫʱ�Ƿ񴴽�
	int IsErJiMiBao;//�Ƿ��ж����ܱ�
	char _GameScript[100];//Ĭ�Ͻű���
};

/*
*��Ϸ��ɫ��Ϣ,(������Ϸ�ɹ�����)
*/
struct SocketGameRoleInfo
{
	char RoleName[30];//��ɫ��
	unsigned int RoleLevel;//��ɫ�ȼ�
	unsigned int RoleMenPai;//��ɫ����
	unsigned int RoleTi;//��
	unsigned int RoleFa;//��
	char GameMap[20];//���ڵ�ͼ
	int PointX;//X����
	int PointY;//Y����
	unsigned int NoBindGold;//��Ǯ
	unsigned int BindGold;//����
	unsigned int YuanBap;//Ԫ��
	unsigned int RoleStatus;//��ɫ״̬
};

#pragma pack(pop)



#endif