#pragma once


// CRotationDlg 对话框

class CRotationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRotationDlg)

public:
	CRotationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRotationDlg();

// 对话框数据
	enum { IDD = IDD_Rotation };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Rotationx;
};
