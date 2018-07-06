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
	if (m_Server.Start(ADDRESS, PORT))
	{
		TRACE("����������");
	}
	else
	{
		ASSERT(FALSE);
	}
}

void CHPServer::MyStop()
{
	if (m_Server.Stop())
	{
		TRACE("ֹͣ������");
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
	m_Server.Disconnect(dwConnID);
}

void CHPServer::MySendPackets(CONNID dwConnID, DWORD dwpacketID, int body_len, char * Socketbody)
{
	TPkgHeader header;
	header.seq = dwpacketID;
	header.body_len = body_len;

	WSABUF bufs[2];
	bufs[0].len = sizeof(TPkgHeader);
	bufs[0].buf = (char*)&header;
	bufs[1].len = body_len;
	bufs[1].buf = Socketbody;
	m_Server.SendPackets(dwConnID, bufs, 2);
}

INT CHPServer::MyDelClient(CONNID dwConnID)
{
	CriticalSectionLock Lock(&g_State);
	vector<SocketBind>::iterator it;
	for (it = m_vClient.begin(); it != m_vClient.end();)
	{
		if (it->dwConnID == dwConnID)
		{
			it = m_vClient.erase(it);//�Ƴ���Ч�İ���
		}
		else
		{
			++it;
		}
	}

	return TRUE;
}

INT CHPServer::MyDelClient(SocketBind _SocketBind)
{
	CriticalSectionLock Lock(&g_State);
	if (!((CString)_SocketBind.Account).IsEmpty())//�ʺűȽ�
	{
		vector<SocketBind>::iterator it;
		for (it = m_vClient.begin(); it != m_vClient.end();)
		{
			if ((CString)it->Account == (CString)_SocketBind.Account)
				it = m_vClient.erase(it);//�Ƴ���Ч�İ�
			else
				++it;
		}
	}
	else if (_SocketBind.dwGameID > 0)//���̱Ƚ�
	{
		vector<SocketBind>::iterator it;
		for (it = m_vClient.begin(); it != m_vClient.end();)
		{
			if (it->dwGameID == _SocketBind.dwGameID)
				it = m_vClient.erase(it);//�Ƴ���Ч�İ�
			else
				++it;
		}
	}

	return TRUE;
}

INT CHPServer::MyAddClient(CONNID dwConnID, SocketBind _SocketBind)
{
	CriticalSectionLock Lock(&g_State);
	if (!((CString)_SocketBind.Account).IsEmpty())//�ʺűȽ�
	{
		vector<SocketBind>::iterator it;
		for (it = m_vClient.begin(); it != m_vClient.end();)
		{
			if ((CString)it->Account == (CString)_SocketBind.Account)
				it = m_vClient.erase(it);//�Ƴ���Ч�İ�
			else
				++it;
		}
	}
	else if (_SocketBind.dwGameID > 0)//���̱Ƚ�
	{
		vector<SocketBind>::iterator it;
		for (it = m_vClient.begin(); it != m_vClient.end();)
		{
			if (it->dwGameID == _SocketBind.dwGameID)
				it = m_vClient.erase(it);//�Ƴ���Ч�İ�
			else
				++it;
		}
	}

	m_vClient.push_back(_SocketBind);

	return TRUE;
}

BOOL CHPServer::MyGetClientConnID(CONNID * dwConnID, SocketBind _SocketBind)
{
	CriticalSectionLock Lock(&g_State);
	if (!((CString)_SocketBind.Account).IsEmpty())//�ʺűȽ�
	{
		for (auto Bind : m_vClient)
		{
			if ((CString)Bind.Account == (CString)_SocketBind.Account)
			{
				*dwConnID = Bind.dwConnID;
				return TRUE;
			}
		}
	}
	else if (_SocketBind.dwGameID > 0)//���̱Ƚ�
	{
		for (auto Bind : m_vClient)
		{
			if (Bind.dwGameID == _SocketBind.dwGameID)
			{
				*dwConnID = Bind.dwConnID;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CHPServer::MyGetClientBind(CONNID dwConnID, SocketBind * _SocketBind)
{
	CriticalSectionLock Lock(&g_State);
	for (auto Bind : m_vClient)
	{
		if (Bind.dwConnID == dwConnID)
		{
			*_SocketBind = Bind;
			return TRUE;
		}
	}

	return FALSE;
}

vector<SocketBind> CHPServer::MyGetAllClient()
{
	CriticalSectionLock Lock(&g_State);
	vector<SocketBind> Client = m_vClient;

	return Client;
}

BOOL CHPServer::MyAddLoginInfo(SocketLoginInfo _SocketLoginInfo)
{
	CriticalSectionLock Lock(&g_State_Queue);
	m_vLoginInfo.push(_SocketLoginInfo);

	return TRUE;
}

BOOL CHPServer::MyGetLoginInfo(SocketLoginInfo * pSocketLoginInfo)
{
	CriticalSectionLock Lock(&g_State_Queue);

	if (m_vLoginInfo.empty())return FALSE;//Ԫ��Ϊ�գ��˳�
										  //��ȡһ����Ϸ�ʺ���Ϣ�����ڵ�¼ʹ��
	*pSocketLoginInfo = m_vLoginInfo.front(); //���ʵ�һ��Ԫ��
	m_vLoginInfo.pop();//��һ��Ԫ�س�ջ

	return TRUE;
}

BOOL CHPServer::MyLoginInfoIsEmpty()
{
	CriticalSectionLock Lock(&g_State_Queue);
	if (m_vLoginInfo.empty())
	{
		return TRUE;
	}//Ԫ��Ϊ�գ��˳�

	return FALSE;
}

void CHPServer::SendUnInJect()
{
	TRACE("����ж����Ϣ");
	m_Server.Send(SOCKET_GAME_UNINSTALL, NULL, 0);
}

void CHPServer::MySendLoginInfo(CONNID dwConnID, CBufferPtr pbuffer)
{
	SocketBind _SocketBind = { 0 };
	_SocketBind.dwConnID = dwConnID;
	_SocketBind.dwGameID = *(DWORD*)(BYTE*)pbuffer;

	SocketLoginInfo __SocketLoginInfo = { 0 };
	if (!MyGetLoginInfo(&__SocketLoginInfo)) {//���˺�Ϊ��ʱ
		MyAddClient(dwConnID, _SocketBind);
		ActionInfo(_SocketBind, "��ע��");
		return;//��ȡ��¼�ʺ���Ϣ
	}
	strcpy(_SocketBind.Account, __SocketLoginInfo.GameName);
	MyAddClient(dwConnID, _SocketBind);
	ActionInfo(_SocketBind, "��ע��");

	//�����ʺ���Ϣ��dll
	int body_len = sizeof(__SocketLoginInfo);
	MySendPackets(dwConnID, SOCEKT_LOGIN_INFO, body_len, (char*)&__SocketLoginInfo);
}

void CHPServer::MySendGameScript(SocketBind _SocketBind, CString Script)
{
}

void CHPServer::MySendStopScript(SocketBind _SocketBind)
{
}

void CHPServer::MySendContinueScript(SocketBind _SocketBind)
{
}

void CHPServer::SendValidateAnswer(SocketValidateResult * _Validate, INT body_len)
{
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
					pInfo->seq = pHeader->seq;
					required = pHeader->body_len;
					if (required == 0)		//���յ�ֻ�е����İ�ID�������͵İ�
					{
						required = sizeof(TPkgHeader);
						pInfo->is_header = false;
						HandlePacket(dwConnID, pInfo->seq, (CBufferPtr)NULL);
					}
				}
				else
				{
					HandlePacket(dwConnID, pInfo->seq, buffer);
					required = sizeof(TPkgHeader);
					pInfo->seq = NULL;
				}

				pInfo->is_header = !pInfo->is_header;
				pInfo->length = required;
			}
		}
	}

	return HR_OK;
}

EnHandleResult CHPServer::OnClose(ITcpServer * pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
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
	switch (dwPacketID)
	{
		//////////////////////////////////////////////////////////////////////////
	case SOCKET_LINK:
	{
		MySendLoginInfo(dwConnID, pbuffer);
		TRACE(__FUNCTION__"[Server]��������\n");
	}
	break;
	//////////////////////////////////////////////////////////////////////////
	case SOCKET_LINK_����:
	{
		TRACE("��������Ϣ");
		/*
		SocketBind _SocketBind = { 0 };
		_SocketBind = *(SocketBind*)(BYTE*)pbuffer.Ptr();
		_SocketBind.dwConnID = dwConnID;
		MyAddClient(dwConnID, _SocketBind);
		״����Ϣ(_SocketBind, "��ע��");
		TRACE(__FUNCTION__"[Server]�����п�\n");
		*/
	}
	break;
	//////////////////////////////////////////////////////////////////////////
	case SOCKET_GAME_INFO:
	{
		TRACE("��Ϸ�ʺŵ�״����Ϣ");
		/*��Ϸ�ʺŵ�״����Ϣ
		SocketBind _SocketBind = { 0 };
		if (MyGetClientBind(dwConnID, &_SocketBind))
		{
			״����Ϣ(_SocketBind, (char*)(BYTE*)pbuffer.Ptr());
		}
		else
		{
			TRACE(__FUNCTION__"��Ϸ�ʺŵ�״����Ϣ-->>������û�а��κ���Ϣ");
		}*/
	}
	break;
	//////////////////////////////////////////////////////////////////////////
	case SOCKET_USERINFO:
	{
		//��Ϸ�Ľ�ɫ������Ϣ
		SocketBind _SocketBind = { 0 };
		if (MyGetClientBind(dwConnID, &_SocketBind))
		{
			SocketBind* pBind = new SocketBind;
			*pBind = _SocketBind;
			SocketGameRoleInfo* _socketgameInfo = new SocketGameRoleInfo;
			*_socketgameInfo = *(SocketGameRoleInfo*)(BYTE*)pbuffer.Ptr();
			::PostMessage(g_TabAHwnd, WM_USER_����������Ϣ, (WPARAM)pBind, (LPARAM)_socketgameInfo);
		}
		else
		{
			TRACE(__FUNCTION__"��Ϸ�Ľ�ɫ������Ϣ-->>������û�а��κ��ʺ�");
		}
	}
	break;
	case  SOCKET_���ؽ��ܿͻ���_������Ϣ:
	{
		break;
	}
	default:
		break;
	}
}
//״����Ϣ
void ActionInfo(SocketBind _SocketBind, const char * _Message)
{
	SocketBind* pBind = new SocketBind;
	*pBind = _SocketBind;
	SocketGameInfo* _socketgameInfo = new SocketGameInfo;
	strcpy(_socketgameInfo->_Message, _Message);
	::PostMessage(g_TabAHwnd, WM_USER_״��, (WPARAM)pBind, (LPARAM)_socketgameInfo);
}
