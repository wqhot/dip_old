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
    // ��ɫͼ��ҶȻ�
    BitmapMat rgbToGray(BitmapMat imageMat);
    // ͼ����,mode=0��ʾˮƽ����=1��ʾ��ֱ����
    BitmapMat mirror(BitmapMat imageMat, int mode=0);
    // ͼ����ת
    BitmapMat rotate(BitmapMat imageMat, float degree, float fillcolor=0, int mode=1);
    // ƽ��
    BitmapMat translation(BitmapMat imageMat, int dx, int dy, float fillcolor=0);
    BitmapMat cut(BitmapMat imageMat, int startrow, int startcol, int endrow, int endcol);
    // ����,mode=1������ڣ�mode=2��˫���Բ�ֵ��mode=3�������ڲ�ֵ
    BitmapMat zoom(BitmapMat imageMat, float scalex, float scaley, int mode=1);
private:
    // ����sin(pi*x)/(pi*x)
    float sinpixdivpix(float x);
public:
	// �˲�
	// --ƽ��--
	// 1.��ֵ
	// 2.�ݶȵ�����Ȩƽ��
	// 3.��������ƽ����
	// 4.�������޷�
	// 5.��ֵ�˲�
	// 6.������ֵ�˲�
	// --��--
	// 7.Roberts
	// 8.Prewitt
	// 9.Sobel
	// 10.Laplace
	BitmapMat filter(BitmapMat imageMat, int type = 1, int size = 3, int T = 0);
	// ����һ���˲����ڵ�ֵ
	// --ƽ��--
	// 1.��ֵ
	// 2.�ݶȵ�����Ȩƽ��
	// 3.��������ƽ����
	// 4.�������޷�
	// 5.��ֵ�˲�
	// 6.������ֵ�˲�
	// --��--
	// 7.Roberts
	// 8.Prewitt
	// 9.Sobel
	// 10.Laplace
	float getFilterWindow(int type, Matrix info, int size=3, int T=0);
};

