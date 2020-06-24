#include  <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc , char **argv){
    if (argc < 2)
    {
        cerr << "Input should be an image" << endl;
        return -1;
    }
    Mat  img = imread(argv[1]);// 3 channel BGR color
    Vec3b intensity = img.at<Vec3b>(12,4);// random coordinates (y=12, x=4)
    uchar blue = intensity.val[0];
    uchar green = intensity.val[1];
    uchar red = intensity.val[2];

    cout << "Blue: " << blue << " Green: " << green << " Red: " << red << endl;
    return 0;
}