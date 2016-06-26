
//20160626
//Gregory J Petty and Kiron NMI Mateti


//Goal: (Completed!)
//View Webcam, have 3 slides (BGR tolerance (+/-)), mouse click picks color center point (in HSV), track color, reclick on new point to change color center point. Works well with a tennis ball or bright color lacrosse ball.

//Basically is the C++ version of http://www.pyimagesearch.com/2015/09/14/ball-tracking-with-opencv/

//compiles with: g++ ColorTrack.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_legacy -lopencv_ml -lopencv_objdetect -o colorTrack

#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/gpu/gpu.hpp"
#include <stdio.h>
#include <iostream>
#include <string> //It's unlikely that I use all of these.

using namespace cv;
using namespace std;

//Function Prototypes
void setColorBounds();


	//Global Variables	
	Vec3b centerColor;
	Vec3b colorOffset,colorLower(29,86,6),colorUpper(64,255,255);
	int oH = 20;
	int oS = 40;
	int oV = 80;
	Point mp;
	Mat frame,hsvFrame,mask;
	bool isTracking = false;

	int strelSize =5;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<Point> c; //Biggest contour

	int largest_area=0;
	int bounding_index;
	Rect bounding_rect;
	
	Point2f enclosedCirclePoint;
	float enclosedCircleRadius;

//Callback for all Trackbars
static void onTrackbar(int, void*)
{
	
	setColorBounds();
	cout << "--- Slider Values ---" << endl;
	cout << colorOffset << endl;
}


//Mouse Callback for when you click on a color
void mouseEvent(int evt, int x, int y, int flags, void* param){
    if(evt==CV_EVENT_LBUTTONDOWN){
	cout << "Tracking Initiated" << endl;
        isTracking=true;
        mp.x = x;
        mp.y = y;
	cvtColor(frame,hsvFrame,COLOR_BGR2HSV);
	centerColor =hsvFrame.at<Vec3b>(mp);
	setColorBounds();
        return;
    }
}
// setColorBounds
void setColorBounds(){
	colorOffset=Vec3b(oH,oS,oV);
	if(isTracking){
		for(int x=0;x<3;x++){
			if((centerColor[x]-colorOffset[x])<0){
				colorLower[x] = 0;
			}else{
				colorLower[x] = centerColor[x] - colorOffset[x];
			}
			if((centerColor[x]+colorOffset[x])>255){
				colorUpper[x] = 255;
			}else{
				colorUpper[x] = centerColor[x] + colorOffset[x];
			}
		}
		cout << "--- Lower Bound ---" << endl;
		cout << colorLower << endl;
		cout << "--- Upper Bound ---" << endl;
		cout << colorUpper << endl <<endl;
		
	}
	return;
}

// findBiggestContour
void findBiggestContour(){
	findContours(mask.clone(),contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0) );
	for(int x=0;x<contours.size();x++)
	{
		double a=contourArea(contours[x],false);
		if(a>largest_area)
		{
			largest_area=a;
			bounding_index=x;
			bounding_rect=boundingRect(contours[x]);
		}
	}
	c=contours[bounding_index];
}
int main(){
	
	
	int key= -1; //controls overall loop
	
	Mat strel = getStructuringElement(MORPH_ELLIPSE,Size(2*strelSize+1,2*strelSize+1),Point(strelSize,strelSize));

	VideoCapture stream(0);
	namedWindow("Tracker",WINDOW_AUTOSIZE);
	moveWindow("Tracker",50,50);
	//namedWindow("Mask",WINDOW_AUTOSIZE);
	//moveWindow("Mask",750,150);
	createTrackbar("H", "Tracker", &oH, 100, onTrackbar);
	createTrackbar("S", "Tracker", &oS, 100, onTrackbar);
	createTrackbar("V", "Tracker", &oV, 100, onTrackbar);
	cvSetMouseCallback("Tracker",mouseEvent,&frame);
	startWindowThread();
	while(key==-1)
	{
		stream.read(frame);
		
		if(isTracking)
		{		
			cvtColor(frame,hsvFrame,COLOR_BGR2HSV);
			inRange(hsvFrame, colorLower, colorUpper, mask);

			erode(mask,mask, strel);
			erode(mask,mask, strel);
			dilate(mask,mask,strel);
			dilate(mask,mask,strel);

			findBiggestContour();
			minEnclosingCircle(c, enclosedCirclePoint, enclosedCircleRadius);			
			circle(frame,enclosedCirclePoint,int(enclosedCircleRadius),(0,255,255),2);

			cout<<"Pixel Location: " << enclosedCirclePoint <<endl;
			//imshow("Mask",mask);
		}
		imshow("Tracker",frame);
		key=waitKey(30);		
		
	}
	destroyWindow("Tracker");
	waitKey(1);
	

	cout <<"Complete"<<endl; 

	
	return 0;
}
	

	
