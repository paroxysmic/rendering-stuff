#include "mlib.h"
#include <cmath>
#include <iostream>
#define min(a, b) ((a > b) ? (b) : (a))
#define max(a, b) ((a > b) ? (a) : (b))
void draw_tri(float fpa[6], int bw, int bh, long *bptr, long color){
    float A, B, C, D, E, F;
    A = fpa[0], B = fpa[1], C = fpa[2], D = fpa[3], E = fpa[4], F = fpa[5];
    int minx = (int)min(min(A, C), E);
    int miny = (int)min(min(B, D), F);
    int maxx = (int)max(max(A, C), E);
    int maxy = (int)max(max(B, D), F);
    std::cerr << minx << ' ' << miny << ' ' << maxx << ' ' << maxy;
    // intriangle &= ((tx - fpa[0]) * (fpa[3] - fpa[1]) - (fpa[2] - fpa[0]) * (ty - fpa[1])) > 0;
    // intriangle &= ((tx - fpa[2]) * (fpa[5] - fpa[3]) - (fpa[4] - fpa[2]) * (ty - fpa[3])) > 0;
    // intriangle &= ((tx - fpa[4]) * (fpa[1] - fpa[5]) - (fpa[0] - fpa[4]) * (ty - fpa[5])) > 0;
    for(int y=minx;y<maxy;y++){
        for(int x=minx;x<maxx;x++){
            std::cerr << "started pix " << x << ' ' << y << '\n';
            bptr[x + y * bw] = color;
            std::cerr << "done with pix " << x << ' ' << y << '\n';
        }
    }
}
void draw_rect(float cpa[4], int bw, int bh, long *bptr, long color){
    int lx, hx, ly, hy;
    lx = floor(cpa[0] < cpa[2] ? cpa[0] : cpa[2]);
    ly = floor(cpa[2] < cpa[0] ? cpa[0] : cpa[2]);
    hx = ceil(cpa[1] < cpa[3] ? cpa[1] : cpa[3]);
    hy = ceil(cpa[3] < cpa[1] ? cpa[1] : cpa[3]);    
    for(int i=lx;i<hx;i++){
        for(int j=ly;j<hy;j++){
            bptr[i + j * bw] = color;
        }
    }
}
long floattocol(float r, float g, float b){
    int ir = (int) (r * 255.999);
    int ig = (int) (g * 255.999);
    int ib = (int) (b * 255.999);
    return (ir << 16) + (ig << 8) + ib;
}
void setpix(float parr[2], int bw, int bh, long* board, long val){
    board[(int)floor(parr[0]) + (int)floor(parr[1]) * bw] = val;
}