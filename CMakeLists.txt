cmake_minimum_required(VERSION 3.8)
project(keywords)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        keywords.c
        utilfuncs.c
        utilfuncs.h)

add_executable(keywords ${SOURCE_FILES})