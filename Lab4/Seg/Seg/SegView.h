
// SegView.h : CSegView 类的接口
//

#pragma once
#include"ImgWnd.h"

class CSegView : public CView
{
protected: // 仅从序列化创建
	CSegView();
	DECLARE_DYNCREATE(CSegView)
private:
	CImgWnd *SegImgWnd;
	CImgWnd *SrcImgWnd;
	CImage CImg;
	CImage SrcImg;

// 特性
public:
	CSegDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSegView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowsrcimg();
	afx_msg void OnShowsegimg();
};

#ifndef _DEBUG  // SegView.cpp 中的调试版本
inline CSegDoc* CSegView::GetDocument() const
   { return reinterpret_cast<CSegDoc*>(m_pDocument); }
#endif

