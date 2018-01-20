cmake_minimum_required(VERSION 3.8)
project(SLP-Course-project)

set(CMAKE_C_STANDARD 11)

include_directories(/home/yakov/Загрузки/psmoveapi-4.0.4/include)


set(SOURCE_FILES lib.c lib.c)
add_executable(SLP-Course-project ${SOURCE_FILES} lib.c)

#add_library(ps SHARED ${SOURCE_FILES})

target_link_libraries(SLP-Course-project psmoveapi psmoveapi_tracker)
