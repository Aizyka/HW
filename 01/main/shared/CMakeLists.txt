cmake_minimum_required(VERSION 3.23)
project(hw_shared)

add_executable(hw_shared main.cpp)
target_compile_features(hw_shared PUBLIC cxx_std_20)

set_target_properties( hw_shared
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(hw_shared hw)

include(CTest)

add_test(NAME test_main_shared COMMAND hw_shared)
