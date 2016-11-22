#include "ImagProc.h"



ImagProc::ImagProc() {
}


ImagProc::~ImagProc() {
}


// 彩色图像灰度化
BitmapMat ImagProc::rgbToGray(BitmapMat imageMat) {
    BitmapMat dest;
    if (imageMat.channel == 1) {
        dest = imageMat;
    }
    else {
        dest.channel = 1;
        dest.matrixB.create(imageMat.matrixB.width, imageMat.matrixB.height);
        dest.matrixB = imageMat.matrixB.dot(0.11).add(imageMat.matrixG.dot(0.59).add(imageMat.matrixR.dot(0.30)));
    }
    return dest;
}


// 图像镜像,mode=0表示水平镜像，=1表示垂直镜像
BitmapMat ImagProc::mirror(BitmapMat imageMat, int mode) {
    BitmapMat dest;
    if (imageMat.channel == 1) {
        dest.channel = 1;
        dest.matrixB = imageMat.matrixB.copy();
        if (mode == 0) {//水平翻转
            float *temp = (float*)malloc(sizeof(float)*dest.matrixB.height);
            for (int i = 0; i < dest.matrixB.width / 2; i++) {
                temp = dest.matrixB.getCols(i + 1);
                dest.matrixB.setCols(i + 1, dest.matrixB.getCols(dest.matrixB.width - i));
                dest.matrixB.setCols(dest.matrixB.width - i, temp);
            }
            free(temp);
        }
        else if (mode == 1) {
            float *temp = (float*)malloc(sizeof(float)*dest.matrixB.width);
            for (int i = 0; i < dest.matrixB.height / 2; i++) {
                temp = dest.matrixB.getRows(i + 1);
                dest.matrixB.setRows(i + 1, dest.matrixB.getRows(dest.matrixB.height - i));
                dest.matrixB.setRows(dest.matrixB.height - i, temp);
            }
            //free(temp);
        }
    }
    else if (imageMat.channel == 3) {
        dest.channel = 3;
        dest.matrixB = imageMat.matrixB.copy();
        dest.matrixG = imageMat.matrixG.copy();
        dest.matrixR = imageMat.matrixR.copy();
        if (mode == 0) {//水平翻转
            float *temp = (float*)malloc(sizeof(float)*dest.matrixB.height);
            for (int i = 0; i < dest.matrixB.width / 2; i++) {
                temp = dest.matrixB.getCols(i + 1);
                dest.matrixB.setCols(i + 1, dest.matrixB.getCols(dest.matrixB.width - i));
                dest.matrixB.setCols(dest.matrixB.width - i, temp);
                temp = dest.matrixG.getCols(i + 1);
                dest.matrixG.setCols(i + 1, dest.matrixG.getCols(dest.matrixG.width - i));
                dest.matrixG.setCols(dest.matrixG.width - i, temp);
                temp = dest.matrixR.getCols(i + 1);
                dest.matrixR.setCols(i + 1, dest.matrixR.getCols(dest.matrixR.width - i));
                dest.matrixR.setCols(dest.matrixR.width - i, temp);
            }
            free(temp);
        }
        else if (mode == 1) {
            float *temp = (float*)malloc(sizeof(float)*dest.matrixB.width);
            for (int i = 0; i < dest.matrixB.height / 2; i++) {
                temp = dest.matrixB.getRows(i + 1);
                dest.matrixB.setRows(i + 1, dest.matrixB.getRows(dest.matrixB.height - i));
                dest.matrixB.setRows(dest.matrixB.height - i, temp);
                temp = dest.matrixG.getRows(i + 1);
                dest.matrixG.setRows(i + 1, dest.matrixG.getRows(dest.matrixG.height - i));
                dest.matrixG.setRows(dest.matrixG.height - i, temp);
                temp = dest.matrixR.getRows(i + 1);
                dest.matrixR.setRows(i + 1, dest.matrixR.getRows(dest.matrixR.height - i));
                dest.matrixR.setRows(dest.matrixR.height - i, temp);
            }
            //free(temp);
        }
    }
    return dest;
}




