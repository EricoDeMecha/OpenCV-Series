cmake_minimum_required(VERSION 3.15)
project(cartoonifier)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(OpenCV_DIR  /home/openqt/cv3/OpenCV-3.4/lib/cmake/opencv4/)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDEDIRS})
endif()

set(SOURCE_FILES  ${CMAKE_SOURCE_DIR}/main.cpp cartoonifier.h)

add_executable(cartoonifier ${SOURCE_FILES})
target_link_libraries(cartoonifier  ${OpenCV_LIBS})