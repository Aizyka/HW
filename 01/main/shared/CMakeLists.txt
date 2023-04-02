cmake_minimum_required(VERSION 3.23)
project(hw_shared)

add_executable(hw_shared main.cpp)
target_compile_features(hw_shared PUBLIC cxx_std_20)

set_target_properties( hw_shared
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (WIN32)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}"${CMAKE_BINARY_DIR}/bin/lib")
find_library(DLL_NAME libhw.dll PATHS ${CMAKE_LIBRARY_PATH})
target_link_libraries(hw_shared ${DLL_NAME})
else()
target_link_libraries(hw_shared hw)
endif()



include(CTest)

add_test(NAME test_main_shared COMMAND hw_shared)
