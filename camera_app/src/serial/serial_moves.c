#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "serial_moves.h"
#include "sc_logger.h"

enum portmode{
    S_AVAILABLE,
    S_MOVE_R,
    S_MOVE_L,
    S_DEAD
};


struct serail_controller_s {
    serial_t* serial;
    pthread_t thrd;
    pthread_cond_t cond;
    pthread_mutex_t mutex; //mode guard
    enum portmode  mode;
    int is_alive;
};


void _send_move_left(serial_t * s){
    unsigned char* msg = "l\n";
    write_serail(s, msg, 2);
}


void _send_move_right(serial_t * s){
    unsigned char* msg = "r\n";
    write_serail(s, msg, 2);
}


void * _thread_func(void * s){
    serial_controller serial_c= (serial_controller)s;
    while(serial_c->is_alive) {
        //wait for new cmd
        pthread_mutex_lock(&serial_c->mutex);
        while(serial_c->mode == S_AVAILABLE) {
            pthread_cond_wait(&serial_c->cond,&serial_c->mutex);
        }
        pthread_mutex_unlock(&serial_c->mutex);
        // execute new cmd
        if (serial_c->is_alive == 1 && serial_c->mode != S_DEAD) {
            if(serial_c-> mode == S_MOVE_L){
                _send_move_left(serial_c->serial);
            }
            if(serial_c-> mode == S_MOVE_R){
                _send_move_right(serial_c->serial);
            }
            char buffer[1000];
            read_serail(serial_c->serial,buffer, 1000);
            printf("serail read %s",buffer);
            sleep(3);
            pthread_mutex_lock(&serial_c->mutex);
            serial_c->mode = S_AVAILABLE;
            pthread_mutex_unlock(&serial_c->mutex);
        }
    }
}


serial_controller serial_controller_open(serial_t  *t) {
    serial_controller serail_c;
    if (t == NULL){
        return NULL;
    }
    serail_c = malloc(sizeof(struct serail_controller_s));
    if (serail_c == NULL){
        return NULL;
    }
    serail_c->serial = t;
    serail_c->is_alive = 1;
    serail_c->mode = S_AVAILABLE;
    if (0 !=pthread_mutex_init(&serail_c->mutex,NULL)){
        LOGGER_LOG(L_ERROR, "mutex can't init");
        free(serail_c);
        return NULL;
    }
    if (0 !=pthread_cond_init(&serail_c->cond,NULL)){
        LOGGER_LOG(L_ERROR, "condtion variable can't init");
        pthread_mutex_destroy(&serail_c->mutex);
        free(serail_c);
        return NULL;
    }
    pthread_create(&serail_c->thrd,NULL, _thread_func,serail_c);
    return serail_c;
}


void serail_controller_destroy(serial_controller s){
    if (s == NULL || s->is_alive == 0) {
        return;
    }
    s->is_alive = 0;
    pthread_join(s->thrd,NULL);
    pthread_mutex_destroy(&s->mutex);
    free(s);
}


SerialErrors serail_controller_available(serial_controller s){
    if(s == NULL) {
        return SERIAL_ERORR_NULLPTR;
    }
    if(! s->is_alive) {
        return SERIAL_ERROR_DEAD;
    }
    if(s->mode != S_AVAILABLE) {
        return SERIAL_ERROR_BUSY;
    }
    return SERIAL_ERROR_SUCCESS;
}


SerialErrors serial_controller_move_left(serial_controller t,int degrees) {
    if (t == NULL) {
        return SERIAL_ERORR_NULLPTR;
    }
    if (t->is_alive == 0) {
        return SERIAL_ERROR_DEAD;
    }

    pthread_mutex_lock(&t->mutex);
    if (t->mode != S_AVAILABLE) {
        pthread_mutex_unlock(&t->mutex);
        return SERIAL_ERROR_BUSY;
    }
    t->mode = S_MOVE_L;
    pthread_cond_signal(&t->cond);
    pthread_mutex_unlock(&t->mutex);
    return SERIAL_ERROR_SUCCESS;
}


SerialErrors serial_controller_move_right(serial_controller t,int degrees) {
    if (t == NULL) {
        return SERIAL_ERORR_NULLPTR;
    }
    if (t->is_alive == 0) {
        return SERIAL_ERROR_DEAD;
    }

    pthread_mutex_lock(&t->mutex);
    if (t->mode != S_AVAILABLE) {
        pthread_mutex_unlock(&t->mutex);
        return SERIAL_ERROR_BUSY;
    }
    t->mode = S_MOVE_R;
    pthread_cond_signal(&t->cond);
    pthread_mutex_unlock(&t->mutex);
    return SERIAL_ERROR_SUCCESS;
}
