cmake_minimum_required(VERSION 3.8)
project(SLP-Course-project)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c main.c main.h)
add_executable(SLP-Course-project ${SOURCE_FILES} main.c main.h)
