/*********************************************
* File - serial_moves.h
* Decpiption - controll of engine movment via serail. 
* Project - Smart Camera
* Author - Yosi Malka, yehosefm@gmail.com
*********************************************/

#include "serial.h"

typedef struct serail_controller_s * serial_controller;

typedef enum {
    SERIAL_ERROR_SUCCESS,
    SERIAL_ERORR_NULLPTR,
    SERIAL_ERROR_DEAD,
    SERIAL_ERROR_TIMEOUT,
    SERIAL_ERROR_BUSY,
} SerialErrors;


serial_controller serial_controller_open(serial_t  *t);


void serail_controller_destroy(serial_controller s);


SerialErrors serail_controller_available(serial_controller s);


SerialErrors serial_controller_move_left(serial_controller t,int degrees);


SerialErrors serial_controller_move_right(serial_controller t,int degrees);
