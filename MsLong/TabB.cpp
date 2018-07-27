// TabB.cpp : 实现文件
//

#include "stdafx.h"
#include "MsLong.h"
#include "TabB.h"
#include "afxdialogex.h"
#include "MsFileUtil.h"

extern CFileUtil* fileUtil;
// CTabB 对话框

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
	/* CListCtrl设置类型                                               */
	/************************************************************************/
	m_list_b.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_EX_MULTIWORKAREAS | LVS_EX_INFOTIP | LVS_EX_LABELTIP | LVS_EX_FLATSB);//加上鼠标移动到表格显示全部文字
	m_list_b.InsertColumn(0, _T("序号"), NULL, 60, -1);
	m_list_b.InsertColumn(1, _T("账号"), NULL, 200, -1);
	m_list_b.InsertColumn(2, _T("密码"), NULL, 200, -1);
	m_list_b.InsertColumn(3, _T("大区"), NULL, 150, -1);
	m_list_b.InsertColumn(3, _T("服号"), NULL, 150, -1);
	m_list_b.InsertColumn(4, _T("角色"), NULL, 100, -1);
	m_list_b.InsertColumn(5, _T("默认脚本"), NULL, 100, -1);

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
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("手机号码登录"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->AddString(_T("输入其他账号后缀"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->AddString(_T("第一个角色"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->AddString(_T("第二个角色"));
	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->AddString(_T("第三个角色"));
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


// CTabB 消息处理程序


void CTabB::OnNMRClickListB(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//首先得到点击的位置
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
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);
}


void CTabB::OnBnClickedBtnB1()
{
	CString str = fileUtil->GetFileDirDlg();
	if (!str.IsEmpty())
	{
		GetDlgItem(IDC_EDIT_B_1)->SetWindowText(str);//将路径设置到编辑框中
		fileUtil->SaveGamePath(str);
	}
}


void CTabB::OnBnClickedBtnB3()
{
	// 修改账号
}


void CTabB::OnBnClickedBtnB2()
{
	// 新增账号
	CString strText2, strText3, strText4, strComb1, strComb2, strComb3, strComb4;

	GetDlgItem(IDC_EDIT_B_2)->GetWindowText(strText2);//账号
	GetDlgItem(IDC_EDIT_B_3)->GetWindowText(strText3);//密码
	((CComboBox*)GetDlgItem(IDC_COMBO_B_1))->GetWindowText(strComb1);//后缀
	GetDlgItem(IDC_EDIT_B_4)->GetWindowText(strText4);//其他后缀
	((CComboBox*)GetDlgItem(IDC_COMBO_B_2))->GetWindowText(strComb2);//大区
	((CComboBox*)GetDlgItem(IDC_COMBO_B_3))->GetWindowText(strComb3);//服号
	((CComboBox*)GetDlgItem(IDC_COMBO_B_4))->GetWindowText(strComb4);//角色

	if (strComb4 == _T("第一个角色"))
		strComb4 = "0";
	else if (strComb4 == _T("第二个角色"))
		strComb4 = "1";
	else if (strComb4 == _T("第三个角色"))
		strComb4 = _T("2");

	if (strText2.IsEmpty())
	{
		AfxMessageBox(_T("账号不能为空！！"));
	}else if (strText3.IsEmpty())
	{
		AfxMessageBox(_T("密码不能为空！！"));
	}
	else if (strComb3.IsEmpty())
	{
		AfxMessageBox(_T("服号不能为空！！"));
	}
	else
	{
		CString CStrText;
		INT nCount = m_list_b.GetItemCount();
		//添加到表格中
		CStrText.Format(_T("%d"), nCount + 1);
		m_list_b.InsertItem(nCount, CStrText);//序
		m_list_b.SetItemText(nCount, 1, strText2);//账号
		m_list_b.SetItemText(nCount, 2, strText3);//密码
		m_list_b.SetItemText(nCount, 3, strComb1);//后缀
		m_list_b.SetItemText(nCount, 4, strComb2);//大区
		m_list_b.SetItemText(nCount, 5, strComb3);//服号
		m_list_b.SetItemText(nCount, 6, strComb4);//角色

		CStrText = "";
		for (INT i = 0; i < nCount; i++)
		{
			CString strItemText = m_list_b.GetItemText(i, 1);//账号
			CStrText = CStrText + strItemText + _T(",");
			strItemText = m_list_b.GetItemText(i, 2);//密码
			CStrText = CStrText + strItemText + _T(",");
			strItemText = m_list_b.GetItemText(i, 3);//大区
			CStrText = CStrText + strItemText + _T(",");
			strItemText = m_list_b.GetItemText(i, 4);//选择第几个角色
			CStrText = CStrText + strItemText + _T(",");
			strItemText = m_list_b.GetItemText(i, 5);//默认脚本
			if (m_list_b.GetCheck(i))
				strItemText = _T("是");
			else
				strItemText = _T("否");
			CStrText = CStrText + strItemText + _T(",\n");
		}
		fileUtil->SaveAccountFile(CStrText);
	}
}


void CTabB::OnCbnSelchangeComboB2()
{
	this->updateServer();
}
