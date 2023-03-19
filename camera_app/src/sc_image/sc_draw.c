#include <limits.h>
#include "sc_image.h"


#define BYTE_FOR_PIXEL 3
#define LINE_FONT 4
#define LINE_COLOR ((unsigned int)(255) << 8) 


void _draw_vertical_line(unsigned char* buffer,unsigned int length){
    for(unsigned int i = 0; i < length; i += BYTE_FOR_PIXEL) {
        *buffer++ = CHAR_MAX & (LINE_COLOR >> 16);
        *buffer++ = CHAR_MAX & (LINE_COLOR >> 8);
        *buffer++ = CHAR_MAX & LINE_COLOR; 
    }
}


void _draw_horizonal_line(unsigned char* buffer, unsigned int width, unsigned int length){
    for(unsigned int line = 0; line < length; line++) {
        buffer[0] = CHAR_MAX & (LINE_COLOR >> 16);
        buffer[1] = CHAR_MAX & (LINE_COLOR >> 8);
        buffer[2] = CHAR_MAX & LINE_COLOR; 
        buffer += width * BYTE_FOR_PIXEL; 
    }
}


ScImageErrors sc_image_draw_box(ScImage *image, ScBox box){
    if(box.class_num < 0){
        return SC_IMAGE_ERROR_SUCCESS;
    }
    unsigned char * buffer = image->buffer;
    int x_min = box.x_min * image->width;
    int x_max = box.x_max * image->width;
    int y_min = box.y_min * image->height;
    int y_max = box.y_max * image->height;
    if(x_min <= 0){
        x_min = 1;
    }
    if(x_max >= image->width){
        x_max = image->width - 1;
    }
    if(y_min <= 0){
        y_min = 1;
    }
    if(y_max >= image->height){
        y_max = image->height - 1;
    }
    //draw top line
    for(int line = 0; line < LINE_FONT; line++) {
        if (y_min + line < image->height ){
            _draw_vertical_line(buffer + BYTE_FOR_PIXEL *((y_min + line) * image->width + x_min),
                                BYTE_FOR_PIXEL * (x_max - x_min));
        }
    }
    //draw bottom line
    for(int line = 0; line < LINE_FONT; line++) {
        if (y_max + line < image->height ){
            _draw_vertical_line(buffer + BYTE_FOR_PIXEL *((y_max + line) * image->width + x_min), 
                                BYTE_FOR_PIXEL *(x_max - x_min));
        }
    }
    //draw left line 
    for(int line = 0; line < LINE_FONT; line++) {
        if (x_min + line < image->width ){
            _draw_horizonal_line(buffer + BYTE_FOR_PIXEL * (y_min * image->width + x_min + line),
                                 image->width , y_max - y_min);
        }
    }
    //draw right line 
    for(int line = 0; line < LINE_FONT; line++) {
        if (x_min + line < image->width ){
            _draw_horizonal_line(buffer + BYTE_FOR_PIXEL * (y_min * image->width + x_max + line),
                                 image->width, y_max - y_min);
        }
    }
    return SC_IMAGE_ERROR_SUCCESS;
}