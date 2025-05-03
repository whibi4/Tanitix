set (srcs 
        interpreter.cpp
        lexer.cpp
        parser.cpp)
add_library(lib_interpreter_s STATIC ${srcs})
target_include_directories(lib_interpreter_s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/space ${CMAKE_SOURCE_DIR}/utils/geometric)
target_link_libraries(lib_interpreter_s lib_space_s)