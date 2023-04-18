cmake_minimum_required(VERSION 3.23)
project(proj-01)

add_executable(proj-01 header.h main.cpp)

set_target_properties( proj-01
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(proj-01 PRIVATE SDL3::SDL3-shared)