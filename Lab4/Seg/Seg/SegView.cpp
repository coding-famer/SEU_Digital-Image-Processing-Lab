
// SegView.cpp : CSegView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Seg.h"
#endif

#include "SegDoc.h"
#include "SegView.h"
#include"ImgWnd.h"
#include"Segmentation.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSegView

IMPLEMENT_DYNCREATE(CSegView, CView)

BEGIN_MESSAGE_MAP(CSegView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSegView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ShowSrcImg, &CSegView::OnShowsrcimg)
	ON_COMMAND(ID_ShowSegImg, &CSegView::OnShowsegimg)
END_MESSAGE_MAP()

// CSegView 构造/析构

CSegView::CSegView()
	:SegImgWnd(NULL)
	,SrcImgWnd(NULL)
	,CImg()
{
	// TODO: 在此处添加构造代码
	CString path = _T("seed.bmp");
	SrcImg.Load(path);
	CImg.Load(path);
}

CSegView::~CSegView()
{
	if(SegImgWnd!=NULL)
		delete SegImgWnd;
	if(SrcImgWnd!=NULL)
		delete SrcImgWnd;
}

BOOL CSegView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSegView 绘制

void CSegView::OnDraw(CDC* /*pDC*/)
{
	CSegDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CSegView 打印


void CSegView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSegView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSegView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSegView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CSegView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSegView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSegView 诊断

#ifdef _DEBUG
void CSegView::AssertValid() const
{
	CView::AssertValid();
}

void CSegView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSegDoc* CSegView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSegDoc)));
	return (CSegDoc*)m_pDocument;
}
#endif //_DEBUG


// CSegView 消息处理程序


void CSegView::OnShowsrcimg()
{
	// TODO: 在此添加命令处理程序代码
		// TODO: 在此添加命令处理程序代码
	if(SrcImgWnd == NULL)
	{
		SrcImgWnd = new CImgWnd(this, CRect(100,100,600,600), &SrcImg, _T("Source Image"));
		//mpSrcImgWnd->CImg = CSrcImg;
	}
	else
	{
		delete SrcImgWnd;
		SrcImgWnd = NULL;
	}
}


void CSegView::OnShowsegimg()
{
	// TODO: 在此添加命令处理程序代码
	CSegmentation CSeg(&CImg);
	CSeg.Seg();
	if(SegImgWnd == NULL)
	{
		SegImgWnd = new CImgWnd(this, CRect(700,100,1200,600), &CImg, _T("Seg Image"));
	}
	else
	{
		delete SegImgWnd;
		SegImgWnd = NULL;
	}
	LPCTSTR savepath = _T("SegSeed.bmp");
	CImg.Save(savepath);
}
