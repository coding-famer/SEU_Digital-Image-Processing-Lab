
// Geo_Lab1View.cpp : CGeo_Lab1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CGeo_Lab1View ����/����

CGeo_Lab1View::CGeo_Lab1View()
	:mpSrcImgWnd(NULL)
	,mpTransImgWnd(NULL)
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGeo_Lab1View ����

void CGeo_Lab1View::OnDraw(CDC* /*pDC*/)
{
	CGeo_Lab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGeo_Lab1View ��ӡ


void CGeo_Lab1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGeo_Lab1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGeo_Lab1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGeo_Lab1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CGeo_Lab1View ���

#ifdef _DEBUG
void CGeo_Lab1View::AssertValid() const
{
	CView::AssertValid();
}

void CGeo_Lab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeo_Lab1Doc* CGeo_Lab1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeo_Lab1Doc)));
	return (CGeo_Lab1Doc*)m_pDocument;
}
#endif //_DEBUG


// CGeo_Lab1View ��Ϣ�������


void CGeo_Lab1View::OnWndSrcwnd()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mpSrcImgWnd != NULL);
}




void CGeo_Lab1View::OnWndTranslation()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
