# Define the object sources as a list
set(objects
    ${CMAKE_CURRENT_SOURCE_DIR}/physical_object/physicalObject.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/physical_object/drawableObject.cpp
)
# Add library with proper expansion of the list
add_library(lib_space_s STATIC
    space.cpp
    ${objects}
)

# Add include directories
target_include_directories(lib_space_s PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/rules
    ${CMAKE_CURRENT_SOURCE_DIR}/physical_object
    ${CMAKE_CURRENT_SOURCE_DIR}/drawable_object
    ${CMAKE_SOURCE_DIR}/utils/geometric
)
