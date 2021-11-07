
// Geo_Lab1View.cpp : CGeo_Lab1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Geo_Lab1.h"
#endif

#include "Geo_Lab1Doc.h"
#include "Geo_Lab1View.h"

#include "atlimage.h"
#include"ImgWnd.h"
#include"GeometricTransform.h"
#include"TranslationDlg.h"
#include"ScalingDlg.h"
#include"RotationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeo_Lab1View

IMPLEMENT_DYNCREATE(CGeo_Lab1View, CView)

BEGIN_MESSAGE_MAP(CGeo_Lab1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGeo_Lab1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_WND_SRCWND, &CGeo_Lab1View::OnWndSrcwnd)
	ON_UPDATE_COMMAND_UI(ID_WND_SRCWND, &CGeo_Lab1View::OnUpdateWndSrcwnd)
	ON_COMMAND(ID_WND_TRANSLATION, &CGeo_Lab1View::OnWndTranslation)
	ON_COMMAND(ID_WND_SCALING, &CGeo_Lab1View::OnWndScaling)
	ON_COMMAND(ID_WND_ROTATION, &CGeo_Lab1View::OnWndRotation)
END_MESSAGE_MAP()

// CGeo_Lab1View 构造/析构

CGeo_Lab1View::CGeo_Lab1View()
	:mpSrcImgWnd(NULL)
	,mpTransImgWnd(NULL)
{
	// TODO: 在此处添加构造代码
	CString path = _T("barbara.bmp");
	CSrcImg.Load(path);
	int nHeight = CSrcImg.GetHeight();
	int nWidth = CSrcImg.GetWidth();
	int nPitch = CSrcImg.GetPitch();
	int nBPP = CSrcImg.GetBPP();
	//CWndImg.Create(nWidth, nHeight, nBPP);
	CWndImg.Load(path);
}

CGeo_Lab1View::~CGeo_Lab1View()
{
	if(mpSrcImgWnd != NULL)
		delete mpSrcImgWnd;
}

BOOL CGeo_Lab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGeo_Lab1View 绘制

void CGeo_Lab1View::OnDraw(CDC* /*pDC*/)
{
	CGeo_Lab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGeo_Lab1View 打印


void CGeo_Lab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGeo_Lab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGeo_Lab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGeo_Lab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGeo_Lab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGeo_Lab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGeo_Lab1View 诊断

#ifdef _DEBUG
void CGeo_Lab1View::AssertValid() const
{
	CView::AssertValid();
}

void CGeo_Lab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeo_Lab1Doc* CGeo_Lab1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeo_Lab1Doc)));
	return (CGeo_Lab1Doc*)m_pDocument;
}
#endif //_DEBUG


// CGeo_Lab1View 消息处理程序


void CGeo_Lab1View::OnWndSrcwnd()
{
	// TODO: 在此添加命令处理程序代码
	if(mpSrcImgWnd == NULL)
	{
		mpSrcImgWnd = new CImgWnd(this, CRect(100,100,500,500), &CSrcImg, _T("Source Image"));
		//mpSrcImgWnd->CImg = CSrcImg;
	}
	else
	{
		delete mpSrcImgWnd;
		mpSrcImgWnd = NULL;
	}
}


void CGeo_Lab1View::OnUpdateWndSrcwnd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mpSrcImgWnd != NULL);
}




void CGeo_Lab1View::OnWndTranslation()
{
	// TODO: 在此添加命令处理程序代码
	CTranslationDlg Dlg;
	int x=0,y=0;
	if(Dlg.DoModal() == IDOK)
	{
		x=Dlg.m_Translationx;
		y=Dlg.m_Translationy;

		GeometricTransform gf(&CSrcImg,&CWndImg);
		gf.Translation(x,y);
		
		if(mpTransImgWnd==NULL)
		{
			mpTransImgWnd = new CImgWnd(this, CRect(600,100,1000,500), &CWndImg, _T("Translation Image"));
		}
		else
		{
			mpTransImgWnd->Invalidate();
			mpTransImgWnd->UpdateWindow();
		}
	}

}





void CGeo_Lab1View::OnWndScaling()
{
	// TODO: 在此添加命令处理程序代码
	CScalingDlg Dlg;
	int x=0,y=0;
	if(Dlg.DoModal() == IDOK)
	{
		x = Dlg.m_Scalingx;
		y = Dlg.m_Scalingy;

		GeometricTransform gf(&CSrcImg,&CWndImg);
		gf.Scaling(x,y);
		
		if(mpTransImgWnd==NULL)
		{
			mpTransImgWnd = new CImgWnd(this, CRect(600,100,1000,500), &CWndImg, _T("Translation Image"));
		}
		else
		{
			mpTransImgWnd->Invalidate();
			mpTransImgWnd->UpdateWindow();
		}
	}
}


void CGeo_Lab1View::OnWndRotation()
{
	// TODO: 在此添加命令处理程序代码
	CRotationDlg Dlg;
	int x=0,y=0;
	if(Dlg.DoModal() == IDOK)
	{
		x = Dlg.m_Rotationx;

		GeometricTransform gf(&CSrcImg,&CWndImg);
		gf.Rotation(x);
		
		if(mpTransImgWnd==NULL)
		{
			mpTransImgWnd = new CImgWnd(this, CRect(600,100,1000,500), &CWndImg, _T("Translation Image"));
		}
		else
		{
			mpTransImgWnd->Invalidate();
			mpTransImgWnd->UpdateWindow();
		}
		if(x == 30)
		{
			LPCTSTR savepath = _T("Rotation30.bmp");
			CWndImg.Save(savepath);
		}
	}
}
