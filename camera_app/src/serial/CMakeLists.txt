project(Serail)
cmake_minimum_required(VERSION 3.20)

add_library(sc_serial SHARED serial_moves.c serial.c)
target_include_directories(sc_serial PUBLIC  ../../include)
target_link_libraries(sc_serial sc_common)

#add_executable(test test.c)
#target_link_libraries(test sc_serial)