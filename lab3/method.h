#ifndef LAB3_METHOD_H
#define LAB3_METHOD_H

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

uchar saturate(int val);                // 溢出检测
void color2grey(Mat &src, Mat &dst);    // 彩色图转灰度图
void filter(Mat &src, Mat &dst, int size, uchar (*func)(Mat image));  // 滤波通用模板

//获取滤波核
Mat Mean_kernel(int size);
Mat Gauss_kernel(int size);
Mat Laplace_kernel(int size);
vector<Mat> Robert_kernel(int size);
vector<Mat> Sobel_kernel(int size);

//滤波操作(回调函数)
uchar Mean(Mat image);
uchar Gauss(Mat image);
uchar Laplace(Mat image);
uchar Robert(Mat image);
uchar Sobel(Mat image);
uchar Up(Mat image);

#endif //LAB3_METHOD_H
