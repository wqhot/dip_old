////////////////////////////////////////////////////////////////
//FileName:ImageBase.h//Creator:WQ
//Date:2016��10��29��20:18:51
//Comment:bmpͼ���ʽ�ļ��Ĵ�
//
///////////////////////////////////////////////////////////////
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <malloc.h>
#include "Matrix.h"

typedef struct Bitmap_Mat {
    int channel;
    Matrix matrixR;
    Matrix matrixG;
    Matrix matrixB;
} BitmapMat;

typedef struct Bitmap_File_Header {
    char* bfType;//�ļ�����
    int bfSize = 0;//�ļ���С
    short bf1, bf2;//����
    int bfOffBits = 0;//λͼ����ƫ����
} BitmapFileHeader;

typedef struct Bitmap_Info_Header {
    int biSize; //��Ϣͷ����
    int biWidth;//���(px)
    int biHeight;//�߶�(px)
    short biPlanes;//λƽ����
    short biBitCount;//ÿ��������ռλ��
    int biCompression;//�Ƿ�ѹ��
    int biSizeImage;//ͼ���С
    int biXPelsPerMeter;//ˮƽ�ֱ���
    int biYPelsPerMeter;//��ֱ�ֱ���
    int biClrUsed;//��ɫ��
    int biClrImportant;//��Ҫ��ɫ��
} BitmapInfoHeader;

typedef struct BitmapFile {

    BitmapFileHeader bitmapheader;
    BitmapInfoHeader bitmapinfoheader;
    float* R;
    float* G;
    float* B;

} Bitmap;


class ImageBase {
public:
    ImageBase();
    ~ImageBase();
    BitmapMat open(std::string fileName);
    // ����ͼƬ
    int save(std::string filename, BitmapMat bitmapMat);
    // ����
    int destory(BitmapMat imageMat);
	BitmapMat create(Matrix matrix);
};

