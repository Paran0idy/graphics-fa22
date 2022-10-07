#include "method.h"

int main(){
    //读取图像
    Mat image = imread("../lena.jpg");
    if(image.empty()){  // 错误处理
        printf("open image failed!\n");
        exit(1);
    }
    namedWindow("image",WINDOW_FREERATIO); //调整尺寸
    imshow("image", image);

    //灰度化
    Mat grey_image;
    color2grey(image, grey_image);
    imshow("grey_image", grey_image);

    //二值化
    Mat bin_image;
    binarization(grey_image, bin_image, 127);
    imshow("bin_image", bin_image);

    //对数变换
    Mat log_image;
    logtransform(grey_image, log_image, 20);
    imshow("log_image", log_image);

    //伽马变换
    Mat gamma_image;
    gammatransform(grey_image, gamma_image, 1, 1.1);
    imshow("gamma_image", gamma_image);

    //补色变换
    Mat comple_image;
    completransform(image, comple_image);
    imshow("comple_image", comple_image);

    waitKey(0);
    destroyAllWindows();
    return 0;
}