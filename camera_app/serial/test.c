#include "serial_moves.h"
#include <unistd.h>
#include <stdio.h>


int echo(serial_t *s){
    char buff[256];
    while(1) {
        write_serail(s, "l\n", 4);

        int res = read_serail(s, buff, 256);
        if(res >0){
            printf("%d reading: %s",res, buff);
        } else {
            printf("Noting reading \n");
        }
    }
}



int main(int argc, void *argv[])
{

    char buf[256];
    serial_t *s = open_serail();
    while(1){
        for(int i = 0; i < 18; i++){
            printf("%d",serial_move_left(s,1));
            sleep(1);
        }
        for(int i = 0; i < 18; i++){
            printf("%d", serial_move_right(s,1));
            sleep(1);
        }
    }
}