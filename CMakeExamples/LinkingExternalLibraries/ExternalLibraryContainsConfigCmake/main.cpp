#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(){
    std::cout << "***** *******************************" << std::endl;
    std::cout << "***** Running image program*******" << std::endl;
    std::cout << "***** *******************************" << std::endl;    
    Mat image;    
    image = imread("sample.jpeg");
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}