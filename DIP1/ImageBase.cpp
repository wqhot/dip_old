#include "ImageBase.h"



ImageBase::ImageBase() {
}


ImageBase::~ImageBase() {
}


Image ImageBase::open(std::string fileName) {
    std::ifstream fin(fileName, std::ios::binary);
    unsigned char* temp;
    Bitmap bitmap;
    Image bitmapMat;

    bitmap.bitmapheader.bfType = (char*)malloc(sizeof(char) * 2);
    temp = (unsigned char*)malloc(sizeof(char) * 4);

    fin.read((char*)bitmap.bitmapheader.bfType, sizeof(char) * 2);
    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapheader.bfSize = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);
    fin.read((char*)temp, sizeof(short));
    bitmap.bitmapheader.bf1 = *temp + (*(temp + 1) << 8);
    fin.read((char*)temp, sizeof(short));
    bitmap.bitmapheader.bf2 = *temp + (*(temp + 1) << 8);
    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapheader.bfOffBits = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biSize = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biWidth = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biHeight = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(short));
    bitmap.bitmapinfoheader.biPlanes = *temp + (*(temp + 1) << 8);

    fin.read((char*)temp, sizeof(short));
    bitmap.bitmapinfoheader.biBitCount = *temp + (*(temp + 1) << 8);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biCompression = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biSizeImage = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biXPelsPerMeter = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biYPelsPerMeter = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biClrUsed = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);

    fin.read((char*)temp, sizeof(int));
    bitmap.bitmapinfoheader.biClrImportant = *temp + (*(temp + 1) << 8) + (*(temp + 2) << 16) + (*(temp + 3) << 24);
    //��ɫͼ
    if (bitmap.bitmapinfoheader.biBitCount / 8 == 3) {
        //�����ڴ�ռ�
        bitmap.R = (float*)malloc(sizeof(float)*bitmap.bitmapinfoheader.biHeight*bitmap.bitmapinfoheader.biWidth);
        bitmap.G = (float*)malloc(sizeof(float)*bitmap.bitmapinfoheader.biHeight*bitmap.bitmapinfoheader.biWidth);
        bitmap.B = (float*)malloc(sizeof(float)*bitmap.bitmapinfoheader.biHeight*bitmap.bitmapinfoheader.biWidth);
        //����ƫ�������ļ�
        fin.seekg(bitmap.bitmapheader.bfOffBits, std::ios::beg);

        for (int i = 0; i < bitmap.bitmapinfoheader.biHeight; i++) {
            for (int j = 0; j < bitmap.bitmapinfoheader.biWidth; j++) {
                fin.read((char*)temp, sizeof(char) * 3);
                *(bitmap.B + bitmap.bitmapinfoheader.biWidth*(bitmap.bitmapinfoheader.biHeight - 1 - i) + j) = *temp;
                *(bitmap.G + bitmap.bitmapinfoheader.biWidth*(bitmap.bitmapinfoheader.biHeight - 1 - i) + j) = *(temp + 1);
                *(bitmap.R + bitmap.bitmapinfoheader.biWidth*(bitmap.bitmapinfoheader.biHeight - 1 - i) + j) = *(temp + 2);
            }
            if (bitmap.bitmapinfoheader.biWidth * 3 % 4 != 0) {
                for (int j = 0; j < 4 - (bitmap.bitmapinfoheader.biWidth * 3 % 4); j++) {
                    fin.read((char*)temp, sizeof(char));
                }
            }
        }
        bitmapMat.channel = 3;
        bitmapMat.matrixR.setMatrix(bitmap.bitmapinfoheader.biWidth, bitmap.bitmapinfoheader.biHeight, bitmap.R);
        bitmapMat.matrixG.setMatrix(bitmap.bitmapinfoheader.biWidth, bitmap.bitmapinfoheader.biHeight, bitmap.G);
        bitmapMat.matrixB.setMatrix(bitmap.bitmapinfoheader.biWidth, bitmap.bitmapinfoheader.biHeight, bitmap.B);
    }
    else//��ɫͼ
    {
        //�����ڴ�ռ�
        bitmap.B = (float*)malloc(sizeof(float)*bitmap.bitmapinfoheader.biHeight*bitmap.bitmapinfoheader.biWidth);
        //����ƫ�������ļ�
        fin.seekg(bitmap.bitmapheader.bfOffBits, std::ios::beg);

        for (int i = 0; i < bitmap.bitmapinfoheader.biHeight; i++) {
            for (int j = 0; j < bitmap.bitmapinfoheader.biWidth; j++) {
                fin.read((char*)temp, sizeof(char));
                *(bitmap.B + bitmap.bitmapinfoheader.biWidth*(bitmap.bitmapinfoheader.biHeight - 1 - i) + j) = *temp;
            }
            if (bitmap.bitmapinfoheader.biWidth % 4 != 0) {
                for (int j = 0; j < 4 - (bitmap.bitmapinfoheader.biWidth % 4); j++) {
                    fin.read((char*)temp, sizeof(char));
                }
            }
        }
        bitmapMat.channel = 1;
        bitmapMat.matrixB.setMatrix(bitmap.bitmapinfoheader.biWidth, bitmap.bitmapinfoheader.biHeight, bitmap.B);
    }
    fin.close();
    free(bitmap.bitmapheader.bfType);
    free(temp);
    return bitmapMat;
}




