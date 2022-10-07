#include "method.h"

void color2grey(Mat &src, Mat &dst){
    int r = src.rows, c = src.cols;
    dst = Mat::zeros(src.size(), CV_8UC1);
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            for(int k = 0; k < 3; k++)
                dst.at<uchar>(i, j) += src.at<Vec3b>(i , j)[k] / 3;
}

 void grey_Histogram(Mat &src, Mat &dst, vector<double> &grey_hist_value){
    //将灰度频率存入数组，并归一化
    double r = src.rows, c = src.cols;
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++) grey_hist_value[src.at<uchar>(i, j)]++;
    double size = r * c;
    double max_value = -1;
    for(int i = 0; i < 256; i++){
        grey_hist_value[i] /= size;
        max_value = max(grey_hist_value[i], max_value);
    }
    //绘制直方图
    int scale = 20000;   //定义缩放尺度
    int hist_h = scale * max_value, hist_w = 280;
    dst = Mat::zeros(hist_h, hist_w, CV_8U);
    for(int i = 0; i < 256; i++){
        int realValue  = grey_hist_value[i] * scale;
        rectangle(dst,
                      Point(i, hist_h - realValue),
                      Point(i + 1, hist_h),
                      Scalar(255));
    }
}

void grey_Equalization(Mat &src, Mat &dst, vector<double> &grey_hist_value){
    dst = Mat::zeros(src.size(), src.type());
    for(int i = 0; i < src.rows; i++)
        for(int j = 0; j < src.cols; j++){
            int k = src.at<uchar>(i, j);
            double sum = 0;
            for(int l = 0; l <= k; l++) sum += grey_hist_value[l];
            dst.at<uchar>(i, j) = sum * (256 - 1);
        }
}

void color_Histogram(Mat &src, Mat &dst, vector<vector<double>> &color_hist_value){
    double r = src.rows, c = src.cols;
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            for(int k = 0; k < 3; k++)
                color_hist_value[k][src.at<Vec3b>(i , j)[k]]++;
    double size = r * c;
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 3; j++)
            color_hist_value[j][i] /= size;
    }
}
void color_Equalization(Mat &src, Mat &dst, vector<vector<double>> &color_hist_value){
    dst = Mat::zeros(src.size(), src.type());
    for(int i = 0; i < src.rows; i++)
        for(int j = 0; j < src.cols; j++)
            for(int l = 0; l < 3; l++){
                int k = src.at<Vec3b>(i, j)[l];
                double sum = 0;
                for(int m = 0; m <= k; m++) sum += color_hist_value[l][m];
                dst.at<Vec3b>(i, j)[l] = sum * (256 - 1);
            }
}