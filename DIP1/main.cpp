#include <iostream>
#include "dipInclude.h"


int main() {
    ImageBase imageBase;
    Image img;
    img = imageBase.open("lena.bmp");
    ImagProc imageProc;
	//FreCal freCal;
	//std::cout << cos(DIP_PI)<<std::endl;
    Image img1=imageProc.rgbToGray(img);
   // img1.matrixB=img1.matrixB.cut(1, 500, 1, 500);
   // img1.matrixB = img1.matrixB.mul(img1.matrixB);
    //img1 = imageProc.zoom(img1, 0.5, 0.5, 1);
    img1 = imageProc.gaussLowPassFilter(img, 30,-1);
	//FreCal freCal;
    //Matrix mat = freCal.dct2d(img1.matrixB,8);
    //img1.matrixB = freCal.idct2d(mat,8);

   // Image img2(mat.normalization(255,0));
	//Complex* fuliye=0;
	//int w = img1.matrixB.width;
	//int h = img1.matrixB.height;
	//fuliye=freCal.DFT2D(img1.matrixB);

 //   Complex* fuliye1 = (Complex*)malloc(sizeof(Complex)*img1.matrixB.width*img1.matrixB.height);
 //   memcpy(fuliye1, fuliye, sizeof(Complex)*img1.matrixB.width*img1.matrixB.height);
 //   //freCal.IDFT2D(fuliye, img1.matrixB, img1.matrixB.width, img1.matrixB.height, w, h);
 //   img1.matrixB = freCal.fre2im(fuliye, img1.matrixB.width, img1.matrixB.height);
    
    imageBase.save("final.bmp", img1);
    img1.destory();
    img.destory();
    //img2.destory();

	//free(fuliye);
    //free(fuliye1);
	//freCal.destory();
    return 0;
}