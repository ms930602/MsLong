#pragma once
#include "afxcmn.h"
#include <vector>
using namespace std;

// CTabA 对话框

class CTabA : public CDialogEx
{
	DECLARE_DYNAMIC(CTabA)

public:
	CTabA(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabA();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
private:
	void GameProcessActionADD(vector<DWORD> &vGamePID);
	void GameProcessActionDELETE(vector<DWORD> &vGamePID);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_a_list;
	afx_msg void OnNMRClickListA(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnA1();
	afx_msg void OnMenuInJect();
	afx_msg void OnMenuUnInJect();
};
