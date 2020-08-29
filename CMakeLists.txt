cmake_minimum_required(VERSION 3.12)
project(kypluk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3" )

include_directories(include)

option(BUILD_TESTS "enable build tests" ON)
option(BUILD_BENCHMARKS "enable build benchmarks" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory( test ./test )
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks ./benchmarks)
endif()
