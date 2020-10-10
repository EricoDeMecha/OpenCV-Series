#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

#include <zbar.h>
#include <zbar/Decoder.h>
#include <zbar/ImageScanner.h>

using namespace cv;
using namespace std;
using namespace zbar;

inline namespace qr{
    typedef struct{
        std::string  type;
        std::string data;
        std::vector<Point> location;
    }decodedObject;

    QRCodeDetector qrDetector;// for opencv4
    ImageScanner scanner;// zbar scanner

    void cv_display(Mat& inputImg, Mat &bbox) {
        int n = bbox.rows;
        for (int i = 0; i < n; i++) {
            line(inputImg, Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)),
                 Point2i(bbox.at<float>((i + 1) % n, 0), bbox.at<float>((i + 1) % n, 1)), Scalar(255, 0, 0), 3);
        }
        imshow("result", inputImg);
    }
    void cv_decode(Mat& imgFrame){
        Mat bbox, rectifiedImage;
        std::string data = qrDetector.detectAndDecode(imgFrame, bbox, rectifiedImage);
        if(data.length() > 0){
            cout << "Decoded data: " << data << endl;
            cv_display(imgFrame, bbox);
            rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
            imshow("Rectified QR Code", rectifiedImage);
        }else{
            cout << "Error: Could not detect QRCode" << endl;
        }
    }
    void zbar_display(Mat& im, std::vector<decodedObject>& decodedObjects){
        for(int i = 0; i < decodedObjects.size();i++){
            vector<Point> points = decodedObjects[i].location;
            vector<Point> hull;
            // if the size do not form a quad find a convex hull
            if(points.size() > 4){
                convexHull(points , hull);
            }else{
                hull = points;
            }
            int n = hull.size();
            for(int j = 0; j < n; j++){
                line(im, hull[j], hull[(j+1) % n], Scalar(255, 0, 0), 3);
            }
        }
        // display results
        imshow("results", im);
    }

    void zbar_decode(Mat& im){
        std::vector<decodedObject> decodedObjects;
        scanner.set_config(ZBAR_NONE,ZBAR_CFG_ENABLE, 1);// configure the scanner
        // convert image  to grayscale
        Mat imGray;
        cvtColor(im, imGray, COLOR_BGR2GRAY);
        // wrap image data in a zbar  image
        Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);
        // scan for bar codes and QrCodes
        int n = scanner.scan(image);
        //print results
        for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol){
            decodedObject obj;
            obj.type = symbol->get_type_name();
            obj.data = symbol->get_data();
            // print the type and the data
            cout << "Type: " << obj.type << std::endl;
            cout << "Data: " << obj.data << std::endl;
            // obtain the location
            for(int i = 0; i < symbol->get_location_size(); i++){
                obj.location.emplace_back(symbol->get_location_x(i), symbol->get_location_y(i));
            }
            decodedObjects.push_back(obj);
        }
        zbar_display(im, decodedObjects);
    }
}

