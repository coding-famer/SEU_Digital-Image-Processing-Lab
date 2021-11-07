// ImgWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Geo_Lab1.h"
#include "ImgWnd.h"
#include "atlimage.h"
#include"TranslationDlg.h"
#include "GeometricTransform.h"
// CImgWnd

IMPLEMENT_DYNAMIC(CImgWnd, CWnd)

CImgWnd::CImgWnd(CWnd *pParentWnd, RECT rect, CImage* img, LPCTSTR pname)
:CWnd()
,CImg(img)
{
	CWnd::Create(AfxRegisterWndClass(NULL), pname, WS_CHILD | WS_CAPTION | WS_VISIBLE , rect, pParentWnd, 1);
}

CImgWnd::~CImgWnd()
{
	CImg = NULL;
}


BEGIN_MESSAGE_MAP(CImgWnd, CWnd)
	ON_WM_PAINT()
	//ON_COMMAND(ID_WND_TRANSLATION, &CImgWnd::OnWndTranslation)
END_MESSAGE_MAP()



// CImgWnd ��Ϣ�������




void CImgWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()

	if(CImg!=NULL)
	{
		CImg->Draw(dc,0,0);
	}
}



