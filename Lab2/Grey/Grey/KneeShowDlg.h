#pragma once


// CKneeShowDlg �Ի���

class CKneeShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKneeShowDlg)

public:
	CKneeShowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CKneeShowDlg();

// �Ի�������
	enum { IDD = IDD_ShowKnee };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_KneeWndw;
	int m_KneeWndx;
};
