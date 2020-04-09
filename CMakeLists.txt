cmake_minimum_required(VERSION 3.15)
project(kypluk)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -O3" )

enable_testing()

include_directories(include)

add_subdirectory( test ./test )
