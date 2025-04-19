add_library(lib_space_s STATIC space.cpp)
target_include_directories(lib_space_s PUBLIC 
                                            ${CMAKE_CURRENT_SOURCE_DIR}/rules
                                            ${CMAKE_CURRENT_SOURCE_DIR}/physical_object
                                            ${CMAKE_CURRENT_SOURCE_DIR}/drawable_object
                                            )