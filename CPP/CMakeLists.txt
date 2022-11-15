cmake_minimum_required(VERSION 3.21)
project(CPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP
        test.cpp)

add_executable(Lee1447 Lee1447.cpp)
add_executable(Lee717 Lee717.cpp)
add_executable(lee599 lee599.cpp)
add_executable(lee2043 lee2043.cpp)
add_executable(Lee1114 Lee1114.cpp)
add_executable(Lee1114Two Lee1114Two.cpp)
add_executable(Lee1114Three Lee1114Three.cpp)
add_executable(Lee606 Lee606.cpp)
add_executable(Lee780 Lee780.cpp)
add_executable(Lee388 Lee388.cpp)
include_directories(D:\\boost_1_78_0)
link_directories(D:\\boost_1_78_0\\libs)
add_executable(Lee427 Lee427.cpp)
add_executable(Lee713 Lee713.cpp)
add_executable(BlockingQueue BlockingQueue.cpp)
add_executable(NewHandlerTest NewHandlerTest/NewHandlerTest.cpp NewHandlerTest/Widget.h NewHandlerTest/NewHandlerHolder.h NewHandlerTest/NewHandlerSupport.h)
