#pragma once
#include "vec3.h"
#include <cmath>
struct matr3 {
    float data[9];
    matr3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
        data[0] = a; data[1] = b; data[2] = c;
        data[3] = d; data[4] = e; data[5] = f;
        data[6] = g; data[7] = h; data[8] = i;
    }
    matr3(float arr[9]) {for (int i=0;i<9;i++) {data[i] = arr[i];}}
    matr3() {for (int i=0;i<9;i++) {data[i] = 0;}}
    inline matr3 operator+(const matr3 &a) const noexcept {
        float retarr[9];
        for (int i=0;i<9;i++) {retarr[9] = data[i] + a.data[i];}
        return matr3(retarr);
    }
    inline matr3 operator-(const matr3 &a) const noexcept {
        float retarr[9];
        for (int i=0;i<9;i++) {retarr[9] = data[i] - a.data[i];}
        return matr3(retarr);
    }
    inline matr3 operator*(const float &a) const noexcept {
        float retarr[9];
        for (int i=0;i<9;i++) {retarr[9] = data[i] * a;}
        return matr3(retarr);
    };
    inline matr3 matmul(const matr3 &a) const noexcept {
        float retarr[9];
        retarr[0] = data[0] * a.data[0] + data[1] * a.data[3] + data[2] * a.data[6];
        retarr[1] = data[0] * a.data[1] + data[1] * a.data[4] + data[2] * a.data[7];
        retarr[2] = data[0] * a.data[2] + data[1] * a.data[5] + data[2] * a.data[8];
        retarr[3] = data[3] * a.data[0] + data[4] * a.data[3] + data[5] * a.data[6];
        retarr[4] = data[3] * a.data[1] + data[4] * a.data[4] + data[5] * a.data[7];
        retarr[5] = data[3] * a.data[2] + data[4] * a.data[5] + data[5] * a.data[8];
        retarr[6] = data[6] * a.data[0] + data[7] * a.data[3] + data[8] * a.data[6];
        retarr[7] = data[6] * a.data[1] + data[7] * a.data[4] + data[8] * a.data[7];
        retarr[8] = data[6] * a.data[2] + data[7] * a.data[5] + data[8] * a.data[8];
        return matr3(retarr);
    }; 
    inline vec3 transform(const vec3 &a) const noexcept {
       float x = a.x * data[0] + a.y * data[1] + a.z * data[2];
       float y = a.x * data[3] + a.y * data[4] + a.z * data[5]; 
       float z = a.x * data[6] + a.y * data[7] + a.z * data[8];
       return vec3(x, y, z); 
    }
    inline matr3 inverse() const noexcept {
        float A = data[4] * data[8] - data[5] * data[7];
        float B = data[2] * data[7] - data[1] * data[8];
        float C = data[1] * data[5] - data[2] * data[4];
        float D = data[5] * data[6] - data[3] * data[8];
        float E = data[0] * data[8] - data[2] * data[6];
        float F = data[2] * data[3] - data[0] * data[5];
        float G = data[3] * data[7] - data[4] * data[6];
        float H = data[1] * data[6] - data[0] * data[7];
        float I = data[0] * data[4] - data[1] * data[3];
        float det = data[0] * A + data[1] * B + data[2] * C;
        return matr3(A, B, C, D, E, F, G, H, I) * (1 / det);
    }
    inline void desc() const noexcept;
};