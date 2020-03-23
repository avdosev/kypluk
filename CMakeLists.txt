cmake_minimum_required(VERSION 3.15)

project(kypluk)
set(CMAKE_CXX_STANDARD 14)

add_library(kypluk INTERFACE)
target_sources(kypluk INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(kypluk INTERFACE ${CMAKE_SOURCE_DIR}/include)
