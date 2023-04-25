cmake_minimum_required(VERSION 3.23)

add_library(renderer SHARED)

target_sources( renderer
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
                )

target_include_directories( renderer
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                            )

target_link_libraries(renderer ppm)

set_target_properties( renderer
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/libs"
)

if(WIN32)
    set_target_properties(renderer PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS 1
    )
endif()