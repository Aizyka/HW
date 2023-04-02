cmake_minimum_required(VERSION 3.23)
add_library(hw SHARED lib.cpp)


set_target_properties( hw
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
)