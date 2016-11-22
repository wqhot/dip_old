#include <iostream>
#include "ImageBase.h"
#include "Matrix.h"
#include "ImagProc.h"
#include "FreCal.h"

int main() {
    ImageBase imageBase;
    BitmapMat bitmapMat;
    bitmapMat = imageBase.open("lena.bmp");
    ImagProc imageProc;
	//FreCal freCal;
	//std::cout << cos(DIP_PI)<<std::endl;
    BitmapMat bitmapMat1=imageProc.rgbToGray(bitmapMat);
    //bitmapMat1 = imageProc.mirror(bitmapMat1,1);
    //bitmapMat1 = imageProc.translation(bitmapMat, 50, 50, 0);
    //bitmapMat1 = imageProc.cut(bitmapMat, 100, 1, 400, 500);
    bitmapMat1 = imageProc.zoom(bitmapMat1, 0.5, 0.5, 1);

    //bitmapMat1 = imageProc.rotate(bitmapMat, 85,255.0,1);
	//bitmapMat1=imageProc.filter(bitmapMat1,2 ,3,1);
	FreCal freCal;
	Complex* fuliye=0;
	int w = bitmapMat1.matrixB.width;
	int h = bitmapMat1.matrixB.height;
	fuliye=freCal.DFT2D(bitmapMat1.matrixB);
    freCal.IDFT2D(fuliye, bitmapMat1.matrixB, bitmapMat1.matrixB.width, bitmapMat1.matrixB.height, bitmapMat1.matrixB.width, bitmapMat1.matrixB.height);

    bitmapMat1 = freCal.fre2im(fuliye, bitmapMat1.matrixB.width, bitmapMat1.matrixB.height);
    imageBase.save("final.bmp", bitmapMat1);
	
    imageBase.destory(bitmapMat1);
    imageBase.destory(bitmapMat);
	free(fuliye);
	//freCal.destory();
    return 0;
}