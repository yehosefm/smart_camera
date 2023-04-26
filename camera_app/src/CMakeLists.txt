##################### STANDARD HEADER #########################
cmake_minimum_required(VERSION 3.20)


project(smart_camera VERSION 1.0)

# Gstreamer
find_package(PkgConfig) 
pkg_search_module(GLIB REQUIRED glib-2.0) 
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GST_APP REQUIRED gstreamer-app-1.0)
pkg_check_modules(GST_VIDEO REQUIRED gstreamer-video-1.0)


# Tensorflow
set(TENSORFLOW_SOURCE_DIR "${CMAKE_SOURCE_DIR}/../../external/tensorflow_src" )

if(NOT TENSORFLOW_SOURCE_DIR)
  get_filename_component(TENSORFLOW_SOURCE_DIR
    "${CMAKE_CURRENT_LIST_DIR}/../../../../"
    ABSOLUTE
  )
endif()

add_subdirectory(
  "${TENSORFLOW_SOURCE_DIR}/tensorflow/lite/c"
  "${CMAKE_CURRENT_BINARY_DIR}/tensorflow-lite"
  EXCLUDE_FROM_ALL
)

#Include dir
add_library(project_config INTERFACE)
target_include_directories(project_config INTERFACE  "${CMAKE_SOURCE_DIR}/../include/")


add_subdirectory(sc_common)

add_subdirectory(sc_image)

add_subdirectory(serial)

add_subdirectory(detection)

add_subdirectory(detection_plugin)

add_subdirectory(app)