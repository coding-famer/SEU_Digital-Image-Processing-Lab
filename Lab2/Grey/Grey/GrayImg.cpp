#include "StdAfx.h"
#include "GrayImg.h"

CGrayImg::CGrayImg(DWORD h,DWORD w,WORD* i, CImage* ii)
{
	height = h;
	width = w;
	img = i;
	transimg = i;
	CImg = ii;
}


CGrayImg::~CGrayImg(void)
{
}

void CGrayImg::TransintoCImage(void)
{	
	LPBYTE ptr;
	int p = CImg->GetPitch();
	//ptr = (LPBYTE)CImg->GetBits()+(p*(height-1));
	ptr = (LPBYTE)CImg->GetBits();


	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			BYTE tmp = (BYTE)transimg[i*width+j]/16;
			ptr[i*p+j]=(BYTE)(transimg[i*width+j]/16);
			int a = 0;
		}
	}

}

void CGrayImg::GrayMapping(int x, int w)
{
	for(int i=0;i<height*width;i++)
	{
		if(transimg[i]<x-w/2)
			transimg[i]=0;
		else if(transimg[i]>x+w/2)
			transimg[i]=4095;
		else
			transimg[i] = (WORD)(img[i]-(x-w/2))*4095/w;
	}
}
