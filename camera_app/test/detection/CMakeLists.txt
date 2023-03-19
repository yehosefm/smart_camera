
project(DetectorTest)
cmake_minimum_required(VERSION 3.20)

set(DETECTION_DIR ../../detection)

add_subdirectory(${DETECTION_DIR} detection)  

add_executable(detector_tests test.c)

target_include_directories(detector_tests PUBLIC ${DETECTION_DIR})
target_link_libraries(detector_tests sc_detector)
