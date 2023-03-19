##################### STANDARD HEADER #########################
cmake_minimum_required(VERSION 3.20)


##################### PROJECT DEF #############################
project(sc_image)

####################### Targets ########################
add_library(${PROJECT_NAME} SHARED sc_resizer.c sc_draw.c)

#add_subdirectory(../sc_common sc_common)

target_include_directories(${PROJECT_NAME} PUBLIC  ../../include)
target_link_libraries(${PROJECT_NAME} sc_common)