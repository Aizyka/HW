add_executable(square_fill square_fill.cpp)
add_executable(lines lines.cpp)
add_executable(triangle triangle.cpp)
add_executable(triangle_indexed triangle_indexed.cpp)
add_executable(triangle_interpolated triangle_interpolated.cpp)

project(gfx_program CXX)

add_executable(gfx_program gfx_program.cpp)
target_compile_features(gfx_program PUBLIC cxx_std_20)

target_link_libraries(square_fill ppm renderer)
target_link_libraries(lines ppm renderer)
target_link_libraries(triangle ppm renderer)
target_link_libraries(triangle_indexed ppm renderer)
target_link_libraries(triangle_interpolated ppm renderer)
target_link_libraries(gfx_program PRIVATE SDL3::SDL3-shared ppm renderer)

set_target_properties( square_fill
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties( lines
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties( triangle
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties( triangle_indexed
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties( triangle_interpolated
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties( gfx_program
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
