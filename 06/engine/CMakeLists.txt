if(!WIN32)
add_library(engine SHARED)
else()
add_library(engine)
endif()

set_target_properties(engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_compile_definitions(engine PRIVATE BUILD_LIBRARY)

file(GLOB_RECURSE engine_sources CONFIGURE_DEPENDS
     "*.cpp"
)

target_sources( engine
                PRIVATE
                ${engine_sources}
                )

target_include_directories( engine
                            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                            )

target_link_libraries(engine glad SDL3::SDL3-shared glm)

if (WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON CACHE BOOL "" FORCE)
  target_compile_definitions(
     engine PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
    target_compile_definitions(
     engine PRIVATE DLL_EXPORT)
endif ()

