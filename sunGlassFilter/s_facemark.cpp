#include "s_facemark.hpp"

void sunglassFilter::s_facemarking() {
    // load the face detector
    CascadeClassifier faceDetector("./data/haarcascade_frontalface_alt2.xml");
    // an instance of the facemark
    Ptr<Facemark> facemark = FacemarkLBF::create();
    //loading the landmark detector
    facemark->loadModel("./data/lbfmodel.yaml");
    // webcam for the video source
    VideoCapture  cam(0);
    // Matrices to store video frames and its grayscale
    Mat frame, gray;

    while(cam.read(frame))
    {
        // find faces
        vector<Rect> faces;
        // BGR -> gray
        cvtColor(frame,gray, COLOR_BGR2GRAY);
        //  detect faces
        faceDetector.detectMultiScale(gray, faces);
        // landmark for one face is a vector of points
        // and there can be more than one face in an image
        // so therefore a vector of a vector of points
        vector<vector<Point2f>> landmarks;
        // run the facial landmark detector
        bool success = facemark->fit(frame, faces , landmarks);
        if(success)
        {
            for(int i =0; i < landmarks.size(); i++)
            {
                drawLandmarks(frame, landmarks[i]);
            }
        }
        imshow("Facial Landmark detection", frame);
        if(waitKey(1) == 27)
            break;
    }
}
