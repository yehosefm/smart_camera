##################### STANDARD HEADER #########################
cmake_minimum_required(VERSION 3.20)


##################### PROJECT DEF #############################
project(SmartCamera)

add_executable(${PROJECT_NAME} main.cpp video_pip.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC  ../../include)

add_subdirectory(../detection_plugin detection_plugin)

find_package(PkgConfig) 
pkg_search_module(GLIB REQUIRED glib-2.0) 
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GST_VIDEO REQUIRED gstreamer-video-1.0)

target_include_directories(${PROJECT_NAME} PUBLIC ${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GST_APP_LIBRARIES} ${GST_VIDEO_LIBRARIES})