#pragma once
#include "afxcmn.h"


// CTabB �Ի���

class CTabB : public CDialogEx
{
	DECLARE_DYNAMIC(CTabB)

public:
	CTabB(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabB();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	void updateServer();
public:
	CListCtrl m_list_b;
	afx_msg void OnNMRClickListB(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnB1();
	afx_msg void OnBnClickedBtnB3();
	afx_msg void OnBnClickedBtnB2();
	afx_msg void OnCbnSelchangeComboB2();
};
