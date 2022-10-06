#include "method.h"

uchar saturate(int val){
    if(val > 255) return 255;
    else if(val < 0) return 0;
    return val;
}

void color2grey(Mat &src, Mat &dst){
    int r = src.rows, c = src.cols;
    dst = Mat::zeros(src.size(), CV_8UC1);
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            for(int k = 0; k < 3; k++)
                dst.at<uchar>(i, j) += src.at<Vec3b>(i, j)[k] / 3;
}

void filter(Mat &src, Mat &dst, int size, uchar (*func)(Mat image)){
    int border = size / 2;
    Mat tmp;
    copyMakeBorder(src, tmp, border, border, border, border, BorderTypes::BORDER_DEFAULT);
    dst = Mat::zeros(src.size(), src.type());
    int r = dst.rows, c = dst.cols;

    for(int k = 0; k < src.channels(); k++){
        if(src.channels() > 1){                     // 传入的是彩色图像
            vector<Mat> vec(src.channels());
            split(tmp, vec);                // 通道分割
            for(int i = border; i < r + border; i++)
                for(int j = border; j < c + border; j++)
                    dst.at<Vec3b>(i - border, j - border)[k] = func(vec[k](Rect(j - border, i - border, size, size)));
        }
        else{                                       // 传入的是灰度图像
            for(int i = border; i < r + border; i++)
                for(int j = border; j < c + border; j++)
                    dst.at<uchar>(i - border, j - border) = func(tmp(Rect(j - border, i - border, size, size)));
        }
    }
}

Mat Mean_kernel(int size){
    return Mat::ones(size, size, CV_64FC1);
}

Mat Gauss_kernel(int size){
    double sigma = 0.01;
    Mat kernel = Mat::zeros(size, size, CV_64FC1);
    int center = size / 2;       // 中点
    double sum = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++) {
            kernel.at<double>(i, j) = 1 / (2 * CV_PI * sigma * sigma) *
                                      exp(-((i - center) * (i - center) + (j - center) * (j - center)) /
                                          (2 * sigma * sigma));
            sum += kernel.at<double>(i, j);
        }

    // 归一化
    for(int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) kernel.at<double>(i, j) /= sum;

    return kernel;
}

Mat Laplace_kernel(int size){
    Mat kernel = (Mat_<double>(3,3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
    return kernel;
}

vector<Mat> Robert_kernel(int size){
    Mat kernel_x = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 0, 0, 0, 1);
    Mat kernel_y = (Mat_<double>(3, 3) << 0, 0, 0, 0, 0, -1, 0, 1, 0);
    vector<Mat> kernel;
    kernel.push_back(kernel_x);
    kernel.push_back(kernel_y);
    return kernel;
}

vector<Mat> Sobel_kernel(int size){
    Mat kernel_x = (Mat_<double>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    Mat kernel_y = (Mat_<double>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    vector<Mat> kernel;
    kernel.push_back(kernel_x);
    kernel.push_back(kernel_y);
    return kernel;
}

uchar Mean(Mat image){
    int size = image.rows;
    Mat kernel = Mean_kernel(size);
    double res = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            res += image.at<uchar>(i, j) * kernel.at<double>(i, j) / (size * size);
    return saturate(res);
}

uchar Gauss(Mat image){
    int size = image.rows;
    Mat kernel = Gauss_kernel(size);
    double res = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            res += image.at<uchar>(i, j) * kernel.at<double>(i, j);
    return saturate(res);
}

uchar Laplace(Mat image){
    int size = image.rows;
    Mat kernel = Laplace_kernel(size);
    double res = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            res += image.at<uchar>(i, j) * kernel.at<double>(i, j);
    res += image.at<uchar>(size / 2, size / 2);         // 加上本身
    return saturate(res);
}


uchar Robert(Mat image){
    int size = image.rows;
    vector<Mat> kernel = Robert_kernel(size);
    Mat kernel_x = kernel[0];
    Mat kernel_y = kernel[1];
    double res = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++) {
            res += image.at<uchar>(i, j) * kernel_x.at<double>(i, j);
            res += image.at<uchar>(i, j) * kernel_y.at<double>(i, j);
        }
    res += image.at<uchar>(size / 2, size / 2);
    return saturate(res);
}

uchar Sobel(Mat image){
    int size = image.rows;
    vector<Mat> kernel = Sobel_kernel(size);
    Mat kernel_x = kernel[0];
    Mat kernel_y = kernel[1];
    double res = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++) {
            res += image.at<uchar>(i, j) * kernel_x.at<double>(i, j);
            res += image.at<uchar>(i, j) * kernel_y.at<double>(i, j);
        }
    res += image.at<uchar>(size / 2, size / 2);
    return saturate(res);
}

uchar Up(Mat image){
    int size = image.rows;
    Mat kernel = Gauss_kernel(size);
    double res = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            res += image.at<uchar>(i, j) * kernel.at<double>(i, j);
    res = image.at<uchar>(size / 2, size / 2) + 3 * (image.at<uchar>(size / 2, size / 2) - res);    // k = 3
    return saturate(res);
}