#include "cartoonifier.h"

int main(){
    VideoCapture cap(0, CAP_V4L);
    // set  the resolution to 640x480
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT,480);

    namedWindow("Window", WINDOW_AUTOSIZE);
    while(waitKey(1) < 0){
        Mat frame;
        cap >> frame;
        if(frame.empty())
            break;
        Mat dispFrame;
        // run the filter
        ct::cartoonify(frame,dispFrame);
        // show
        imshow("Window", dispFrame);
    }
    cap.release();
    destroyAllWindows();
    return 0;
}