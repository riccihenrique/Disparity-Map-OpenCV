#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/videoio/videoio_c.h>
#include <stdio.h>
#include <iostream>

#include "./imgs/serialize.h"

#include <math.h>
#include <stdio.h>
#include <thread>

using namespace cv;
using namespace std;

int preFiltCap = 41;
int minDisp = 0;
int numOfDisp = 128;
int TxtrThrshld = 10;
int unicRatio = 10;
int spcklRng = 2;
int spklWinSze = 200;
int preFilterSize = 31;
int disp13MaxDiff = 1;

void onMouseClick(int event, int x, int y, int flags, void *ptr) {
    if(event == cv::EVENT_LBUTTONDOWN) {
        cv::Mat *snapshot = (cv::Mat*) ptr;
        cv::Vec3b pixel = snapshot->at<cv::Vec3b>(cv::Point(x, y));
        printf("Color: R = %d G = %d B = %d\n", pixel[2], pixel[1], pixel[0]);
    }
}

void dispt() {
    cv::Mat imgLeft, imgRight, gLeft, gRight;
    cv::Mat disp, disp8;
    cv::Mat corL, corR;
    cv::Mat camMatLeft, camMatRight, distLeft, distRight;

    /*camMatRight = matread("./imgs/params/rightMatrix"); // If you have the calibrate camera files, use this part
    distRight = matread("./imgs/params/rightDist");
    camMatLeft = matread("./imgs/params/leftMatrix");
    distLeft = matread("./imgs/params/leftDist");*/

    cv::VideoCapture cap1;
    cv::VideoCapture cap2;
    
    /*bm->setBlockSize(13);
    bm->setNumDisparities(128);
    bm->setUniquenessRatio(unicRatio);
    bm->setSpeckleRange(spcklRng);*/
    if(cap1.open(0) && cap2.open(2))
        while(true) {            
            /*cap1 >> imgLeft; // If you have the calibrate camera files, use this part
            cap2 >> imgRight;
            cv::undistort(imgLeft, corL, camMatLeft, distLeft);
            cv::undistort(imgRight, corR, camMatRight, distRight);*/

            cap1 >> corL;
            cap2 >> corR;

            cv::cvtColor(corL, gLeft, cv::COLOR_BGR2GRAY);
            cv::cvtColor(corR, gRight, cv::COLOR_BGR2GRAY);

            int numDisparity = (int)(corL.size().width/8);
                cv::Ptr<cv::StereoSGBM> bm = cv::StereoSGBM ::create(
                0,    // min DIsparities
                numDisparity, // numDisparities
                13,   // SADWindowSize
                2*11*11,   // 8*number_of_image_channels*SADWindowSize*SADWindowSize   // p1
                5*11*11,  // 8*number_of_image_channels*SADWindowSize*SADWindowSize  // p2
                -1,   // disp12MaxDiff
                63,   // prefilterCap
                10,   // uniqueness ratio
                0, // sreckleWindowSize
                32, // spreckle Range
                0); // full DP

            cv::Mat disp8, colored;
            bm->compute(gLeft, gRight, disp);
            cv::normalize(disp, disp8, 0, 255, NORM_MINMAX, CV_8UC1);
            //cv::applyColorMap(disp8, colored, cv::COLORMAP_JET); // Add color to disparity map
            cv::imshow("left", corL);
            cv::imshow("right", corR);
            cv::setMouseCallback("teste", onMouseClick, &disp8); // Get the color when click on map
            cv::imshow("Map", disp8);
            if( cv::waitKey(1) == 27 )
				break;
        }
}

int main() {
    std::thread t2(dispt);
    t2.join();
    return 0;
}
