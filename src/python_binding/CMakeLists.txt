add_library(cppmodule SHARED module.cpp)
target_compile_definitions(cppmodule PRIVATE EXPORT_DLL)