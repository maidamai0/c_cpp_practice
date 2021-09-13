get_filename_component(_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${_name} main.cpp)
target_precompile_headers(${_name} PRIVATE pch.h)