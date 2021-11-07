#pragma once


// CTranslationDlg 对话框

class CTranslationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTranslationDlg)

public:
	CTranslationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTranslationDlg();

// 对话框数据
	enum { IDD = IDD_TranslationDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Translationx;
	int m_Translationy;
	afx_msg void OnStnClickedStaticx();
};
