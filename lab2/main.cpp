#include "method.h"

int main(){
    Mat image = imread("../Lena.bmp");
    if(image.empty()){
        printf("open image failed!\n");
        exit(1);
    }

    // 灰度图像绘制直方图
    Mat grey_image, histogram;
    vector<double> hist_value(256, 0);
    color2grey(image, grey_image);
    grey_Histogram(grey_image, histogram, hist_value);
    namedWindow("Histogram", 0);
    imshow("Histogram", histogram);


    // 灰度图像均衡化
    Mat grey_equalization;
    grey_Equalization(grey_image, grey_equalization, hist_value);
    namedWindow("grey_Equalization", 0);
    imshow("grey_Equalization", grey_equalization);

    // 彩色图像均衡化
    Mat color_equalization;
    vector<vector<double>> color_hist_value(3, vector<double>(256, 0));
    color_Histogram(image, color_equalization, color_hist_value);
    color_Equalization(image, color_equalization, color_hist_value);
    namedWindow("color_Equalization", 0);
    imshow("color_Equalization", color_equalization);

    waitKey(0);
    return 0;
}