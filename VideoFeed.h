#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class VideoFeed
{
public:
	bool debugMode = false;
	std::string filename;
	cv::VideoCapture Capture;
	cv::Mat frame;
	void step(void);
	VideoFeed();
	VideoFeed(std::string);
	~VideoFeed();
};

