#pragma once


// CDlgTabB �Ի���

class CDlgTabB : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabB)

public:
	CDlgTabB(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTabB();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TAB_B };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
