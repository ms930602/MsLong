#pragma once


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
};
