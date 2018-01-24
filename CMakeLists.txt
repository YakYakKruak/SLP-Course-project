cmake_minimum_required(VERSION 3.8)
project(SLP-Course-project)

set(CMAKE_C_STANDARD 11)


include_directories(/home/yakov/Загрузки/psmoveapi-4.0.4/include)
include_directories(/usr/lib/jvm/java-1.8.0-openjdk-amd64/include)
include_directories(/usr/lib/jvm/java-1.8.0-openjdk-amd64/include/linux)
include_directories(/usr/include/tesseract)
include_directories(/usr/include/leptonica)


set(SOURCE_FILES src/lib.c src/move.c src/move.h src/recognizer.c src/recognizer.h)
#add_executable(SLP-Course-project ${SOURCE_FILES} lib.c)

add_library(ps SHARED ${SOURCE_FILES})

target_link_libraries(ps tesseract )
target_link_libraries(ps psmoveapi psmoveapi_tracker)
