cmake_minimum_required(VERSION 3.23)
add_library(hw SHARED lib.cpp)
target_compile_features(hw PUBLIC cxx_std_20)

if(WIN32)
    set_target_properties(hw PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS 1
    )
endif()

set_target_properties( hw
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
)

add_library(hws STATIC lib.cpp)
target_compile_features(hws PUBLIC cxx_std_20)

set_target_properties( hws
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
)