add_executable(app1 app1.cpp)
add_executable(app2 app2.cpp)

#project(gfx_program CXX)

#add_executable(gfx_program gfx_program.cpp)
target_compile_features(app1 PUBLIC cxx_std_17)
target_compile_features(app2 PUBLIC cxx_std_17)

target_link_libraries(app1 engine)
target_link_libraries(app2 engine)

set_target_properties( app1
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties( app2
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)