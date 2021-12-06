#include "StdAfx.h"
#include "Segmentation.h"


CSegmentation::CSegmentation(CImage* i)
{
	CSegImg = i;
}


CSegmentation::~CSegmentation(void)
{
}

void CSegmentation::Seg()
{
	smoothing();
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
			otsu(i*79,j*79,79);
	}
}


void CSegmentation::smoothing()
{
int core[9] = { 1, 1, 1,
				1, 1, 1,
				1, 1, 1};
	LPBYTE ptr;
	int p = CSegImg->GetPitch();
	ptr = (LPBYTE)CSegImg->GetBits();
	int height = CSegImg->GetHeight();
	int width = CSegImg->GetWidth();
	for (int j=1;j<height-1;j++)
	{
		for (int i=1;i<width-1;i++)
		{
			int sum = 0;
			int pr = 0;
			for ( int m=j-1; m<j+2; m++)
			{
				for (int n=i-1; n<i+2; n++)
				{
					/*sum += ptr [ m*width + n] * core[pr++] ;*/
					sum += ptr [ m*p + n] * core[pr++] ;
				}
			}
			sum/=8;
			if (sum > 255)
				sum = 255;
			if (sum <0)
				sum = 0;
			ptr [ j*p+i ] = sum;
		}
	}
			for ( int m=0; m<height; m++)
			{
				for (int n=0; n<width; n++)
				{
					BYTE xx;
					xx = ptr [ m*p + n];
				}
			}
}

void CSegmentation::otsu(int r,int c,int x)
{
	int grayhis[256]; //灰度直方图
	int thresigma[256];//存储各阈值的方差
	memset(grayhis,0,1024);
	memset(thresigma,0,1024);
	LPBYTE ptr;
	int p = CSegImg->GetPitch();
	ptr = (LPBYTE)CSegImg->GetBits();
	//计算灰度直方图
	for(int i=r;i<r+x;i++)
	{
		for(int j=c;j<c+x;j++)
		{
			BYTE gray = ptr[i*p+j];
			grayhis[gray]++;
		}
	}
	int l=0,h=255;
	while(grayhis[l]==0)
		l++;
	while(grayhis[h]==0)
		h--;
	for(int t=l+1;t<h-1;t++)
	{
		int PA=0,PB=0;
		for(int i=l;i<t;i++)
			PA+=grayhis[i];
		for(int i=t;i<=h;i++)
			PB+=grayhis[i];
		int miua=0,miub=0;
		for(int i=l;i<t;i++)
			miua+=(i*grayhis[i]);
		for(int i=t;i<=h;i++)
			miub+=(i*grayhis[i]);
		miua/=PA;
		miub/=PB;
		int sigmaa=0,sigmab=0;
		for(int i=l;i<t;i++)
			sigmaa+=((i-miua)*(i-miua)*grayhis[i]);
		for(int i=t;i<=h;i++)
			sigmab+=((i-miub)*(i-miub)*grayhis[i]);
		sigmaa/=PA;
		sigmab/=PB;
		int sigma=PA*sigmaa+PB*sigmab;
		thresigma[t]=sigma;
	}
	int thre=0,mint=INT_MAX;
	for(int i=l+1;i<h-1;i++)
	{
		if(thresigma[i]<mint)
		{
			mint=thresigma[i];
			thre=i;
		}
	}
	for(int i=r;i<r+x;i++)
	{
		for(int j=c;j<c+x;j++)
		{
			if(ptr[i*p+j]<thre)
				ptr[i*p+j]=0;
			else
				ptr[i*p+j]=255;
		}
	}
}