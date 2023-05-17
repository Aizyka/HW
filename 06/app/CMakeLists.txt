add_executable(app1 app1.cpp)
target_compile_features(app1 PUBLIC cxx_std_17)

target_link_libraries(app1 engine)

set_target_properties( app1
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)