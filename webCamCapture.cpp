//GJP
//2016021

//compiles with: g++ webCamCapture.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_legacy -lopencv_ml -lopencv_objdetect -o webCamCapture

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

int main(){
	
	Mat frame;
	string filename;
	int key=-1;
	VideoCapture stream(0);
	namedWindow("Capture",WINDOW_AUTOSIZE);
	startWindowThread();
	while(key==-1){
		stream.read(frame);
		imshow("Capture",frame);
		key=waitKey(30);		
		
	}
	destroyWindow("Capture");
	waitKey(1);
	cout <<"Please enter filename (including extension): "<<endl;
	cin >> filename;
	imwrite(filename,frame);

	
	return 0;
}
	

	
