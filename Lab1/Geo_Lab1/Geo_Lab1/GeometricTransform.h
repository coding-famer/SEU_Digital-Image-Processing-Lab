#pragma once
#include "atlimage.h"
class GeometricTransform
{
public:
	GeometricTransform(CImage* pt = NULL,CImage* ppt = NULL);
	~GeometricTransform(void);
private:
	CImage* CSrcImg;
	CImage* CWndImg;
	int Height;
	int Width;
	int Pitch;
public:
	void Translation(double x, double y);
	void Scaling(double sx, double sy);
	void Rotation(int Theta);
	void AffTransform(double a11, double a12, double a13, double a21, double a22, double a23);
	BYTE BiInter(BYTE x00, BYTE x10, BYTE x01, BYTE x11, double r1, double r2);
};

