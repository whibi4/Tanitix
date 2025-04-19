add_library(lib_visio_s STATIC visio.cpp)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

target_include_directories(lib_visio_s PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/space)
target_link_libraries(lib_visio_s ${GTK3_LIBRARIES} lib_space_s)