#include "FreCal.h"
#include <math.h>


FreCal::FreCal() {
}

FreCal::~FreCal() {
}


// 二维傅里叶变换
//FreCal FreCal::fft2(Matrix matrix) {
//	int width = matrix.width;
//	int height = matrix.height;
//	float* Rdata = (float*)malloc(sizeof(float)*width*height);
//	float* Idata = (float*)malloc(sizeof(float)*width*height);
//	float* amplitude = (float*)malloc(sizeof(float)*width*height);
//	float* phase = (float*)malloc(sizeof(float)*width*height);
//	float* energy = (float*)malloc(sizeof(float)*width*height);
//	//float* matdata= (float*)malloc(sizeof(float)*width*height);
//	float* matdata;
//	matdata = matrix.data;
//	//e^ix=cosx+i*sinx
//	for (int u = 0; u < height; u++) {
//		for (int v = 0; v < width; v++) {
//			float sumr = 0;
//			float sumi = 0;
//			for (int x = 0; x < height; x++) {
//				for (int y = 0; y < width; y++) {
//					float er = cos(-2.0 * DIP_PI*((float)u*(float)x / (float)height + (float)v*(float)y / (float)width));
//					float ei = sin(-2.0 * DIP_PI*((float)u*(float)x / (float)height + (float)v*(float)y / (float)width));
//					float temp = ((x + y) % 2 == 0 ? 1 : -1);
//					sumr += *(matdata + x*width + y)*er*temp;
//					sumi += *(matdata + x*width + y)*ei*temp;
//				}
//			}
//			//sumr = sumr / width / height;
//			//sumi = sumi / width / height;
//			*(Rdata + width*u + v) = sumr;
//			*(Idata + width*u + v) = sumi;
//			*(amplitude + width*u + v) = sqrt(sumr*sumr + sumi*sumi);
//			*(phase + width*u + v) = atan(sumi / sumr);
//			*(energy + width*u + v) = *(amplitude + width*u + v) * *(amplitude + width*u + v);
//		}
//	}
//	FreCal dest;
//	dest.R.setMatrix(height, width, Rdata);
//	dest.I.setMatrix(height, width, Idata);
//	dest.amplitude.setMatrix(height, width, amplitude);
//	dest.phase.setMatrix(height, width, phase);
//	dest.energy.setMatrix(height, width, energy);
//	return dest;
//}


//int FreCal::destory() {
//	this->amplitude.destory();
//	this->energy.destory();
//	this->I.destory();
//	this->phase.destory();
//	this->R.destory();
//	return 0;
//}


BitmapMat FreCal::fre2im(Complex* src, int size_w, int size_h) {
	BitmapMat dest;
	dest.channel = 1;
	int base2_w = size_w;
	if (isBase2(size_w) == -1) {
		base2_w = 1 << getBase2(size_w);
	}
	dest.matrixB.create(size_w, size_h);
	for (int i = 0; i < size_h; i++) {
		for (int j = 0; j < size_w; j++) {
			Complex temp = *(src + i*base2_w + j);
			float t = sqrt(temp.real*temp.real + temp.imagin*temp.imagin);
			dest.matrixB.setPixel(i + 1, j + 1, t);
		}
	}
	//memcpy(dest.matrixB.data, this->amplitude.data, this->amplitude.width*this->amplitude.height * sizeof(float));
	//dest.matrixB = dest.matrixB.dot(1.0 / this->amplitude.width / this->amplitude.height);

	return dest;
}


// 傅里叶反变换
//int FreCal::ifft2(Matrix& matrix) {
//	int width = this->R.width;
//	int height = this->R.height;
//	float* data = (float*)malloc(sizeof(float)*width*height);
//	float* matdataR;
//	float* matdataI;
//	matdataR = this->R.data;
//	matdataI = this->I.data;
//	for (int u = 0; u < height; u++) {
//		for (int v = 0; v < width; v++) {
//			float sumr = 0;
//			//float sumi = 0;
//			for (int x = 0; x < height; x++) {
//				for (int y = 0; y < width; y++) {
//					float er = cos(2.0 * DIP_PI*((float)u*(float)x / (float)height + (float)v*(float)y / (float)width));
//					float ei = sin(2.0 * DIP_PI*((float)u*(float)x / (float)height + (float)v*(float)y / (float)width));
//					//float temp = (-1) ^ (x + y);
//					sumr += *(matdataR + x*width + y)*er - *(matdataI + x*width + y)*ei;
//					//sumi += this->R.getPixel(x + 1, y + 1)*ei + this->I.getPixel(x + 1, y + 1)*er;
//				}
//			}
//			sumr = sumr / width / height;
//			//sumi = sumi / width / height;
//			*(data + width*u + v) = sumr* ((u + v) % 2 == 0 ? 1 : -1);
//		}
//	}
//	matrix.destory();
//	//matrix.create(height, width);
//	matrix.setMatrix(height, width, data);
//	//Matrix dest(height, width, data);
//	//free(data);
//	return 0;
//}


