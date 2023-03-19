project(Detection)
cmake_minimum_required(VERSION 3.20)

add_library(sc_detector SHARED detector.cpp)

set(TENSORFLOW_SOURCE_DIR "../../external/tensorflow_src" )

if(NOT TENSORFLOW_SOURCE_DIR)
  get_filename_component(TENSORFLOW_SOURCE_DIR
    "${CMAKE_CURRENT_LIST_DIR}/../../../../"
    ABSOLUTE
  )
endif()

add_subdirectory(
  "${TENSORFLOW_SOURCE_DIR}/tensorflow/lite"
  "${CMAKE_CURRENT_BINARY_DIR}/tensorflow-lite"
  EXCLUDE_FROM_ALL
)

#add_subdirectory(../sc_common sc_common)

set(CMAKE_CXX_STANDARD 17)
target_include_directories(sc_detector PUBLIC
  ../sc_common ../sc_image)
target_link_libraries(sc_detector
  tensorflow-lite sc_common
)
