cmake_minimum_required(VERSION 2.8)
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME Aros)
project(${PROJECT_NAME})

print_board_list()
print_programmer_list()

generate_arduino_firmware(${PROJECT_NAME}
    SRCS ${PROJECT_NAME}.cpp
    BOARD uno)

