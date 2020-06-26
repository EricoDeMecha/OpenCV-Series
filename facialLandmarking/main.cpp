#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

int main(int  argc , char **argv) {
    try
    {
        // face detector for bounding boxes
        frontal_face_detector detector = get_frontal_face_detector();
        // shape predictor-> if given an image with face and bounding box
        shape_predictor sp;
        deserialize("./data/shape_predictor_68_face_landmarks.dat") >> sp;

        image_window win, win_faces;
        // loop over the images provided in the commandline
        for(int i = 1; i < argc; i++)
        {
            cout << "Processing " << argv[i] << endl;
            array2d<rgb_pixel> img;
            load_image(img,argv[i]);
            // make the image larger so we could detect even small faces
            pyramid_up(img);
            // face detector to make bounding  boxes
            std::vector<rectangle> dets = detector(img);
            cout << "Number of faces detected " << dets.size() << std::endl;
            // determine the pose of each of the detected faces using the shape_predictor
            std::vector<full_object_detection> shapes;
            for(unsigned long  j =0; j < dets.size(); ++j)
            {
                full_object_detection shape = sp(img, dets[j]);
                cout << "Number of parts :" <<shape.num_parts() << endl;
                cout << "Pixel Position of the first part " << shape.part(0) << endl;
                cout  << "Pixel position of the second part: " << shape.part(1) << endl;
                shapes.push_back(shape);
            }
            // viewing the face  poses
            win.clear_overlay();
            win.set_image(img);
            win.add_overlay(render_face_detections(shapes));

            // extract copies of the detected copies and scaling them
            dlib::array<array2d<rgb_pixel>> face_chips;
            extract_image_chips(img, get_face_chip_details(shapes), face_chips);
            win_faces.set_image(tile_images(face_chips));
            cout << "Hit ENTER to process the next image ..." << endl;
            cin.get();
        }
    }catch (exception  &e)
    {
        cout << "\n Exeception Thrown" << endl;
        cout  << e.what() << endl;
    }
    return 0;
}