// 快速傅里叶变换
//FreCal FreCal::dft2d(Matrix matrix) {
//	int width = matrix.width;
//	int height = matrix.height;
//	float* Rdata = (float*)malloc(sizeof(float)*width*height);
//	float* Idata = (float*)malloc(sizeof(float)*width*height);
//	float* amplitude = (float*)malloc(sizeof(float)*width*height);
//	float* phase = (float*)malloc(sizeof(float)*width*height);
//	float* energy = (float*)malloc(sizeof(float)*width*height);
//	//float* matdata= (float*)malloc(sizeof(float)*width*height);
//	float* matdata;
//	matdata = matrix.data;
//	for (int u = 0; u < height; u++) {
//		for (int v = 0; v < width; v++) {
//			float sumr = 0;
//			float sumi = 0;
//			for (int x = 0; x < height; x++) {
//				for (int y = 0; y < width; y++) {
//					float er = cos(-2.0 * DIP_PI*((float)u*(float)x / (float)height + (float)v*(float)y / (float)width));
//					float ei = sin(-2.0 * DIP_PI*((float)u*(float)x / (float)height + (float)v*(float)y / (float)width));
//					float temp = ((x + y) % 2 == 0 ? 1 : -1);
//					sumr += *(matdata + x*width + y)*er*temp;
//					sumi += *(matdata + x*width + y)*ei*temp;
//				}
//			}
//			
//			//sumr = sumr / width / height;
//			//sumi = sumi / width / height;
//			*(Rdata + width*u + v) = sumr;
//			*(Idata + width*u + v) = sumi;
//			*(amplitude + width*u + v) = sqrt(sumr*sumr + sumi*sumi);
//			*(phase + width*u + v) = atan(sumi / sumr);
//			*(energy + width*u + v) = *(amplitude + width*u + v) * *(amplitude + width*u + v);
//		}
//	}
//	return FreCal();
//}


int FreCal::addComplex(Complex * src1, Complex * src2, Complex * dst) {
	dst->imagin = src1->imagin + src2->imagin;
	dst->real = src1->real + src2->real;
	return 0;
}


int FreCal::subComplex(Complex * src1, Complex * src2, Complex * dst) {
	dst->imagin = src1->imagin - src2->imagin;
	dst->real = src1->real - src2->real;
	return 0;
}


int FreCal::mulComplex(Complex * src1, Complex * src2, Complex * dst) {
	float r1 = 0.0, r2 = 0.0;
	float i1 = 0.0, i2 = 0.0;
	r1 = src1->real;
	r2 = src2->real;
	i1 = src1->imagin;
	i2 = src2->imagin;
	dst->imagin = r1*i2 + r2*i1;
	dst->real = r1*r2 - i1*i2;
	return 0;
}


int FreCal::copyComplex(Complex * src, Complex * dst) {
	dst->real = src->real;
	dst->imagin = src->imagin;
	return 0;
}


int FreCal::getW(float n, float size_n, Complex * dst) {
	float x = 2.0*DIP_PI*n / size_n;
	dst->imagin = -sin(x);
	dst->real = cos(x);
	return 0;
}


int FreCal::FFTRealRemap(float* src, int size_n) {
	if (size_n == 1)
		return 0;
	float * temp = (float *)malloc(sizeof(float)*size_n);
	for (int i = 0; i<size_n; i++)
		if (i % 2 == 0)
			temp[i / 2] = src[i];
		else
			temp[(size_n + i) / 2] = src[i];
	for (int i = 0; i<size_n; i++)
		src[i] = temp[i];
	free(temp);
	FFTRealRemap(src, size_n / 2);
	FFTRealRemap(src + size_n / 2, size_n / 2);
	return 0;
}


