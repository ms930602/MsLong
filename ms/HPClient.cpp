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
		TRACE("连接成功！IP:%c 端口:%d -->发送连接ID", strAddress, usPort);
		MySendPID();
	}
	else {
		TRACE("连接失败!");
	}
}

void CHPClient::HPRelease()
{
	if (m_Client.Stop()) {
		TRACE("客户端退出成功");
	}
	else
	{
		TRACE("退出失败");
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
			MySendReconnection();//发送重连中控
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
	MySendPackets(SOCKET_LINK_重连, sizeof(_SocketBind), (char*)&_SocketBind);
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
DWORD WINAPI FreeSelfProc(PVOID param)
{
	pSelf->bLoginAgain = false;
	pSelf->bInitLoadThread = false;
	pSelf->bUiThread = false;

	while (pSelf->atomic_int_work_thread > 0) Sleep(50);//等待所有线程全部自然退出

	PostMessage(pMainUI->m_hWnd, WM_CLOSE, NULL, NULL);//向对话框投递销毁窗体的消息

	if (pSelf->hAgainLoginThread)//退出登录绑定线程
	{
		::WaitForSingleObject(pSelf->hAgainLoginThread, INFINITE);
		::CloseHandle(pSelf->hAgainLoginThread);
	}

	if (pSelf->hUIThread)//UI线程
	{
		::WaitForSingleObject(pSelf->hUIThread, INFINITE);
		::CloseHandle(pSelf->hUIThread);
	}

	pMsg->Release();
	pClient->HPRelease();
	delete pClient;
	TRACE("卸载->pClient");
	delete pMainUI;
	TRACE("卸载->pMainUI");
	delete pMsg;
	TRACE("卸载->pMsg");
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
	//判断人物血是否大于0,大于则每3秒发送一次
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
	strcpy_s(__SocketLoginInfo.GameServerName, "宠爱一生");
	strcpy_s(__SocketLoginInfo.GameName, "ms930602");
	strcpy_s(__SocketLoginInfo.GameNameHouZhui, "@changyou.com");
	strcpy_s(__SocketLoginInfo.GamePWD, "mtopotqx0");
	__SocketLoginInfo.IsErJiMiBao = false;
	strcpy_s(__SocketLoginInfo.RoleName, "虞兮");

	TRACE("进入自动登录功能");
	
	for (INT i = 0; i < 30; i++)
	{
		if (pMsg->IsWindowShow_MSG("LoginSelectServer"))//判断选择大区界面
		{
			Sleep(4000);
			pMsg->SelectServer_MSG(__SocketLoginInfo.GameServerName);//选择大区
			Sleep(1000);
			break;
		}
		Sleep(2000);
	}

	Sleep(2000);
	
	TRACE("输入密码");
	//输入账号，密码，确定进入游戏
	pMsg->LoginPassWord(__SocketLoginInfo.GameName, __SocketLoginInfo.GamePWD, __SocketLoginInfo.GameNameHouZhui);//输入帐号，选择后缀
	Sleep(1000);
	pMsg->msg_dostring("setmetatable(_G, { __index = LoginLogOn_Env }); LogOn_CheckAccount();");

	//防沉迷、密保
	//排队，排队满判断
	//账号密码错误
	//登陆时过渡的窗口,正在连接XX服务器,正在进入,错误,无法连接
	CCLoginState _CCLoginState;
	CControlsCommon _CControlsCommon;
	*/
	/*
	//等待进入选择角色或者创建角色
	bool isSelectRole = pMsg->IsWindowShowEx("LoginSelectRole");//选择角色
	bool isCreateRole = pMsg->IsWindowShowEx("LoginCreateRole");//创建角色
	bool isFangChenMi_MiBao = _CControlsCommon.isVisiableControl("FangChenMi_Frame_1");//防沉迷FangChenMi_Frame_1
	*/
	return 0;
}

UINT __stdcall Dll_threadFunc(void* p)//登录线程函数
{
	int nType = (int)p;

	if (nType == 注入模块)
	{
		Initial();
		TRACE("加载线程执行完毕");
		return 0;
	}
	return 1;
}

UINT __stdcall Login_AgainFunc(void* p)//登录线程函数
{
	for (size_t i = 0; i < 10 && pSelf->bLoginAgain; i++)
	{
		if (!pMsg->msg_getnumber("if IsWindowShow(\"MiniMap\") then g_GetValue = 1 else g_GetValue = 0 end"))//迷你地图
		{
			break;
		}
		Sleep(2000);
	}

	while (pSelf->bLoginAgain)
	{
		if (pMsg->msg_getnumber("if IsWindowShow(\"MiniMap\") then g_GetValue = 1 else g_GetValue = 0 end"))//迷你地图
		{
			Sleep(1000);//暂时不延迟不行
			//pFileSystem->FileInitial();//初始化文件
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

	TRACE("退出登录绑定线程");

	return 0;
}