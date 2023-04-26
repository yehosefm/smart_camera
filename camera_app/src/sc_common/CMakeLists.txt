

add_library(sc_common SHARED sc_logger.c sc_paths.c)
target_link_libraries(sc_common PUBLIC  project_config)