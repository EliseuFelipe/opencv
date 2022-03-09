#include <opencv2/opencv.hpp>
#include <iostream>
// using namespaces to nullify use of cv::function(); syntax and std::function();
using namespace std;
using namespace cv;

int main()
{
    // Reading image
    VideoCapture cap(0); 

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);
    // Display original image
    waitKey(0);

    while(1){
        Mat img;
        cap >> img;

        Mat img_gray;
        cvtColor(img, img_gray, COLOR_BGR2GRAY);
        // Blur the image for better edge detection
        Mat img_blur;
        GaussianBlur(img_gray, img_blur, Size(3,3), 0);
        
        // Sobel edge detection
        Mat sobelx, sobely, sobelxy;
        Sobel(img_blur, sobelx, CV_64F, 1, 0, 5);
        Sobel(img_blur, sobely, CV_64F, 0, 1, 5);
        Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);
        // Canny edge detection
        Mat edges;
        Canny(img_blur, edges, 0, 250, 3, false);
        // Display canny edge detected image
        imshow("Canny edge detection", edges);
        // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
    }

    destroyAllWindows();
    return 0;
}   