int FreCal::FFTComplexRemap(Complex * src, int size_n) {
	if (size_n == 1)
		return 0;
	Complex * temp = (Complex *)malloc(sizeof(Complex)*size_n);9
	for (int i = 0; i<size_n; i++)
		if (i % 2 == 0)
			copyComplex(&src[i], &(temp[i / 2]));
		else
			copyComplex(&(src[i]), &(temp[(size_n + i) / 2]));
	for (int i = 0; i<size_n; i++)
		copyComplex(&(temp[i]), &(src[i]));
	free(temp);
	FFTComplexRemap(src, size_n / 2);
	FFTComplexRemap(src + size_n / 2, size_n / 2);
	return 0;
}


int FreCal::FFT(Complex * src, Complex * dst, int size_n) {
	int k = size_n;
	int z = 0;
	while (k /= 2) {
		z++;
	}
	k = z;
	if (size_n != (1 << k))
		return -1;
	Complex * src_com = (Complex*)malloc(sizeof(Complex)*size_n);

	for (int i = 0; i<size_n; i++) {
		copyComplex(&src[i], &src_com[i]);
	}
	FFTComplexRemap(src_com, size_n);
	for (int i = 0; i<k; i++) {
		z = 0;
		for (int j = 0; j<size_n; j++) {
			if ((j / (1 << i)) % 2 == 1) {
				Complex wn;
				getW(z, size_n, &wn);
				mulComplex(&src_com[j], &wn, &src_com[j]);
				z += 1 << (k - i - 1);
				Complex temp;
				int neighbour = j - (1 << (i));
				temp.real = src_com[neighbour].real;
				temp.imagin = src_com[neighbour].imagin;
				addComplex(&temp, &src_com[j], &src_com[neighbour]);
				subComplex(&temp, &src_com[j], &src_com[j]);
			}
			else
				z = 0;
		}
	}
	for (int i = 0; i<size_n; i++) {
		copyComplex(&src_com[i], &dst[i]);
	}
	free(src_com);
	return 0;
}


int FreCal::reaFFT(float * src, Complex * dst, int size_n) {
	int k = size_n;
	int z = 0;
	while (k /= 2) {
		z++;
	}
	k = z;
	if (size_n != (1 << k))
		return -1;
	Complex * src_com = (Complex*)malloc(sizeof(Complex)*size_n);
	for (int i = 0; i<size_n; i++) {
		src_com[i].real = src[i];
		src_com[i].imagin = 0;
	}
	FFTComplexRemap(src_com, size_n);
	for (int i = 0; i<k; i++) {
		z = 0;
		for (int j = 0; j<size_n; j++) {
			if ((j / (1 << i)) % 2 == 1) {
				Complex wn;
				getW(z, size_n, &wn);
				mulComplex(&src_com[j], &wn, &src_com[j]);
				z += 1 << (k - i - 1);
				Complex temp;
				int neighbour = j - (1 << (i));
				temp.real = src_com[neighbour].real;
				temp.imagin = src_com[neighbour].imagin;
				addComplex(&temp, &src_com[j], &src_com[neighbour]);
				subComplex(&temp, &src_com[j], &src_com[j]);
			}
			else
				z = 0;
		}
	}
	for (int i = 0; i<size_n; i++) {
		copyComplex(&src_com[i], &dst[i]);
	}
	free(src_com);
	return 0;
}


int FreCal::IFFT(Complex * src, Complex * dst, int size_n) {
	for (int i = 0; i<size_n; i++)
		src[i].imagin = -src[i].imagin;
	FFTComplexRemap(src, size_n);
	int z, k;
	if ((z = isBase2(size_n)) != -1)
		k = isBase2(size_n);
	else
		return -1;
	for (int i = 0; i<k; i++) {
		z = 0;
		for (int j = 0; j<size_n; j++) {
			if ((j / (1 << i)) % 2 == 1) {
				Complex wn;
				getW(z, size_n, &wn);
				mulComplex(&src[j], &wn, &src[j]);
				z += 1 << (k - i - 1);
				Complex temp;
				int neighbour = j - (1 << (i));
				copyComplex(&src[neighbour], &temp);
				addComplex(&temp, &src[j], &src[neighbour]);
				subComplex(&temp, &src[j], &src[j]);
			}
			else
				z = 0;
		}
	}
	for (int i = 0; i<size_n; i++) {
		dst[i].imagin = (1. / size_n)*src[i].imagin;
		dst[i].real = (1. / size_n)*src[i].real;
	}
	return 0;
}


