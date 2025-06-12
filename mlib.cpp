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
    std::cout << '|' << x << "|\n";
    std::cout << '|' << y << "|\n";
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
void vec3::desc() {
    std::cout << '|' << x << "|\n";
    std::cout << '|' << y << "|\n";
    std::cout << '|' << z << "|\n";
}
matr3::matr3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    a00 = a;
    a01 = b;
    a02 = c;
    a10 = d;
    a11 = e;
    a12 = f;
    a20 = g;
    a21 = h;
    a22 = i;
    det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    trace = a00 + a11 + a22;
}
matr3 matr3::operator+(const matr3 &a) const {
    return matr3(a00 + a.a00, a01 + a.a01, a02 + a.a02, a10 + a.a10, a11 + a.a11, a12 + a.a12, a20 + a.a20, a21 + a.a21, a22 + a.a22);
}
matr3 matr3::operator-(const matr3 &a) const {
    return matr3(a00 - a.a00, a01 - a.a01, a02 - a.a02, a10 - a.a10, a11 - a.a11, a12 - a.a12, a20 - a.a20, a21 - a.a21, a22 - a.a22);
}
matr3 matr3::operator*(const float a) const {
    return matr3(a00 * a, a01 * a, a02 * a, a10 * a, a11 * a, a12 * a, a20 * a, a21 * a, a22 * a);
}
matr3 matr3::operator/(const float a) const {
    return matr3(a00 / a, a01 / a, a02 / a, a10 / a, a11 / a, a12 / a, a20 / a, a21 / a, a22 / a);
}
vec3 matr3::transform(const vec3 &a) const {
    return vec3(a.x * a00 + a.y * a01 + a.z * a02, a.x * a10 + a.y * a11 + a.z * a12, a.x * a20 + a.y * a21 + a.z * a22);
}
matr3 matr3::matmul(const matr3 &a) const {
    float b00, b01, b02, b10, b11, b12, b20, b21, b22;
    b00 = a00 * a.a00 + a01 * a.a10 + a02 * a.a20;
    b01 = a00 * a.a01 + a01 * a.a11 + a02 * a.a21;
    b02 = a00 * a.a02 + a01 * a.a12 + a02 * a.a22;    
    b10 = a10 * a.a00 + a11 * a.a10 + a12 * a.a20;
    b11 = a10 * a.a01 + a11 * a.a11 + a12 * a.a21;
    b12 = a10 * a.a02 + a11 * a.a12 + a12 * a.a22;
    b20 = a20 * a.a00 + a21 * a.a10 + a22 * a.a20;
    b21 = a20 * a.a01 + a21 * a.a11 + a22 * a.a21;
    b22 = a20 * a.a02 + a21 * a.a12 + a22 * a.a22;
    return matr3(b00, b01, b02, b10, b11, b12, b20, b21, b22);
}
matr3 matr3::transp() const {
    return matr3(a00, a10, a20, a01, a11, a21, a02, a12, a22);
}
matr3 matr3::inver() const {
    if (det == 0) {
        throw std::invalid_argument("non-invertible matrix! det is zero!");
    }
    float b00, b01, b02, b10, b11, b12, b20, b21, b22;
    b00 = a11 * a22 - a12 * a21;
    b01 = a02 * a21 - a01 * a22;
    b02 = a01 * a12 - a02 * a11;
    b10 = a12 * a20 - a10 * a22;
    b11 = a00 * a22 - a02 * a20;
    b12 = a02 * a10 - a00 * a12;
    b20 = a10 * a21 - a11 * a20;
    b21 = a01 * a20 - a00 * a21;
    b22 = a00 * a11 - a01 * a10;
    //calculating adjugate matrix above
    return matr3(b00, b01, b02, b10, b11, b12, b20, b21, b22) / det;
}
void matr3::desc() {
    std::cout << '|' << a00 << ' ' << a01 << ' ' << a02 << '|' << '\n';
    std::cout << '|' << a10 << ' ' << a11 << ' ' << a12 << '|' << '\n';
    std::cout << '|' << a20 << ' ' << a21 << ' ' << a22 << '|' << '\n';    
}
//the setpix function is deprecated, only use for explicit testing!
//literally directly setting pixels makes it twice as fast 
//but then there's no bounds check so just be better ig 
void setpix(vec2 t, int bw, int bh, std::vector<long> *bptr, long val) {
    if(t.x >= 0 && t.x < bw && t.y >= 0 && t.y < bh) {
        (*bptr)[(int)t.x + (int)t.y * bw] = val;
    }
}
void draw_line(float ox, float oy, float ex, float ey, int bw, int bh, std::vector<long> *bptr, long color) {
    bool steep = (oy - ey) > (ox - ex);
    if (steep) {
        std::swap(ox, oy);
        std::swap(ex, ey);
    }   
    if (ox > ex) {
        std::swap(ox, ex);
        std::swap(oy, ey);
    }
    float y = oy;
    for(int x=ox;x<ex;x++){
        if (steep) // if transposed, de−transpose
            (*bptr)[y + bw * x] = color;
        else {
            (*bptr)[x + bw * y] = color;
        }
        y += (ey-oy) / static_cast<float>(ex-ox);
    }
}
void draw_tri(std::vector<vec2> cpa, int bw, int bh, std::vector<long> *bptr, long color) {
    //THE POINTS SHOULD BE COUNTERCLOCKWISE (in the normal x-y plane, not graphics plane) TO WORK
    //this is because math loves conuterclockwise and time is of the devil
    if (abs(areacalc(&cpa)) < 1e-2){
        std::swap(cpa[0], cpa[1]);
    }
    if(sidecheck(cpa[2], cpa[0], cpa[1]) > 0){
        int minx = std::min(cpa[0].x, std::min(cpa[1].x, cpa[2].x));
        int miny = std::min(cpa[0].y, std::min(cpa[1].y, cpa[2].y));
        int maxx = std::max(cpa[0].x, std::max(cpa[1].x, cpa[2].x));
        int maxy = std::max(cpa[0].y, std::max(cpa[1].y, cpa[2].y));
        vec2 tvec;
        for (int y = miny; y < maxy; y++) {
            for (int x = minx; x < maxx; x++) {
                tvec = vec2(x, y);
                if (sidecheck(tvec, cpa[0], cpa[1]) > 0 && sidecheck(tvec, cpa[1], cpa[2]) > 0 && sidecheck(tvec, cpa[2], cpa[0]) > 0){
                    (*bptr)[x + bw * y] = color;
                }
            }
        }
    }
}
void draw_rect(vec2 toplef, vec2 botrig, int bw, int bh, std::vector<long> *bptr, long color) {
    for (int i = floor(toplef.x); i < botrig.x; i++) {
        for (int j = floor(botrig.y); j < toplef.y; j++) {
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
                (*bptr)[x + y * bw] = color;
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
float areacalc(std::vector<vec2> *cpa) {
    float rt = 0;
    for(int i=0;i<cpa->size();i++){
        vec2 v0 = (*cpa)[i];
        vec2 v1 = (*cpa)[(i + 1) % cpa->size()];
        rt += v0.x * v1.y;
        rt -= v0.y * v1.x;
    }
    return rt;
}
