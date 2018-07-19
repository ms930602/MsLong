#pragma once


// CDlgTabB 对话框

class CDlgTabB : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTabB)

public:
	CDlgTabB(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTabB();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TAB_B };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
