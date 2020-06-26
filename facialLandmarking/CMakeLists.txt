cmake_minimum_required(VERSION 3.15)
project(facialLandmarking)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenCV_DIR /home/openqt/cv3/OpenCV-3.4/lib/cmake/opencv4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

add_subdirectory(${CMAKE_SOURCE_DIR} dlib_build)

add_executable(facialLandmarking realTime_dlib.cpp)
target_link_libraries(facialLandmarking ${OpenCV_LIBS} dlib::dlib)