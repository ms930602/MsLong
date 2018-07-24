#pragma once
#include <string>
using namespace std;
#define  IsReadAddrInt(addr) !IsBadReadPtr(addr,sizeof(unsigned int))//���ֽ��ж�
#define  IsReadAddrByte(addr) !IsBadReadPtr(addr,sizeof(byte))//һ�ֽ��ж�
class CControlsProperty
{
private:
	int ControlsBase;//��ַ
	int ControlPointLeftX;//���Ͻ�X����
	int ControlPointLeftY;//���Ͻ�Y����
	int ControlPointRightX;//���Ͻ�X����
	int ControlPointRightY;//���Ͻ�Y����
	string ControlName;//�ؼ�����
	int NameTag;//��������ж������Ƿ��ȡ��һָ��
	bool IsVisiable;//�ؼ��Ƿ���ʾ
	string IsVisiableStr;//�Ƿ���ʾ��������
private:
	int SubArrayStart;//�ӿؼ����鿪ʼ��ַ
	int SubArrayEnd;//�ӿؼ����������ַ
public:
	CControlsProperty(void);
	CControlsProperty(int ControlBase);
	~CControlsProperty(void);
public:	//��������
		//��ȡ�ؼ���ַ
	int getControlsBase()
	{
		return ControlsBase;
	}
	//��ȡ�Ƚϵ�ַ
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
	//��ȡ���Ͻ�X
	int getControlPointLeftX()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			ControlPointLeftX = (int)(*(float *)(ControlsBase + 0x1BC));
		}
		return ControlPointLeftX;
	}
	//��ȡ���Ͻ�Y
	int getControlPointLeftY()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			ControlPointLeftY = (int)(*(float *)(ControlsBase + 0x1C0));
		}
		return ControlPointLeftY;
	}
	//��ȡ���Ͻ�X
	int getControlPointRightX()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			ControlPointRightX = (int)(*(float *)(ControlsBase + 0x1C4));
		}
		return ControlPointRightX;
	}
	//��ȡ���Ͻ�Y
	int getControlPointRightY()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			ControlPointRightY = (int)(*(float *)(ControlsBase + 0x1C8));
		}
		return ControlPointRightY;
	}
	//��ȡ�ؼ�����
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
	//��ȡ��ʾ״̬���Ƿ����أ�
	bool getIsVisiable()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			BYTE _isVisiable = *(BYTE *)(ControlsBase + 0x139);
			if (_isVisiable == 1)
			{
				IsVisiable = true;
				IsVisiableStr = "��";
			}
		}
		return IsVisiable;
	}
	//�Ƿ���ʾ���ı�
	string getIsVisiableStr()
	{
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			BYTE _isVisiable = *(BYTE *)(ControlsBase + 0x139);
			if (_isVisiable == 1)
			{
				IsVisiable = true;
				IsVisiableStr = "��";
			}
		}
		return IsVisiableStr;
	}
	//��ȡ�ӿؼ���ʼ��ַ
	int getSubArrayStart()
	{
		//AFX_MANAGE_STATE(AfxGetStaticModuleState());
		if (IsReadAddrInt((PVOID)(ControlsBase)))
		{
			SubArrayStart = *(int *)(ControlsBase + 0x2C);
		}
		return SubArrayStart;
	}
	//��ȡ�ӿؼ�������ַ
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
	int BASE_ADDR;//�ؼ���ַ

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


#define  FANGCHENMI_MIBAO  0x9D9900 //�����ԣ�����
#define  LOGIN_EXCEPTION   0x9D8898 //��¼�쳣

class CCLoginState
{
public:
	CCLoginState();
	~CCLoginState();
	bool IsFangChenMi_MiBaoUI();//�����ԣ��ܱ������ж�
	bool IsExceptionUI();//���ڽ��룬�����޷�����
};