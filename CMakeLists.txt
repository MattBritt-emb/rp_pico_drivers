#
#   Top cmake file for rp_pico_drivers.
#   This just pulls in subdirs.
#
cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(rp_pico_drivers)

pico_sdk_init()

add_subdirectory(ssd1306)
add_subdirectory(ssd1306/example)
add_subdirectory(pwmPin)
add_subdirectory(pwmPin/example)