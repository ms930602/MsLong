#include "stdafx.h"
#include "HPClient.h"
#include "self.h"
#include "MainDlg.h"
#include "Message.h"
#include "ms.h"

#define DEFAULT_CONTENT	_T("text to be sent")
#define DEFAULT_ADDRESS	_T("127.0.0.1")
#define DEFAULT_PORT	_T("9897")

CHPClient* pClient = nullptr;
extern CSelf* pSelf;

CMainDlg * pMainUI;
CMessage * pMsg;

void CHPClient::HPInit()
{
	CString strAddress = DEFAULT_ADDRESS;
	CString strPort = DEFAULT_PORT;
	USHORT usPort = (USHORT)_ttoi(strPort);
	m_pkgInfo.Reset();

	if (m_Client.Start(strAddress, usPort, 0))
	{
		TRACE("���ӳɹ���IP:%s �˿�:%d -->��������ID", strAddress, usPort);
		MySendPID();
	}
	else {
		TRACE("����ʧ��!");
	}
}

void CHPClient::HPRelease()
{
	m_Client.Stop();
}

void CHPClient::MySendPID()
{
	DWORD dwGameID = GetCurrentProcessId();
	MySendPackets(SOCKET_LINK, sizeof(dwGameID), (char*)&dwGameID);
}

EnHandleResult CHPClient::OnConnect(ITcpClient * pSender, CONNID dwConnID)
{
	TCHAR szAddress[50];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	pSender->GetLocalAddress(szAddress, iAddressLen, usPort);

	return HR_OK;
}

EnHandleResult CHPClient::OnSend(ITcpClient * pSender, CONNID dwConnID, const BYTE * pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CHPClient::OnReceive(ITcpClient * pSender, CONNID dwConnID, int iLength)
{
	ITcpPullClient* pClient = ITcpPullClient::FromS(pSender);
	int required = m_pkgInfo.length;
	int remain = iLength;

	while (remain >= required)
	{
		remain -= required;
		CBufferPtr buffer(required);

		EnFetchResult result = pClient->Fetch(buffer, (int)buffer.Size());
		if (result == FR_OK)
		{
			if (m_pkgInfo.is_header)
			{
				TPkgHeader* pHeader = (TPkgHeader*)buffer.Ptr();
				TRACE("[Client] head -> seq: %d, body_len: %d\n", pHeader->seq, pHeader->body_len);

				required = pHeader->body_len;
			}
			else
			{
				TPkgBody* pBody = (TPkgBody*)buffer.Ptr();
				TRACE("[Client] body -> name: %s, age: %d, desc: %s\n", pBody->name, pBody->age, pBody->desc);

				required = sizeof(TPkgHeader);
			}

			m_pkgInfo.is_header = !m_pkgInfo.is_header;
			m_pkgInfo.length = required;
		}
	}

	return HR_OK;
}

EnHandleResult CHPClient::OnClose(ITcpClient * pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	return HR_OK;
}

void CHPClient::MySendPackets(DWORD dwConnID, int body_len, char * Socketbody)
{
	TPkgHeader header;
	header.seq = dwConnID;
	header.body_len = body_len;

	WSABUF bufs[2];
	bufs[0].len = sizeof(TPkgHeader);
	bufs[0].buf = (char*)&header;
	bufs[1].len = body_len;
	bufs[1].buf = Socketbody;
	if (!m_Client.SendPackets(bufs, 2))
	{
		TRACE("����ʧ��");
	}
}

void CHPClient::HandlePacket(DWORD dwPacketID, CBufferPtr & buffer)
{
	switch (dwPacketID)
	{
	case SOCEKT_LOGIN_INFO://��¼��Ϣ
	{
		TRACE("----client--------->��¼��Ϣ");
	}
	break;
	case SOCKET_GAME_SCRIPT_INFO://ִ�нű�
	{
		TRACE("-----client-------->ִ�нű�");
	}
	break;
	case SOCKET_GAME_STOP_SCRIPT://ֹͣ�ű�
	{	
		TRACE("-----client-------->ֹͣ�ű�");
	}
	break;
	case SOCKET_�ͻ��˽�������_������://�յ�������
	{
		TRACE("-----client-------->�յ�������");
	}
	break;
	case SOCKET_GAME_UNINSTALL://ж��DLL
	{
		TRACE("------client------->ж����Ϸ");
	}
	break;
	default:
		break;
	}
}

UINT CHPClient::SendRoleInfo()
{
	//�ж�����Ѫ�Ƿ����0,������û3�뷢��һ��
	SocketGameRoleInfo _SocketGameRoleInfo = { 0 };
	strcpy_s(_SocketGameRoleInfo.RoleName, "���Խ�ɫ");
	_SocketGameRoleInfo.RoleLevel = 95;
	_SocketGameRoleInfo.RoleMenPai = 1;
	_SocketGameRoleInfo.RoleTi = 0;
	_SocketGameRoleInfo.RoleFa = 0;
	strcpy_s(_SocketGameRoleInfo.GameMap, "����");
	_SocketGameRoleInfo.PointX =200;
	_SocketGameRoleInfo.PointY = 100;
	int JinQian = 500;
	if (JinQian >= 0)
	{
		_SocketGameRoleInfo.NoBindGold = JinQian;
	}
	else
	{
		_SocketGameRoleInfo.NoBindGold = 0;
	}
	int JiaoZi = 1010;
	if (JiaoZi >= 0)
	{
		_SocketGameRoleInfo.BindGold = JiaoZi;
	}
	else
	{
		_SocketGameRoleInfo.BindGold = 0;
	}
	int YuanBao = 4000;
	if (YuanBao >= 0)
	{
		_SocketGameRoleInfo.YuanBap = YuanBao;
	}
	else
	{
		_SocketGameRoleInfo.YuanBap = 0;
	}
	_SocketGameRoleInfo.RoleStatus = 1;

	MySendPackets(SOCKET_USERINFO, sizeof(_SocketGameRoleInfo), (char*)&_SocketGameRoleInfo);
	return 0;
}

void Initial()
{
	pClient = new CHPClient();
	pClient->HPInit();
	pMsg = new CMessage();

	pMsg->Init();
	pSelf->CreatUI();

	pClient->SendRoleInfo();
}

UINT __stdcall Dll_threadFunc(void* p)//��¼�̺߳���
{
	int nType = (int)p;

	if (nType == ע��ģ��)
	{
		Initial();
		TRACE("ע�����");
		return 0;
	}

	dbgPrint("ж��ģ��");
	return 0;

	return 1;
}