#pragma once
class CEnhance
{
public:
	CEnhance(DWORD h, DWORD w, WORD* i);
	~CEnhance(void);
	DWORD height;
	DWORD width;
	WORD* img;
	WORD* Sharpimg;
	void Sharp(double f);
	void Smooth();
	void UnsharpMasking();
};