// 图像旋转
BitmapMat ImagProc::rotate(BitmapMat imageMat, float degree, float fillcolor, int mode) {
    degree = -degree;
    float angle = degree * DIP_PI / 180.;
    float alpha = cos(angle);
    float beta = sin(angle);
    int oldWidth = imageMat.matrixB.width;
    int oldHeight = imageMat.matrixB.height;
    int oldMidW = oldWidth / 2;
    int oldMidH = oldHeight / 2;
    int width = floor(oldWidth * fabs(alpha) + oldHeight * fabs(beta));
    int height = floor(oldHeight * fabs(alpha) + oldWidth * fabs(beta));
    int midW = width / 2;
    int midH = height / 2;
    if (mode != 1 && mode != 2 && mode != 3) {
        mode = 1;
    }

    BitmapMat dest;
    if (imageMat.channel == 3) {
        dest.channel = 3;
        if (mode == 1) {//最近邻
            dest.matrixB.create(width, height, fillcolor);
            dest.matrixG.create(width, height, fillcolor);
            dest.matrixR.create(width, height, fillcolor);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    int tempi = i - midH;
                    int tempj = j - midW;
                    int newx = (int)(tempj*alpha - tempi*beta + 0.5);
                    int newy = (int)(tempj*beta + tempi*alpha + 0.5);
                    newx = newx + oldMidW;
                    newy = newy + oldMidH;
                    if (newx >= 0 && newx < imageMat.matrixB.width&&newy >= 0 && newy < imageMat.matrixB.height) {
                        dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                        dest.matrixG.setPixel(i + 1, j + 1, imageMat.matrixG.getPixel(newy + 1, newx + 1));
                        dest.matrixR.setPixel(i + 1, j + 1, imageMat.matrixR.getPixel(newy + 1, newx + 1));
                    }
                }
            }
        }
        else if (mode == 2) {//双线性插值
            dest.matrixB.create(width, height, fillcolor);
            dest.matrixG.create(width, height, fillcolor);
            dest.matrixR.create(width, height, fillcolor);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    int tempi = i - midH;
                    int tempj = j - midW;
                    float newfx = tempj*alpha - tempi*beta;
                    float newfy = tempj*beta + tempi*alpha;
                    int intx = (int)newfx;//i
                    int inty = (int)newfy;//j
                    int u = (newfx - intx) * 2048;//u
                    int v = (newfy - inty) * 2048;//v
                    int invx = 2048 - u;//1-u
                    int invy = 2048 - v;//1-v
                    int temp;
                    intx = intx + oldMidW;
                    inty = inty + oldMidH;
                    if (inty > -1 && inty <= imageMat.matrixB.height - 2 && intx > -1 && intx <= imageMat.matrixB.width - 2) {
                        temp = (int)(imageMat.matrixB.getPixel(inty + 2, intx + 2)*invx*invy
                            + invx*v*imageMat.matrixB.getPixel(inty + 2, intx + 1)
                            + invy*u*imageMat.matrixB.getPixel(inty + 1, intx + 2)
                            + u*v*imageMat.matrixB.getPixel(inty + 1, intx + 1)) >> 22;
                        dest.matrixB.setPixel(i + 1, j + 1, (float)temp);
                        temp = (int)(imageMat.matrixG.getPixel(inty + 2, intx + 2)*invx*invy
                            + invx*v*imageMat.matrixG.getPixel(inty + 2, intx + 1)
                            + invy*u*imageMat.matrixG.getPixel(inty + 1, intx + 2)
                            + u*v*imageMat.matrixG.getPixel(inty + 1, intx + 1)) >> 22;
                        dest.matrixG.setPixel(i + 1, j + 1, (float)temp);
                        temp = (int)(imageMat.matrixR.getPixel(inty + 2, intx + 2)*invx*invy
                            + invx*v*imageMat.matrixR.getPixel(inty + 2, intx + 1)
                            + invy*u*imageMat.matrixR.getPixel(inty + 1, intx + 2)
                            + u*v*imageMat.matrixR.getPixel(inty + 1, intx + 1)) >> 22;
                        dest.matrixR.setPixel(i + 1, j + 1, (float)temp);
                    }
                }
            }
        }
        else if (mode == 3) {
            dest.matrixB.create(width, height, fillcolor);
            dest.matrixG.create(width, height, fillcolor);
            dest.matrixR.create(width, height, fillcolor);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    if (i == 0 || j == 0) {//左、上边缘
                        int tempi = i - midH;
                        int tempj = j - midW;
                        int newx = (int)(tempj*alpha - tempi*beta + 0.5);
                        int newy = (int)(tempj*beta + tempi*alpha + 0.5);
                        newx = newx + oldMidW;
                        newy = newy + oldMidH;
                        if (newx >= 0 && newx < imageMat.matrixB.width&&newy >= 0 && newy < imageMat.matrixB.height) {
                            dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                            dest.matrixG.setPixel(i + 1, j + 1, imageMat.matrixG.getPixel(newy + 1, newx + 1));
                            dest.matrixR.setPixel(i + 1, j + 1, imageMat.matrixR.getPixel(newy + 1, newx + 1));
                        }
                    }
                    else if (i >= dest.matrixB.height - 3 || j >= dest.matrixB.width - 3) {//右、下边缘
                        int tempi = i - midH;
                        int tempj = j - midW;
                        int newx = (int)(tempj*alpha - tempi*beta + 0.5);
                        int newy = (int)(tempj*beta + tempi*alpha + 0.5);
                        newx = newx + oldMidW;
                        newy = newy + oldMidH;
                        if (newx >= 0 && newx < imageMat.matrixB.width&&newy >= 0 && newy < imageMat.matrixB.height) {
                            dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                            dest.matrixG.setPixel(i + 1, j + 1, imageMat.matrixG.getPixel(newy + 1, newx + 1));
                            dest.matrixR.setPixel(i + 1, j + 1, imageMat.matrixR.getPixel(newy + 1, newx + 1));
                        }
                    }
                    else {
                        //在这里，后缀为i表示列,后缀为j表示行
                        int tempj = i - midH;
                        int tempi = j - midW;
                        float newfi = tempi*alpha - tempj*beta;
                        float newfj = tempi*beta + tempj*alpha;
                        int inti = (int)newfi;//i
                        int intj = (int)newfj;//j
                        if (inti + oldMidW > 1 && inti + oldMidW < imageMat.matrixB.width - 2 && intj + oldMidH >= 1 && intj + oldMidH < imageMat.matrixB.height - 2) {
                            float u = (newfi - inti);//u-intx-temp1-j
                            float v = (newfj - intj);//v-inty-temp2-i
                            float A[4], B1[16], B2[16], B3[16], C[4];
                            A[0] = sinpixdivpix(1 + u); A[1] = sinpixdivpix(u); A[2] = sinpixdivpix(u - 1); A[3] = sinpixdivpix(u - 2);
                            C[0] = sinpixdivpix(1 + v); C[1] = sinpixdivpix(v); C[2] = sinpixdivpix(v - 1); C[3] = sinpixdivpix(v - 2);
                            for (int temp1 = -1; temp1 <= 2; temp1++) {
                                for (int temp2 = -1; temp2 <= 2; temp2++) {
                                    B1[(temp1 + 1) * 4 + temp2 + 1] = imageMat.matrixB.getPixel(intj + temp2 + 2 + oldMidH, inti + temp1 + 2 + oldMidW);
                                    B2[(temp1 + 1) * 4 + temp2 + 1] = imageMat.matrixG.getPixel(intj + temp2 + 2 + oldMidH, inti + temp1 + 2 + oldMidW);
                                    B3[(temp1 + 1) * 4 + temp2 + 1] = imageMat.matrixR.getPixel(intj + temp2 + 2 + oldMidH, inti + temp1 + 2 + oldMidW);
                                }
                            }
                            Matrix mA(1, 4, A); Matrix mC(4, 1, C);
                            Matrix mB1(4, 4, B1); Matrix mB2(4, 4, B2); Matrix mB3(4, 4, B3);
                            Matrix result1 = mA.mul(mB1); result1 = result1.mul(mC);
                            dest.matrixB.setPixel(i + 1, j + 1, result1.getPixel(1, 1));
                            Matrix result2 = mA.mul(mB2); result2 = result2.mul(mC);
                            dest.matrixG.setPixel(i + 1, j + 1, result2.getPixel(1, 1));
                            Matrix result3 = mA.mul(mB3); result3 = result3.mul(mC);
                            dest.matrixR.setPixel(i + 1, j + 1, result3.getPixel(1, 1));
                            mA.destory(); mC.destory();
                            mB1.destory(); result1.destory();
                            mB2.destory(); result2.destory();
                            mB3.destory(); result3.destory();
                        }
                    }
                }
            }
        }
    }
    else if (imageMat.channel == 1) {
        dest.channel = 1;
        if (mode == 1) {//最近邻
            dest.matrixB.create(width, height,fillcolor);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    int tempi = i - midH;
                    int tempj = j - midW;
                    int newx = (int)(tempj*alpha - tempi*beta + 0.5);
                    int newy = (int)(tempj*beta + tempi*alpha + 0.5);
                    newx = newx + oldMidW;
                    newy = newy + oldMidH;
                    if (newx >= 0 && newx < imageMat.matrixB.width&&newy >= 0 && newy < imageMat.matrixB.height) {
                        dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                    }
                }
            }
        }
        else if (mode == 2) {//双线性插值
            dest.matrixB.create(width, height, fillcolor);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    int tempi = i - midH;
                    int tempj = j - midW;
                    float newfx = tempj*alpha - tempi*beta;
                    float newfy = tempj*beta + tempi*alpha;
                    int intx = (int)newfx;//i
                    int inty = (int)newfy;//j
                    int u = (newfx - intx) * 2048;//u
                    int v = (newfy - inty) * 2048;//v
                    int invx = 2048 - u;//1-u
                    int invy = 2048 - v;//1-v
                    int temp;
                    intx = intx + oldMidW;
                    inty = inty + oldMidH;
                    if (inty > -1 && inty <= imageMat.matrixB.height - 2 && intx > -1 && intx <= imageMat.matrixB.width - 2) {
                        temp = (int)(imageMat.matrixB.getPixel(inty + 2, intx + 2)*invx*invy
                            + invx*v*imageMat.matrixB.getPixel(inty + 2, intx + 1)
                            + invy*u*imageMat.matrixB.getPixel(inty + 1, intx + 2)
                            + u*v*imageMat.matrixB.getPixel(inty + 1, intx + 1)) >> 22;
                        dest.matrixB.setPixel(i + 1, j + 1, (float)temp);
                    }
                }
            }
        }
        else if (mode == 3) {
            dest.matrixB.create(width, height, fillcolor);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    if (i == 0 || j == 0) {//左、上边缘
                        int tempi = i - midH;
                        int tempj = j - midW;
                        int newx = (int)(tempj*alpha - tempi*beta + 0.5);
                        int newy = (int)(tempj*beta + tempi*alpha + 0.5);
                        newx = newx + oldMidW;
                        newy = newy + oldMidH;
                        if (newx >= 0 && newx < imageMat.matrixB.width&&newy >= 0 && newy < imageMat.matrixB.height) {
                            dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                        }
                    }
                    else if (i >= dest.matrixB.height - 3 || j >= dest.matrixB.width - 3) {//右、下边缘
                        int tempi = i - midH;
                        int tempj = j - midW;
                        int newx = (int)(tempj*alpha - tempi*beta + 0.5);
                        int newy = (int)(tempj*beta + tempi*alpha + 0.5);
                        newx = newx + oldMidW;
                        newy = newy + oldMidH;
                        if (newx >= 0 && newx < imageMat.matrixB.width&&newy >= 0 && newy < imageMat.matrixB.height) {
                            dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                        }
                    }
                    else {
                        //在这里，后缀为i表示列,后缀为j表示行
                        int tempj = i - midH;
                        int tempi = j - midW;
                        float newfi = tempi*alpha - tempj*beta;
                        float newfj = tempi*beta + tempj*alpha;
                        int inti = (int)newfi;//i
                        int intj = (int)newfj;//j
                        if (inti + oldMidW > 1 && inti + oldMidW < imageMat.matrixB.width - 2 && intj + oldMidH >= 1 && intj + oldMidH < imageMat.matrixB.height - 2) {
                            float u = (newfi - inti);//u-intx-temp1-j
                            float v = (newfj - intj);//v-inty-temp2-i
                            float A[4], B1[16], C[4];
                            A[0] = sinpixdivpix(1 + u); A[1] = sinpixdivpix(u); A[2] = sinpixdivpix(u - 1); A[3] = sinpixdivpix(u - 2);
                            C[0] = sinpixdivpix(1 + v); C[1] = sinpixdivpix(v); C[2] = sinpixdivpix(v - 1); C[3] = sinpixdivpix(v - 2);
                            for (int temp1 = -1; temp1 <= 2; temp1++) {
                                for (int temp2 = -1; temp2 <= 2; temp2++) {
                                    B1[(temp1 + 1) * 4 + temp2 + 1] = imageMat.matrixB.getPixel(intj + temp2 + 2 + oldMidH, inti + temp1 + 2 + oldMidW);
                                }
                            }
                            Matrix mA(1, 4, A); Matrix mC(4, 1, C);
                            Matrix mB1(4, 4, B1);
                            Matrix result1 = mA.mul(mB1); result1 = result1.mul(mC);
                            dest.matrixB.setPixel(i + 1, j + 1, result1.getPixel(1, 1));
                            mA.destory(); mC.destory();
                            mB1.destory(); result1.destory();
                        }
                    }
                }
            }
        }
    }


    return dest;
}


