project(sc_common)
cmake_minimum_required(VERSION 3.20)

add_library(${PROJECT_NAME} SHARED sc_logger.c sc_paths.c)
target_include_directories(${PROJECT_NAME} PUBLIC  ../../include)