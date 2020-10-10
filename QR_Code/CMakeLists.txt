cmake_minimum_required(VERSION 3.15)
project(QR_Code)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED  true)

set(OpenCV_DIR /home/openqt/cv3/OpenCV-3.4/lib/cmake/opencv4/)
set(CMAKE_MODULE_PATH  ${CMAKE_SOURCE_DIR})

find_package(OpenCV)
find_package(ZBar0)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/main.cpp qr.h)
add_executable(QR_Code ${SOURCE_FILES})
target_link_libraries(QR_Code  ${OpenCV_LIBS} ${ZBAR_LIBRARIES})