#include <pthread.h>
#include "detector.h"
#include "sc_image.h"

typedef struct detector_thread_s {
    pthread_t thread;
    pthread_mutex_t lock;
    ScImage* image;
    ScBox boxes;
    int is_alive;
} * detector_thread_s;



ScBox detection_thread_read_box(detector_thread_s t);


//return 1 if is empy;
//return 0 if is full;
int  detection_thread_image_is_empty(detector_thread_s t);


void detection_thread_image_push(detector_thread_s t, ScImage * image);


detector_thread_s open_detection_thread();


void destroy_detection_thread(detector_thread_s t);
