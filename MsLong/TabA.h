#pragma once
#include "afxcmn.h"
#include <vector>
using namespace std;

// CTabA �Ի���

class CTabA : public CDialogEx
{
	DECLARE_DYNAMIC(CTabA)

public:
	CTabA(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabA();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
private:
	void GameProcessActionADD(vector<DWORD> &vGamePID);
	void GameProcessActionDELETE(vector<DWORD> &vGamePID);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
