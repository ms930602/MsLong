#include "stdafx.h"
#include "HPServer.h"

const LPCTSTR CHPServer::ADDRESS = _T("127.0.0.1");
const USHORT CHPServer::PORT = 9897;

CCriticalSection g_State;
CCriticalSection g_State_Queue;

CHPServer::CHPServer() : m_Server(this)
{
	
}

CHPServer::~CHPServer()
{
	MyStop();
}

void CHPServer::MyStart()
{
	m_strAddress = ADDRESS;
	m_strAddress.Trim();
	if (m_Server->Start(ADDRESS, PORT))
	{
		TRACE("启动服务器");
	}
	else
	{
		ASSERT(FALSE);
	}
}

void CHPServer::MyStop()
{
	if (m_Server->Stop())
	{
		TRACE("停止服务器");
	}
	else
	{
		ASSERT(FALSE);
	}
}

void CHPServer::MyDisconnect()
{
	CString strConnID;
	CONNID dwConnID = (CONNID)_ttoi(strConnID);
	m_Server->Disconnect(dwConnID);
}

EnHandleResult CHPServer::OnPrepareListen(ITcpServer * pSender, SOCKET soListen)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetListenAddress(szAddress, iAddressLen, usPort);
	return HR_OK;
}

EnHandleResult CHPServer::OnAccept(ITcpServer * pSender, CONNID dwConnID, SOCKET soClient)
{
	BOOL bPass = TRUE;
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);

	if (!m_strAddress.IsEmpty())
	{
		if (m_strAddress.CompareNoCase(szAddress) == 0)
			bPass = FALSE;
	}

	if (bPass) pSender->SetConnectionExtra(dwConnID, new TPkgInfo(true, sizeof(TPkgHeader)));

	return bPass ? HR_OK : HR_ERROR;
}

EnHandleResult CHPServer::OnSend(ITcpServer * pSender, CONNID dwConnID, const BYTE * pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CHPServer::OnReceive(ITcpServer * pSender, CONNID dwConnID, int iLength)
{
	TPkgInfo* pInfo = FindPkgInfo(pSender, dwConnID);
	ITcpPullServer* pServer = ITcpPullServer::FromS(pSender);

	if (pInfo != nullptr)
	{
		int required = pInfo->length;
		int remain = iLength;

		while (remain >= required)
		{
			remain -= required;
			CBufferPtr buffer(required);

			EnFetchResult result = pServer->Fetch(dwConnID, buffer, (int)buffer.Size());
			if (result == FR_OK)
			{
				if (pInfo->is_header)
				{
					TPkgHeader* pHeader = (TPkgHeader*)buffer.Ptr();
					TRACE("[Server] head -> seq: %d, body_len: %d\n", pHeader->seq, pHeader->body_len);

					required = pHeader->body_len;
				}
				else
				{
					TPkgBody* pBody = (TPkgBody*)(BYTE*)buffer;
					TRACE("[Server] body -> name: %s, age: %d, desc: %s\n", pBody->name, pBody->age, pBody->desc);

					required = sizeof(TPkgHeader);
				}

				pInfo->is_header = !pInfo->is_header;
				pInfo->length = required;

				//::PostOnReceive(dwConnID, buffer, (int)buffer.Size());

				if (!pSender->Send(dwConnID, buffer, (int)buffer.Size()))
					return HR_ERROR;
			}
		}
	}

	return HR_OK;
}

EnHandleResult CHPServer::OnClose(ITcpServer * pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	RemovePkgInfo(pSender, dwConnID);

	return HR_OK;
}

EnHandleResult CHPServer::OnShutdown(ITcpServer * pSender)
{
	return HR_OK;
}

TPkgInfo * CHPServer::FindPkgInfo(ITcpServer * pSender, CONNID dwConnID)
{
	PVOID pInfo = nullptr;

	pSender->GetConnectionExtra(dwConnID, &pInfo);

	return (TPkgInfo*)pInfo;
}

void CHPServer::RemovePkgInfo(ITcpServer * pSender, CONNID dwConnID)
{
	TPkgInfo* pInfo = FindPkgInfo(pSender, dwConnID);
	ASSERT(pInfo != nullptr);

	delete pInfo;
}

void CHPServer::HandlePacket(CONNID dwConnID, DWORD dwPacketID, CBufferPtr pbuffer)
{
}