#include "stdafx.h"
#include "Controls.h"

CControlsCommon::CControlsCommon()
{
}

CControlsCommon::~CControlsCommon()
{
}

bool CControlsCommon::isVisiableControl(string strControlName)
{
	bool isVisiable = false;
	CControls _CCControls;

	return isVisiable;
}

bool CControlsCommon::isPaiDui_()
{
	return false;
}

bool CControlsCommon::isPaiDuiYiMan()
{
	return false;
}

CCLoginState::CCLoginState()
{
}

CCLoginState::~CCLoginState()
{
}

bool CCLoginState::IsFangChenMi_MiBaoUI()
{
	return false;
}

bool CCLoginState::IsExceptionUI()
{
	return false;
}

CControlsProperty::CControlsProperty(void)
{
}

CControlsProperty::CControlsProperty(int ControlBase)
{
}

CControlsProperty::~CControlsProperty(void)
{
}

CControls::CControls(void)
{
	BASE_ADDR = 0;
	InitData();
}

void CControls::InitData()
{
	/*
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRACE("��ʼ��ѯUI��ڻ�ַ");
	HMODULE hdll;
	hdll = GetModuleHandleA("CEGUIBase.dll");
	//////////////////////////////////////////////////////////////////////////
	if (hdll)
	{
		int ControlsBase = 0, ControlsBaseA = 0;
		ControlsBase = (int)GetProcAddress(hdll, "?ms_Singleton@?$Singleton@VSystem@CEGUI@@@CEGUI@@1PAVSystem@2@A");
		ControlsBaseA = (int)GetProcAddress(hdll, "?getSingleton@?$Singleton@VWindowManager@CEGUI@@@CEGUI@@SAAAVWindowManager@2@XZ");
		TRACE("����UI��ַA�� %x", ControlsBase);
		TRACE("����ControlsBaseA��ַA�� %x", ControlsBaseA);
		ControlsBase = *(int*)ControlsBase;
		BASE_ADDR = *(int*)(ControlsBase + 0x30);
		TRACE("����UI��ַ��ַ�� %x", BASE_ADDR);
	}
	*/
}

void CControls::GetAllControls(vector<CControlsProperty>& _AllControls)
{
}

CControls::~CControls(void)
{
}

void CControls::getControls(int BaseAddr, vector<CControlsProperty>& _AllControls)
{
}
