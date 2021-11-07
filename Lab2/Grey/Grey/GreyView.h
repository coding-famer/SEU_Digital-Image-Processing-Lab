
// GreyView.h : CGreyView 类的接口
//

#pragma once

#include"ImgWnd.h"

class CGreyView : public CView
{
protected: // 仅从序列化创建
	CGreyView();
	DECLARE_DYNCREATE(CGreyView)
private:
	CImgWnd *mpImgWnd;
	CImage CImg;
// 特性
public:
	CGreyDoc* GetDocument() const;

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
	virtual ~CGreyView();
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
	afx_msg void OnShowlung();
	afx_msg void Onshowknee();
};

#ifndef _DEBUG  // GreyView.cpp 中的调试版本
inline CGreyDoc* CGreyView::GetDocument() const
   { return reinterpret_cast<CGreyDoc*>(m_pDocument); }
#endif

