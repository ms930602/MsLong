#pragma once

#include "../HPSocket/Src/TcpPullServer.h"
#include "../HPSocket/Common/Src/BufferPtr.h"
#include "SocketStruct.h"
#include <vector>
#include <string>
#include <queue>

using namespace std;

class CHPServer :public CTcpPullServerListener
{
public:
	CHPServer();
	~CHPServer();
public:
	void MyStart();
	void MyStop();
	void MyDisconnect();
private:
	//��װ����ṹ��
	void MySendPackets(CONNID dwConnID, DWORD dwpacketID, int body_len, char* Socketbody);
public:
	vector<SocketBind> m_vClient;//�󶨵�ע���˺�
	queue<SocketLoginInfo> m_vLoginInfo;//Ҫ��½���ʺ���Ϣ


	INT MyDelClient(CONNID dwConnID);//�Ƴ������ӵ��ʺ���
	INT MyDelClient(SocketBind _SocketBind);//�Ƴ������ӵ��ʺ���
	INT MyAddClient(CONNID dwConnID, SocketBind _SocketBind);//��Ӱ����ӵ��ʺ���
	BOOL MyGetClientConnID(CONNID* dwConnID, SocketBind _SocketBind);//��ȡ���ʺ������ӵ�ID
	BOOL MyGetClientBind(CONNID dwConnID, SocketBind* _SocketBind);//��ȡ�����ӵ��ʺ���
	vector<SocketBind> MyGetAllClient();//��ȡ�����ʺ�
	//-->��ӵ�¼�˺�
	BOOL MyAddLoginInfo(SocketLoginInfo _SocketLoginInfo);//���һ����¼�ʺ���Ϣ����
	BOOL MyGetLoginInfo(SocketLoginInfo* pSocketLoginInfo);//��ȡһ����¼��Ϣ����
	BOOL MyLoginInfoIsEmpty();//��ȡ��¼��Ϣ�����Ƿ�Ϊ��
public:
	void SendUnInJect();

	//������dll����Ϣ
	void MySendLoginInfo(CONNID dwConnID, CBufferPtr pbuffer);
	//������dll��ִ�нű���Ϣ
	void MySendGameScript(SocketBind _SocketBind, CString Script);
	//������dll��ֹͣ�ű���Ϣ
	void MySendStopScript(SocketBind _SocketBind);
	//������dll�������ű���Ϣ
	void MySendContinueScript(SocketBind _SocketBind);
	//������dll����������Ϣ
	void SendValidateAnswer(SocketValidateResult* _Validate, INT body_len);//������֤�����֣�������
private:
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen);
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, SOCKET soClient);
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength);
	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnShutdown(ITcpServer* pSender);
private:
	static TPkgInfo* FindPkgInfo(ITcpServer* pSender, CONNID dwConnID);
	static void RemovePkgInfo(ITcpServer* pSender, CONNID dwConnID);
	//HpSocket �ص�
	void HandlePacket(CONNID dwConnID, DWORD dwPacketID, CBufferPtr pbuffer);
private:
	static const USHORT PORT;
	static const LPCTSTR ADDRESS;
	CTcpPullServer m_Server;
	CString m_strAddress;
};

extern  CCriticalSection g_State;
extern  CCriticalSection g_State_Queue;
//״����Ϣ
void ActionInfo(SocketBind _SocketBind, const char* _Message);