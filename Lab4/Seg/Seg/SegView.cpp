
// SegView.cpp : CSegView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSegView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ShowSrcImg, &CSegView::OnShowsrcimg)
	ON_COMMAND(ID_ShowSegImg, &CSegView::OnShowsegimg)
END_MESSAGE_MAP()

// CSegView ����/����

CSegView::CSegView()
	:SegImgWnd(NULL)
	,SrcImgWnd(NULL)
	,CImg()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSegView ����

void CSegView::OnDraw(CDC* /*pDC*/)
{
	CSegDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSegView ��ӡ


void CSegView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSegView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSegView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSegView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CSegView ���

#ifdef _DEBUG
void CSegView::AssertValid() const
{
	CView::AssertValid();
}

void CSegView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSegDoc* CSegView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSegDoc)));
	return (CSegDoc*)m_pDocument;
}
#endif //_DEBUG


// CSegView ��Ϣ�������


void CSegView::OnShowsrcimg()
{
	// TODO: �ڴ���������������
		// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
