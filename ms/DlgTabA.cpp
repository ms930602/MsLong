// DlgTabA.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ms.h"
#include "DlgTabA.h"
#include "afxdialogex.h"
#include "Message.h"
#include "HPClient.h"
extern CMessage* pMsg;
extern CHPClient* pClient;
// CDlgTabA �Ի���

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


// CDlgTabA ��Ϣ�������


BOOL CDlgTabA::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

void CDlgTabA::OnBnClickedTabABtn1()
{
	CString str;
	GetDlgItem(IDC_EDIT_A_1)->GetWindowTextW(str);
	str.ReleaseBuffer();
	USES_CONVERSION;
	char * pFileName = T2A(str);

	if (pMsg->IsWindowShowEx(pFileName)) {
		TRACE("����");
	}
	else {
		TRACE("�ر���");
	}
	//pClient->Login_Thread();
}
