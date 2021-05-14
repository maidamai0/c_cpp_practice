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
  add_compile_options(/Zc:__cplusplus) # see https://docs.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-160 for detail
else()
  add_compile_options(-fcoroutines)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_program(GIT_CHGLOG git-chglog)
if(GIT_CHGLOG)
  message(STATUS "Found git-chglog:${GIT_CHGLOG}")
  execute_process(
    COMMAND ${GIT_CHGLOG}
    OUTPUT_FILE CHANGELOG.md
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
else()
  message(STATUS "git-chglog not found, changelog will not be updated")
endif()

# dependencies
add_compile_definitions(ANKERL_NANOBENCH_IMPLEMENT)
add_compile_definitions(DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/fmt)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/nanobench/src/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/nlohmann_json/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/doctest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/magic_enum/include)
link_libraries(fmt::fmt-header-only)

enable_testing()
add_subdirectory(src)
