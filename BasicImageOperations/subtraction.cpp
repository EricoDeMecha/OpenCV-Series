#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat  src, src_part, output;
    src = imread("../17808.jpg");
    src_part = imread("../17808_part.jpg");
    Mat mask = Mat(output.size(), CV_8UC3);
    subtract(src, src_part,output,mask,-1);
    imshow("Subtracted", output);
    return 0;
}