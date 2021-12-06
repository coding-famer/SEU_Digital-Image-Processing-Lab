#pragma once
class CSegmentation
{
public:
	CSegmentation(CImage* i);
	~CSegmentation(void);
	CImage* CSegImg;
	void Seg();
	void smoothing();
	void otsu(int r,int c,int x);
};

