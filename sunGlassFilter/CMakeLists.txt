cmake_minimum_required(VERSION 3.15)
project(sunGlassFilter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenCV_DIR /home/openqt/cv3/OpenCV-3.4/lib/cmake/opencv4)
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/s_facemark.cpp
        ${CMAKE_SOURCE_DIR}/renderFace.cpp)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

add_executable(sunGlassFilter ${SOURCE_FILES})
target_link_libraries(sunGlassFilter ${OpenCV_LIBS})