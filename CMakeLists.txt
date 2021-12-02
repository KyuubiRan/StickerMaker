cmake_minimum_required(VERSION 3.20)
project(StickerMaker)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV 4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

link_libraries(${OpenCV_LIBS})

add_executable(StickerMaker main.cpp)
