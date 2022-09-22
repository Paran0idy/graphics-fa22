#ifndef LAB1_METHOD_H
#define LAB1_METHOD_H

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void color2grey(Mat &src, Mat &dst);
void binarization(Mat &src, Mat &dst, uchar value);
void logtransform(Mat &src, Mat &dst, int factor);
void gammatransform(Mat &src, Mat &dst, int factor, double gamma);
void completransform(Mat &src, Mat &dst);




#endif //LAB1_METHOD_H
