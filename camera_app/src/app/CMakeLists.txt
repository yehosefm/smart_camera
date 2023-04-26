
add_executable(${PROJECT_NAME} main.cpp video_pip.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GST_APP_LIBRARIES} ${GST_VIDEO_LIBRARIES} project_config)