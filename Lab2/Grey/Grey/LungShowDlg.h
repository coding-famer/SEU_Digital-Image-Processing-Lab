#pragma once


// CLungShowDlg �Ի���

class CLungShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLungShowDlg)

public:
	CLungShowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLungShowDlg();

// �Ի�������
	enum { IDD = IDD_ShowLung };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_LungWndw;
	int m_LungWndx;
};
