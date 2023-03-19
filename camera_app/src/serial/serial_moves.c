#include "serial_moves.h"


int serial_move_left(serial_t *t,int degrees){
    unsigned char msg[] = { 'l', '\r' };
    return write_serail(t, msg, 2);
}


int serial_move_right(serial_t *t, int degrees){
    unsigned char msg[] = { 'r', '\r' };
    return write_serail(t, msg, 2);
}