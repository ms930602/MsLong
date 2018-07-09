// TabA.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MsLong.h"
#include "TabA.h"
#include "afxdialogex.h"
#include <vector>
#include "GameUtil.h"
#include "HPServer.h"

using namespace std;

CString title = _T("Game.exe");
HWND g_TabAHwnd = nullptr;

extern CHPServer* MyServer;
// CTabA �Ի���

IMPLEMENT_DYNAMIC(CTabA, CDialogEx)

CTabA::CTabA(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
}

CTabA::~CTabA()
{
}

void CTabA::GameProcessActionADD(vector<DWORD> &vGamePID)
{
	for (DWORD id : vGamePID)
	{
		INT i = 0;
		while (i < m_a_list.GetItemCount())
		{
			CString strPID = m_a_list.GetItemText(i, 0);
			DWORD dwPID = _tcstoul(strPID, NULL, 10);
			 
			vector<DWORD>::iterator result = find(vGamePID.begin(), vGamePID.end(), dwPID);
			if (result == vGamePID.end()) {//�ҵ��˲�ɾ û�ҵ���ɾ��
				m_a_list.DeleteItem(i);
				--i;
			}
			++i;
		}
	}
}

void CTabA::GameProcessActionDELETE(vector<DWORD> &vGamePID)
{
	CString strPID;
	for (auto PID : vGamePID)
	{
		strPID.Format(_T("%d"), PID);
		LVFINDINFO info;
		info.flags = LVFI_PARTIAL | LVFI_STRING;
		info.psz = strPID;//�ַ�����	
		int nIndex = m_a_list.FindItem(&info, -1);
		if (nIndex == -1)	//����ָ����
			m_a_list.InsertItem(0, strPID);
	}
}

void CTabA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_A, m_a_list);
}

BOOL CTabA::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/************************************************************************/
	/* CListCtrl��������                                               */
	/************************************************************************/
	m_a_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_MULTIWORKAREAS | LVS_EX_INFOTIP | LVS_EX_LABELTIP | LVS_EX_FLATSB);//��������ƶ��������ʾȫ������
	m_a_list.InsertColumn(0, _T("��ϷID"), NULL, 60, -1);
	m_a_list.InsertColumn(1, _T("��¼�˺�"), NULL, 100, -1);
	m_a_list.InsertColumn(1, _T("�ű�"), NULL, 100, -1);
	m_a_list.InsertColumn(2, _T("״��"), NULL, 100, -1);
	m_a_list.InsertColumn(3, _T("����"), NULL, 50, -1);
	m_a_list.InsertColumn(4, _T("����"), NULL, 80, -1);
	m_a_list.InsertColumn(5, _T("����"), NULL, 60, -1);
	m_a_list.InsertColumn(6, _T("�ȼ�"), NULL, 50, -1);
	m_a_list.InsertColumn(7, _T("����"), NULL, 80, -1);
	m_a_list.InsertColumn(8, _T("��ͼ"), NULL, 80, -1);
	m_a_list.InsertColumn(9, _T("����"), NULL, 80, -1);
	m_a_list.InsertColumn(10, _T("״̬"), NULL, 80, -1);
	m_a_list.InsertColumn(11, _T("����"), NULL, 60, -1);
	m_a_list.InsertColumn(12, _T("��Ǯ"), NULL, 60, -1);
	m_a_list.InsertColumn(13, _T("Ԫ��"), NULL, 60, -1);
	CString title_ = title;
	vector<DWORD> vGamePID = GetGameProcessId(title_);
	CString strPID;
	for (auto id : vGamePID)
	{
		strPID.Format(_T("%d"), id);
		m_a_list.InsertItem(0, strPID);
	}

	g_TabAHwnd = m_hWnd;
	::SetTimer(m_hWnd, 1, 5000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


BEGIN_MESSAGE_MAP(CTabA, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_A, &CTabA::OnNMRClickListA)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_MESSAGE(WM_USER_״��, &CTabA::OnSocketMsg_ActionInfo)
	ON_MESSAGE(WM_USER_����������Ϣ, &CTabA::OnSocketMsg_RoleInfo)
	ON_BN_CLICKED(IDC_BTN_A_1, &CTabA::OnBnClickedBtnA1)
	ON_COMMAND(ID_32772, &CTabA::OnMenuInJect)
	ON_COMMAND(ID_32774, &CTabA::OnMenuUnInJect)
END_MESSAGE_MAP()


// CTabA ��Ϣ�������


void CTabA::OnNMRClickListA(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	//���ȵõ������λ��
	POSITION pos = m_a_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}

	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU1);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}


void CTabA::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


void CTabA::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1: {
		CString title_ = title;
		vector<DWORD> vGamePID = GetGameProcessId(title_);

		GameProcessActionDELETE(vGamePID);
		GameProcessActionADD(vGamePID);
		
	}
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CTabA::OnBnClickedBtnA1()
{
	
}

