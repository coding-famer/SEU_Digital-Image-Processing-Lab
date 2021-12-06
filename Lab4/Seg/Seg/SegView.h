
// SegView.h : CSegView ��Ľӿ�
//

#pragma once
#include"ImgWnd.h"

class CSegView : public CView
{
protected: // �������л�����
	CSegView();
	DECLARE_DYNCREATE(CSegView)
private:
	CImgWnd *SegImgWnd;
	CImgWnd *SrcImgWnd;
	CImage CImg;
	CImage SrcImg;

// ����
public:
	CSegDoc* GetDocument() const;

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
	virtual ~CSegView();
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
	afx_msg void OnShowsrcimg();
	afx_msg void OnShowsegimg();
};

#ifndef _DEBUG  // SegView.cpp �еĵ��԰汾
inline CSegDoc* CSegView::GetDocument() const
   { return reinterpret_cast<CSegDoc*>(m_pDocument); }
#endif

