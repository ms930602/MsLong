#pragma once
#include <WinBase.h>
#include "../HPSocket/Src/TcpPullClient.h"
#include "../HPSocket/Common/Src/BufferPtr.h"
#include "SocketStruct.h"

class CHPClient : public CTcpPullClientListener
{
public:
	CHPClient() : m_Client(this) { ZeroMemory(&__SocketLoginInfo, sizeof(__SocketLoginInfo)); };
	~CHPClient() {};
public:
	/************************************************************************/
	/*
	/*tcp/ip�ͻ���ͨ�ź���ʵ��
	/*
	/************************************************************************/
	void HPInit();
	void HPRelease();
	void MySendPID();
	void MyReconnection();   //���ͨ�Ŷ��ߵĺ���
	void MySendReconnection();//���������п�
private:
	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID);
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength);
	virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
private:
	SocketLoginInfo __SocketLoginInfo;
	void MySendPackets(DWORD dwConnID, int body_len, char* Socketbody);
	void HandlePacket(DWORD dwPacketID, CBufferPtr& buffer);
private:
	TPkgInfo m_pkgInfo;
	CTcpPullClient m_Client;
public:
	UINT SendRoleInfo();	//����������Ϣ�����ص��߳�
	UINT Login_Thread();    //��¼�̺߳���
};