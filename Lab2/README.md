# 图像灰度映射实验

[数字图像处理实验——灰度映射](https://coding-famer.github.io/blog/2021/11/15/数字图像处理实验——灰度映射/)

## 1.实验目标 

本实验要求实现一个大灰度动态范围的灰度图像浏览器。该程序可以读取一个自定义格式 的灰度图像文件（格式定义见下文），设计简易的人机交互方式选择“灰度窗”，将灰度窗映 射到[0,255]并显示。 

## 2.具体要求： 

1. 程序使用 C++语言编写，集成开发环境可以选择 vs 或 Qt，不允许使用 opencv 等第三方库。 

2. 设计人机交互界面，用户可以方便设置/调整灰度窗参数（窗宽和窗位），将 此灰度窗映射到[0,255]并显示。 

3. 鼓励扩展图像浏览功能，但不做要求，也不计入本次实验成绩。 

4. 自行编写程序从文件中读出实验图像数据。实验图像数据有效灰度范围[0,  4095]，即 12 位有效灰度，每像素 2 字节（最高 4 位数据无效，有效灰度保 存于低 12 位）。数据文件为自定义格式（非标准格式），文件中的数据存放 如下图：

   ![](https://gitee.com/seugch/image-bed/raw/master/img/image-20211201235119922.png) 

   文件开始的 4 字节存放图像宽，其后 4 字节存放图像高，此两参数均为无符 号长整型（unsigned long），紧随其后为按光栅扫描顺序（从左向右，逐行 扫描）存放的像素值，像素值为无符号短整型（unsigned short）。所有多字 节数据都按 intel 顺序（即低字节在前，高字节在后）存放。文件不包含其它 数据。 

5. 当图像尺寸大于窗口尺寸时，应选择合适的方案由用户调整图像在窗口显示 的区域（如使用窗口滚动条、鼠标抓取图像拖动等），不允许缩小图像以适 应窗口尺寸显示。 

6. 两幅实验图像保存于文件 lung.raw 和 knee.raw 中，上交的实验结果应包含 以下三幅截屏图像（以下灰度窗的位置记为 [窗位，窗宽]，其中窗位表示灰 度窗中央位置的灰度值，窗宽表示灰度窗的宽度）：[1] lung.raw 文件包含的 图像，以灰度窗[2048，4096]显示，并将胸脊（胸椎）置于画面的中间位 置；[2] lung.raw 文件包含的图像，以灰度窗[3000, 2000]显示，并将肺 （左、右肺任选）置于画面的中间位置；[3] knee.raw 文件包含的图像，以 灰度窗[250，500]显示，并将膝关节置于画面的中间位置。

## 3. 实现方法

### 读入图像

实验给出的图像是用于医学影像的raw格式，不能直接用之前的CImage的load函数了。于是使用最原始的文件读写将图片数据读进来。这段代码读入的是名为“lung.raw“的文件。

```c++
	FILE* fplung;
	fplung = fopen("lung.raw","rb");
	fseek(fplung, 0, SEEK_SET);
	DWORD height[1];
	DWORD width[1];
	fread(width, 4, 1,fplung);
	fread(height, 4, 1, fplung);
	WORD* img = new WORD[height[0]*width[0]];
	int xx=fread(img, sizeof(WORD), height[0]*width[0],fplung);
```

### 新建CImage图像

实验中发现CImage的create操作是需要指定调色板的，否则的话就会显示一片黑色。由于不知道怎么新建调色板，在做实验时就使用了上一次实验时图片的调色板

```c++
		CImg.Destroy();
		CImg.Create(width[0], height[0],8, 0);
		CImage colortable;
		colortable.Load(_T("barbara.bmp"));
		RGBQUAD pal[256];  
        int nColors=colortable.GetMaxColorTableEntries(); 
		colortable.GetColorTable(0,nColors,pal);
		CImg.SetColorTable(0,nColors,pal);
```

### 灰度映射类

### 数据成员和成员函数

保存转换前和转换后的图像数据数组，并提供一个将图像数据转为CImage的方法

```c++
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
```

### 将图像数据数组转换为CImage类

```c++
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
```

### 灰度映射方法

灰度映射实现起来其实并不是很难，其实只是一个分段线性函数。

其中参数x为窗位，w为窗宽。

灰度映射就是将小于窗口下界的设为0大于窗口上界的设为最大灰度值，剩下的按比例进行映射。

```c++
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
```

### 设置滚轮实现图片浏览

这个要求是最难实现的一个要求，主要还是由于对于MFC的机制不熟悉。其主要的实现机制在自己的ImgWnd类里。

```c++
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
```

