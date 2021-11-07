#pragma once


// CLungShowDlg 对话框

class CLungShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLungShowDlg)

public:
	CLungShowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLungShowDlg();

// 对话框数据
	enum { IDD = IDD_ShowLung };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_LungWndw;
	int m_LungWndx;
};
