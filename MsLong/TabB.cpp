// TabB.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MsLong.h"
#include "TabB.h"
#include "afxdialogex.h"


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
}

BOOL CTabB::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return 0;
}


BEGIN_MESSAGE_MAP(CTabB, CDialogEx)
END_MESSAGE_MAP()


// CTabB ��Ϣ�������
