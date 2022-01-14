# 图像几何变换实验 

数字图像处理课程实验，具体内容可以见[数字图像处理实验](https://coding-famer.github.io/blog/2021/11/12/%E6%95%B0%E5%AD%97%E5%9B%BE%E5%83%8F%E5%A4%84%E7%90%86%E5%AE%9E%E9%AA%8C%E2%80%94%E2%80%94%E5%87%A0%E4%BD%95%E5%8F%98%E6%8D%A2/)

这是我在完成数字图像处理课程实验时的一些记录，其中实验目标和要求来自老师的实验讲义。第一个实验是完成图像的基本几何变换（包括平移、旋转、缩放）并将其显示出来，其中插值使用双线性插值。由于实验要求使用c++实现且不得调用相关的第三方库，因此选择了基于MFC实现，使用的平台是Visual Studio 2010。

## 1. 实验目标 

本实验要求实现一个包含图像基本几何变换（包括平移、旋转、缩放）的实验程序。该程 序可以读取以 bmp 格式存放的灰度图像文件，提供简易的人机交互方式选择变换方式及输 入相关的参数，可以显示处理前及处理后的图像。 

## 2. 具体要求： 

（1） 程序使用 C++语言编写，集成开发环境可以选择 vs 或 Qt，几何变换的核心 代码（包括坐标映射、像素遍历、灰度插值等）不允许直接调用库函数实 现，不允许使用 opencv 等第三方库。 

（2） 图像几何变换（包括插值）部分以类的形式封装（类及接口自由设计），与 人机交互功能分离。图像几何变换应该包含平移、旋转和缩放三种基本变换 的接口，并由接口函数导入变换的相关参数。其中，旋转的中心可以设定为 图像的几何中心或通过接口函数导入。原始图像以及结果图像的导入和导出 方式不限，可以自由设计。 

（3） 人机交互方式可以自由设计，应该可以显示原始和结果图像（不限制显示方 式，例如可以直接在主界面上显示，或新建窗口显示，或同时显示处理前后 图像，或每一时刻只能显示一幅图像）。可以由用户选择加载以 BMP 格式保 存的灰度图像作为原始图像，不要求保存处理结果。

## 3. 实现方法

本实验基于MFC实现，使用的平台是visual studio 2010。窗口显示使用基于CWnd的类。图片使用CImage类。

### 继承CWnd实现一个窗口类

考虑到会对一个窗口做一些适合我们的修改，我们从CWnd类中继承出一个自己的类CImgWnd，其中包含一个成员：一个指向CImage对象的指针。

它的构造函数如下：

```c++
CImgWnd::CImgWnd(CWnd *pParentWnd, RECT rect, CImage* img, LPCTSTR pname)
:CWnd()
,CImg(img)
{
	CWnd::Create(AfxRegisterWndClass(NULL), pname, WS_CHILD | WS_CAPTION | WS_VISIBLE , rect, pParentWnd, 1);
}
```

在这个类中实现对于图像的显示

```c++
void CImgWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(CImg!=NULL)
	{
		CImg->Draw(dc,0,0);
	}
}
```

view中的显示窗口的消息函数

其中`mpSrcImgWnd`是一个CImgWnd对象的指针，当这个指针为NULL时，新建一个CImgWnd对象，如果已经存在一个对象，则更新它。

```c++
void CGeo_Lab1View::OnWndSrcwnd()
{
	// TODO: 在此添加命令处理程序代码
	if(mpSrcImgWnd == NULL)
	{
		mpSrcImgWnd = new CImgWnd(this, CRect(100,100,500,500), &CSrcImg, _T("Source Image"));
		//mpSrcImgWnd->CImg = CSrcImg;
	}
	else
	{
		delete mpSrcImgWnd;
		mpSrcImgWnd = NULL;
	}
}
```



### 图像读入及显示

使用CImage的Load函数来读入图像，在CImgWnd类的OnPaint函数中使用Draw函数来显示图像。而我们要写的几何变换实现的是对于一个CImage对象的内部的像素值的改变。具体可以看代码。

### 几何变换类

主要的函数为仿射变换和双线性插值。平移、旋转、缩放都是通过仿射变换实现的。由于缩放，旋转时导致的一些不能取到整数像素的情况，需要通过插值来实现。考虑到每次都判断坐标是否为整数过于繁琐，我们假设每次的坐标变化都是通过插值得到的。

#### 数据成员及成员函数

```c++
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
```

#### 双线性插值

算法原理如下图，还是很好理解和实现的。

![](../../../blog/source/_posts/数字图像处理实验——几何变换/image-20211112214025061.png)

```c++
BYTE GeometricTransform::BiInter(BYTE x00, BYTE x10, BYTE x01, BYTE x11, double r1, double r2)
{
	double m = x00 + r2*(x10-x00);
	double n = x01 + r2*(x11-x01);
	return BYTE(m + r1*(n-m));
}
```



#### 仿射变换

假设每个获得的像素值都是通过插值实现的。变换公式如下图，实现时需反解出x和y。

![](../../../blog/source/_posts/数字图像处理实验——几何变换/image-20211112221049518.png)

```c++
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
```

#### 平移

```c++
void GeometricTransform::Translation(double x, double y)
{
	AffTransform(1, 0, x, 0, 1, y);	
}
```

#### 缩放

```c++
void GeometricTransform::Scaling(double sx, double sy)
{
	AffTransform(sx, 0, 0, 0, sy, 0);
}
```

#### 旋转

旋转中心为图像中心而非坐标原点，所以需要增加两个常数项，可以通过公式计算出。

```c++
void GeometricTransform::Rotation(int Theta)
{
	AffTransform(cos(Theta*PI/180), -sin(Theta*PI/180), Width*(1-cos(Theta*PI/180))/2+Height*sin(Theta*PI/180)/2, 
		sin(Theta*PI/180), cos(Theta*PI/180), -Width*sin(Theta*PI/180)/2+Height*(1-cos(Theta*PI/180))/2);	
}
```

------------------

## 小结

几何变换是图像处理的基本功能，由于只是课程小实验，我的程序还不是很完善，但完全实现了应有的功能，在网上目前也很难找到关于基于MFC的图像处理，尤其是不能调库的情况的资料，后续的实验内容我也会持续更新到博客上。