if(!WIN32)
add_library(glad SHARED)
else()
add_library(glad)
endif()



target_sources( glad
                PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
                )

target_include_directories( glad
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                            )


if (WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON CACHE BOOL "" FORCE)
  target_compile_definitions(
    glad PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
    target_compile_definitions(
        glad PRIVATE DLL_EXPORT)
endif ()
