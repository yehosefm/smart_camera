
add_library(sc_serial SHARED serial_moves.c serial.c)
target_link_libraries(sc_serial project_config sc_common)