// 平移
BitmapMat ImagProc::translation(BitmapMat imageMat, int dx, int dy, float fillcolor) {
    BitmapMat dest;
    dx = -dx;
    dy = -dy;
    if (imageMat.channel == 3) {
        dest.channel = 3;
        dest.matrixB.create(imageMat.matrixB.width, imageMat.matrixB.height, fillcolor);
        dest.matrixG.create(imageMat.matrixB.width, imageMat.matrixB.height, fillcolor);
        dest.matrixR.create(imageMat.matrixB.width, imageMat.matrixB.height, fillcolor);
        for (int i = 0; i < dest.matrixB.height; i++) {
            for (int j = 0; j < dest.matrixB.width; j++) {
                if (i + 1 + dy > 0 && i + 1 + dy <= dest.matrixB.height && j + 1 + dx > 0 && j + 1 + dx <= dest.matrixB.width) {
                    dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(i + 1 + dy, j + 1 + dx));
                    dest.matrixG.setPixel(i + 1, j + 1, imageMat.matrixG.getPixel(i + 1 + dy, j + 1 + dx));
                    dest.matrixR.setPixel(i + 1, j + 1, imageMat.matrixR.getPixel(i + 1 + dy, j + 1 + dx));
                }
            }
        }
    }
    else if (imageMat.channel == 1) {
        dest.channel = 1;
        dest.matrixB.create(imageMat.matrixB.width, imageMat.matrixB.height, fillcolor);
        for (int i = 0; i < dest.matrixB.height; i++) {
            for (int j = 0; j < dest.matrixB.width; j++) {
                if (i + 1 + dy > 0 && i + 1 + dy <= dest.matrixB.height && j + 1 + dx > 0 && j + 1 + dx <= dest.matrixB.width) {
                    dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(i + 1 + dy, j + 1 + dx));
                }
            }
        }
    }


    return dest;
}


