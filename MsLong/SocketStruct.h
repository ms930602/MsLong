#ifndef _STRURCT_SOCKET
#define _STRURCT_SOCKET

#define SOCKET_GAME_启动游戏 1
#define SOCKET_GAME_单独登录 2
#define SOCKET_GAME_批量登陆 3

#define SOCKET_LINK 10 //连接服务端消息
#define SOCKET_USERINFO 11 //客户端->服务端 发送角色信息
#define SOCEKT_LOGIN_INFO 16 //登录信息
#define SOCKET_LOGIN_ACTION 18 //登录游戏命令
#define SOCKET_GAME_INFO	19 //游戏信息
#define SOCKET_GAME_SCRIPT_INFO	20 //执行游戏脚本
#define SOCKET_GAME_PAUSE_SCRIPT 22 //暂定当前脚本
#define SOCKET_GAME_LOGIN_INI_OK 23 //游戏通知到了账号输入界面
#define SOCKET_GAME_START_SCRIPT 24 //继续当前脚本
#define SOCKET_GAME_VALIDATE 25 //验证码
#define SOCKET_GAME_VALIDATE_RESULT 26 //验证码结果
#define SOCKET_GAME_SECURITY 27 //密保
#define SOCKET_LINK_重连 28 //连接服务端消息
#define SOCKET_GAME_STOP_SCRIPT 29 //停止脚本


#define SOCKET_客户端接受主控_答题结果 49

#define SOCKET_客户端发送主控_答题信息 50

#define SOCKET_主控发送客户端_答题结果 SOCKET_客户端接受主控_答题结果

#define SOCKET_主控接受客户端_答题信息 SOCKET_客户端发送主控_答题信息

#define SOCKET_主控发送答题端_答题信息 51

#define SOCKET_主控接受答题端_答题结果 52

#define SOCKET_答题端发送_答题结果 SOCKET_主控接受答题端_答题结果

#define SOCKET_答题端接受_答题信息 SOCKET_主控发送答题端_答题信息

//----------------------------------------------------------------------
//定义通讯结构体
//----------------------------------------------------------------------
#pragma pack(push)//定义字节对齐方式为1字节
#pragma pack(1)

struct TPkgHeader
{
	DWORD seq;
	int body_len;
};

struct TPkgBody
{
	char name[30];
	short age;
	char desc[1];
};

struct TPkgInfo
{
	bool is_header;
	int length;

	TPkgInfo(bool header = true, int len = sizeof(TPkgHeader)) : is_header(header), length(len) {}
	void Reset() { is_header = true, length = sizeof(TPkgHeader); }
	~TPkgInfo() {}
};


#pragma pack(pop)



#endif