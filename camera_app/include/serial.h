/*********************************************
* File - serial.h
* Description - interanl serial manager. 
* Project - Smart Camera
* Author - Yosi Malka, yehosefm@gmail.com
*********************************************/


#ifndef SERIAL_H_
#define SERIAL_H_


typedef struct serial serial_t;


serial_t *open_serail();


int read_serail(serial_t *s,char *buffer, int len);


int write_serail(serial_t *s, char * buffer, int len);


#endif //SERIAL_H_