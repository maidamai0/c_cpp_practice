get_filename_component(module ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB srcs *.cpp)

foreach(src ${srcs})
    get_filename_component(file_name ${src} NAME_WLE)
    set(app ${module}_${file_name})
    add_executable(${app} ${src})
    add_test(${app}_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${app})
endforeach()

