#pragma once
#include <string>
using namespace std;
#define  IsReadAddrInt(addr) !IsBadReadPtr(addr,sizeof(unsigned int))//四字节判断
#define  IsReadAddrByte(addr) !IsBadReadPtr(addr,sizeof(byte))//一字节判断
class CControlsProperty
{
private:
	int ControlsBase;//基址
	int ControlPointLeftX;//左上角X坐标
	int ControlPointLeftY;//左上角Y坐标
	int ControlPointRightX;//右上角X坐标
	int ControlPointRightY;//右上角Y坐标
	string ControlName;//控件名称
	int NameTag;//根据这个判断名字是否读取下一指针
	bool IsVisiable;//控件是否显示
	string IsVisiableStr;//是否显示文字字体
private:
	int SubArrayStart;//子控件数组开始地址
	int SubArrayEnd;//子控件数组结束地址
public:
	CControlsProperty(void);
	CControlsProperty(int ControlBase);
	~CControlsProperty(void);
public:	//内联函数
		//获取控件基址
	int getControlsBase()
	{
		return ControlsBase;
	}
	//获取比较地址
	int getTempAddr()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			int TempAddr = *(int *)(ControlsBase + 0x48);
			return TempAddr;
		}
		return 0;
	}
	//获取左上角X
	int getControlPointLeftX()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			ControlPointLeftX = (int)(*(float *)(ControlsBase + 0x1BC));
		}
		return ControlPointLeftX;
	}
	//获取左上角Y
	int getControlPointLeftY()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			ControlPointLeftY = (int)(*(float *)(ControlsBase + 0x1C0));
		}
		return ControlPointLeftY;
	}
	//获取右上角X
	int getControlPointRightX()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			ControlPointRightX = (int)(*(float *)(ControlsBase + 0x1C4));
		}
		return ControlPointRightX;
	}
	//获取右上角Y
	int getControlPointRightY()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			ControlPointRightY = (int)(*(float *)(ControlsBase + 0x1C8));
		}
		return ControlPointRightY;
	}
	//获取控件名称
	string getControlName()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			if (NameTag >= 8 && NameTag <= 0xF)
			{
				char ControlTxt[255] = { 0 };
				strcpy_s(ControlTxt, (char *)(ControlsBase + 0x244));
				ControlName = ControlTxt;
			}
			else
			{
				if (IsReadAddrInt((PVOID)((ControlsBase + 0x244))))
				{
					char ControlTxt[255] = { 0 };
					strcpy_s(ControlTxt, (char*)(*(int*)(ControlsBase + 0x244)));
					ControlName = ControlTxt;
				}
			}
		}
		return ControlName;
	}
	//获取显示状态（是否隐藏）
	bool getIsVisiable()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			BYTE _isVisiable = *(BYTE *)(ControlsBase + 0x139);
			if (_isVisiable == 1)
			{
				IsVisiable = true;
				IsVisiableStr = "是";
			}
		}
		return IsVisiable;
	}
	//是否显示的文本
	string getIsVisiableStr()
	{
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			BYTE _isVisiable = *(BYTE *)(ControlsBase + 0x139);
			if (_isVisiable == 1)
			{
				IsVisiable = true;
				IsVisiableStr = "是";
			}
		}
		return IsVisiableStr;
	}
	//获取子控件开始地址
	int getSubArrayStart()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			SubArrayStart = *(int *)(ControlsBase + 0x2C);
		}
		return SubArrayStart;
	}
	//获取子控件结束地址
	int getSubArrayEnd()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			SubArrayEnd = *(int *)(ControlsBase + 0x30);
		}
		return SubArrayEnd;
	}
};

class CControls
{
private:
	int BASE_ADDR;//控件基址

public:
	CControls(void);
	void InitData();
	void GetAllControls(vector<CControlsProperty> &_AllControls);
	~CControls(void);
private:
	void getControls(int BaseAddr, vector<CControlsProperty> &_AllControls);
};

class CControlsCommon
{
public:
	CControlsCommon();
	~CControlsCommon();
	bool CControlsCommon::isVisiableControl(string strControlName);
	bool CControlsCommon::isPaiDui_();
	bool CControlsCommon::isPaiDuiYiMan();
};


#define  FANGCHENMI_MIBAO  0x9D9900 //防沉迷，密码
#define  LOGIN_EXCEPTION   0x9D8898 //登录异常

class CCLoginState
{
public:
	CCLoginState();
	~CCLoginState();
	bool IsFangChenMi_MiBaoUI();//防沉迷，密保窗口判断
	bool IsExceptionUI();//正在进入，错误，无法连接
};