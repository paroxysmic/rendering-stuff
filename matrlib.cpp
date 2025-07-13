#include "matrlib.h"
#include <vector>
#include <iostream>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
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
vec2 vec2::rot(const float a) const {
    double rang = a * M_PI / 180;
    return vec2(this->x * cos(rang) + this->y * sin(rang), -this->x * sin(rang) + this->y * cos(rang));
}
float vec2::dot(const vec2 &a) const {
    return (x * a.x) + (y * a.y);    
}
vec2 vec2::projonto(const vec2 &a) const {
    float scalar = this->dot(a) / a.dot(a);
    return a * scalar;
}
void vec2::desc() {
    std::cout << '|' << x << ' ' << y << "|\n";
}
vec3::vec3(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
    len = sqrt(x * x + y * y + z * z);
    xy = vec2(x, y);
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
vec3 vec3::cross(const vec3 &a) const {
    return vec3(y * a.z - z * a.y, z * a.x - a.z * x, x * a.y - y * a.x);
}
float vec3::dot(const vec3 &a) const {
    return x * a.x + y * a.y + z * a.z;
}
vec3 vec3::projonto(const vec3 &a) const {
    float scalar = this->dot(a) / a.dot(a);
    return a * scalar; 
}
vec2 vec3::camproj() const {
     return vec2(200 + (450 * this->x) / (this->z + 3), 200 + (450 * this->y) / (this->z + 3));
}
void vec3::desc() {
    std::cout << '|' << x << ' ' << y << ' ' << z << "|\n";
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
    //calculating adjugate matrix above, transposed
    return matr3(b00, b01, b02, b10, b11, b12, b20, b21, b22) / det;
}
void matr3::desc() {
    std::cout << '|' << a00 << ' ' << a01 << ' ' << a02 << '|' << '\n';
    std::cout << '|' << a10 << ' ' << a11 << ' ' << a12 << '|' << '\n';
    std::cout << '|' << a20 << ' ' << a21 << ' ' << a22 << '|' << '\n';    
}
//TODO: implement the general matrix type
//the setpix function is deprecated, only use for explicit testing!
//literally directly setting pixels makes it twice as fast 
//but then there's no bounds check so just be better ig 
