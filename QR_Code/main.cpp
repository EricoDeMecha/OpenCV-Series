#include "qr.h"

const char* keys = "{help h usage ? | | Usage examples: \n\t\t ./<executable_name> --image=<Path to Image> "
                   "\n\t\t ./<executable_name> --video=<video file>"
                   "\n\t\t ./<executable_name --device=<camera number>}"
                   "{ image i |<none>| input image}"
                   "{ video v |<none>| input video file}"
                   "{ device d |<none>| input device(camera)}";
int main(int argc, char** argv){
    CommandLineParser parser(argc, argv, keys);
    parser.about("Qr/bar code scanner command line usage");
    if(parser.has("help")){
        parser.printMessage();
        return 0;
    }
    std::string str;
    VideoCapture cap;
    if(parser.has("image")){
        str = parser.get<std::string>("image");
        std::ifstream ifs(str.c_str());
        if(!ifs) throw std::runtime_error("Error: could  not open file");
        Mat img = imread(str);
        qr::zbar_decode(img);
        waitKey(0);
    }else if(parser.has("video")){
        str = parser.get<std::string>("video");
        std::ifstream ifs(str.c_str());
        if(!ifs) throw std::runtime_error("Error: could  not open file");

        cap.open(str, CAP_V4L);
        Mat frame;
        while(waitKey(1) < 0){
            cap >> frame;
            if(frame.empty()){
                break;
            }
            qr::cv_decode(frame);
        }
    }else if(parser.has("device")){
        cap.open(parser.get<int>("device"), CAP_V4L);
        Mat frame;
        while(waitKey(1) < 0){
            cap >> frame;
            if(frame.empty()){
                break;
            }
            qr::cv_decode(frame);
        }
    }else{
        parser.printMessage();
    }

    cap.release();
    destroyAllWindows();
    return 0;
}