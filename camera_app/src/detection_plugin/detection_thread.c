#include "detection_thread.h"
#include "serial_moves.h"

#include <stdlib.h>
#include <stdio.h>

void *detection_func(void *vargsp){
    detector_thread_s t_s = (detector_thread_s)vargsp;
    ScImage *image;
    ScBox res;
    detector detector_obj;
    if(DETECTION_ERORR_SUCCESS != detector_init(NULL, &detector_obj)) {
        printf("ERROR opening detector");
        return NULL;
    }
    //serial_t* serial_port = open_serail();
    //if(serial_port == NULL){
    //    printf("bug with serail\n");
    //}
    while(t_s->is_alive){
        pthread_mutex_lock(&t_s->lock);
        image = t_s->image;
        t_s->image = NULL;
        pthread_mutex_unlock(&t_s->lock);
        if(image != NULL){
            if(DETECTION_ERORR_SUCCESS != detector_detect(detector_obj,image,&res)){
                printf("ERORR detect detector");
            }
            pthread_mutex_lock(&t_s->lock);
            t_s->boxes = res;
            pthread_mutex_unlock(&t_s->lock);
            free(image);
            float avg = (t_s->boxes.x_max + t_s->boxes.x_min) / 2;
            if (avg > 0.6){
                //int byte_writen = serial_move_right(serial_port, 0);
                //printf("right %d\n", byte_writen);
                printf("right\n");
            } else if (avg < 0.4){
                //int byte_writen = serial_move_left(serial_port, 0);
                //printf("left %d\n", byte_writen);
                printf("left\n");
            }
        }
    }
}


ScBox detection_thread_read_box(detector_thread_s t){
    ScBox res;
    pthread_mutex_lock(&t->lock);
    res = t->boxes;
    pthread_mutex_unlock(&t->lock);
    return res;
}

//return 1 if is empy;
//return 0 if is full;
int  detection_thread_image_is_empty(detector_thread_s t){
    int res = 0;
    if(t == NULL){
        return 0;
    }
    pthread_mutex_lock(&t->lock);
    if(t->image == NULL){
        res = 1;
    }
    pthread_mutex_unlock(&t->lock);
    return res;
}

void detection_thread_image_push(detector_thread_s t, ScImage * image){
    if(t == NULL || image == NULL){
        return;
    }
    pthread_mutex_lock(&t->lock);
    t->image = image;
    pthread_mutex_unlock(&t->lock);
}


detector_thread_s open_detection_thread(){
    detector_thread_s res = malloc(sizeof(struct detector_thread_s));
    if(NULL == res){
        return NULL;
    }
    if (pthread_mutex_init(&res->lock, NULL) != 0) {
        free(res);
        return NULL;
    }
    res->image = NULL;
    res->boxes.class_num = -1;
    res->is_alive = 1;
    pthread_create(&res->thread,NULL,detection_func, res);
    return res;
}

void destroy_detection_thread(detector_thread_s t){
    if(t == NULL)
        return;
    t->is_alive = 0;
    pthread_join(t->thread, NULL);
    pthread_mutex_destroy(&t->lock);
    free(t);
}
