add_library(lib_rules_s STATIC rules.cpp)
target_include_directories(lib_rules_s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
