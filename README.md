# M-P-Tracker

----------------------

Update 2016-09-04

- Created CMakeLists.txt file to build on L4T (haven't tried on Visual Studio)
	- Must have Cmake installed (only version 2.8.x on L4T I guess)
	- Then the CMakeLists.txt should be good, need to include dependent .cpp files
	- run cmake .
	- then that creates Makefile, and from then on just compile with make
	- project name is MSFT
- single main.cpp with cmd line options started (need to create man MSFT help menu)
	- command -p and "<pathname>" is required (haven't forced error if omitted)
- started OOP with VideoFeed.cpp class -- work trackers into that
- debug mode available with -d, actually display video feeds with -v,

----------------------

Update 2016-07-10

Goals/TODO:
- create CMakeLists.txt file to build cross platform on Linux (Ubuntu) and Window 10
- have single main file, and cmd line options or menu options to determine what program does
- migrate everything to be OOP (slowly but surely, but for the greater good)
- create a debug mode where the thresholded binary image can be viewed

Description of project:
This project will enable tracking of an object selected by an operator. 

Methods available: 
- centroid tracker
- TODO: corr tracker


