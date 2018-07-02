
// MsLongDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "TabA.h"
#include "TabB.h"

// CMsLongDlg �Ի���
class CMsLongDlg : public CDialogEx
{
// ����
public:
	CMsLongDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSLONG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNotifyMsg(WPARAM wparam, LPARAM lparam);
	NOTIFYICONDATA m_notify;  //ϵͳ������
	CTabCtrl m_tab;
	int m_CurSelTab;
	CTabA m_pageA;
	CTabB m_pageB;
	CDialog* pDialog[2];  //��������Ի������ָ��  
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
