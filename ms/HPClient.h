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
	/*tcp/ip客户端通信函数实现
	/*
	/************************************************************************/
	void HPInit();
	void HPRelease();
	void MySendPID();
	void MyReconnection();   //检测通信断线的函数
	void MySendReconnection();//发送重连中控
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
	UINT SendRoleInfo();	//传递人物信息给主控的线程
	UINT Login_Thread();    //登录线程函数
};