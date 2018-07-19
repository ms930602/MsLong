#pragma once


// CDlgTabA 对话框

class CDlgTabA : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabA)

public:
	CDlgTabA(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTabA();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TAB_A };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedTabABtn1();
};
