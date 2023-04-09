cmake_minimum_required(VERSION 3.23)
project(main_static)

add_executable(main_static main.cpp)

target_link_libraries(main_static PRIVATE SDL3::SDL3-static)