#pragma once


// CKneeShowDlg 对话框

class CKneeShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKneeShowDlg)

public:
	CKneeShowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKneeShowDlg();

// 对话框数据
	enum { IDD = IDD_ShowKnee };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_KneeWndw;
	int m_KneeWndx;
};