int FreCal::isBase2(int n) {
	int k = n;
	int z = 0;
	while (k /= 2) {
		z++;
	}
	k = z;
	if (n != (1 << k))
		return -1;
	else
		return k;
	return 0;
}


Complex * FreCal::DFT2D(Matrix& mat/*, Complex * dst*/) {
	int size_w = mat.width;
	int size_h = mat.height;

	if (isBase2(size_w) == -1 || isBase2(size_h) == -1) {
		int newWidth = 1 << getBase2(size_w);
		int newHeight = 1 << getBase2(size_h);
		size_h = newHeight;
		size_w = newWidth;
		mat = mat.expand(newWidth, newHeight);
	}
	float* src = (float*)malloc(sizeof(float)*size_w*size_h);
	Complex * dst = (Complex*)malloc(sizeof(Complex)*size_w*size_h);
	memcpy(src, mat.data, sizeof(float)*size_w*size_h);
	for (int i = 0; i < size_h; i++) {
		for (int j = 0; j < size_w; j++) {
			*(src + i*size_w + j) *= (i + j) % 2 == 0 ? 1 : -1;
		}
	}
	Complex *temp = (Complex *)malloc(sizeof(Complex)*size_h*size_w);
	for (int i = 0; i<size_h; i++) {
		reaFFT(&src[size_w*i], &temp[size_w*i], size_w);
	}

	Complex *Column = (Complex *)malloc(sizeof(Complex)*size_h);

	for (int i = 0; i<size_w; i++) {
		columnVector(&temp[i], Column, size_w, size_h);
		FFT(Column, Column, size_h);
		iColumnVector(Column, &temp[i], size_w, size_h);

	}
	for (int i = 0; i<size_h*size_w; i++)
		copyComplex(&temp[i], &dst[i]);
	free(temp);
	free(Column);
	free(src);
	return dst;
}


int FreCal::IDFT2D(Complex * src, Matrix& dest, int size_w, int size_h, int old_w,int old_h) {
	if (isBase2(size_w) == -1 || isBase2(size_h) == -1)
		return -1;

	Complex *temp = (Complex *)malloc(sizeof(Complex)*size_h*size_w);
	if (temp == NULL)
		return -1;
	Complex *Column = (Complex *)malloc(sizeof(Complex)*size_h);
	if (Column == NULL)
		return -1;

	for (int i = 0; i<size_w; i++) {
		columnVector(&src[i], Column, size_w, size_h);
		IFFT(Column, Column, size_h);
		iColumnVector(Column, &src[i], size_w, size_h);

	}
	for (int i = 0; i<size_w*size_h; i++)
		src[i].imagin = -src[i].imagin;
	for (int i = 0; i<size_h; i++) {
		IFFT(&src[size_w*i], &temp[size_w*i], size_w);

	}
	Complex* dst = (Complex*)malloc(sizeof(Complex)*size_w*size_h);
	dest.destory();
	dest.create(size_w, size_h);
	for (int i = 0; i<size_h*size_w; i++){
		copyComplex(&temp[i], dst + i);
		Complex c = *(dst + i);
		*(dest.data + i) = c.real;
	}	
	for (int i = 0; i < size_h; i++) {
		for (int j = 0; j < size_w; j++) {
			dest.setPixel(i + 1, j + 1, dest.getPixel(i + 1, j + 1)* ((i + j) % 2 == 0 ? 1 : -1));
		}
	}
    dest = dest.cut(1, old_h, 1, old_w);

	free(temp);
	free(Column);
	free(dst);
	return 0;
}


int FreCal::columnVector(Complex * src, Complex * dst, int size_w, int size_h) {
	for (int i = 0; i<size_h; i++)
		copyComplex(&src[size_w*i], &dst[i]);
	return 0;
}


int FreCal::iColumnVector(Complex * src, Complex * dst, int size_w, int size_h) {
	for (int i = 0; i<size_h; i++)
		copyComplex(&src[i], &dst[size_w*i]);
	return 0;
}


//Matrix FreCal::expand(int newWidth, int newHeight) {
//	if(newWi)
//	return Matrix();
//}


int FreCal::getBase2(int n) {
	int k = n;
	int z = 0;
	while (k /= 2) {
		z++;
	}
	k = z;
	return k+1;
}
