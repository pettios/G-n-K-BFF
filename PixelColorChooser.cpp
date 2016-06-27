/* Gregory J. Petty and Kiron Mateti

Created 2016-02-01

Updated 2016-06-22: Added webcam if no arguments provided

On Ubuntu 14.04. Compiles with: g++ PixelColorChooser.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_legacy -lopencv_ml -lopencv_objdetect -o pixelColorChooser
 
On Windows 10, Microsoft Visual Studio Community 2015 Version 14.0 compiles with prebuilt OpenCV libraries, with opencv_world310d.lib

*/

#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/gpu/gpu.hpp" // Currently do not have gpu functionality
#include <stdio.h>
#include <iostream>
#include <string> //It's unlikely that I use all of these.
using namespace cv;
using namespace std;

//Prototypes
void mouseEvent(int evt, int x, int y, int flags, void* param);


//Global Variables
Mat frame,frame2;
Mat colorChip(50,50,CV_8UC3,Scalar(255,255,255));

Point mp;
//Main
int main(int argc, char** argv){
	
	if (argc != 2) {

		//Mat cameraFrame;
		VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.

		if (!stream1.isOpened()) { //check if video device has been initialised
			cout << "cannot open camera";

			return -1;
		}

		stream1.read(frame);
	}
	else {
		frame = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	}
	
	frame2 =frame.clone();
		

	namedWindow("Image",WINDOW_AUTOSIZE);
	namedWindow("Color",WINDOW_AUTOSIZE);
	moveWindow("Color",750,50);
	startWindowThread();
	
	cvSetMouseCallback("Image",mouseEvent,&frame);
	imshow("Color",colorChip);
	imshow("Image",frame2);
	
	


	waitKey(0);
	destroyWindow("Color");
	destroyWindow("Image");

	waitKey(1);
	
	return 0;
}
	
//Mouse Event Listener

void mouseEvent(int evt, int x, int y, int flags, void* param){
    if(evt==CV_EVENT_LBUTTONDOWN){
        printf("down %d %d\n",x,y);
        mp.x = x;
        mp.y = y;
	circle(frame2,mp,10,Scalar(0,255,0),1,8,0);
	imshow("Image",frame2);
	Vec3b intensity =frame.at<Vec3b>(mp);
	cout << intensity<<endl;
	//cout << frame.at<Vec3b>(mp)[1]<<endl;
	//cout << frame.at<Vec3b>(mp)[2]<<endl;
	for(int a=0;a<colorChip.rows;a++){
		for(int b=0;b<colorChip.cols;b++){
			colorChip.at<Vec3b>(Point(b,a))=intensity;
		}
	}
	imshow("Color",colorChip);
	frame2=frame.clone();
		

        return;
    }
}

