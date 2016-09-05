
#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
#if(COMPILER_SUPPORTS_CXX11)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#elseif(COMPILER_SUPPORTS_CXX0X)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#else()
#        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a #different C++ compiler.")
#endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

cmake_minimum_required(VERSION 2.8)
project( MSFT )
find_package( OpenCV REQUIRED )
add_executable( MSFT main.cpp VideoFeed.cpp )
target_link_libraries( MSFT ${OpenCV_LIBS} )

# http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
#project(MSFT CXX)
#add_executable(MSFT main.cpp)
#target_compile_features(MSFT PRIVATE cxx_range_for)
#target_link_libraries( MSFT ${OpenCV_LIBS} )
