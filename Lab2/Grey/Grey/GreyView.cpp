
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
#include"GrayImg.h"
#include"ImgWnd.h"

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
	,CImg()
{
	// TODO: �ڴ˴���ӹ������
}

CGreyView::~CGreyView()
{
	if(mpImgWnd!=NULL)
		delete mpImgWnd;
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

	//for(int i=0;i<height[0];i++)
	//{
	//	for(int j=0;j<width[0];j++)
	//	{
	//		WORD tmp = img[i*width[0]+j];
	//		int a=1;
	//	}
	//}

	if(Dlg.DoModal() == IDOK)
	{
		int x,w;
		x = Dlg.m_LungWndx;
		w = Dlg.m_LungWndw;

		//����ͼ�������õ�ɫ��
		CImg.Destroy();
		CImg.Create(width[0], height[0],8, 0);
		CImage colortable;
		colortable.Load(_T("barbara.bmp"));
		RGBQUAD pal[256];  
        int nColors=colortable.GetMaxColorTableEntries(); 
		colortable.GetColorTable(0,nColors,pal);
		CImg.SetColorTable(0,nColors,pal);

		CGrayImg ShowImg(CImg.GetHeight(), CImg.GetWidth(), img, &CImg);

		ShowImg.GrayMapping(x,w);
		ShowImg.TransintoCImage();



		if(mpImgWnd==NULL)
		{
			mpImgWnd = new CImgWnd(this, CRect(100,100,1000,800), &CImg,  _T("Lung Image"),0,0);
		}
		else
		{
			mpImgWnd->Invalidate();
			mpImgWnd->UpdateWindow();
		}
	}
}


void CGreyView::Onshowknee()
{
	// TODO: �ڴ���������������
		CKneeShowDlg Dlg;
	FILE* fpknee;

	fpknee = fopen("knee.raw","rb");
	DWORD height[1];
	DWORD width[1];
	fread(width, 4, 1,fpknee);
	fread(height, 4, 1, fpknee);
	WORD* img = new WORD[height[0]*width[0]];
	fread(img, sizeof(WORD), height[0]*width[0],fpknee);

	if(Dlg.DoModal() == IDOK)
	{
		int x,w;
		x = Dlg.m_KneeWndx;
		w = Dlg.m_KneeWndw;

		//����ͼ�������õ�ɫ��
		CImg.Destroy();
		CImg.Create(width[0], height[0],8, 0);
		CImage colortable;
		colortable.Load(_T("barbara.bmp"));
		RGBQUAD pal[256];  
        int nColors=colortable.GetMaxColorTableEntries(); 
		colortable.GetColorTable(0,nColors,pal);
		CImg.SetColorTable(0,nColors,pal);

		CGrayImg ShowImg(CImg.GetHeight(), CImg.GetWidth(), img, &CImg);

		ShowImg.GrayMapping(x,w);
		ShowImg.TransintoCImage();


		if(mpImgWnd==NULL)
		{
			mpImgWnd = new CImgWnd(this, CRect(100,100,600,600), &CImg,  _T("Knee Image"));
		}
		else
		{
			mpImgWnd->Invalidate();
			mpImgWnd->UpdateWindow();
		}
	}
}
