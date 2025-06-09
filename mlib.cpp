#include "mlib.h"
#include <cmath>
#include <iostream>
#include <algorithm>
float sidecheck(vec2 test, vec2 orig, vec2 end){
    return (test.x - orig.x) * (end.y - orig.y) - (test.y  - orig.y) * (end.x - orig.x);
}
void draw_tri(vec2 cpa[3], int bw, int bh, long *bptr, long color) {
    if (sidecheck((cpa[0] + cpa[1] + cpa[2])/3, cpa[0], cpa[1]) > 0){
        int minx = (int)std::min(std::min(cpa[0].x, cpa[1].x), cpa[2].x);
        int miny = (int)std::min(std::min(cpa[0].y, cpa[1].y), cpa[2].y);
        int maxx = (int)std::max(std::max(cpa[0].x, cpa[1].x), cpa[2].x);
        int maxy = (int)std::max(std::max(cpa[0].y, cpa[1].y), cpa[2].y);
        vec2 tvec;
        int dpix = 0;
        for (int y = miny; y < maxy; y++) {
            for (int x = minx; x < maxx; x++) {
                tvec = vec2(x, y);
                if (sidecheck(tvec, cpa[0], cpa[1]) > 0){
                    if (sidecheck(tvec, cpa[1], cpa[2]) > 0){
                        if (sidecheck(tvec, cpa[2], cpa[0]) > 0){
                            setpix(vec2(x, y), 400, 400, bptr, color);
                            dpix++;
                        }
                    }
                }
            }
        }
        std::cerr << "hey ";
    }
    else{
        vec2 fcpa[3] = {cpa[0], cpa[2], cpa[1]};
        draw_tri(fcpa, bw, bh, bptr, color);
    }
}
void draw_rect(vec2 cpa[2], int bw, int bh, long *bptr, long color) {
    int lx, hx, ly, hy;
    lx = floor(std::min(cpa[0].x, cpa[1].x));
    ly = floor(std::min(cpa[0].y, cpa[1].y));
    hx = ceil(std::max(cpa[0].x, cpa[1].x));
    hy = ceil(std::max(cpa[0].y, cpa[1].y));
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