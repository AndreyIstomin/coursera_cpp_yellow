cmake_minimum_required(VERSION 2.4)

set(HEADER_FILES coursera_cpp_yellow/Source.h)
set(SOURCE_FILES coursera_cpp_yellow/Source.cpp)

project(coursera_yellow_cpp)

add_executable(app ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(app PRIVATE coursera_yellow_cpp)