get_filename_component(dir ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB entries *)

foreach(entry ${entries})
  if(IS_DIRECTORY ${entry})
    file(GLOB srcs ${entry}/*.cpp)
    get_filename_component(module ${entry} NAME)
    add_executable(${module} ${srcs})
    add_test(${module}_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${module})
    target_include_directories(${module} PRIVATE ${CMAKE_SOURCE_DIR}/deps/fmt/include)
  endif()
endforeach()
