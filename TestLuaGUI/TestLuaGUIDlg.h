
// TestLuaGUIDlg.h : 头文件
//

#pragma once
#include "ScriptSystem.h"

// CTestLuaGUIDlg 对话框
class CTestLuaGUIDlg : public CDialogEx
{
// 构造
public:
	CTestLuaGUIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTLUAGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CScriptSystem * pScriptSys;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton1();
};
