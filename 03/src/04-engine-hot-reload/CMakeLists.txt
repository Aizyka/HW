cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)

add_library(engine-04 STATIC)

target_sources( engine-04
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/engine.cpp
                )

target_include_directories( engine-04
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                            )

if(WIN32)
    set_target_properties(engine-04 PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS 1
    )
endif()

set_target_properties( engine-04
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
)

target_link_libraries(engine-04 PRIVATE SDL3::SDL3-shared)

add_library(proj-04 SHARED)

target_sources( proj-04
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
                )

target_include_directories( proj-04
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                            )

if(WIN32)
    set_target_properties(proj-04 PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS 1
    )
endif()

set_target_properties( proj-04
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib"
)

target_link_libraries(proj-04 PRIVATE SDL3::SDL3-shared engine-04)

project(app-04)

add_executable(app-04 app.cpp)

set_target_properties( app-04
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(app-04 PRIVATE SDL3::SDL3-shared engine-04)