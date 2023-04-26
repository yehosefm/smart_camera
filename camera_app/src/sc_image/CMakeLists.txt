
add_library(sc_image SHARED sc_resizer.c sc_draw.c)

target_link_libraries(sc_image project_config sc_common)