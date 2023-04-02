cmake_minimum_required(VERSION 3.23)
project(hw_main)

add_executable(hw_main main.cpp)
target_compile_features(hw_main PUBLIC cxx_std_20)
set_target_properties( hw_main
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

include(CTest)

add_test(NAME test_main COMMAND hw_main)
