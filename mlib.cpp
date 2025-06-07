#include "mlib.h"
#include <cmath>
#include <iostream>
#define min(a, b) ((a > b) ? (b) : (a))
#define max(a, b) ((a > b) ? (a) : (b))
void draw_tri(vec2 cpa[3], int bw, int bh, long *bptr, long color) {
    float A, B, C, D, E, F;
    A = cpa[0].x, B = cpa[0].y, C = cpa[1].x, D = cpa[1].y, E = cpa[2].x, F = cpa[2].y;
    int minx = (int)min(min(A, C), E);
    int miny = (int)min(min(B, D), F);
    int maxx = (int)max(max(A, C), E);
    int maxy = (int)max(max(B, D), F);
    std::cerr << "A " << A << " B " << B << " C " << C << " D " << D << " E " << E << " F " << F << '\n';
    std::cerr << "minx " << minx << "maxx " << maxx << "miny " << miny << "maxy " << maxy << '\n';
    for (int y = minx; y < maxy; y++) {
        for (int x = minx; x < maxx; x++) {
            bool intriangle = true;
            intriangle &= ((x-A)*(D-B)-(y-B)*(C-A) < 0);
            intriangle &= ((x-C)*(B-D)-(y-D)*(A-C) < 0);
            intriangle &= ((x-E)*(B-F)-(y-F)*(A-E) < 0);
            if (intriangle) {
                setpix(vec2(x, y), 400, 400, bptr, color);
                std::cerr << "set pix " << x << ' ' << y << '\n';
            }
        }
    }
    std::cerr << "done drawing triangle!\n";
}
void draw_rect(vec2 cpa[2], int bw, int bh, long *bptr, long color) {
    int lx, hx, ly, hy;
    lx = floor(min(cpa[0].x, cpa[1].x));
    ly = floor(min(cpa[0].y, cpa[1].y));
    hx = ceil(max(cpa[0].x, cpa[1].x));
    hy = ceil(max(cpa[0].y, cpa[1].y));
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
void setpix(vec2 target, int bw, int bh, long *board, long val) {
    board[(int)floor(target.x) + (int)floor(target.y) * bw] = val;
}
void vec2::desc(){
    std::cout << x << ' ' << y << '\n';
}
vec2::vec2(float a, float b){
    x = a;
    y = b;
    len = sqrt(a*a+b*b);
}
vec2 vec2::operator+(const vec2 &a){
    return vec2(x + a.x, y + a.y);
}
vec2 vec2::operator-(const vec2 &a){
    return vec2(x - a.x, y - a.y);
}
vec2 vec2::operator*(const float a){
    return vec2(x * a, y * a);
}
vec2 vec2::operator/(const float a){
    return vec2(x / a, y / a);
}
vec2 vec2::norm(){
    if (len - 1 > -1e-8 && len - 1 < 1e-8){
        return *this;
    }
    else{
        return *this / len;
    }
}
float vec2::dot(const vec2 &a){
    return (x * a.x) + (y * a.y);    
}