BitmapMat ImagProc::cut(BitmapMat imageMat, int startrow, int startcol, int endrow, int endcol) {
    if (startrow<1 || startcol<1 || endrow>imageMat.matrixB.height || endcol>imageMat.matrixB.width || startrow > endrow || startcol > endcol) {
        return BitmapMat();
    }
    BitmapMat dest;
    if (imageMat.channel == 3) {
        dest.channel = 3;
        float *temp;
        temp = (float*)malloc(sizeof(float)*(endcol - startcol + 1));
        dest.matrixB.create(endcol - startcol + 1, endrow - startrow + 1);
        dest.matrixG.create(endcol - startcol + 1, endrow - startrow + 1);
        dest.matrixR.create(endcol - startcol + 1, endrow - startrow + 1);
        for (int i = 0; i < dest.matrixB.height; i++) {
            memcpy(temp, imageMat.matrixB.getRows(i + startrow) + startcol, sizeof(float)*(endcol - startcol + 1));
            dest.matrixB.setRows(i + 1, temp);
            memcpy(temp, imageMat.matrixG.getRows(i + startrow) + startcol, sizeof(float)*(endcol - startcol + 1));
            dest.matrixG.setRows(i + 1, temp);
            memcpy(temp, imageMat.matrixR.getRows(i + startrow) + startcol, sizeof(float)*(endcol - startcol + 1));
            dest.matrixR.setRows(i + 1, temp);
        }
        free(temp);
    }
    else if (imageMat.channel == 1) {
        dest.channel = 1;
        float *temp;
        temp = (float*)malloc(sizeof(float)*(endcol - startcol + 1));
        dest.matrixB.create(endcol - startcol + 1, endrow - startrow + 1);
        for (int i = 0; i < dest.matrixB.height; i++) {
            memcpy(temp, imageMat.matrixB.getRows(i + startrow) + startcol, sizeof(float)*(endcol - startcol + 1));
            dest.matrixB.setRows(i + 1, temp);
        }
        free(temp);
    }
    return dest;
}


