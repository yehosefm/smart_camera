#define NET_Y_PIXEL 320
#define NET_X_PIXEL 320
#define BLACK 0

int resizer(unsigned char *image, int width, int height,unsigned char *output){
    for(int line = 0; line < NET_Y_PIXEL; ++line){
        for(int col =0; col < NET_X_PIXEL; ++col){
            unsigned int y = (float)height / NET_Y_PIXEL * line;
            unsigned int x = (float)width / NET_X_PIXEL * col;
            unsigned char *pixel = (unsigned char *)image + 3 * (y * width + x);
            output[(line * NET_X_PIXEL + col) *3] = pixel[0] ;
            output[(line * NET_X_PIXEL + col) * 3 + 1] = pixel[1] ;
            output[(line * NET_X_PIXEL + col) * 3 + 2] = pixel[2] ;
        }
    }
}