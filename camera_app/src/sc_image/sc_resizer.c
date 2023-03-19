#include <stddef.h>
#include <stdlib.h>

#include "sc_image.h"
#include "sc_logger.h"

#define PIXEL_SIZE 3


ScImageErrors sc_image_resizer(ScImage *input, unsigned int nwidth, unsigned int nheight,ScImage *output) {
    unsigned char * buffer, *src_pixel, *new_pixel;
    unsigned int i, old_x, old_y;
    if (input == NULL || input->buffer == NULL || output == NULL){
        LOGGER_LOG(L_ERROR, "resizer got null ptr\n");
        return SC_IMAGE_ERROR_NULLPTR;
    }
    if (output->buffer != NULL){
        LOGGER_LOG(L_ERROR, "resizer got not null ptr\n");
        return SC_IMAGE_OUTPUT_NOT_NULL;
    }
    if (NULL == (buffer = malloc(PIXEL_SIZE * nwidth * nheight))){
        LOGGER_LOG(L_ERROR, "resizer alloc failed\n");
        return SC_IMAGE_ALLOC_FAILED; 
    }
    for (int line = 0; line < nheight; ++line){
        old_y = (float)input->height / nheight * line;
        for(int col =0; col < nwidth; ++col){
            old_x = (float)input->width / nwidth * col;
            src_pixel = input->buffer + PIXEL_SIZE * (old_y * input->width + old_x);
            new_pixel = buffer + (line * nwidth + col) * PIXEL_SIZE;
            for(i =0; i < PIXEL_SIZE; ++i) {
                *new_pixel++ = *src_pixel++;
            }
        }
    }
    output->height = nheight;
    output->width = nwidth;
    output->buffer = buffer;
    return SC_IMAGE_ERROR_SUCCESS;
}