// ImgWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "Grey.h"
#include "ImgWnd.h"
#include "atlimage.h"
// CImgWnd

IMPLEMENT_DYNAMIC(CImgWnd, CWnd)

CImgWnd::CImgWnd(CWnd *pParentWnd, RECT rect,CImage* img, LPCTSTR pname, int xx, int yy)
:CWnd()
,Cimage(img)
{
	x = xx;
	y = yy;
	CWnd::Create(AfxRegisterWndClass(NULL), pname, WS_CHILD | WS_CAPTION | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL, rect, pParentWnd, 1);
}

CImgWnd::~CImgWnd()
{

}


BEGIN_MESSAGE_MAP(CImgWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CImgWnd 消息处理程序




void CImgWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()


		
	if(Cimage!=NULL)
	{
		int succ = Cimage->Draw(dc,x,y);
	}
}







void CImgWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	static int oldpos = 0;
	int minpos = 0;
	int maxpos = 0;
	GetScrollRange(SB_HORZ, &minpos, &maxpos); 
	maxpos = GetScrollLimit(SB_HORZ);
	int curpos = GetScrollPos(SB_HORZ);
 
	switch (nSBCode)
	{
	case SB_LEFT:     
		curpos = minpos;
		break;
 
	case SB_RIGHT:      
		curpos = maxpos;
		break;
 
	case SB_ENDSCROLL:   
		break;
 
	case SB_LINELEFT:      
		if (curpos > minpos)
			curpos-=50;
		break;
 
	case SB_LINERIGHT:   
		if (curpos < maxpos)
			curpos+=50;
		break;
 
	case SB_PAGELEFT:    
		{
			SCROLLINFO   info;
			GetScrollInfo(SB_HORZ, &info, SIF_ALL);
 
			if (curpos > minpos)
				curpos = max(minpos, curpos - (int) info.nPage);
		}
		break;
 
	case SB_PAGERIGHT:      
		{
			SCROLLINFO   info;
			GetScrollInfo(SB_HORZ, &info, SIF_ALL);
 
			if (curpos < maxpos)
				curpos = min(maxpos, curpos + (int) info.nPage);
		}
		break;
 
	case SB_THUMBPOSITION: 
		curpos = nPos;     
		break;
 
	case SB_THUMBTRACK:   
		curpos = nPos;     
		break;
	}	
	SetScrollPos(SB_HORZ, curpos);
	x = -curpos;
	oldpos = curpos;
	Invalidate(TRUE);
    CWnd::OnHScroll(nSBCode, nPos, pScrollBar);

}


void CImgWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	static int oldpos = 0;
	int minpos = 0;
	int maxpos = 0;
	GetScrollRange(SB_VERT, &minpos, &maxpos); 
	maxpos = GetScrollLimit(SB_VERT);
	int curpos = GetScrollPos(SB_VERT);

	switch (nSBCode)
	{
	case SB_TOP:      
		curpos = minpos;
		break;
 
	case SB_BOTTOM:      
		curpos = maxpos;
		break;
 
	case SB_ENDSCROLL:   
		break;
 
	case SB_LINEUP:      
		if (curpos > minpos)
			curpos-=50;
		break;
 
	case SB_LINEDOWN:   
		if (curpos < maxpos)
			curpos+=50;
		break;
 
	case SB_PAGEUP:    
		{
			SCROLLINFO   info;
			GetScrollInfo(SB_VERT, &info, SIF_ALL);
 
			if (curpos > minpos)
				curpos = max(minpos, curpos - (int) info.nPage);
		}
		break;
 
	case SB_PAGEDOWN:      
		{
			SCROLLINFO   info;
			GetScrollInfo(SB_VERT, &info, SIF_ALL);
 
			if (curpos < maxpos)
				curpos = min(maxpos, curpos + (int) info.nPage);
		}
		break;
 
	case SB_THUMBPOSITION: 
		curpos = nPos;     
		break;
 
	case SB_THUMBTRACK:   
		curpos = nPos;     
		break;
	}
 
	SetScrollPos(SB_VERT, curpos);
	y = -curpos;
	oldpos = curpos;
	Invalidate(TRUE);
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}





void CImgWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	int xoldpos = 0;
	int yoldpos = 0;
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = Cimage->GetWidth();
	si.nPage = cx;
	SetScrollInfo(SB_HORZ,&si,TRUE);
	si.nMax = Cimage->GetHeight();
	si.nPage = cy;
	SetScrollInfo(SB_VERT,&si,TRUE);
 
	int curxpos = GetScrollPos(SB_HORZ);
	int curypos = GetScrollPos(SB_VERT);
	
	xoldpos = curxpos;
	yoldpos = curypos;
 
	Invalidate(TRUE);
}
