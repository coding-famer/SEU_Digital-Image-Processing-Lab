// RotationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Geo_Lab1.h"
#include "RotationDlg.h"
#include "afxdialogex.h"


// CRotationDlg 对话框

IMPLEMENT_DYNAMIC(CRotationDlg, CDialogEx)

CRotationDlg::CRotationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRotationDlg::IDD, pParent)
{

	m_Rotationx = 0;
}

CRotationDlg::~CRotationDlg()
{
}

void CRotationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Rotationx, m_Rotationx);
}


BEGIN_MESSAGE_MAP(CRotationDlg, CDialogEx)
END_MESSAGE_MAP()


// CRotationDlg 消息处理程序
