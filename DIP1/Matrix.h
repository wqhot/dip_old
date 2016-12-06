////////////////////////////////////////////////////////////////
//FileName:Matrix.h//Creator:WQ
//Date:2016��10��30��00:33:21
//Comment:����Ļ�������
//
///////////////////////////////////////////////////////////////
#ifndef MATRIX_H
#define MATRIX_H
#include <malloc.h>
#include <string.h>
#include <cfloat> 

class Matrix {
public:
    Matrix();
    Matrix(int rows, int cols, float* data);
    ~Matrix();
    int width;
    int height;
    float*data;
    // ���þ���
    int setMatrix(int width, int height, float* data);
    // �õ�ĳ�����ص�ֵ
    float getPixel(int row, int col);
    // ����ĳ�����ص�ֵ
    int setPixel(int row, int col, float data);
    // ��ȡĳһ�У���Ҫ�ͷ��ڴ�
    float* getRows(int row);
    // ��ȡһ�У���Ҫ�ͷ��ڴ棬��
    float* getCols(int col);
    // ����ĳһ��
    int setRows(int row, float* data);
    // ����ĳһ��
    int setCols(int col, float* data);
    // ת��
    Matrix transpose();
    // �������
    Matrix add(Matrix matrix);
    // ���
    Matrix dot(Matrix matrix);
    // ���
    Matrix dot(float k);
    // ���
    Matrix mul(Matrix matrix);
    // �������
    Matrix sub(Matrix matrix);
    // �������󣬷����ڴ�
    int create(int width, int height);
    // �������󣬷����ڴ�
    int create(int width, int height,float fillcolor );
    // ���ƾ���
    Matrix copy();
    // ����
    int destory();
    // ��ȡĳһ��
    int getRows(int row, float* data);
	// ��ȡĳ��һ����Χ��ֵ
	int getRowsPart(int row, float* data, int start, int end);
	// Strassen�㷨���
	Matrix mulFast(Matrix matrix);
	Matrix cut(int startrow, int endrow, int startcol, int endcol);
	//Matrix& operator=(Matrix mat);
    void operator = (Matrix & mat);
	Matrix expand(int newWidth, int newHeight);
    Matrix normalization(int max, int min);
};
#endif
