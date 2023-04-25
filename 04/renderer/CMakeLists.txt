cmake_minimum_required(VERSION 3.23)

add_library(renderer SHARED)

target_sources( renderer
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
                )

target_include_directories( renderer
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                            )

target_link_libraries(renderer ppm)