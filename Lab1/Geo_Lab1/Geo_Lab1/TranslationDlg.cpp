// TranslationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Geo_Lab1.h"
#include "TranslationDlg.h"
#include "afxdialogex.h"


// CTranslationDlg 对话框

IMPLEMENT_DYNAMIC(CTranslationDlg, CDialogEx)

CTranslationDlg::CTranslationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTranslationDlg::IDD, pParent)
{

	m_Translationx = 0;
	m_Translationy = 0;
}

CTranslationDlg::~CTranslationDlg()
{
}

void CTranslationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Translationx, m_Translationx);
	DDX_Text(pDX, IDC_Translationy, m_Translationy);
}


BEGIN_MESSAGE_MAP(CTranslationDlg, CDialogEx)
END_MESSAGE_MAP()


// CTranslationDlg 消息处理程序
