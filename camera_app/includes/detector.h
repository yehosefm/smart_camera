#include "sc_image.h"


#ifndef DETECTOR_H
#define DETECTOR_H


typedef struct p_detector * detector;


typedef enum {
    DETECTION_ERORR_SUCCESS,
    DETECTION_ERROR_NULL_PTR,
    DETECTION_ERROR_UNKNOWN,
    DETECTION_ERROR_UNMATCH_IMAGE
} DetectionErrors;


DetectionErrors detector_init(char *path, detector *res);


DetectionErrors detector_detect(detector d, ScImage *image, ScBox* res);


DetectionErrors detector_destroy(detector d);


#endif //DETECTOR_H





