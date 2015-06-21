cmake_minimum_required(VERSION 2.8)
project( particle_filter_example )
find_package( OpenCV REQUIRED )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

ADD_DEFINITIONS(
  -g
  -O0
  -Wall
  -std=c++11
  )

add_executable( 
  example1 example1.cpp 
  )
target_link_libraries( example1 ${OpenCV_LIBS} )
