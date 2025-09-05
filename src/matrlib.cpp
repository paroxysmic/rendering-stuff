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
    data[0] = a;
    data[1] = b;
    data[2] = c;
    data[3] = d;
    data[4] = e;
    data[5] = f;
    data[6] = g;
    data[7] = h;
    data[8] = i;
    det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}
matr3::matr3(float arr[9]) {
    for(int i=0;i<9;i++) {
        data[i] = arr[i];
    }
    det = data[0] * (data[4] * data[8] - data[5] * data[7]) - 
            data[1] * (data[3] * data[8] - data[5] * data[6]) + 
            data[2] * (data[3] * data[7] - data[4] * data[6]);
}
matr3::matr3() {
    for(int i=0;i<9;i++) {
        data[i] = 0;
    }
    det = 0;
}
matr3 matr3::operator+(const matr3 &a) const {
    float ret[9];
    for(int i=0;i<9;i++) {
        ret[i] = data[i] + a.data[i];
    }
    return matr3(ret);
}
matr3 matr3::operator-(const matr3 &a) const {
    float ret[9];
    for(int i=0;i<9;i++) {
        ret[i] = data[i] - a.data[i];
    }
    return matr3(ret);
}
matr3 matr3::operator*(const float &a) const {
    float ret[9];
    for(int i=0;i<9;i++) {
        ret[i] = data[i] * a;
    }
    return matr3(ret);
}
matr3 matr3::operator/(const float &a) const {
    float ret[9];
    for(int i=0;i<9;i++) {
        ret[i] = data[i] / a;
    }
    return matr3(ret);
}
vec3 matr3::transform(const vec3 &a) const {
    return vec3(a.x * a00 + a.y * a01 + a.z * a02, a.x * a10 + a.y * a11 + a.z * a12, a.x * a20 + a.y * a21 + a.z * a22);
}
matr3 matr3::matmul(const matr3 &a) const {
    float retarr[9];
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            float rt = 0;
            for(int k=0;k<3;k++) {
                rt += data[j + k * 3] * a.data[k + i * 3];
            }
            retarr[j + i * 3] = rt;
        }
    }
    return matr3(retarr);
}
matr3 matr3::transp() const {
    float retarr[9];
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            retarr[i + j * 3] = data[j + i * 3];
        }
    } 
    return matr3(retarr);
} 
matr3 matr3::inver() const {
    if (det == 0) {
        throw std::invalid_argument("non-invertible matrix! det is zero!");
    }
    float b0, b1, b2, b3, b4, b5, b6, b7, b8;
    b0 = a4 * a8 - a5 * a7;
    b1 = a2 * a7 - a1 * a8;
    b2 = a1 * a5 - a2 * a4;
    b3 = a5 * a6 - a3 * a8;
    b4 = a0 * a8 - a2 * a6;
    b5 = a2 * a3 - a0 * a5;
    b6 = a3 * a7 - a4 * a6;
    b7 = a1 * a6 - a0 * a7;
    b8 = a0 * a4 - a1 * a3;
    //calculating adjugate matrix above, transposed
    return matr3(b0, b1, b2, b3, b4, b5, b6, b7, b8) / det;
}
void matr3::desc() {
    for(int i=0;i<3;i++) {
        std::cout << '| ';
        for(int j=0;j<3;j++) {
            std::cout << data[j + i * 3] << ' ';
        }
        std::cout << "|\n";
    } 
}
