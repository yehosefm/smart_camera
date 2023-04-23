/*********************************************
* File - sc_image.h
* Description - repersention of RGB image. 
* Project - Smart Camera
* Author - Yosi Malka, yehosefm@gmail.com
*********************************************/

#ifndef SC_IMAGE_H
#define SC_IMAGE_H

typedef enum {
    SC_IMAGE_ERROR_SUCCESS,
    SC_IMAGE_ERROR_NULLPTR,
    SC_IMAGE_OUTPUT_NOT_NULL,
    SC_IMAGE_ALLOC_FAILED
} ScImageErrors;



/*
* ScImage struct represent RGB image 1 byte for color
*/
typedef struct {
    unsigned char *buffer;
    unsigned int width;
    unsigned int height;
} ScImage;


/*
* ScBox represent box to draw on image.
* y_min, x_min, y_max, x_max float value between 0 to 1.
*/
typedef struct {
    int class_num;
    float y_min, x_min, y_max, x_max;
} ScBox;


/*
* sc_image_resizer take ScImage and create a new ScImage with other proportion.  
*/
ScImageErrors sc_image_resizer(ScImage *input, unsigned int nwidth, unsigned int nheight, ScImage *ouput);


/*
* sc_image_draw_box drawinig box with given place on image
*/
ScImageErrors sc_image_draw_box(ScImage *image, ScBox box); 


#endif //SC_IMAGE_H