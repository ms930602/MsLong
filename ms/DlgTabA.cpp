// DlgTabA.cpp : 实现文件
//

#include "stdafx.h"
#include "ms.h"
#include "DlgTabA.h"
#include "afxdialogex.h"
#include "Message.h"

extern CMessage* pMsg;
// CDlgTabA 对话框

IMPLEMENT_DYNAMIC(CDlgTabA, CDialogEx)

CDlgTabA::CDlgTabA(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_TAB_A, pParent)
{

}

CDlgTabA::~CDlgTabA()
{
}

void CDlgTabA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTabA, CDialogEx)
	ON_BN_CLICKED(IDC_TAB_A_BTN_1, &CDlgTabA::OnBnClickedTabABtn1)
END_MESSAGE_MAP()


// CDlgTabA 消息处理程序


BOOL CDlgTabA::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

void CDlgTabA::OnBnClickedTabABtn1()
{
	// TODO: 在此添加控件通知处理程序代码
}
