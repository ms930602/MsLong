// TabA.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MsLong.h"
#include "TabA.h"
#include "afxdialogex.h"
#include <vector>
#include "GameUtil.h"

using namespace std;

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

	vector<DWORD> vGamePID = GetGameProcessId(_T("Channel_18ũ��.exe"));
	CString strPID;
	for (auto id : vGamePID)
	{
		strPID.Format(_T("%d"), id);
		m_a_list.InsertItem(0, strPID);
	}

	::SetTimer(m_hWnd, 1, 5000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


BEGIN_MESSAGE_MAP(CTabA, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_A, &CTabA::OnNMRClickListA)
	ON_WM_PAINT()
	ON_WM_TIMER()
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
		vector<DWORD> vGamePID = GetGameProcessId(_T("Channel_18ũ��.exe"));

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
	InJectDll(pID, _T("ms.dll"));
}

void CTabA::OnMenuUnInJect()
{
}