// 缩放
BitmapMat ImagProc::zoom(BitmapMat imageMat, float scalex,float scaley, int mode) {
    BitmapMat dest;
    int width = (int)(scalex*imageMat.matrixB.width);
    int height = (int)(scaley*imageMat.matrixB.height);
    if (mode != 1 && mode != 2 && mode != 3) {
        mode = 1;
    }
    if (imageMat.channel == 3) {
        dest.channel = 3;
        if (mode == 1) {//最近邻
            dest.matrixB.create(width, height);
            dest.matrixG.create(width, height);
            dest.matrixR.create(width, height);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    int newx = (int)(j/scalex + 0.5);
                    int newy = (int)(i/scaley + 0.5);
                    dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                    dest.matrixG.setPixel(i + 1, j + 1, imageMat.matrixG.getPixel(newy + 1, newx + 1));
                    dest.matrixR.setPixel(i + 1, j + 1, imageMat.matrixR.getPixel(newy + 1, newx + 1));
                }
            }
        }
        else if (mode == 2) {//双线性插值
            dest.matrixB.create(width, height);
            dest.matrixG.create(width, height);
            dest.matrixR.create(width, height);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    float newfx = (j + 0.5) / scalex - 0.5;
                    float newfy = (i + 0.5) / scaley - 0.5;
                    int intx = (int)newfx;//i
                    int inty = (int)newfy;//j
                    int u = (newfx - intx) * 2048;//u
                    int v = (newfy - inty) * 2048;//v
                    int invx = 2048 - u;//1-u
                    int invy = 2048 - v;//1-v
                    int temp;

                    temp = (int)(imageMat.matrixB.getPixel(inty + 2, intx + 2)*invx*invy
                        + invx*v*imageMat.matrixB.getPixel(inty + 2, intx + 1)
                        + invy*u*imageMat.matrixB.getPixel(inty + 1, intx + 2)
                        + u*v*imageMat.matrixB.getPixel(inty + 1, intx + 1)) >> 22;
                    dest.matrixB.setPixel(i + 1, j + 1, (float)temp);
                    temp = (int)(imageMat.matrixG.getPixel(inty + 2, intx + 2)*invx*invy
                        + invx*v*imageMat.matrixG.getPixel(inty + 2, intx + 1)
                        + invy*u*imageMat.matrixG.getPixel(inty + 1, intx + 2)
                        + u*v*imageMat.matrixG.getPixel(inty + 1, intx + 1)) >> 22;
                    dest.matrixG.setPixel(i + 1, j + 1, (float)temp);
                    temp = (int)(imageMat.matrixR.getPixel(inty + 2, intx + 2)*invx*invy
                        + invx*v*imageMat.matrixR.getPixel(inty + 2, intx + 1)
                        + invy*u*imageMat.matrixR.getPixel(inty + 1, intx + 2)
                        + u*v*imageMat.matrixR.getPixel(inty + 1, intx + 1)) >> 22;
                    dest.matrixR.setPixel(i + 1, j + 1, (float)temp);
                }
            }
        }
        else if (mode == 3) {
            dest.matrixB.create(width, height);
            dest.matrixG.create(width, height);
            dest.matrixR.create(width, height);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    if (i == 0 || j == 0) {//左、上边缘
                        int newx = (int)(j / scalex + 0.5);
                        int newy = (int)(i / scaley + 0.5);
                        dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                        dest.matrixG.setPixel(i + 1, j + 1, imageMat.matrixG.getPixel(newy + 1, newx + 1));
                        dest.matrixR.setPixel(i + 1, j + 1, imageMat.matrixR.getPixel(newy + 1, newx + 1));
                    }
                    else if (i >= dest.matrixB.height - 3 || j >= dest.matrixB.width-3) {//右、下边缘
                        int newx = (int)(j / scalex + 0.5);
                        int newy = (int)(i / scaley + 0.5);
                        dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                        dest.matrixG.setPixel(i + 1, j + 1, imageMat.matrixG.getPixel(newy + 1, newx + 1));
                        dest.matrixR.setPixel(i + 1, j + 1, imageMat.matrixR.getPixel(newy + 1, newx + 1));
                    }
                    else {
                        float newfi = j / scalex;
                        float newfj = i / scaley;
                        int inti = (int)newfi;//i
                        int intj = (int)newfj;//j
                        float u = (newfi - inti);//u-intx-temp1-j
                        float v = (newfj - intj);//v-inty-temp2-i
                        float A[4], B1[16], B2[16], B3[16], C[4];
                        A[0] = sinpixdivpix(1 + u); A[1] = sinpixdivpix(u); A[2] = sinpixdivpix(u - 1); A[3] = sinpixdivpix(u - 2);
                        C[0] = sinpixdivpix(1 + v); C[1] = sinpixdivpix(v); C[2] = sinpixdivpix(v - 1); C[3] = sinpixdivpix(v - 2);
                        for (int temp1 = -1; temp1 <= 2; temp1++) {
                            for (int temp2 = -1; temp2 <= 2; temp2++) {
                                B1[(temp1 + 1) * 4 + temp2 + 1] = imageMat.matrixB.getPixel(intj + temp2 + 2, inti + temp1 + 2);
                                B2[(temp1 + 1) * 4 + temp2 + 1] = imageMat.matrixG.getPixel(intj + temp2 + 2, inti + temp1 + 2);
                                B3[(temp1 + 1) * 4 + temp2 + 1] = imageMat.matrixR.getPixel(intj + temp2 + 2, inti + temp1 + 2);
                            }
                        }
                        Matrix mA(1, 4, A); Matrix mC(4, 1, C);
                        Matrix mB1(4, 4, B1); Matrix mB2(4, 4, B2); Matrix mB3(4, 4, B3);
                        Matrix result1 = mA.mul(mB1); result1 = result1.mul(mC);
                        Matrix result2 = mA.mul(mB2); result2 = result2.mul(mC);
                        Matrix result3 = mA.mul(mB3); result3 = result3.mul(mC);
                        dest.matrixB.setPixel(i + 1, j + 1, result1.getPixel(1, 1));
                        dest.matrixG.setPixel(i + 1, j + 1, result2.getPixel(1, 1));
                        dest.matrixR.setPixel(i + 1, j + 1, result2.getPixel(1, 1));
                        mA.destory(); mC.destory();
                        mB1.destory(); result1.destory();
                        mB2.destory(); result2.destory();
                        mB3.destory(); result3.destory();
                    }            
                }
            }
        }
    }
    else if (imageMat.channel == 1) {
        dest.channel = 1;
       
        if (mode == 1) {
            dest.matrixB.create(width, height);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    int newx = (int)(j/scalex + 0.5);
                    int newy = (int)(i/scaley + 0.5);
                    dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                }
            }
        }
        else if (mode == 2) {//双线性插值
            dest.matrixB.create(width, height);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    float newfx = (j + 0.5) / scalex - 0.5;
                    float newfy = (i + 0.5) / scaley - 0.5;
                    int intx = (int)newfx;//i
                    int inty = (int)newfy;//j
                    int u = (newfx - intx) * 2048;//u
                    int v = (newfy - inty) * 2048;//v
                    int invx = 2048 - u;//1-u
                    int invy = 2048 - v;//1-v
                    int temp;

                    temp = (int)(imageMat.matrixB.getPixel(inty + 2, intx + 2)*invx*invy
                        + invx*v*imageMat.matrixB.getPixel(inty + 2, intx + 1)
                        + invy*u*imageMat.matrixB.getPixel(inty + 1, intx + 2)
                        + u*v*imageMat.matrixB.getPixel(inty + 1, intx + 1)) >> 22;
                    dest.matrixB.setPixel(i + 1, j + 1, (float)temp);
                }
            }
        }
        else if (mode == 3) {
            dest.matrixB.create(width, height);
            for (int i = 0; i < dest.matrixB.height; i++) {
                for (int j = 0; j < dest.matrixB.width; j++) {
                    if (i == 0 || j == 0) {//左、上边缘
                        int newx = (int)(j / scalex + 0.5);
                        int newy = (int)(i / scaley + 0.5);
                        dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                       
                    }
                    else if (i >= dest.matrixB.height - 3 || j >= dest.matrixB.width-3) {//右、下边缘
                        int newx = (int)(j / scalex + 0.5);
                        int newy = (int)(i / scaley + 0.5);
                        dest.matrixB.setPixel(i + 1, j + 1, imageMat.matrixB.getPixel(newy + 1, newx + 1));
                       
                    }
                    else {
                        float newfi = j / scalex;
                        float newfj = i / scaley;
                        int inti = (int)newfi;//i
                        int intj = (int)newfj;//j
                        float u = (newfi - inti);//u-intx-temp1-j
                        float v = (newfj - intj);//v-inty-temp2-i
                        float A[4], B1[16], C[4];
                        A[0] = sinpixdivpix(1 + u); A[1] = sinpixdivpix(u); A[2] = sinpixdivpix(u - 1); A[3] = sinpixdivpix(u - 2);
                        C[0] = sinpixdivpix(1 + v); C[1] = sinpixdivpix(v); C[2] = sinpixdivpix(v - 1); C[3] = sinpixdivpix(v - 2);
                        for (int temp1 = -1; temp1 <= 2; temp1++) {
                            for (int temp2 = -1; temp2 <= 2; temp2++) {
                                B1[(temp1 + 1) * 4 + temp2 + 1] = imageMat.matrixB.getPixel(intj + temp2 + 2, inti + temp1 + 2);                         
                            }
                        }
                        Matrix mA(1, 4, A); Matrix mC(4, 1, C);
                        Matrix mB1(4, 4, B1);
                        Matrix result1 = mA.mul(mB1); result1 = result1.mul(mC);
                       
                        dest.matrixB.setPixel(i + 1, j + 1, result1.getPixel(1, 1));
                       
                        mA.destory(); mC.destory();
                        mB1.destory(); result1.destory();
                       
                    }
                }
            }
        }
    }
    return dest;
}


