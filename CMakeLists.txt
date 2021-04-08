cmake_minimum_required(VERSION 3.16)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${ROOT} CXX)

set(CMAKE_GENERATOR Ninja)

# cpp compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
  # add_compile_options(/fsanitize=address)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/fmt)
link_libraries(fmt::fmt-header-only)
add_subdirectory(src)