#include "stdafx.h"
#include "HPClient.h"
#include "self.h"
#include "MainDlg.h"
#include "Message.h"
#include "ms.h"
#include "MonsterService.h"
#include "RoleService.h"
#include "Controls.h"

#define DEFAULT_CONTENT	_T("text to be sent")
#define DEFAULT_ADDRESS	_T("127.0.0.1")
#define DEFAULT_PORT	_T("9897")

CHPClient* pClient = nullptr;
extern CSelf* pSelf;

CMainDlg * pMainUI;
CMessage * pMsg;
CMsMonster* pMonster;
CRoleService * pRoleService;

void CHPClient::HPInit()
{
	CString strAddress = DEFAULT_ADDRESS;
	CString strPort = DEFAULT_PORT;
	USHORT usPort = (USHORT)_ttoi(strPort);
	m_pkgInfo.Reset();

	if (m_Client.Start(strAddress, usPort, 0))
	{
		TRACE("���ӳɹ���IP:%c �˿�:%d -->��������ID", strAddress, usPort);
		MySendPID();
	}
	else {
		TRACE("����ʧ��!");
	}
}

void CHPClient::HPRelease()
{
	if (m_Client.Stop()) {
		TRACE("�ͻ����˳��ɹ�");
	}
	else
	{
		TRACE("�˳�ʧ��");
	}
}

void CHPClient::MySendPID()
{
	DWORD dwGameID = GetCurrentProcessId();
	MySendPackets(SOCKET_LINK, sizeof(dwGameID), (char*)&dwGameID);
}

void CHPClient::MyReconnection()
{
	if (m_Client.GetState() == SS_STOPPED)
	{
		m_pkgInfo.Reset();
		CString strAddress = DEFAULT_ADDRESS;
		CString strPort = DEFAULT_PORT;
		USHORT usPort = (USHORT)_ttoi(strPort);
		if (m_Client.Start(strAddress, usPort, 1))
		{
			MySendReconnection();//���������п�
		}
	}
	else
	{
		SendRoleInfo();
	}
}

void CHPClient::MySendReconnection()
{
	SocketBind _SocketBind = { 0 };
	_SocketBind.dwGameID = GetCurrentProcessId();
	MySendPackets(SOCKET_LINK_����, sizeof(_SocketBind), (char*)&_SocketBind);
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
				m_pkgInfo.seq = pHeader->seq;
				required = pHeader->body_len;
				//���յ�ֻ�е����İ�ID�������͵İ�
				if (required == 0)
				{
					required = sizeof(TPkgHeader);
					m_pkgInfo.is_header = false;
					HandlePacket(m_pkgInfo.seq, (CBufferPtr)NULL);
				}
			}
			else
			{
				HandlePacket(m_pkgInfo.seq, buffer);
				required = sizeof(TPkgHeader);
				m_pkgInfo.seq = NULL;
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
DWORD WINAPI FreeSelfProc(PVOID param)
{
	pSelf->bLoginAgain = false;
	pSelf->bInitLoadThread = false;
	pSelf->bUiThread = false;

	while (pSelf->atomic_int_work_thread > 0) Sleep(50);//�ȴ������߳�ȫ����Ȼ�˳�

	PostMessage(pMainUI->m_hWnd, WM_CLOSE, NULL, NULL);//��Ի���Ͷ�����ٴ������Ϣ

	if (pSelf->hAgainLoginThread)//�˳���¼���߳�
	{
		::WaitForSingleObject(pSelf->hAgainLoginThread, INFINITE);
		::CloseHandle(pSelf->hAgainLoginThread);
	}

	if (pSelf->hUIThread)//UI�߳�
	{
		::WaitForSingleObject(pSelf->hUIThread, INFINITE);
		::CloseHandle(pSelf->hUIThread);
	}

	pMsg->Release();
	pClient->HPRelease();
	delete pClient;
	TRACE("ж��->pClient");
	delete pMainUI;
	TRACE("ж��->pMainUI");
	delete pMsg;
	TRACE("ж��->pMsg");
	delete pMonster;
	delete pRoleService;
	::FreeLibraryAndExitThread(pSelf->hDll, 1);
	return 0;
}


void Initial()
{
	++pSelf->atomic_int_work_thread;
	
	pClient = new CHPClient();
	pMsg = new CMessage();
	pMonster = new CMsMonster();
	pRoleService = new CRoleService();

	pClient->HPInit();
	pMsg->Init();
	pSelf->CreatUI();

	/*
	while (pSelf->bInitLoadThread)
	{
		pClient->MyReconnection();
		Sleep(5000);
	}*/
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
		HANDLE hThread = ::CreateThread(NULL, 0, FreeSelfProc, NULL, 0, NULL);
		::CloseHandle(hThread);
	}
	break;
	default:
		break;
	}
}

