cmake_minimum_required(VERSION 3.12)

project(pwmPin C CXX ASM)
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
        src/pwmPin.cpp)

set( HEADERS
        include/pwmPin.hpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} 
                                pico_stdlib 
                                hardware_gpio 
                                hardware_pwm)

# Include headers
target_include_directories(${PROJECT_NAME} PUBLIC include)
