//
// Created by 17622 on 2022/9/18.
//

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
                dst.at<uchar>(i, j) += src.at<Vec3b>(i , j)[k] / 3;
}

void binarization(Mat &src, Mat &dst, uchar value){
    int r = src.rows, c = src.cols;
    dst = src.clone();
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            dst.at<uchar>(i, j) = src.at<uchar>(i, j) > value ? 255 : 0;
}

void logtransform(Mat &src, Mat &dst, int factor){
    int r = src.rows, c = src.cols;
    dst = src.clone();
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            dst.at<uchar>(i, j) = saturate(factor * log((double)(src.at<uchar>(i, j)) + 1));
}

void gammatransform(Mat &src, Mat &dst, int factor, double gamma){
    int r = src.rows, c = src.cols;
    dst = src.clone();
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            dst.at<uchar>(i, j) = saturate(factor * pow(src.at<uchar>(i, j), gamma));
}

void completransform(Mat &src, Mat &dst){
    int r = src.rows, c = src.cols;
    dst = src.clone();
    for(int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            uchar R = src.at<Vec3b>(i, j)[2];
            uchar G = src.at<Vec3b>(i, j)[1];
            uchar B = src.at<Vec3b>(i, j)[0];
            uchar maxRGB = max(max(R, G), B), minRGB = min(min(R, G), B);
            dst.at<Vec3b>(i, j)[2] = maxRGB + minRGB - R;
            dst.at<Vec3b>(i, j)[1] = maxRGB + minRGB - G;
            dst.at<Vec3b>(i, j)[0] = maxRGB + minRGB - B;
        }
}