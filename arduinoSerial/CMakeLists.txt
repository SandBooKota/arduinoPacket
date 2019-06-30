cmake_minimum_required(VERSION 2.8)

project(arduinoSerial)

add_executable(serialTest arduino-serial.c arduino-serial-lib.c)
