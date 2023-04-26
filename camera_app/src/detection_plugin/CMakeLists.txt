

add_library(gstmyfilter SHARED gstmyfilter.c resizer.c detection_thread.c)
target_link_libraries(gstmyfilter ${GST_APP_LIBRARIES} ${GST_VIDEO_LIBRARIES})
target_include_directories(gstmyfilter PUBLIC ${GSTREAMER_INCLUDE_DIRS})

target_link_libraries(gstmyfilter 
                      project_config
                      sc_common
                      sc_image
                      sc_serial
                      sc_detector)
