cmake_minimum_required(VERSION 3.15)
project(BasicImageOperations)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenCV_DIR /home/openqt/cv3/OpenCV-3.4/lib/cmake/opencv4)
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/image_addition.cpp)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

add_executable(Basics-addition ${SOURCE_FILES})
target_link_libraries(Basics-addition ${OpenCV_LIBS})