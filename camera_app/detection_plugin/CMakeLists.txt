##################### STANDARD HEADER #########################
cmake_minimum_required(VERSION 3.20)


##################### PROJECT DEF #############################
project(gstmyfilter)

####################### Targets ########################
add_library(${PROJECT_NAME} SHARED gstmyfilter.c resizer.c detection_thread.c)

################### Linked Libraries ###################

find_package(PkgConfig) 
pkg_search_module(GLIB REQUIRED glib-2.0) 
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GST_VIDEO REQUIRED gstreamer-video-1.0)

target_include_directories(${PROJECT_NAME} PUBLIC ${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GST_APP_LIBRARIES} ${GST_VIDEO_LIBRARIES})

add_subdirectory(../detection/ detection)
target_link_libraries(${PROJECT_NAME} sc_detector)
target_include_directories(${PROJECT_NAME} PRIVATE ../detection/)

add_subdirectory(../serial/ serial)
target_link_libraries(${PROJECT_NAME} sc_serial)
target_include_directories(${PROJECT_NAME} PRIVATE ../serial/)

add_subdirectory(../sc_common/ sc_common)
target_link_libraries(${PROJECT_NAME} sc_common)
target_include_directories(${PROJECT_NAME} PRIVATE ../sc_common/)

add_subdirectory(../sc_image/ sc_image)
target_link_libraries(${PROJECT_NAME} sc_image)
target_include_directories(${PROJECT_NAME} PRIVATE ../sc_image/)