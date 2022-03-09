#include <opencv2/opencv.hpp>
#include <iostream>
// using namespaces to nullify use of cv::function(); syntax and std::function();
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); 

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    
    Mat img;
    cap >> img;

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // since your image has compression artifacts, we have to threshold the image
    int threshold = 200;
    cv::Mat mask = gray > threshold;

    cv::imshow("mask", mask);

    // extract contours
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

    for(int i=0; i<contours.size(); ++i)
    {
        // fit bounding rectangle around contour
        cv::RotatedRect rotatedRect = cv::minAreaRect(contours[i]);

        // read points and angle
        cv::Point2f rect_points[4]; 
        rotatedRect.points( rect_points );

        float  angle = rotatedRect.angle; // angle

        // read center of rotated rect
        cv::Point2f center = rotatedRect.center; // center

        // draw rotated rect
        for(unsigned int j=0; j<4; ++j)
            cv::line(gray, rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,255,0));

        // draw center and print text
        std::stringstream ss;   ss << angle; // convert float to string
        cv::circle(gray, center, 5, cv::Scalar(0,255,0)); // draw center
        cv::putText(gray, ss.str(), center + cv::Point2f(-25,25), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(255,0,255)); // print angle
    }

    cv::imshow("mask1", mask);
        while(1){
        char c=(char)waitKey(25);
        if(c==27)
        break;
        }

    return 0;
}   