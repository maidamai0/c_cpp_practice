find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
file(GLOB srcs *.cpp)
add_library(cppmodule SHARED ${srcs})
target_compile_definitions(cppmodule PRIVATE EXPORT_DLL)
target_include_directories(cppmodule PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(cppmodule PRIVATE ${Python3_LIBRARIES})