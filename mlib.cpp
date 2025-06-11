#include "mlib.h"
#include <cmath>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
vec2::vec2(float a, float b) {
    x = a;
    y = b;
    len = sqrt(a*a+b*b);
}
vec2 vec2::operator+(const vec2 &a) const {
    return vec2(x + a.x, y + a.y);
}
vec2 vec2::operator-(const vec2 &a) const {
    return vec2(x - a.x, y - a.y);
}
vec2 vec2::operator*(const float a) const {
    return vec2(x * a, y * a);
}
vec2 vec2::operator/(const float a) const {
    return vec2(x / a, y / a);
}
vec2 vec2::norm() const {
    if (len - 1 > -1e-8 && len - 1 < 1e-8){
        return *this;
    }
    else{
        return *this / len;
    }
}
float vec2::dot(const vec2 &a) const {
    return (x * a.x) + (y * a.y);    
}
vec2 vec2::projonto(const vec2 &a) const {
    float scalar = this->dot(a) / a.dot(a);
    return a * scalar;
}
void vec2::desc() {
    std::cout << x << ' ' << y << '\n';
}
vec3::vec3(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
    len = sqrt(x * x + y * y + z * z);
}
vec3 vec3::operator+(const vec3 &a) const {
    return vec3(x + a.x, y + a.y, z + a.z);
}
vec3 vec3::operator-(const vec3 &a) const {
    return vec3(x - a.x, y - a.y, z - a.z);
}
vec3 vec3::operator*(const float a) const {
    return vec3(x * a, y * a, z * a);
}
vec3 vec3::operator/(const float a) const {
    return vec3(x / a, y / a, z / a);
}
vec3 vec3::norm() const {
    if (abs(len - 1) > 1e-8) {
        return *this / len;
    }
    else {
        return *this;
    }
}
float vec3::dot(const vec3 &a) const {
    return x * a.x + y * a.y + z * a.z;
}
vec3 vec3::projonto(const vec3 &a) const {
    float scalar = this->dot(a) / a.dot(a);
    return a * scalar; 
}
void setpix(vec2 t, int bw, int bh, std::vector<long> *bptr, long val) {
    if(t.x >= 0 && t.x < bw && t.y >= 0 && t.y < bh) {
        (*bptr)[(int)t.x + (int)t.y * bw] = val;
    }
}
//TODO: implement draw_line
void draw_line(vec2 orig, vec2 endp, int bw, int bh, std::vector<long> *bptr, long color) {

}
void draw_tri(vec2 cpa[3], int bw, int bh, std::vector<long> *bptr, long color) {
    //THE POINTS SHOULD BE COUNTERCLOCKWISE (in the normal x-y plane, not graphics plane) TO WORK
    if (abs(areacalc(cpa, 3)) >= 1e-2){
        if(sidecheck(cpa[2], cpa[0], cpa[1]) > 0){
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
        }
        else{
            vec2 ncpa[3] = {cpa[0], cpa[2], cpa[1]};
            draw_tri(ncpa, bw, bh, bptr, color);
        }
    }
}
void draw_rect(vec2 cpa[2], int bw, int bh, std::vector<long> *bptr, long color) {
    int lx, hx, ly, hy;
    lx = floor(std::min(cpa[0].x, cpa[1].x));
    ly = floor(std::min(cpa[0].y, cpa[1].y));
    hx = ceil(std::max(cpa[0].x, cpa[1].x));
    hy = ceil(std::max(cpa[0].y, cpa[1].y));
    for (int i = lx; i < hx; i++) {
        for (int j = ly; j < hy; j++) {
            (*bptr)[i + j * bw] = color;
        }
    }
}
void draw_circle(vec2 centre, float r, int bw, int bh, std::vector<long> *bptr, long color) {
    float lx, hx, ly, hy;
    lx = std::max((int)ceil(centre.x - r), 0);
    hx = std::min((int)ceil(centre.x + r), bw-1);
    ly = std::max((int)ceil(centre.y - r), 0);
    hy = std::min((int)ceil(centre.y + r), bh-1);
    for (int x = lx; x < hx; x++){
        for (int y = ly; y < hy; y++){
            float dx = x + 0.5 - centre.x;
            float dy = y + 0.5 - centre.y;
            if (dx * dx + dy * dy < r * r) {
                setpix(vec2(x, y), bw, bh, bptr, color);
            }
        }
    }
}
long floattocol(float r, float g, float b) {
    int ir = (int)(r * 255.999);
    int ig = (int)(g * 255.999);
    int ib = (int)(b * 255.999);
    return (ir << 16) + (ig << 8) + ib;
}
float sidecheck(vec2 test, vec2 orig, vec2 end) {
    //sidecheck gives a float back based on which side of the directed side the test point is on
    //positive if the point is on the left side 
    //zero if the point is on the line
    //and negative if the point in on the right side
    return (test.y  - orig.y) * (end.x - orig.x) - (test.x - orig.x) * (end.y - orig.y);
}
float areacalc(vec2 cpa[], int pnum) {
    float rt = 0;
    for(int i=0;i<pnum;i++){
        vec2 v0 = cpa[i];
        vec2 v1 = cpa[(i + 1) % pnum];
        rt += v0.x * v1.y;
        rt -= v0.y * v1.x;
    }
    return rt;
}
