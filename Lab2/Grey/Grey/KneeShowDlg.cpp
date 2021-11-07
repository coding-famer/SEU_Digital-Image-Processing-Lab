// KneeShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Grey.h"
#include "KneeShowDlg.h"
#include "afxdialogex.h"


// CKneeShowDlg �Ի���

IMPLEMENT_DYNAMIC(CKneeShowDlg, CDialogEx)

CKneeShowDlg::CKneeShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKneeShowDlg::IDD, pParent)
{

	m_KneeWndw = 0;
	m_KneeWndx = 0;
}

CKneeShowDlg::~CKneeShowDlg()
{
}

void CKneeShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KneeWndw, m_KneeWndw);
	DDX_Text(pDX, IDC_KneeWndx, m_KneeWndx);
}


BEGIN_MESSAGE_MAP(CKneeShowDlg, CDialogEx)
END_MESSAGE_MAP()


// CKneeShowDlg ��Ϣ�������
