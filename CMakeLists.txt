cmake_minimum_required(VERSION 3.4)
project(GraphDeepSearch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp List.cpp List.h)
add_executable(GraphDeepSearch ${SOURCE_FILES})