#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <unistd.h>
#include "VideoFeed.h"

int main(int argc, char** argv)
{
	std::string pathname = "";
	int debugMode = 0;
	int Nframes = 300;
	int displayFeeds = 0;
	int c;
		
	// See http://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
	while ((c = getopt (argc, argv, "dvp:")) != -1)
		switch (c)
		{
			case 'd':
				debugMode = 1;
				break;
			case 'v':
				displayFeeds = 1;
				break;
			case 'p':
				pathname = optarg;
				break;
			case '?':
				if (optopt == 'p')
					fprintf (stderr, "Option -%c requires an pathname to the MSDMI folder.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr,
							"Unknown option character `\\x%x'.\n",
							optopt);
				return 1;
			default:
				abort ();
		}

	VideoFeed visFeed(pathname + "DAY_VIS_MSDMI.mp4");
	VideoFeed swirFeed(pathname + "DAY_SWIR_MSDMI.mp4");
	VideoFeed mwirFeed(pathname + "DAY_MWIR_MSDMI.mp4");

	visFeed.debugMode = debugMode;
	swirFeed.debugMode = debugMode;
	mwirFeed.debugMode = debugMode;

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	for (int iFrame = 0; iFrame < Nframes; iFrame++)
	{
		visFeed.step();
		swirFeed.step();
		mwirFeed.step();
		if (displayFeeds)
		{
			cv::imshow("VIS", visFeed.frame);
			cv::imshow("SWIR", swirFeed.frame);
			cv::imshow("MWIR", mwirFeed.frame);
			cv::waitKey(1); // waits to display frame
		}
	}

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "Average frame rate for " << Nframes << " frames is " << (double) Nframes / (double) duration * 1000 << " fps" << std::endl;

	return 0;

}

