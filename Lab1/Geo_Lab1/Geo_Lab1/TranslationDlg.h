#pragma once


// CTranslationDlg �Ի���

class CTranslationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTranslationDlg)

public:
	CTranslationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTranslationDlg();

// �Ի�������
	enum { IDD = IDD_TranslationDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_Translationx;
	int m_Translationy;
	afx_msg void OnStnClickedStaticx();
};
