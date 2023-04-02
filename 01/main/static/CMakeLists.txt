cmake_minimum_required(VERSION 3.23)
project(hw_static)

add_executable(hw_static main.cpp)

set_target_properties( hw_static
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(hw_static hws)

include(CTest)

add_test(NAME test_main_static COMMAND hw_static)
