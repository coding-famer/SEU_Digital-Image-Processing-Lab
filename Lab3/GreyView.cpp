
// GreyView.cpp : CGreyView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Grey.h"
#endif

#include "GreyDoc.h"
#include "GreyView.h"

#include"LungShowDlg.h"
#include"KneeShowDlg.h"
#include"AdjustDlg.h"
#include"GrayImg.h"
#include"ImgWnd.h"
#include"Enhance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGreyView

IMPLEMENT_DYNCREATE(CGreyView, CView)

BEGIN_MESSAGE_MAP(CGreyView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGreyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ShowLung, &CGreyView::OnShowlung)
	ON_COMMAND(ID_showknee, &CGreyView::Onshowknee)
END_MESSAGE_MAP()

// CGreyView ����/����

CGreyView::CGreyView()
	:mpImgWnd(NULL)
	,SrcImgWnd(NULL)
	,CImg()
{
	// TODO: �ڴ˴���ӹ������
}

CGreyView::~CGreyView()
{
	if(mpImgWnd!=NULL)
		delete mpImgWnd;
	if(SrcImgWnd!=NULL)
		delete SrcImgWnd;
}

BOOL CGreyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGreyView ����

void CGreyView::OnDraw(CDC* /*pDC*/)
{
	CGreyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGreyView ��ӡ


void CGreyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGreyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGreyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGreyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CGreyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGreyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGreyView ���

#ifdef _DEBUG
void CGreyView::AssertValid() const
{
	CView::AssertValid();
}

void CGreyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGreyDoc* CGreyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGreyDoc)));
	return (CGreyDoc*)m_pDocument;
}
#endif //_DEBUG





void CGreyView::OnShowlung()
{
	// TODO: �ڴ���������������
	CLungShowDlg Dlg;
	FILE* fplung;
	fplung = fopen("lung.raw","rb");
	fseek(fplung, 0, SEEK_SET);
	DWORD height[1];
	DWORD width[1];
	fread(width, 4, 1,fplung);
	fread(height, 4, 1, fplung);
	WORD* img = new WORD[height[0]*width[0]];
	int xx=fread(img, sizeof(WORD), height[0]*width[0],fplung);


	//if(Dlg.DoModal() == IDOK)
	//{
		int x,w;
		//x = Dlg.m_LungWndx;
		//w = Dlg.m_LungWndw;

		//���������
		x=2048;
		w=4096;
		//����ͼ�������õ�ɫ��
		SrcImg.Destroy();
		SrcImg.Create(width[0], height[0],8, 0);
		CImage colortable;
		colortable.Load(_T("barbara.bmp"));
		RGBQUAD pal[256];  
        int nColors=colortable.GetMaxColorTableEntries(); 
		colortable.GetColorTable(0,nColors,pal);
		SrcImg.SetColorTable(0,nColors,pal);
		CGrayImg ShowSrcImg(SrcImg.GetHeight(), SrcImg.GetWidth(), img, &SrcImg);

		ShowSrcImg.GrayMapping(x,w);
		ShowSrcImg.TransintoCImage();

		if(SrcImgWnd==NULL)
		{
			SrcImgWnd = new CImgWnd(this, CRect(900,0,1800,900), &SrcImg,  _T("Lung Image"),0,0);
		}
		else
		{
			SrcImgWnd->Invalidate();
			SrcImgWnd->UpdateWindow();
		}

		CImg.Destroy();
		CImg.Create(width[0], height[0],8, 0);
		CImg.SetColorTable(0,nColors,pal);

		CEnhance enhimg(height[0],width[0],img);
		enhimg.Sharp(0);
		CGrayImg ShowImg(CImg.GetHeight(), CImg.GetWidth(), enhimg.Sharpimg, &CImg);

		ShowImg.GrayMapping(x,w);
		ShowImg.TransintoCImage();



		if(mpImgWnd==NULL)
		{
			mpImgWnd = new CImgWnd(this, CRect(0,0,900,900), &CImg,  _T("Enhance Lung Image"),0,0);
		}
		else
		{
			mpImgWnd->Invalidate();
			mpImgWnd->UpdateWindow();
		}
		CAdjustDlg ADlg;
		while(ADlg.DoModal()!=IDOK)
		{
			int f = ADlg.m_e1;
			enhimg.Sharp(f*0.01);
			ShowImg.img = enhimg.Sharpimg;
			ShowImg.GrayMapping(x,w);
			ShowImg.TransintoCImage();
			mpImgWnd->Invalidate();
			mpImgWnd->UpdateWindow();
		}


	//}

}


void CGreyView::Onshowknee()
{
	// TODO: �ڴ���������������
		CKneeShowDlg Dlg;
	FILE* fpknee;

	fpknee = fopen("knee.raw","rb");
	fseek(fpknee, 0, SEEK_SET);
	DWORD height[1];
	DWORD width[1];
	fread(width, 4, 1,fpknee);
	fread(height, 4, 1, fpknee);
	WORD* img = new WORD[height[0]*width[0]];
	int xx=fread(img, sizeof(WORD), height[0]*width[0],fpknee);


	//if(Dlg.DoModal() == IDOK)
	//{
		int x,w;
		//x = Dlg.m_KmeeWndx;
		//w = Dlg.m_KneeWndw;

		//���������
		x=250;
		w=500;
		//����ͼ�������õ�ɫ��
		SrcImg.Destroy();
		SrcImg.Create(width[0], height[0],8, 0);
		CImage colortable;
		colortable.Load(_T("barbara.bmp"));
		RGBQUAD pal[256];  
        int nColors=colortable.GetMaxColorTableEntries(); 
		colortable.GetColorTable(0,nColors,pal);
		SrcImg.SetColorTable(0,nColors,pal);
		CGrayImg ShowSrcImg(SrcImg.GetHeight(), SrcImg.GetWidth(), img, &SrcImg);
		ShowSrcImg.GrayMapping(x,w);
		ShowSrcImg.TransintoCImage();

		if(SrcImgWnd==NULL)
		{
			SrcImgWnd = new CImgWnd(this, CRect(900,0,1800,900), &SrcImg,  _T("Knee Image"),0,0);
		}
		else
		{
			SrcImgWnd->Invalidate();
			SrcImgWnd->UpdateWindow();
		}

		CImg.Destroy();
		CImg.Create(width[0], height[0],8, 0);
		CImg.SetColorTable(0,nColors,pal);

		CEnhance enhimg(height[0],width[0],img);
		CGrayImg ShowImg(CImg.GetHeight(), CImg.GetWidth(), enhimg.img, &CImg);

		ShowImg.GrayMapping(x,w);
		ShowImg.TransintoCImage();



		if(mpImgWnd==NULL)
		{
			mpImgWnd = new CImgWnd(this, CRect(0,0,900,900), &CImg,  _T("Enhance Knee Image"),0,0);
		}
		else
		{
			mpImgWnd->Invalidate();
			mpImgWnd->UpdateWindow();
		}
		CAdjustDlg ADlg;
		while(ADlg.DoModal()!=IDOK)
		{
			int f = ADlg.m_e1;
			enhimg.Sharp(f*0.01);
			ShowImg.img = enhimg.Sharpimg;
			ShowImg.GrayMapping(x,w);
			ShowImg.TransintoCImage();
			mpImgWnd->Invalidate();
			mpImgWnd->UpdateWindow();
		}
	//}
}


