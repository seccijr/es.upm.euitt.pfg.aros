cmake_minimum_required(VERSION 2.8)
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME Aros)
set(Comm_RECURSE true)
set(Master_RECURSE true)
set(ArduinoUnit_RECURSE true)
set(ROLE "master" CACHE STRING "Role to be used during compilation. Default utility.")
set(PORT "/dev/ttyACM0" CACHE STRING "TTY port where the Arduino board is connected.")
project(${PROJECT_NAME})

register_hardware_platform(${ARDUINO_SDK_PATH}/hardware/arduino/avr/)
link_directories(${ARDUINO_SDK_PATH}/hardware/arduino/avr/libraries)

file(GLOB_RECURSE aros_SRCS
    "src/${ROLE}/*.cpp")

file(GLOB_RECURSE aros_HDRS
    "src/${ROLE}/*.h")

file(GLOB_RECURSE testing_SRCS
    "test/${ROLE}/*.cpp")

file(GLOB_RECURSE testing_HDRS
    "test/${ROLE}/*.h")

include_directories(src test)

generate_arduino_firmware(aros
    SKETCH  ${CMAKE_CURRENT_SOURCE_DIR}/src/${ROLE}/${ROLE}.ino
    SRCS ${aros_SRCS} ${testing_SRCS}
    HDRS ${aros_HDRS} ${testing_HDRS}
    BOARD uno
    PORT  ${PORT})