void CTabA::OnMenuInJect()
{
	//���ȵõ������λ��
	POSITION pos = m_a_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("��ѡ��һ���"), _T("��ʾ"), MB_ICONEXCLAMATION);
		return;
	}
	int size = m_a_list.GetSelectedCount();
	if (size > 1) {
		MessageBox(_T("һ��ֻ��ѡ��һ��"), _T("��ʾ"), MB_ICONEXCLAMATION);
	}
	//�õ��кţ�ͨ��POSITIONת��
	int index = m_a_list.GetNextSelectedItem(pos);
	CString pID = m_a_list.GetItemText(index, 0);
	CString* str = new CString;
	*str = pID;
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, &InJect_thread, (PVOID)str, 0, NULL));
}

void CTabA::OnMenuUnInJect()
{
	//���ȵõ������λ��
	POSITION pos = m_a_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("��ѡ��һ���"), _T("��ʾ"), MB_ICONEXCLAMATION);
		return;
	}
	int size = m_a_list.GetSelectedCount();
	if (size > 1) {
		MessageBox(_T("һ��ֻ��ѡ��һ��"), _T("��ʾ"), MB_ICONEXCLAMATION);
	}
	//�õ��кţ�ͨ��POSITIONת��
	int index = m_a_list.GetNextSelectedItem(pos);
	CString pID = m_a_list.GetItemText(index, 0);
	CString loginName = m_a_list.GetItemText(index, 1);
	SocketBind _SocketBind = { 0 };
	_SocketBind.dwGameID = _ttoi(pID);
	MyServer->SendUnInJect(_SocketBind);
}

LRESULT CTabA::OnSocketMsg_ActionInfo(WPARAM wparam, LPARAM lparam)
{
	SocketGameInfo* _Info = (SocketGameInfo*)lparam;
	SocketBind* pBind = (SocketBind*)wparam;

	if (pBind->dwGameID > 0)//����ID����
	{
		CString strPID;
		strPID.Format(_T("%d"), pBind->dwGameID);
		LVFINDINFO info;
		info.flags = LVFI_PARTIAL | LVFI_STRING;
		info.psz = strPID;//�ַ�����
		int  nIndex = m_a_list.FindItem(&info);//����ָ����
		if (nIndex == -1)
		{
			m_a_list.InsertItem(0, strPID);
		}
		INT nCount = m_a_list.GetItemCount();//�ʺ�����
		for (INT i = 0; i < nCount; i++)
		{
			CString strItemText = m_a_list.GetItemText(i, 0);//��
			if (strItemText == strPID)
			{
				m_a_list.SetItemText(i, 2, CString(_Info->_Message));//����
				break;
			}
		}
	}

	delete pBind;
	delete _Info;
	return 0;
}

LRESULT CTabA::OnSocketMsg_RoleInfo(WPARAM wparam, LPARAM lparam)
{
	SocketGameRoleInfo* _socketgameInfo = (SocketGameRoleInfo*)lparam;
	SocketBind* pBind = (SocketBind*)wparam;
	if (pBind->dwGameID > 0)//����ID����
	{
		CString strPID;
		strPID.Format(_T("%d"), pBind->dwGameID);
		LVFINDINFO info;
		info.flags = LVFI_PARTIAL | LVFI_STRING;
		info.psz = strPID;//�ַ�����
		int  nIndex = m_a_list.FindItem(&info);//����ָ����
		if (nIndex == -1)
		{
			m_a_list.InsertItem(0, strPID);
		}

		INT nCount = m_a_list.GetItemCount();//�ʺ�����
		CString temp;
		for (INT i = 0; i < nCount; i++)
		{
			CString strItemText = m_a_list.GetItemText(i, 0);//ID
			if (strItemText == strPID)
			{
				m_a_list.SetItemText(i, 4, CString(_socketgameInfo->RoleName));//����
				m_a_list.SetItemText(i, 5, GetRoleMenPai(_socketgameInfo->RoleMenPai));//����

				temp.Format(_T("%d"), _socketgameInfo->RoleLevel);
				m_a_list.SetItemText(i, 6, temp);//��
																				  //m_List2.SetItemText(i, 7, CString(_socketgameInfo->RoleName));//��
				m_a_list.SetItemText(i, 8, CString(_socketgameInfo->GameMap));//��ͼ
				temp.Format(_T("%d , %d"), _socketgameInfo->PointX, _socketgameInfo->PointY);
				m_a_list.SetItemText(i, 9,  temp);//����	
				m_a_list.SetItemText(i, 10, GetRoleState(_socketgameInfo->RoleStatus));//״̬
				
				temp.Format(_T("%d"), _socketgameInfo->BindGold);
				m_a_list.SetItemText(i, 11, temp);//����
				temp.Format(_T("%d"), _socketgameInfo->NoBindGold);
				m_a_list.SetItemText(i, 12, temp);//��Ǯ
				temp.Format(_T("%d"), _socketgameInfo->YuanBap);
				m_a_list.SetItemText(i, 13, temp);//Ԫ��
				break;
			}
		}
	}

	delete pBind;
	delete _socketgameInfo;

	return 0;
}