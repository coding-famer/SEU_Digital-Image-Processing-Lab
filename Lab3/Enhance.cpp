#include "StdAfx.h"
#include "Enhance.h"


CEnhance::CEnhance(DWORD h, DWORD w, WORD* i)
{
	height = h;
	width = w;
	img = i;
	Sharpimg = new WORD[h*w];
}


CEnhance::~CEnhance(void)
{
}

int core[25] = { -1,  -4,  -8,  -4, -1, 
				 -4, -16, -64, -16, -4, 
			   	 -8, -64, 512, -64, -8,
				 -4, -16, -64, -16, -4, 
				 -1,  -4,  -8,  -4, -1 };	

//int a=1;
//int b=4;
//int c=8;
//int d=16;
//int e=64;
//int f=512;
//int core[25] = { -a, -b, -c, -b, -a, 
//				 -b, -d, -e, -d, -4, 
//			   	 -c, -e,  f, -e, -c,
//				 -b, -d, -e, -d, -b, 
//				 -a, -b, -c, -b, -a };
/*double a = 0;
int core[9] = { -a,     -a, -a
				-a, -8*a+1, -a
				-a,     -a, -a};*/	
int coresum(int* core)
{
	int s = 0;
	for(int i=0;i<25;i++)
	{
		s+=core[i];
	}
	return s;

}

void CEnhance::Sharp(double ff)
{

//double a = ff;
//int core[9] = { -a,    -a, -a
//				-a, 8*a+1, -a
//				-a,    -a, -a};
	memcpy ( Sharpimg, img, width*height*sizeof(WORD) );
	for (int j=2;j<height-2;j++)
	{
		for (int i=2;i<width-2;i++)
		{
			int sum = 0;
			int p = 0;
			for ( int m=j-2; m<j+3; m++)
			{
				for (int n=i-2; n<i+3; n++)
				{
					sum += img [ m*width + n] * core[p++] ;
				}
			}
			sum /= coresum(core);
			if (sum > 4096)
				sum = 4096;
			if (sum <0)
				sum = 0;
			Sharpimg [ j*width+i ] = sum;
		}
	}
}

void CEnhance::Smooth()
{

}

void CEnhance::UnsharpMasking()
{

}