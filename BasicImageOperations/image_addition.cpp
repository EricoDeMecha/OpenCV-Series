#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using  namespace std;
using namespace cv;

int main()
{
    Mat src1, src2 , dst;
    double input; double alpha = 0.5; double beta;
    cout << "Simple Linear Blending" << endl;
    cout << "----------------" << endl;
    cout << "Enter alpha[0-1]: ";
    cin >> input;
    if (input >= 0.0 && input  <= 1.0)
    { alpha = input;}
    // open the two images
    src1 = imread("../17808.jpg");
    src2 = imread("../17779.jpg");
    if(!src1.data) {printf("Error loading image src1"); }
    if(!src2.data) {printf("Error loading image src2");}
    // resizing of the images by 75% on each axis
    try {
        resize(src1, src1, cv::Size(320, 640));
        resize(src2, src2, cv::Size(320,640));
    } catch(exception& e)
    {
        cerr << e.what() << endl;
    }
    beta = (1-alpha);
    // adding the two images
    addWeighted(src1, alpha, src2, beta,0.0,dst);
    namedWindow("Blended" , 1);
    imshow("Blended", dst);
    waitKey(0);
    return 0;
}