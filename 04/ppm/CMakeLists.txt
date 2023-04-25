cmake_minimum_required(VERSION 3.23)

add_library(ppm SHARED)

target_sources( ppm
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/ppm.cpp
                )

target_include_directories( ppm
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                            )

set_target_properties( ppm
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/libs"
)

if(WIN32)
    set_target_properties(ppm PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS 1
    )
endif()