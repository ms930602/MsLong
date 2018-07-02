
// MsLongDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "TabA.h"
#include "TabB.h"

// CMsLongDlg 对话框
class CMsLongDlg : public CDialogEx
{
// 构造
public:
	CMsLongDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSLONG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNotifyMsg(WPARAM wparam, LPARAM lparam);
	NOTIFYICONDATA m_notify;  //系统托盘类
	CTabCtrl m_tab;
	int m_CurSelTab;
	CTabA m_pageA;
	CTabB m_pageB;
	CDialog* pDialog[2];  //用来保存对话框对象指针  
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
