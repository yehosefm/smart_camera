add_library(sc_detector SHARED detector.cpp)


target_link_libraries(sc_detector PRIVATE tensorflow-lite sc_common)
target_link_libraries(sc_detector PUBLIC project_config)
