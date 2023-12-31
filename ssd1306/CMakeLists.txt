cmake_minimum_required(VERSION 3.12)

project(ssd1306 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

set( SOURCES
        src/framebuffer.cpp
        src/ssd1306.cpp)

set( HEADERS
        include/font.hpp
        include/framebuffer.hpp
        include/ssd1306.hpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include headers
target_include_directories(${PROJECT_NAME} PUBLIC include)
