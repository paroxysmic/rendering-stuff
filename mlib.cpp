#include "mlib.h"
#include <cmath>
#include <iostream>
#define min(a, b) ((a > b) ? (b) : (a))
#define max(a, b) ((a > b) ? (a) : (b))
void draw_tri(float fpa[6], int bw, int bh, long *bptr, long color) {
    float A, B, C, D, E, F;
    A = fpa[0], B = fpa[1], C = fpa[2], D = fpa[3], E = fpa[4], F = fpa[5];
    float w = (A * D) + (C * F) + (E * B) - (B * C) - (D * E) - (F * A) > 0;
    std::cerr << (w > 0 ? "cw\n" : "ccw\n");
    if (w > 0){
        int minx = (int)min(min(A, C), E);
        int miny = (int)min(min(B, D), F);
        int maxx = (int)max(max(A, C), E);
        int maxy = (int)max(max(B, D), F);
        for (int y = minx; y < maxy; y++) {
            for (int x = minx; x < maxx; x++) {
                bool intriangle = true;
                intriangle &= ((x-A)*(D-B)-(y-B)*(C-A) < 0);
                intriangle &= ((x-C)*(B-D)-(y-D)*(A-C) < 0);
                intriangle &= ((x-E)*(B-F)-(y-F)*(A-E) < 0);
                if (intriangle) {
                    bptr[x + y * bw] = color;
                }
            }
        }
    std::cerr << "done drawing triangle!\n";
    }
}
void draw_rect(float cpa[4], int bw, int bh, long *bptr, long color) {
    int lx, hx, ly, hy;
    lx = floor(min(cpa[0], cpa[2]));
    ly = floor(min(cpa[1], cpa[3]));
    hx = ceil(max(cpa[0], cpa[2]));
    hy = ceil(max(cpa[1], cpa[3]));
    for (int i = lx; i < hx; i++) {
        for (int j = ly; j < hy; j++) {
            bptr[i + j * bw] = color;
        }
    }
}
long floattocol(float r, float g, float b) {
    int ir = (int)(r * 255.999);
    int ig = (int)(g * 255.999);
    int ib = (int)(b * 255.999);
    return (ir << 16) + (ig << 8) + ib;
}
void setpix(float parr[2], int bw, int bh, long *board, long val) {
    board[(int)floor(parr[0]) + (int)floor(parr[1]) * bw] = val;
}
struct vec2{
    float x, y, len;
    vec2(float a, float b){
        x = a;
        y = b;
    }
    vec2 operator+ (const vec2 &a){
        return vec2(x + a.x, y + a.y);
    }
    vec2 operator- (const vec2 &a){
        return vec2(x - a.x, y - a.y);
    }
    vec2 operator* (const float a){
        return vec2(x * a, y * a);
    }
    vec2 operator/ (const float a){
        return vec2(x / a, y / a);
    }
    vec2 norm(){
        if (abs(1 - len) > EPSILON){
            return *this;
        }
        else{
            return *this/len;
        }
    }
};
