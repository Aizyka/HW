cmake_minimum_required(VERSION 3.23)
project(main_shared)

if(MINGW)
set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS "-O0")
endif()

add_executable(main_shared main.cpp)

set_target_properties( main_shared
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(main_shared PRIVATE SDL3::SDL3-shared)