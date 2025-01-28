add_library(lib_interpreter_s STATIC interpreter.cpp)
target_include_directories(lib_interpreter_s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
