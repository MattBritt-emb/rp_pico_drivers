cmake_minimum_required(VERSION 3.12)

project(led C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

set( SOURCES
        main.cpp )

set( HEADERS )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} pwmPin)
# target_link_libraries(${PROJECT_NAME} 
#                                 pico_stdlib 
#                                 hardware_gpio 
#                                 hardware_pwm)

# pico_add_extra_outputs(${PROJECT_NAME})