// ����ͼƬ
int ImageBase::save(std::string filename, Image bitmapMat) {
    std::ofstream fout(filename, std::ios::binary);
    unsigned char* temp;
    int p = 0;//ָ��
    //�����ļ���С
    int bfSize = bitmapMat.channel
        *(bitmapMat.matrixB.width + 4 - (bitmapMat.matrixB.width * bitmapMat.channel % 4))
        *bitmapMat.matrixB.height + 54;
    if (bitmapMat.channel == 1) {
        bfSize += 1024;
    }
    //����ƫ��
    int bfOffset;
    if (bitmapMat.channel == 3) {
        bfOffset = 54;
    }
    else {
        bfOffset = 1024 + 54;
    }

    //����ÿ���ش�С
    int biBitCount = bitmapMat.channel * 8;
    //����ͼ���С
    int biSizeImage = bitmapMat.matrixB.width*bitmapMat.matrixB.height*bitmapMat.channel;
    //��ʼ��temp
    temp = (unsigned char*)malloc(sizeof(unsigned char)*bfSize);
    //д�ļ�ͷ
    *(temp + p++) = 'B';
    *(temp + p++) = 'M';
    *(temp + p++) = (unsigned char)bfSize;
    *(temp + p++) = (unsigned char)(bfSize >> 8);
    *(temp + p++) = (unsigned char)(bfSize >> 16);
    *(temp + p++) = (unsigned char)(bfSize >> 24);
    *(temp + p++) = 0;
    *(temp + p++) = 0;
    *(temp + p++) = 0;
    *(temp + p++) = 0;
    *(temp + p++) = (unsigned char)bfOffset;
    *(temp + p++) = (unsigned char)(bfOffset >> 8);
    *(temp + p++) = (unsigned char)(bfOffset >> 16);
    *(temp + p++) = (unsigned char)(bfOffset >> 24);
    //дλͼ��Ϣ
    *(temp + p++) = 40;
    *(temp + p++) = 0;
    *(temp + p++) = 0;
    *(temp + p++) = 0;
    *(temp + p++) = (unsigned char)bitmapMat.matrixB.width;
    *(temp + p++) = (unsigned char)(bitmapMat.matrixB.width >> 8);
    *(temp + p++) = (unsigned char)(bitmapMat.matrixB.width >> 16);
    *(temp + p++) = (unsigned char)(bitmapMat.matrixB.width >> 24);
    *(temp + p++) = (unsigned char)bitmapMat.matrixB.height;
    *(temp + p++) = (unsigned char)(bitmapMat.matrixB.height >> 8);
    *(temp + p++) = (unsigned char)(bitmapMat.matrixB.height >> 16);
    *(temp + p++) = (unsigned char)(bitmapMat.matrixB.height >> 24);
    *(temp + p++) = 1;
    *(temp + p++) = 0;
    *(temp + p++) = (unsigned char)biBitCount;
    *(temp + p++) = (unsigned char)(biBitCount >> 8);
    *(temp + p++) = 0;
    *(temp + p++) = 0;
    *(temp + p++) = 0;
    *(temp + p++) = 0;
    *(temp + p++) = (unsigned char)biSizeImage;
    *(temp + p++) = (unsigned char)(biSizeImage >> 8);
    *(temp + p++) = (unsigned char)(biSizeImage >> 16);
    *(temp + p++) = (unsigned char)(biSizeImage >> 24);
    for (int i = 0; i < 16; i++) {
        *(temp + p++) = 0;
    }
    //дͼ������
    if (bitmapMat.channel == 3) {
        for (int i = 0; i < bitmapMat.matrixB.height; i++) {
            for (int j = 0; j < bitmapMat.matrixB.width; j++) {
                *(temp + p++) = (unsigned char)bitmapMat.matrixB.getPixel(bitmapMat.matrixB.height - i, j + 1);
                *(temp + p++) = (unsigned char)bitmapMat.matrixG.getPixel(bitmapMat.matrixG.height - i, j + 1);
                *(temp + p++) = (unsigned char)bitmapMat.matrixR.getPixel(bitmapMat.matrixR.height - i, j + 1);
            }
            if (bitmapMat.matrixB.width * 3 % 4 != 0) {
                for (int j = 0; j < 4 - (bitmapMat.matrixB.width * 3 % 4); j++) {
                    *(temp + p++) = 0;
                }
            }
        }
    }
    else {
        //д��ɫ��
        for (int i = 0; i < 256; i++) {
            *(temp + p++) = i;
            *(temp + p++) = i;
            *(temp + p++) = i;
            *(temp + p++) = 0;
        }
        for (int i = 0; i < bitmapMat.matrixB.height; i++) {
            for (int j = 0; j < bitmapMat.matrixB.width; j++) {
                *(temp + p++) = (unsigned char)bitmapMat.matrixB.getPixel(bitmapMat.matrixB.height - i, j + 1);
            }
            if (bitmapMat.matrixB.width % 4 != 0) {
                for (int j = 0; j < 4 - (bitmapMat.matrixB.width % 4); j++) {
                    *(temp + p++) = 0;
                }
            }
        }
    }
    fout.write((char*)temp, sizeof(unsigned char)*bfSize);
    free(temp);
    fout.close();
    return 0;
}


// ����
int ImageBase::destory(Image imageMat) {
    if (imageMat.channel == 3) {
        imageMat.matrixB.destory();
        imageMat.matrixG.destory();
        imageMat.matrixR.destory();
    }
    else {
        imageMat.matrixB.destory();
    }
    return 0;
}





Image ImageBase::create(Matrix matrix) {
	Image dest;
	dest.channel = 1;
	dest.matrixB.create(matrix.width, matrix.height);
	memcpy(dest.matrixB.data, matrix.data, matrix.width*matrix.height * sizeof(float));
	return dest;
}
