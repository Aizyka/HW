cmake_minimum_required(VERSION 3.23)
project(main_static)

add_executable(main_static main.cpp)

set_target_properties( main_static
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(main_static PRIVATE SDL3::SDL3-static)