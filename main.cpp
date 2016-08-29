//#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include "videoFeed.h"

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv)
{
	VideoFeed visFeed("C:\\Users\\kiron\\Downloads\\temp\\MSDMI\\DAY_VIS_MSDMI.mp4");
	VideoFeed swirFeed("C:\\Users\\kiron\\Downloads\\temp\\MSDMI\\DAY_SWIR_MSDMI.mp4");
	VideoFeed mwirFeed("C:\\Users\\kiron\\Downloads\\temp\\MSDMI\\DAY_MWIR_MSDMI.mp4");
	bool debugMode = false;
	int Nframes = 300;
	bool displayFeeds = false;

	visFeed.debugMode = debugMode;
	swirFeed.debugMode = debugMode;
	mwirFeed.debugMode = debugMode;
	
	

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (int iFrame = 0; iFrame < Nframes; iFrame++)
	{
		visFeed.step();
		swirFeed.step();
		mwirFeed.step();
		if (displayFeeds)
		{
			imshow("VIS", visFeed.frame);
			imshow("SWIR", swirFeed.frame);
			imshow("MWIR", mwirFeed.frame);
			waitKey(20); // waits to display frame
		}
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(t2 - t1).count();

	cout << "Average frame rate for " << Nframes << " frames is " << (double) Nframes / (double) duration * 1000.0 << " fps" << endl;

	return 0;

}

