// TabB.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MsLong.h"
#include "TabB.h"
#include "afxdialogex.h"
#include "MsFileUtil.h"

extern CFileUtil* fileUtil;
// CTabB �Ի���

IMPLEMENT_DYNAMIC(CTabB, CDialogEx)

CTabB::CTabB(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CTabB::~CTabB()
{
}

void CTabB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_B, m_list_b);
}

BOOL CTabB::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/************************************************************************/
	/* CListCtrl��������                                               */
	/************************************************************************/
	m_list_b.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_MULTIWORKAREAS | LVS_EX_INFOTIP | LVS_EX_LABELTIP | LVS_EX_FLATSB);//��������ƶ��������ʾȫ������
	m_list_b.InsertColumn(0, _T("���"), NULL, 60, -1);
	m_list_b.InsertColumn(1, _T("�˺�"), NULL, 200, -1);
	m_list_b.InsertColumn(2, _T("����"), NULL, 200, -1);
	m_list_b.InsertColumn(3, _T("����"), NULL, 150, -1);
	m_list_b.InsertColumn(3, _T("����"), NULL, 150, -1);
	m_list_b.InsertColumn(4, _T("��ɫ"), NULL, 100, -1);
	m_list_b.InsertColumn(5, _T("Ĭ�Ͻű�"), NULL, 100, -1);

	CString GamePath = fileUtil->GetKV_ToFileGamePath();
	GetDlgItem(IDC_EDIT_B_1)->SetWindowTextW(GamePath);

	vector<CString> server = fileUtil->GetBigServer();
	for (auto ServerName : server)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_B_2))->AddString(ServerName);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_B_2))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("@changyou.com"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("@game.sohu.com"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("@Sohu.com"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("@chinaren.com"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("@sogou.com"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("@17173.com"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("�ֻ������¼"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("���������˺ź�׺"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->AddString(_T("��һ����ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->AddString(_T("�ڶ�����ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->AddString(_T("��������ɫ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->SetCurSel(0);
	this->updateServer();
	return TRUE;
}

void CTabB::updateServer()
{
	((CComboBox*)GetDlgItem(IDC_COMBO_B_3))->ResetContent();
	CString serverName;
	((CComboBox*)GetDlgItem(IDC_COMBO_B_2))->GetWindowTextW(serverName);
	auto AllName = fileUtil->GetSmallServer(serverName);
	for (auto Name : AllName)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_B_3))->AddString(Name);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_B_3))->SetCurSel(0);
}


BEGIN_MESSAGE_MAP(CTabB, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_B, &CTabB::OnNMRClickListB)
	ON_BN_CLICKED(IDC_BTN_B_1, &CTabB::OnBnClickedBtnB1)
	ON_BN_CLICKED(IDC_BTN_B_3, &CTabB::OnBnClickedBtnB3)
	ON_BN_CLICKED(IDC_BTN_B_2, &CTabB::OnBnClickedBtnB2)
	ON_CBN_SELCHANGE(IDC_COMBO_B_2, &CTabB::OnCbnSelchangeComboB2)
END_MESSAGE_MAP()


// CTabB ��Ϣ�������


void CTabB::OnNMRClickListB(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	//���ȵõ������λ��
	POSITION pos = m_list_b.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}

	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_MENU3);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}


void CTabB::OnBnClickedBtnB1()
{
	CString str = fileUtil->GetFileDirDlg();
	if (!str.IsEmpty())
	{
		GetDlgItem(IDC_EDIT_B_1)->SetWindowText(str);//��·�����õ��༭����
		fileUtil->SaveGamePath(str);
	}
}


void CTabB::OnBnClickedBtnB3()
{
	// �޸��˺�
}


void CTabB::OnBnClickedBtnB2()
{
	// �����˺�
	CString strText2, strText3, strText4, strComb1, strComb2, strComb3, strComb4;

	GetDlgItem(IDC_EDIT_B_2)->GetWindowText(strText2);//�˺�
	GetDlgItem(IDC_EDIT_B_3)->GetWindowText(strText3);//����
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->GetWindowText(strComb1);//��׺
	GetDlgItem(IDC_EDIT_B_4)->GetWindowText(strText4);//������׺
	((CComboBox*)GetDlgItem(IDC_COMBO_B_2))->GetWindowText(strComb2);//����
	((CComboBox*)GetDlgItem(IDC_COMBO_B_3))->GetWindowText(strComb3);//����
	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->GetWindowText(strComb4);//��ɫ

	if (strComb4 == _T("��һ����ɫ"))
		strComb4 = "0";
	else if (strComb4 == _T("�ڶ�����ɫ"))
		strComb4 = "1";
	else if (strComb4 == _T("��������ɫ"))
		strComb4 = _T("2");

	if (strText2.IsEmpty())
	{
		AfxMessageBox(_T("�˺Ų���Ϊ�գ���"));
	}else if (strText3.IsEmpty())
	{
		AfxMessageBox(_T("���벻��Ϊ�գ���"));
	}
	else if (strComb3.IsEmpty())
	{
		AfxMessageBox(_T("���Ų���Ϊ�գ���"));
	}
	else
	{
		CString CStrText;
		INT nCount = m_list_b.GetItemCount();
		//��ӵ������
		CStrText.Format(_T("%d"), nCount + 1);
		m_list_b.InsertItem(nCount, CStrText);//��
		m_list_b.SetItemText(nCount, 1, strText2);//�˺�
		m_list_b.SetItemText(nCount, 2, strText3);//����
		m_list_b.SetItemText(nCount, 3, strComb1);//��׺
		m_list_b.SetItemText(nCount, 4, strComb2);//����
		m_list_b.SetItemText(nCount, 5, strComb3);//����
		m_list_b.SetItemText(nCount, 6, strComb4);//��ɫ

		CStrText = "";
		for (INT i = 0; i < nCount; i++)
		{
			CString strItemText = m_list_b.GetItemText(i, 1);//�˺�
			CStrText = CStrText + strItemText + _T(",");
			strItemText = m_list_b.GetItemText(i, 2);//����
			CStrText = CStrText + strItemText + _T(",");
			strItemText = m_list_b.GetItemText(i, 3);//����
			CStrText = CStrText + strItemText + _T(",");
			strItemText = m_list_b.GetItemText(i, 4);//ѡ��ڼ�����ɫ
			CStrText = CStrText + strItemText + _T(",");
			strItemText = m_list_b.GetItemText(i, 5);//Ĭ�Ͻű�
			if (m_list_b.GetCheck(i))
				strItemText = _T("��");
			else
				strItemText = _T("��");
			CStrText = CStrText + strItemText + _T(",\n");
		}
		fileUtil->SaveAccountFile(CStrText);
	}
}


void CTabB::OnCbnSelchangeComboB2()
{
	this->updateServer();
}