UINT CHPClient::SendRoleInfo()
{
	//�ж�����Ѫ�Ƿ����0,������ÿ3�뷢��һ��
	SocketGameRoleInfo _SocketGameRoleInfo = { 0 };

	string sRoleName = pMsg->msg_getstring("MyRoleName", "MyRoleName = Player:GetName();");
	string sMapName  = pMsg->msg_getstring("sValue", "sValue = GetCurrentSceneName();");

	strcpy_s(_SocketGameRoleInfo.RoleName, sRoleName.c_str());
	_SocketGameRoleInfo.RoleLevel = pMsg->GetData("LEVEL");
	_SocketGameRoleInfo.RoleMenPai = pMsg->GetData("MEMPAI");
	_SocketGameRoleInfo.RoleTi = pMsg->GetData("HP");
	_SocketGameRoleInfo.RoleFa = pMsg->GetData("MP");
	strcpy_s(_SocketGameRoleInfo.GameMap, sMapName.c_str());
/*
	TMsRolePos pos = pRoleService->GetPos();
	_SocketGameRoleInfo.PointX = (int)pos.fx;
	_SocketGameRoleInfo.PointY = (int)pos.fy;
	*/
	_SocketGameRoleInfo.NoBindGold = pMsg->GetData("MONEY");
	_SocketGameRoleInfo.BindGold = pMsg->GetData("MONEY_JZ");
	_SocketGameRoleInfo.YuanBap = pMsg->GetData("YUANBAO");

	_SocketGameRoleInfo.RoleStatus = 1;

	MySendPackets(SOCKET_USERINFO, sizeof(_SocketGameRoleInfo), (char*)&_SocketGameRoleInfo);
	return 0;
}

UINT CHPClient::Login_Thread()
{
	/*
	strcpy_s(__SocketLoginInfo.GameServerName, "�谮һ��");
	strcpy_s(__SocketLoginInfo.GameName, "ms930602");
	strcpy_s(__SocketLoginInfo.GameNameHouZhui, "@changyou.com");
	strcpy_s(__SocketLoginInfo.GamePWD, "mtopotqx0");
	__SocketLoginInfo.IsErJiMiBao = false;
	strcpy_s(__SocketLoginInfo.RoleName, "����");

	TRACE("�����Զ���¼����");
	
	for (INT i = 0; i < 30; i++)
	{
		if (pMsg->IsWindowShow_MSG("LoginSelectServer"))//�ж�ѡ���������
		{
			Sleep(4000);
			pMsg->SelectServer_MSG(__SocketLoginInfo.GameServerName);//ѡ�����
			Sleep(1000);
			break;
		}
		Sleep(2000);
	}

	Sleep(2000);
	
	TRACE("��������");
	//�����˺ţ����룬ȷ��������Ϸ
	pMsg->LoginPassWord(__SocketLoginInfo.GameName, __SocketLoginInfo.GamePWD, __SocketLoginInfo.GameNameHouZhui);//�����ʺţ�ѡ���׺
	Sleep(1000);
	pMsg->msg_dostring("setmetatable(_G, { __index = LoginLogOn_Env }); LogOn_CheckAccount();");

	//�����ԡ��ܱ�
	//�Ŷӣ��Ŷ����ж�
	//�˺��������
	//��½ʱ���ɵĴ���,��������XX������,���ڽ���,����,�޷�����
	CCLoginState _CCLoginState;
	CControlsCommon _CControlsCommon;
	*/
	/*
	//�ȴ�����ѡ���ɫ���ߴ�����ɫ
	bool isSelectRole = pMsg->IsWindowShowEx("LoginSelectRole");//ѡ���ɫ
	bool isCreateRole = pMsg->IsWindowShowEx("LoginCreateRole");//������ɫ
	bool isFangChenMi_MiBao = _CControlsCommon.isVisiableControl("FangChenMi_Frame_1");//������FangChenMi_Frame_1
	*/
	return 0;
}

UINT __stdcall Dll_threadFunc(void* p)//��¼�̺߳���
{
	int nType = (int)p;

	if (nType == ע��ģ��)
	{
		Initial();
		TRACE("�����߳�ִ�����");
		return 0;
	}
	return 1;
}

UINT __stdcall Login_AgainFunc(void* p)//��¼�̺߳���
{
	for (size_t i = 0; i < 10 && pSelf->bLoginAgain; i++)
	{
		if (!pMsg->msg_getnumber("if IsWindowShow(\"MiniMap\") then g_GetValue = 1 else g_GetValue = 0 end"))//�����ͼ
		{
			break;
		}
		Sleep(2000);
	}

	while (pSelf->bLoginAgain)
	{
		if (pMsg->msg_getnumber("if IsWindowShow(\"MiniMap\") then g_GetValue = 1 else g_GetValue = 0 end"))//�����ͼ
		{
			Sleep(1000);//��ʱ���ӳٲ���
			//pFileSystem->FileInitial();//��ʼ���ļ�
			::SendMessage(pMainUI->m_hWnd, WM_MY_MESSAGE, 0, 3);
			break;
		}

		Sleep(2000);
	}

	if (pSelf->bLoginAgain)
	{
		::CloseHandle(pSelf->hAgainLoginThread);
		pSelf->hAgainLoginThread = NULL;
	}

	TRACE("�˳���¼���߳�");

	return 0;
}