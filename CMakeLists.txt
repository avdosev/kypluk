cmake_minimum_required(VERSION 3.12)
project(kypluk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3" )

enable_testing()

include_directories(include)

add_subdirectory( test ./test )
