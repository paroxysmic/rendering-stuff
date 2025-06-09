#include "mlib.h"
int main(){
    long scrarr[9];
    long col = 0x000000;
    vec2 parr[3];
    parr[0] = vec2(0, 0);
    parr[1] = vec2(1, 1);
    parr[2] = vec2(2, 2);
    draw_tri(parr, 3, 3, scrarr, col);
    return 0;
} 