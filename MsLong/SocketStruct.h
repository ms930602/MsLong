#ifndef _STRURCT_SOCKET
#define _STRURCT_SOCKET

#define SOCKET_GAME_������Ϸ 1
#define SOCKET_GAME_������¼ 2
#define SOCKET_GAME_������½ 3

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

#define SOCKET_���ط��Ϳͻ���_������ SOCKET_�ͻ��˽�������_������

#define SOCKET_���ؽ��ܿͻ���_������Ϣ SOCKET_�ͻ��˷�������_������Ϣ

#define SOCKET_���ط��ʹ����_������Ϣ 51

#define SOCKET_���ؽ��ܴ����_������ 52

#define SOCKET_����˷���_������ SOCKET_���ؽ��ܴ����_������

#define SOCKET_����˽���_������Ϣ SOCKET_���ط��ʹ����_������Ϣ

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

	TPkgInfo(bool header = true, int len = sizeof(TPkgHeader)) : is_header(header), length(len) {}
	void Reset() { is_header = true, length = sizeof(TPkgHeader); }
	~TPkgInfo() {}
};


#pragma pack(pop)



#endif