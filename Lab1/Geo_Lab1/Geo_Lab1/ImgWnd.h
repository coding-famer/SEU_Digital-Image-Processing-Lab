#pragma once
#include "atlimage.h"

// CImgWnd

class CImgWnd : public CWnd
{
	DECLARE_DYNAMIC(CImgWnd)

public:
	CImgWnd(CWnd *pParent, RECT rect, CImage* img, LPCTSTR pname = NULL);
	virtual ~CImgWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CImage* CImg;
};


