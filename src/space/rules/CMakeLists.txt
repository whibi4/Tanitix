# Define the object sources as a list
set(srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/motions2D.cpp
)
# Add library with proper expansion of the list
add_library(lib_rules_s STATIC
    ${srcs}
)

# Add include directories
target_include_directories(lib_rules_s PUBLIC 
    ${CMAKE_SOURCE_DIR}/utils/maths
    ${CMAKE_SOURCE_DIR}/utils/physics
)
