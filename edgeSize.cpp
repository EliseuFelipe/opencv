#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    //Load image
    Mat3b img = imread("imagem.jpg");

    //Convert to grayscale
    Mat1b gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    //Compute dx and dy derivatives
    Mat1f dx, dy;
    Sobel(gray, dx, CV_32F, 1, 0);
    Sobel(gray, dy, CV_32F, 0, 1);

    //Compute gradient
    Mat1f magn;
    magnitude(dx, dy, magn);

    //Show gradient
    imshow("Magnitude", magn);
    waitKey();

    return 0;
}