#pragma once
class CMessage
{
public:
	CMessage();
	~CMessage();

	void Init() {//��ʼ����Ϸlua������lua״̬�������໯��Ϸ���ڹ���
		GetGameWindow();//��ȡ���ھ��
		subclass_game_wndproc();//���໯���ڹ���
	};
	void Release() {//ж�����໯
		un_subclass_game_wndproc();
	};
public:
	HWND GamehWnd = nullptr;//��Ϸ�Ĵ��ھ��
	WNDPROC funWndProc = nullptr;
private:
	static LRESULT CALLBACK our_wndproc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);//������Ϣ����
private:
	HWND GetGameWindow();
	CString MyGetClassName(HWND hwnd);
	void subclass_game_wndproc();//���໯���ڹ��̺���
	void un_subclass_game_wndproc();	//ж�����໯���ڹ���
};