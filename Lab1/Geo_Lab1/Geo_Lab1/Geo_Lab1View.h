
// Geo_Lab1View.h : CGeo_Lab1View ��Ľӿ�
//

#pragma once

#include"ImgWnd.h"
#include "atlimage.h"

class CGeo_Lab1View : public CView
{
protected: // �������л�����
	CGeo_Lab1View();
	DECLARE_DYNCREATE(CGeo_Lab1View)
private:
	CImgWnd *mpSrcImgWnd;
	CImgWnd *mpTransImgWnd;
	CImage CSrcImg;
	CImage CWndImg;
// ����
public:
	CGeo_Lab1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGeo_Lab1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWndSrcwnd();
	afx_msg void OnUpdateWndSrcwnd(CCmdUI *pCmdUI);
	afx_msg void OnWndTranslation();
	afx_msg void OnWndScaling();
	afx_msg void OnWndRotation();
};

#ifndef _DEBUG  // Geo_Lab1View.cpp �еĵ��԰汾
inline CGeo_Lab1Doc* CGeo_Lab1View::GetDocument() const
   { return reinterpret_cast<CGeo_Lab1Doc*>(m_pDocument); }
#endif

