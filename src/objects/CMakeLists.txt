add_library(lib_objects_s STATIC objects.cpp)
target_include_directories(lib_objects_s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