// 近似sin(pi*x)/(pi*x)
float ImagProc::sinpixdivpix(float x) {
    float absx = fabs(x);
    if (absx >= 0 && absx < 1) {
        return 1 - 2 * absx*absx + absx*absx*absx;
    }
    else if (absx >= 0 && absx < 2) {
        return 4 - 8 * absx + 5 * absx*absx - absx*absx*absx;
    }
    else {
        return 0.0f;
    }  
}


// 滤波
BitmapMat ImagProc::filter(BitmapMat imageMat, int type, int size, int T) {
	if (size % 2 != 1 || size < 3) {
		size = 3;
	}
	BitmapMat dest;
	int width = imageMat.matrixB.width;
	int height = imageMat.matrixB.height;
	if (imageMat.channel == 3) {
		dest.channel = 3;
		dest.matrixB = imageMat.matrixB.copy();
		dest.matrixG = imageMat.matrixG.copy();
		dest.matrixR = imageMat.matrixR.copy();
		float* infof = (float*)malloc(sizeof(float)*size*size);
		for (int i = (size - 1) / 2; i < height - (size - 1) / 2; i++) {
			for (int j = (size - 1) / 2; j < width - (size - 1) / 2; j++) {			
				for (int l = 0; l < size; l++) {
					imageMat.matrixB.getRowsPart(i + l - (size - 1) / 2 + 1, infof + l*size, j - (size - 1) / 2 + 1, j + (size - 1) / 2 + 1);
				}
				Matrix info(size, size, infof);
				dest.matrixB.setPixel(i + 1, j + 1, getFilterWindow(type, info, size, T));
				info.destory();

				for (int l = 0; l < size; l++) {
					imageMat.matrixG.getRowsPart(i + l - (size - 1) / 2 + 1, infof + l*size, j - (size - 1) / 2 + 1, j + (size - 1) / 2 + 1);
				}
				Matrix info2(size, size, infof);
				dest.matrixG.setPixel(i + 1, j + 1, getFilterWindow(type, info2, size, T));
				info2.destory();

				for (int l = 0; l < size; l++) {
					imageMat.matrixR.getRowsPart(i + l - (size - 1) / 2 + 1, infof + l*size, j - (size - 1) / 2 + 1, j + (size - 1) / 2 + 1);
				}
				Matrix info3(size, size, infof);
				dest.matrixR.setPixel(i + 1, j + 1, getFilterWindow(type, info3, size, T));
				info3.destory();
			}
		}
		free(infof);
	}
	else if (imageMat.channel == 1) {
		dest.channel = 1;
		dest.matrixB = imageMat.matrixB.copy();
		float* infof = (float*)malloc(sizeof(float)*size*size);
		for (int i = (size - 1) / 2; i < height - (size - 1) / 2; i++) {
			for (int j = (size - 1) / 2; j < width - (size - 1) / 2; j++) {
				for (int l = 0; l < size; l++) {
					imageMat.matrixB.getRowsPart(i + l - (size - 1) / 2 + 1, infof + l*size, j - (size - 1) / 2 + 1, j + (size - 1) / 2 + 1);
				}
				Matrix info(size, size, infof);
				dest.matrixB.setPixel(i + 1, j + 1, getFilterWindow(type, info, size, T));
				info.destory();
			}
		}
		free(infof);
	}
	return dest;
}


