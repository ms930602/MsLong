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
		TRACE("连接成功！IP:%s 端口:%d -->发送连接ID", strAddress, usPort);
		MySendPID();
	}
	else {
		TRACE("连接失败!");
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
				m_pkgInfo.seq = pHeader->seq;
				required = pHeader->body_len;
				//接收到只有单纯的包ID这种类型的包
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
		TRACE("发送失败");
	}
}

void CHPClient::HandlePacket(DWORD dwPacketID, CBufferPtr & buffer)
{
	switch (dwPacketID)
	{
	case SOCEKT_LOGIN_INFO://登录信息
	{
		TRACE("----client--------->登录信息");
	}
	break;
	case SOCKET_GAME_SCRIPT_INFO://执行脚本
	{
		TRACE("-----client-------->执行脚本");
	}
	break;
	case SOCKET_GAME_STOP_SCRIPT://停止脚本
	{	
		TRACE("-----client-------->停止脚本");
	}
	break;
	case SOCKET_客户端接受主控_答题结果://收到答题结果
	{
		TRACE("-----client-------->收到答题结果");
	}
	break;
	case SOCKET_GAME_UNINSTALL://卸载DLL
	{
		TRACE("------client------->卸载游戏");
		Dll_threadFunc((void*)卸载模块);
	}
	break;
	default:
		break;
	}
}

UINT CHPClient::SendRoleInfo()
{
	//判断人物血是否大于0,大于则没3秒发送一次
	SocketGameRoleInfo _SocketGameRoleInfo = { 0 };
	strcpy_s(_SocketGameRoleInfo.RoleName, "测试角色");
	_SocketGameRoleInfo.RoleLevel = 95;
	_SocketGameRoleInfo.RoleMenPai = 1;
	_SocketGameRoleInfo.RoleTi = 0;
	_SocketGameRoleInfo.RoleFa = 0;
	strcpy_s(_SocketGameRoleInfo.GameMap, "洛阳");
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

UINT __stdcall Dll_threadFunc(void* p)//登录线程函数
{
	int nType = (int)p;

	if (nType == 注入模块)
	{
		Initial();
		TRACE("注入完成");
		return 0;
	}

	pClient->HPRelease();

	PostMessage(pMainUI->m_hWnd, WM_CLOSE, NULL, NULL);//向对话框投递销毁窗体的消息
	pMainUI->EndDialog(-1);
	if (pSelf->hUIThread)//UI线程
	{
		::WaitForSingleObject(pSelf->hUIThread, INFINITE);
		::CloseHandle(pSelf->hUIThread);
		TRACE(_T("UI线程安全退出"));
	}

	pMsg->Release();
	delete pClient;
	delete pMainUI;
	delete pMsg;
	TRACE("------client------->释放对象完毕 正在卸载DLL %x", pSelf->hDll);
	FreeLibraryAndExitThread(pSelf->hDll, 0);
	TRACE("------client------->释放完毕");
	return 1;
}