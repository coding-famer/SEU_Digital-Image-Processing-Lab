
// GreyView.h : CGreyView ��Ľӿ�
//

#pragma once

#include"ImgWnd.h"

class CGreyView : public CView
{
protected: // �������л�����
	CGreyView();
	DECLARE_DYNCREATE(CGreyView)
private:
	CImgWnd *mpImgWnd;
	CImage CImg;
// ����
public:
	CGreyDoc* GetDocument() const;

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
	virtual ~CGreyView();
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
	afx_msg void OnShowlung();
	afx_msg void Onshowknee();
};

#ifndef _DEBUG  // GreyView.cpp �еĵ��԰汾
inline CGreyDoc* CGreyView::GetDocument() const
   { return reinterpret_cast<CGreyDoc*>(m_pDocument); }
#endif

