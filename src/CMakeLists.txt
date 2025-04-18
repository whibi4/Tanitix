set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
cmake_minimum_required(VERSION 3.10)
project(Tanitix VERSION 1.0 LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_subdirectory(interpreter)
add_subdirectory(space)
add_subdirectory(visio)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE lib_objects_s lib_interpreter_s lib_rules_s lib_visio_s)
