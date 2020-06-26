#include <opencv2/opencv.hpp>

#define COLOR Scalar(255, 200,0)

using  namespace std;
using namespace cv;

void drawPolyline
        (
                Mat &im,
                const vector<Point2f> &landmarks,
                const int start,
                const int end,
                bool isClosed = false
        );

void drawLandmarks(Mat &im, vector<Point2f> &landmarks);
