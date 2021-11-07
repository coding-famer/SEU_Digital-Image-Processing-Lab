#pragma once
#include "atlimage.h"

// CImgWnd

class CImgWnd : public CWnd
{
	DECLARE_DYNAMIC(CImgWnd)

public:
	CImgWnd(CWnd *pParent, RECT rect, CImage* img, LPCTSTR pname = NULL, int xx = 0, int yy = 0);
	virtual ~CImgWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int x;
	int y;
	CImage* Cimage;
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


