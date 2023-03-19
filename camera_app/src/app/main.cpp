#include <stdio.h>
#include "video_pip.hpp"


int main(int argc, char *argv[]){
    printf("Welcome to smart camera project \n");
    VideoPip pipe(argc, argv);
    pipe.play();
    printf("Smart Camera Bybye\n");
}
