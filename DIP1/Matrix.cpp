#include "Matrix.h"



Matrix::Matrix() {
    width = 0;
    height = 0;
}
Matrix::Matrix(int rows, int cols, float* data) {
    this->height = rows;
    this->width = cols;
    this->data = (float*)malloc(sizeof(float)*rows*cols);
    memcpy(this->data, data, sizeof(float)*rows*cols);
}

Matrix::~Matrix() {
}


// ���þ���
int Matrix::setMatrix(int width, int height, float* data) {
    this->width = width;
    this->height = height;
    this->data = data;//��ֱ�Ӹ�ֵָ��!��Ҫ���ԭָ���ڴ�!
    return 0;
}

float Matrix::getPixel(int row, int col) {
    float temp = *(this->data + this->width*(row - 1) + col - 1);
    return temp;
}

// ����ĳ�����ص�ֵ
int Matrix::setPixel(int row, int col, float data) {
    *(this->data + this->width*(row - 1) + col - 1) = data;
    return 0;
}


// ��ȡĳһ�У���Ҫ�ͷ��ڴ�
float* Matrix::getRows(int row) {
    float *temp = (float*)malloc(sizeof(float)*this->width);
    memcpy(temp, this->data + this->width*(row - 1), sizeof(float)*this->width);
    return temp;
}


// ��ȡһ�У���Ҫ�ͷ��ڴ�
float* Matrix::getCols(int col) {
    float *temp = (float*)malloc(sizeof(float)*this->height);
    for (int i = 0; i < this->height; i++) {
        *(temp + i) = *(this->data + this->width*i + col - 1);
    }
    return temp;
}


// ����ĳһ��
int Matrix::setRows(int row, float* data) {
    memcpy(this->data + this->width*(row - 1), data, this->width*sizeof(float));
    return 0;
}


// ����ĳһ��
int Matrix::setCols(int col, float* data) {
    for (int i = 0; i < this->height; i++) {
        *(this->data + this->width*i + col - 1) = *(data + i);
    }
    return 0;
}


// ת��
Matrix Matrix::transpose() {
    Matrix dest;
  /*  float* temp;
    temp = (float*)malloc(sizeof(float)*this->height);*/
    dest.data = (float*)malloc(sizeof(float)*this->height*this->width);
    dest.width = this->height;
    dest.height = this->width;
    for (int i = 0; i < dest.height; i++) {
        dest.setRows(i + 1, this->getCols(i + 1));
        //temp = this->getCols(i+1);
        //memcpy(dest.data + i*dest.width, temp, sizeof(float)*dest.width);
    }
    //free(temp);
    return dest;
}


// �������
Matrix Matrix::add(Matrix matrix) {
    if (matrix.width != this->width || matrix.height != this->height) {
        return Matrix();
    }
    Matrix dest;
    dest.create(matrix.width, matrix.height);
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            dest.setPixel(i+1,j+1,getPixel(i + 1, j + 1)+ matrix.getPixel(i + 1, j + 1));
        }
    }
    return dest;
}


// ���
Matrix Matrix::dot(Matrix matrix) {
    if (matrix.width != this->width || matrix.height != this->height) {
        return Matrix();
    }
    Matrix dest;
    dest.create(matrix.width, matrix.height);
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            dest.setPixel(i + 1, j + 1, getPixel(i + 1, j + 1) * matrix.getPixel(i + 1, j + 1));
        }
    }
    return dest;
}


// ���
Matrix Matrix::dot(float k) {
    Matrix dest;
    dest.create(this->width, this->height);
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            dest.setPixel(i + 1, j + 1, getPixel(i + 1, j + 1) * k);
        }
    }
    return dest;
}


// ���
Matrix Matrix::mul(Matrix matrix) {
    if (this->width == matrix.height) {
        Matrix dest;
        dest.create(matrix.width, this->height);      
        float* factor1;
        float* factor2;
        factor1 = (float*)malloc(this->width * sizeof(float));
        //factor2 = (float*)malloc(this->width * sizeof(float));
        for (int i = 0; i < dest.height; i++) {
            for (int j = 0; j < dest.width; j++) {
                float temp = 0.0;
                this->getRows(i + 1, factor1);
                //factor2 = matrix.getCols(j + 1);
                for (int k = 0; k < this->width; k++) {
                    temp += *(factor1 + k)*matrix.getPixel(k + 1, j + 1);
                }
                dest.setPixel(i + 1, j + 1, temp);
            }
        }
        free(factor1);
        //free(factor2);
        return dest;
    }
    else {
        return Matrix();
    }   
}


// �������
Matrix Matrix::sub(Matrix matrix) {
    if (matrix.width != this->width || matrix.height != this->height) {
        return Matrix();
    }
    Matrix dest;
    dest.create(matrix.width, matrix.height);
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            dest.setPixel(i + 1, j + 1, getPixel(i + 1, j + 1) - matrix.getPixel(i + 1, j + 1));
        }
    }
    return dest;
}


// �������󣬷����ڴ�
int Matrix::create(int width, int height) {
    this->width = width;
    this->height = height;
    this->data = (float*)malloc(sizeof(float)*this->height*this->width);
    return 0;
}

int Matrix::create(int width, int height,float fillcolor) {
    this->width = width;
    this->height = height;
    this->data = (float*)malloc(sizeof(float)*this->height*this->width);
    memset(this->data, fillcolor, sizeof(float)*this->width*this->height);
    return 0;
}


