// LungShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Grey.h"
#include "LungShowDlg.h"
#include "afxdialogex.h"


// CLungShowDlg �Ի���

IMPLEMENT_DYNAMIC(CLungShowDlg, CDialogEx)

CLungShowDlg::CLungShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLungShowDlg::IDD, pParent)
{

	m_LungWndw = 0;
	m_LungWndx = 0;
}

CLungShowDlg::~CLungShowDlg()
{
}

void CLungShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LungWndw, m_LungWndw);
	DDX_Text(pDX, IDC_LungWndx, m_LungWndx);
}


BEGIN_MESSAGE_MAP(CLungShowDlg, CDialogEx)
END_MESSAGE_MAP()


// CLungShowDlg ��Ϣ�������
