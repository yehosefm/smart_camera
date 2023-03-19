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