// 产生一个滤波窗口
float ImagProc::getFilterWindow(int type, Matrix info, int size, int T) {
	float result = 0.0f;
	if ((size - 1) % 2 != 0) {
		size = 3;
	}
	if (type == 1) {//均值	
		float sum = 0.0f;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				sum += info.getPixel(i + 1, j + 1);
			}
		}
		result = sum / size / size;
	}
	else if (type == 2) {
		float d[3][3];
		float temp = info.getPixel(2, 2);
		float sum = 0.;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == 1 && j == 1) {
					continue;
				}
				else {
					d[i][j] = 1. / fabs(info.getPixel(i + 1, j + 1) - temp);
					sum += d[i][j];
				}
			}
		}
		float w[9];
		sum += sum;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == 1 && j == 1) {
					w[4] = 0.5;
				}
				else {
					w[i * 3 + j] = d[i][j] / sum;
				}
				result += w[i * 3 + j] * info.getPixel(i + 1, j + 1);
			}
		}
	}
	else if (type == 3) {
		float sum = 0.0f;
		float temp;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (!(i == (size - 1) / 2 && j == (size - 1) / 2)) {
					sum += info.getPixel(i + 1, j + 1);
				}
				else {
					temp = info.getPixel(i + 1, j + 1);
				}
			}
			
		}
		sum = sum / (size*size - 1);
		result = temp - sum > T ? sum : temp;
	}
	else if (type == 4) {
		int Y = (int)size*size / 2;
		int cnt = 0;
		float sum = 0.0f;
		float temp2=0;
		float center = info.getPixel((size - 1) / 2 + 1, (size - 1) / 2 + 1);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (!(i == (size - 1) / 2 && j == (size - 1) / 2)) {
					temp2 = info.getPixel(i + 1, j + 1);
					if (fabs(temp2 - center) >= T) {
						cnt++;
					}
					sum += info.getPixel(i + 1, j + 1);
				}
			}		
		}
		sum = sum / (size*size - 1);
		result = cnt >= Y ? sum : center;
	}
	else if (type == 5) {
		float *temp = (float*)malloc(sizeof(float)*size*size);
		memcpy(temp, info.data, sizeof(float)*size*size);
		Utils utils;
		utils.quicksort(temp, 0, size*size - 1);
		result = *(temp + (size * size - 1) / 2);
	}
	else if (type == 6) {
		float *temp = (float*)malloc(sizeof(float)*size*size);
		memcpy(temp, info.data, sizeof(float)*size*size);
		result = *(temp + (size*size - 1) / 2);
		Utils utils;
		utils.quicksort(temp, 0, size*size - 1);
		float center = *(temp + (size * size - 1) / 2);
		result = result - center > T ? center : result;
	}
	else if (type == 7) {
		float temp[9];
		memcpy(temp, info.data, sizeof(float) * 9);
		result = fabs(temp[4] - temp[8]) + fabs(temp[5] - temp[7]);
	}
	else if (type == 8) {
		float temp[9];
		memcpy(temp, info.data, sizeof(float) * 9);
		result = fabs(temp[6] + temp[7] + temp[8] - temp[0] - temp[1] - temp[2])
			+ fabs(temp[2] + temp[5] + temp[8] - temp[0] - temp[3] - temp[6]);
	}
	else if (type == 9) {
		float temp[9];
		memcpy(temp, info.data, sizeof(float) * 9);
		result = fabs(temp[6] + 2 * temp[7] + temp[8] - temp[0] - 2 * temp[1] - temp[2])
			+ fabs(temp[2] + 2 * temp[5] + temp[8] - temp[0] - 2 * temp[3] - temp[6]);
	}
	else if (type == 10) {
		float temp[9];
		memcpy(temp, info.data, sizeof(float) * 9);
		result = fabs(4 * temp[4] - temp[1] - temp[3] - temp[5] - temp[7]);
	}
	return result;
}
