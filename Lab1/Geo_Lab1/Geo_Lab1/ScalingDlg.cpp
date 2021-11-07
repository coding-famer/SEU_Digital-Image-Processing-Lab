// ScalingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Geo_Lab1.h"
#include "ScalingDlg.h"
#include "afxdialogex.h"


// CScalingDlg 对话框

IMPLEMENT_DYNAMIC(CScalingDlg, CDialogEx)

CScalingDlg::CScalingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScalingDlg::IDD, pParent)
{

	m_Scalingx = 0;
	m_Scalingy = 0;
}

CScalingDlg::~CScalingDlg()
{
}

void CScalingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Scalingx, m_Scalingx);
	DDX_Text(pDX, IDC_Scalingy, m_Scalingy);
}


BEGIN_MESSAGE_MAP(CScalingDlg, CDialogEx)
END_MESSAGE_MAP()


// CScalingDlg 消息处理程序
