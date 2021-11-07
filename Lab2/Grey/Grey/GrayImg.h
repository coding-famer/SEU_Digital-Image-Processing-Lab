#pragma once
class CGrayImg
{
public:
	CGrayImg(DWORD h,DWORD w,WORD* i, CImage* ii);
	~CGrayImg(void);
	DWORD height;
	DWORD width;
	WORD* img;
	WORD* transimg;
	void TransintoCImage();
	void GrayMapping(int x, int w);
	CImage* CImg;
};

