cmake_minimum_required(VERSION 3.10.2)
project(facialLandMarking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SOURCE_FILES main.cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/dlib dlib_build)

add_executable(facialLandMarking ${SOURCE_FILES})
target_link_libraries(facialLandMarking dlib::dlib)