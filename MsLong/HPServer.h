#pragma once

#include "../HPSocket/Src/HPSocket.h"
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
	virtual EnHandleResult OnPrepareListen(ITcpServer* pSender, SOCKET soListen);
	virtual EnHandleResult OnAccept(ITcpServer* pSender, CONNID dwConnID, SOCKET soClient);
	virtual EnHandleResult OnSend(ITcpServer* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(ITcpServer* pSender, CONNID dwConnID, int iLength);
	virtual EnHandleResult OnClose(ITcpServer* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnShutdown(ITcpServer* pSender);
private:
	TPkgInfo* FindPkgInfo(ITcpServer* pSender, CONNID dwConnID);
	void RemovePkgInfo(ITcpServer* pSender, CONNID dwConnID);
	//HpSocket 回调
	void HandlePacket(CONNID dwConnID, DWORD dwPacketID, CBufferPtr pbuffer);
private:
	static const USHORT PORT;
	static const LPCTSTR ADDRESS;
	CTcpPullServerPtr m_Server;
	CString m_strAddress;
};

extern  CCriticalSection g_State;
extern  CCriticalSection g_State_Queue;
//状况信息
//void ActionInfo(SocketBind _SocketBind, const char* _Message);