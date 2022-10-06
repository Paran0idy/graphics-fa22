#include "method.h"

int main() {
    //读取图像
    Mat image = imread("../lena.jpg");
    if(image.empty()){
        printf("open image failed!\n");
        exit(1);
    }
    namedWindow("image",WINDOW_FREERATIO); //调整尺寸
    imshow("image", image);

    //灰度化
    Mat grey_image;
    color2grey(image, grey_image);
    namedWindow("grey_image",WINDOW_FREERATIO);
    imshow("grey_image", grey_image);

    //灰度图像均值滤波
    Mat mean_filter;
    filter(grey_image, mean_filter, 3, Mean);
    namedWindow("mean_filter",WINDOW_FREERATIO);
    imshow("mean_filter", mean_filter);

    //灰度图像高斯滤波
    Mat gauss_filter;
    filter(grey_image, gauss_filter, 3, Gauss);  // sigma = 0.01
    namedWindow("gauss_filter",WINDOW_FREERATIO);
    imshow("gauss_filter", gauss_filter);

    //灰度图像Laplace锐化
    Mat laplace_filter;
    filter(grey_image, laplace_filter, 3, Laplace);
    namedWindow("laplace_filter",WINDOW_FREERATIO);
    imshow("laplace_filter", laplace_filter);

    //灰度图像Robert锐化
    Mat robert_filter;
    filter(grey_image, robert_filter, 3, Robert);
    namedWindow("robert_filter",WINDOW_FREERATIO);
    imshow("robert_filter", robert_filter);

    //灰度图像Sobel锐化
    Mat sobel_filter;
    filter(grey_image, sobel_filter, 3, Sobel);
    namedWindow("sobel_filter",WINDOW_FREERATIO);
    imshow("sobel_filter", sobel_filter);

    //灰度图像高提升滤波
    Mat up_filter;
    filter(grey_image, up_filter, 3, Up);
    namedWindow("up_filter",WINDOW_FREERATIO);
    imshow("up_filter", up_filter);

    //彩色图像均值滤波
    Mat color_mean;
    filter(image, color_mean, 3, Mean);
    namedWindow("color_mean",WINDOW_FREERATIO);
    imshow("color_mean", color_mean);

    //彩色图像高斯滤波
    Mat color_gauss;
    filter(image, color_gauss, 3, Gauss);   // sigma = 0.01
    namedWindow("color_gauss",WINDOW_FREERATIO);
    imshow("color_gauss", color_gauss);

    //彩色图像Laplace锐化
    Mat color_laplace;
    filter(image, color_laplace, 3, Laplace);
    namedWindow("color_laplace",WINDOW_FREERATIO);
    imshow("color_laplace", color_laplace);

    //彩色图像Robert锐化
    Mat color_robert;
    filter(image, color_robert, 3, Robert);
    namedWindow("color_robert",WINDOW_FREERATIO);
    imshow("color_robert", color_robert);

    //彩色图像Sobel锐化
    Mat color_sobel;
    filter(image, color_sobel, 3, Sobel);
    namedWindow("color_sobel",WINDOW_FREERATIO);
    imshow("color_sobel", color_sobel);

    waitKey(0);

    return 0;
}