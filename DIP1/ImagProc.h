#pragma once
#include "Matrix.h"
#include "ImageBase.h"
#include <math.h>
#include "Utils.h"
#define DIP_PI       3.14159265358979323846

class ImagProc {
public:
    ImagProc();
    ~ImagProc();
    // 彩色图像灰度化
    BitmapMat rgbToGray(BitmapMat imageMat);
    // 图像镜像,mode=0表示水平镜像，=1表示垂直镜像
    BitmapMat mirror(BitmapMat imageMat, int mode=0);
    // 图像旋转
    BitmapMat rotate(BitmapMat imageMat, float degree, float fillcolor=0, int mode=1);
    // 平移
    BitmapMat translation(BitmapMat imageMat, int dx, int dy, float fillcolor=0);
    BitmapMat cut(BitmapMat imageMat, int startrow, int startcol, int endrow, int endcol);
    // 缩放,mode=1：最近邻，mode=2：双线性插值，mode=3：三次内插值
    BitmapMat zoom(BitmapMat imageMat, float scalex, float scaley, int mode=1);
private:
    // 近似sin(pi*x)/(pi*x)
    float sinpixdivpix(float x);
public:
	// 滤波
	// --平滑--
	// 1.均值
	// 2.梯度倒数加权平滑
	// 3.超限邻域平均法
	// 4.噪声门限法
	// 5.中值滤波
	// 6.超限中值滤波
	// --锐化--
	// 7.Roberts
	// 8.Prewitt
	// 9.Sobel
	// 10.Laplace
	BitmapMat filter(BitmapMat imageMat, int type = 1, int size = 3, int T = 0);
	// 返回一个滤波窗口的值
	// --平滑--
	// 1.均值
	// 2.梯度倒数加权平滑
	// 3.超限邻域平均法
	// 4.噪声门限法
	// 5.中值滤波
	// 6.超限中值滤波
	// --锐化--
	// 7.Roberts
	// 8.Prewitt
	// 9.Sobel
	// 10.Laplace
	float getFilterWindow(int type, Matrix info, int size=3, int T=0);
};

