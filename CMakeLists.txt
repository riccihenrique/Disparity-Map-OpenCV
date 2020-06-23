cmake_minimum_required(VERSION 2.8)
project( mapa )

FIND_PACKAGE(PkgConfig REQUIRED)
find_package( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable( mapa mapa.cpp)
target_link_libraries( teste ${OpenCV_LIBS})