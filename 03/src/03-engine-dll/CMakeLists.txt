cmake_minimum_required(VERSION 3.23)

add_library(engine-03 SHARED)

target_sources( engine-03
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/engine.cpp
                )

target_include_directories( engine-03
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                            )

if(WIN32)
    set_target_properties(engine-03 PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS 1
    )
endif()

set_target_properties( engine-03
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
)

target_link_libraries(engine-03 PRIVATE SDL3::SDL3-shared)

project(proj-03)

add_executable(proj-03 game.cpp engine.h)

set_target_properties( proj-03
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(proj-03 PUBLIC SDL3::SDL3-shared engine-03)