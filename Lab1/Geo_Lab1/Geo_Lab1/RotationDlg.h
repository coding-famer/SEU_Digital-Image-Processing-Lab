#pragma once


// CRotationDlg �Ի���

class CRotationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRotationDlg)

public:
	CRotationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRotationDlg();

// �Ի�������
	enum { IDD = IDD_Rotation };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_Rotationx;
};
