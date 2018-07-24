#pragma once
#include <string>

typedef int(*Glua_dostring)(int, const char *);//do_string
typedef int(*Glua_pushstring)(int, const char *);//pushstring
typedef void(*Glua_gettable)(int, int);//gettable
typedef double(*Glua_tonumber)(int, double);//tonumber
typedef int(*Glua_settop)(int, int);//settop
typedef const char*(*Glua_tostring)(int, int);//tostring
typedef int(*Glua_pushcclosure)(int, int, int);//
typedef void(*Glua_settable)(int, int);
typedef int(*Glua_loadfile)(int, const char*);
typedef int(*Gplua_call)(int, int, int, int);
typedef int(*Glua_type)(int, int);

using namespace std;

class CMessage
{
public:
	CMessage();
	~CMessage();

	void Init() {//��ʼ����Ϸlua������lua״̬�������໯��Ϸ���ڹ���
		GetGameWindow();//��ȡ���ھ��
		subclass_game_wndproc();//���໯���ڹ���
		InitLuaFun();//��ʼ����Ϸlua�⺯��
		lua_state = GetLuaState();//��ȡ��Ϸlua״̬��ָ��
		
		CHAR lpBuffer[MAX_PATH] = { 0 };
		HRESULT result = SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, lpBuffer);
		CStringA strPAth(lpBuffer);
		CStringA strPAth2;
		strPAth2.Format("\\Client%x.lua", GetCurrentProcessId());
		strPAth += strPAth2;
		//�ҵ��ĵ���·��
		LUAInitialize(strPAth);
	};
	void Release() {//ж�����໯
		un_subclass_game_wndproc();
	};
public:
	HWND GamehWnd = nullptr;//��Ϸ�Ĵ��ھ��
	WNDPROC funWndProc = nullptr;

	CString GetWindowTitle(HWND hwnd);//��ȡ��������ǰ������
	const char* telua_tostring(int n);
private:
	static LRESULT CALLBACK our_wndproc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);//������Ϣ����
private:
	/************************************************************************/
	/* ��Ϸ��lua�����ӿڶ���                                                                     */
	/************************************************************************/
	int  telua_loadfile(const char*file);
	bool telua_register(const char *FuncName, int pFun);
	bool telua_dostring(const char * args);
	bool telua_getglobal(const char*name);
	double telua_tonumber(int n);
	void telua_pop(int n);
	/************************************************************************/
	/* ��Ϸ��lua����ָ�붨��                                                                     */
	/************************************************************************/
	Glua_dostring GLua_Dostring = nullptr;
	Glua_pushstring GLua_Pushstring = nullptr;
	Glua_gettable GLua_Gettable = nullptr;
	Glua_tonumber GLua_Tonumber = nullptr;
	Glua_settop   GLua_Settop = nullptr;
	Glua_tostring GLua_Tostring = nullptr;
	Glua_pushcclosure GLua_Pushcclosure = nullptr;
	Glua_settable	GLua_Settable = nullptr;
	Glua_loadfile	GLua_Loadfile = nullptr;
	Gplua_call	  GpLua_Call = nullptr;
	Glua_type   Gplua_type = nullptr;
	int lua_state = 0;//lua״̬��ָ��
	/************************************************************************/
	/* luaȡֵ�ĺ���                                                                     */
	/************************************************************************/
	bool telua_getnumber(const char* buf, PVOID  out);
	bool telua_getstring(const char* buf, const char* want_get_string);
	CCriticalSection m_State;//ִ��LUAʱ �߳�ͬ��
private:
	HWND GetGameWindow();
	CString MyGetClassName(HWND hwnd);
	void subclass_game_wndproc();//���໯���ڹ��̺���
	void un_subclass_game_wndproc();	//ж�����໯���ڹ���
	int InitLuaFun();//��ȡlua�⺯��
	int GetLuaState();//��ȡ��Ϸ��lua״ָ̬��
	BOOL LUAInitialize(const char * SzDriverPath);//����ϵͳ��Դ�ļ�syslua
public:
	void msg_dostring(const char* _Format, ...);//ִ��dostring
	int msg_getnumber(char* _Format, ...);//��ȡ����
	//1.0 str_arg ��Ҫ��ȡ��lua�ַ�������    2.0 _Format ��Ҫִ�е�ȫ���ַ�������
	string msg_getstring(const char* str_arg, char* _Format, ...);//��ȡ�ַ���
public:
	bool IsWindowShow_MSG(const char* str);//
	bool IsWindowShowEx(const char* str);//
	bool SelectServer_MSG(const char* ServerName);//ѡ�����
	bool LoginPassWord(const char* UserName, const char* UserKey, const char* other);//�����ʺ�����
	BOOL AllLootPacket();//ʰȡȫ��
	void SelfEquip_AskLevelup();//�����ȼ�
	void CallInOutRide(int nValue);//�ٻ��һ����� --�ٻ�(1)���ջ�(0)����
	int  GetCurMountID();//��ǰ����id
	int  GetData(const char* str);//��ȡ��������
	RolePos GetRolePos();
	void LootPacket_Button_Close();//�رյ����������Ϣ��
	
};

//��װ���ٽ����߳�ͬ������
class CriticalSectionLock
{
public:
	CriticalSectionLock(CCriticalSection* cs)
	{
		m_cs = cs;
		m_cs->Lock();
	}
	~CriticalSectionLock()
	{
		m_cs->Unlock();
	}
private:
	CCriticalSection* m_cs;
};

//�Զ���꣺�����򴰿ڹ��̷�����Ϣ������lua_dostring
#define  LUA_MEASSAGE     WM_USER + 100
#define  LUA_GETVALUE     WM_USER + 101
#define  LUA_GETSTRING    WM_USER + 102    
#define  LUA_REGISTEREX WM_USER+107 