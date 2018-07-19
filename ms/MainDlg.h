#pragma once
#include "afxcmn.h"
#include "DlgTabA.h"
#include "DlgTabB.h"

#define WM_MY_MESSAGE (WM_USER+200)
#define WM_MYSTYLEEX_MESSAGE (WM_USER+201)
// CMainDlg �Ի���

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnMyStyleMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	CTabCtrl m_Tab;
	int m_CurSelTab;
	CDlgTabA m_pageA;
	CDlgTabB m_pageB; 
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
};