// ���ƾ���
Matrix Matrix::copy() {
    Matrix dest;
    dest.create(this->width, this->height);
    memcpy(dest.data, this->data, this->width*this->height * sizeof(float));
    return dest;
}


// ����
int Matrix::destory() {
    if(this->data!=nullptr)
        free(this->data);
    return 0;
}


// ��ȡĳһ��
int Matrix::getRows(int row, float* data) {
    memcpy(data, this->data + this->width*(row - 1), sizeof(float)*this->width);
    return 0;
}


// ��ȡĳ��һ����Χ��ֵ
int Matrix::getRowsPart(int row, float* data, int start, int end) {
	memcpy(data, this->data + this->width*(row - 1) + start - 1, sizeof(float)*(end - start + 1));
	return 0;
}


// Strassen�㷨���
Matrix Matrix::mulFast(Matrix matrix) {
	if (!(this->width == this->height && matrix.width == matrix.height&& this->width == matrix.width) || matrix.width <= 64) {
		return this->mul(matrix);
	}
	int w1 = matrix.width / 2;
	int w2 = matrix.width - w1;
	float* temp1 = (float*)malloc(sizeof(float)*w1*w1);
	float* temp2 = (float*)malloc(sizeof(float)*w2*w2);
	float* temp3 = (float*)malloc(sizeof(float)*w1*w2);
	//A
	for (int i = 1; i <= w1; i++) {
		this->getRowsPart(i, temp1 + (i - 1)*w1, 1, w1);
	}
	Matrix A11(w1, w1, temp1);

	for (int i = 1; i <= w1; i++) {
		this->getRowsPart(i, temp3 + (i - 1)*w2, w1 + 1, w2);
	}
	Matrix A12(w1, w2, temp3);

	for (int i = w1 + 1; i <= w2; i++) {
		this->getRowsPart(i, temp3 + (i - w1 - 1)*w1, 1, w1);
	}
	Matrix A21(w2, w1, temp3);

	for (int i = w1 + 1; i <= w2; i++) {
		this->getRowsPart(i, temp2+ (i - 1)*w2, w1 + 1, w2);
	}
	Matrix A22(w2, w2, temp2);
	//B
	for (int i = 1; i <= w1; i++) {
		matrix.getRowsPart(i, temp1 + (i - 1)*w1, 1, w1);
	}
	Matrix B11(w1, w1, temp1);

	for (int i = 1; i <= w1; i++) {
		matrix.getRowsPart(i, temp3 + (i - 1)*w2, w1 + 1, w2);
	}
	Matrix B12(w1, w2, temp3);

	for (int i = w1 + 1; i <= w2; i++) {
		matrix.getRowsPart(i, temp3 + (i - w1 - 1)*w1, 1, w1);
	}
	Matrix B21(w2, w1, temp3);

	for (int i = w1 + 1; i <= w2; i++) {
		matrix.getRowsPart(i, temp2 + (i - 1)*w2, w1 + 1, w2);
	}
	Matrix B22(w2, w2, temp2);

	free(temp1);
	free(temp2);
	free(temp3);
	
	//M
	
	//Matrix A11(matrix.height/2,martix.width/2,this->)
	return Matrix();
}


Matrix Matrix::cut(int startrow, int endrow, int startcol, int endcol) {
	if (startrow >= 1 && endrow <= this->height&&startcol >= 1 && endcol <= this->width&&endrow > startrow&&endcol > startcol) {
		float* temp = (float*)malloc(sizeof(float)*(endcol - startcol + 1)*(endrow - startrow + 1));
		for (int i = startrow; i <= endrow; i++) {
			this->getRowsPart(i, temp + (i - startrow)*(endcol - startcol + 1), startcol, endcol);
		}
		Matrix dest((endrow - startrow + 1), (endcol - startcol + 1), temp);
		free(temp);
		return dest;
	}
	
	return Matrix();
}



void Matrix::operator=(Matrix& mat) {
    destory();
    if (mat.data != nullptr) {
        this->width = mat.width;
        this->height = mat.height;
        this->data = mat.data;
    }
}


Matrix Matrix::expand(int newWidth, int newHeight) {
	if (newWidth <= this->width && newHeight <= this->height) {
		return *this;
	}
	float* temp = (float*)malloc(sizeof(float)*newWidth*newHeight);
	for (int i = 0; i < this->height; i++) {
		
		memcpy(temp + i*newWidth, this->data + i*this->width, sizeof(float)*this->width);
		for (int j = 0; j < newWidth - this->width; j++) {
			*(temp + i*newWidth + this->width + j) = (float)0.0;
		}
	}
	for (int i = this->height; i < newHeight; i++) {
		for (int j = 0; j < newWidth; j++) {
			*(temp + i*newWidth + j) = (float)0.0;
		}
	}
	Matrix dst(newHeight, newWidth, temp);
	free(temp);
	return dst;
}


Matrix Matrix::normalization(int max, int min) {
    int width = this->width;
    int height = this->height;
    float temp1=FLT_MAX;//��Сֵ
    float temp2=FLT_MIN;//���ֵ

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (temp1 > *(data + i*width + j)) {
                temp1 = *(data + i*width + j);
            }
            if (temp2 < *(data + i*width + j)) {
                temp2 = *(data + i*width + j);
            }
        }
    }
    if (temp1 == temp2) {
        temp1 = 0;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            *(data + i*width + j) = (*(data + i*width + j) - temp1) / (temp2 - temp1)*(max - min) + min;
        }
    }
    Matrix dst(height, width, this->data);
    return dst;
}
