#pragma once


// CScalingDlg 对话框

class CScalingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScalingDlg)

public:
	CScalingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScalingDlg();

// 对话框数据
	enum { IDD = IDD_Scaling };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Scalingx;
	int m_Scalingy;
};
