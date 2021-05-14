cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(static_lib static.cpp)
add_library(shared_lib SHARED static.cpp)

file(GLOB src main.cpp compile.cpp)
add_executable(${TARGET} ${src})
target_link_libraries(${TARGET} static_lib shared_lib)