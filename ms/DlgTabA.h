#pragma once


// CDlgTabA �Ի���

class CDlgTabA : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabA)

public:
	CDlgTabA(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTabA();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TAB_A };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedTabABtn1();
};
