cmake_minimum_required(VERSION 3.16)
project(lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab1 main.cpp method.cpp method.h)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(lab1 ${OpenCV_LIBS})