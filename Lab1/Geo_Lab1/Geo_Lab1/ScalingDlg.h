#pragma once


// CScalingDlg �Ի���

class CScalingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScalingDlg)

public:
	CScalingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScalingDlg();

// �Ի�������
	enum { IDD = IDD_Scaling };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_Scalingx;
	int m_Scalingy;
};
