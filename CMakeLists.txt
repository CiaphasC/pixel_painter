cmake_minimum_required(VERSION 3.16)
project(DroidPixelPainter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(miniwin STATIC
    vendor/miniwin/miniwin.cpp
)

target_include_directories(miniwin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/miniwin)

if(WIN32)
    target_link_libraries(miniwin PUBLIC gdi32 user32)
endif()

add_library(app_core STATIC
    src/app/AndroidPattern.cpp
    src/app/ColorPalette.cpp
    src/app/PixelGrid.cpp
)

target_include_directories(app_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/miniwin
)

target_link_libraries(app_core PUBLIC miniwin)

add_executable(droid_pixel_painter WIN32
    src/main.cpp
)

target_link_libraries(droid_pixel_painter PRIVATE app_core)

if(MSVC)
    target_compile_options(app_core PRIVATE /W4 /permissive-)
    target_compile_options(miniwin PRIVATE /W4 /permissive-)
    target_compile_options(droid_pixel_painter PRIVATE /W4 /permissive-)
else()
    target_compile_options(app_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(miniwin PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(droid_pixel_painter PRIVATE -Wall -Wextra -Wpedantic)
endif()


