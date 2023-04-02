cmake_minimum_required(VERSION 3.23)
add_library(hws STATIC lib.cpp)
target_compile_features(hws PUBLIC cxx_std_20)

set_target_properties( hws
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
)