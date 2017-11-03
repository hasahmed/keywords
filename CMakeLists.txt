cmake_minimum_required(VERSION 3.8)
project(keywords)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        keywords.cpp
        utilfuncs.cpp)

add_executable(keywords ${SOURCE_FILES})
