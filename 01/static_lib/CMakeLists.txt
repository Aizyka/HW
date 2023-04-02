cmake_minimum_required(VERSION 3.23)
add_library(hws STATIC lib.cpp)


set_target_properties( hws
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
)