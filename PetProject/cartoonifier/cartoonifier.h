#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

inline namespace  ct{
    void cartoonify(Mat& orgFrame, Mat& dispFrame){
        // convert image to grayscale
        Mat gray;
        cvtColor(orgFrame, gray, COLOR_BGR2GRAY);
        // remove noise in the grayed image
        medianBlur(gray,gray,7);
        Mat edges;
        // Obtain sketches from the image
        Laplacian(gray,edges,CV_8U,5);
        // clean the sketches
        threshold(gray,dispFrame,80,255,THRESH_BINARY_INV);
    }
    void colorPaintCartoon(Mat& orgFrame, Mat& dispFrame){
        // shrunk the image by 4 for bilateral filter
        Size  _size = orgFrame.size();
        Size __size;
        __size.width = _size.width/2;
        __size.height = _size.height/2;
        Mat bImg(__size , CV_8UC3);
        resize(orgFrame, bImg, __size,0,0, INTER_LINEAR);
    }
}
