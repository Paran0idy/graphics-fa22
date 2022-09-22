#ifndef LAB2_METHOD_H
#define LAB2_METHOD_H
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void color2grey(Mat &src, Mat &dst);  //转灰度图像
void grey_Histogram(Mat &src, Mat &dst, vector<double> &grey_hist_value);
void grey_Equalization(Mat &src, Mat &dst, vector<double> &grey_hist_value);
void color_Histogram(Mat &src, Mat &dst, vector<vector<double>> &color_hist_value);
void color_Equalization(Mat &src, Mat &dst, vector<vector<double>> &color_hist_value);

#endif //LAB2_METHOD_H
