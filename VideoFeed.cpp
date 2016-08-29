#include "VideoFeed.h"


VideoFeed::VideoFeed()
{
	filename = "";
	//VideoCapture swCapture(swFilename);
}

VideoFeed::VideoFeed(std::string filenameIn)
{

	filename = filenameIn;
	Capture = cv::VideoCapture(filenameIn);
	cv::Mat frame;

	if (!Capture.isOpened())
		throw std::runtime_error("Error: bad path, cannot read " + filename);

}

void VideoFeed::step(void)
{
	Capture >> frame;


	if (frame.empty()) {
		throw std::runtime_error("Error: frame is empy, reached end of file " + filename);
	}
	else
	{
		if (debugMode)
		{
			std::cout << "Frame read properly from " << filename << std::endl;
			std::cout << "Size of frame " << frame.cols << " x " << frame.rows << std::endl;
		}
	}
	
}
VideoFeed::~VideoFeed()
{
}
