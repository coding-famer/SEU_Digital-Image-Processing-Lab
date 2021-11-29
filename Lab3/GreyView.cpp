
// GreyView.cpp : CGreyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGreyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ShowLung, &CGreyView::OnShowlung)
	ON_COMMAND(ID_showknee, &CGreyView::Onshowknee)
END_MESSAGE_MAP()

// CGreyView 构造/析构

CGreyView::CGreyView()
	:mpImgWnd(NULL)
	,SrcImgWnd(NULL)
	,CImg()
{
	// TODO: 在此处添加构造代码
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGreyView 绘制

void CGreyView::OnDraw(CDC* /*pDC*/)
{
	CGreyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGreyView 打印


void CGreyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGreyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGreyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGreyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CGreyView 诊断

#ifdef _DEBUG
void CGreyView::AssertValid() const
{
	CView::AssertValid();
}

void CGreyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGreyDoc* CGreyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGreyDoc)));
	return (CGreyDoc*)m_pDocument;
}
#endif //_DEBUG





void CGreyView::OnShowlung()
{
	// TODO: 在此添加命令处理程序代码
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

		//方便测试用
		x=2048;
		w=4096;
		//创建图像需设置调色板
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
	// TODO: 在此添加命令处理程序代码
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

		//方便测试用
		x=250;
		w=500;
		//创建图像需设置调色板
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


