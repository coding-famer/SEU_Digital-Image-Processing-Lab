#include "StdAfx.h"
#include "GeometricTransform.h"
#include "atlimage.h"
#include <cmath>
#include <math.h>

#define PI 3.1415926535898

GeometricTransform::GeometricTransform(CImage* pt,CImage* ppt)
{
	CSrcImg = pt;
	CWndImg = ppt;
	LPBYTE Transptr;
	Transptr=(LPBYTE)CWndImg->GetBits();
	Height = CSrcImg->GetHeight();
	Width = CSrcImg->GetWidth();
	Pitch = CSrcImg->GetPitch();
	for(int ii = 0 ; ii < Height; ii++)  
	{  
		for(int jj = 0 ; jj < Width; jj++)  
		{  
			Transptr[jj+ii*Pitch] = 0;  
		}               
	} 

}


GeometricTransform::~GeometricTransform(void)
{
}


void GeometricTransform::Translation(double x, double y)
{
	AffTransform(1, 0, x, 0, 1, y);	
}

void GeometricTransform::Scaling(double sx, double sy)
{
	AffTransform(sx, 0, 0, 0, sy, 0);
}

void GeometricTransform::Rotation(int Theta)
{
	AffTransform(cos(Theta*PI/180), -sin(Theta*PI/180), Width*(1-cos(Theta*PI/180))/2+Height*sin(Theta*PI/180)/2, 
		sin(Theta*PI/180), cos(Theta*PI/180), -Width*sin(Theta*PI/180)/2+Height*(1-cos(Theta*PI/180))/2);	
}



void GeometricTransform::AffTransform(double a11, double a12, double a13, double a21, double a22, double a23)
{
	LPBYTE Srcptr;
	LPBYTE Transptr;

	Srcptr=(LPBYTE)CSrcImg->GetBits();
    Transptr=(LPBYTE)CWndImg->GetBits();


	for(int i = 0 ; i < Height; i++)  
	{  
		for(int j = 0 ; j < Width; j++)  
		{  
			double xx = (a22*j-a12*i-a13*a22+a12*a23)/(a11*a22-a12*a21);
			double yy = (a11*i-a21*j-a23*a11+a13*a21)/(a11*a22-a12*a21);
			if(xx>=0&&yy>=0&&xx<Width&&yy<Height)
			{
				int yp = int(floor(xx)+floor(yy)*Pitch);
				BYTE x00 = Srcptr[int(floor(xx)+floor(yy)*Pitch)];
				BYTE x10 = Srcptr[int(floor(xx)+ceil(yy)*Pitch)];
				BYTE x01 = Srcptr[int(ceil(xx)+floor(yy)*Pitch)];
				BYTE x11 = Srcptr[int(ceil(xx)+ceil(yy)*Pitch)];
				Transptr[j+i*Pitch]=BiInter(x00,x10,x01,x11,xx-floor(xx),yy-floor(yy));
			}
		}  
	} 
}

BYTE GeometricTransform::BiInter(BYTE x00, BYTE x10, BYTE x01, BYTE x11, double r1, double r2)
{
	//BYTE m = x00 + r1*(x10-x00);
	//BYTE n = x01 + r1*(x11-x01);
	//return m + r2*(n-m);
	double m = x00 + r2*(x10-x00);
	double n = x01 + r2*(x11-x01);
	return BYTE(m + r1*(n-m));
}