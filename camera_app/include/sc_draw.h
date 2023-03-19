/*********************************************
* File - sc_draw.h
* Decpiption - lib for drawing shapes on RGB images. 
* Project - Smart Camera
* Author - Yosi Malka, yehosefm@gmail.com
*********************************************/

#include "detector.h" // for box

#ifndef SC_DRAW_H
#define SC_DRAW_H

typedef enum {
    DRAW_ERROR_SUCCESS,
    DRAW_ERROR_NULLPTR
} DrawErrors;

typedef struct {
    unsigned char *buffer;
    unsigned int width;
    unsigned int height;
} ScImage;





#endif //SC_DRAW_H