#pragma once
#include <cmath>
#include <iostream>
#define TAU 6.283185307179586
typedef float num;
struct vec2 {
    num x, y;
    inline vec2(num a = 0.0f, num b = 0.0f) : x(a), y(b) {}
    inline vec2 operator+(const vec2 &a) const {return vec2(x + a.x, y + a.y);}
    inline vec2 operator-(const vec2 &a) const {return vec2(x - a.x, y - a.y);} 
    inline vec2 operator-() const {return vec2(-x, -y);}
    inline vec2 operator*(const num a) const {return vec2(x * a, y * a);}
    inline vec2 norm() const {
        num len = std::sqrt(x * x + y * y);
        if(std::abs(len - 1) < 1e-8) {return *this;}
        else { return *this * (1 / len); }
    };
    inline num dot(const vec2 &a) const {return x * a.x + y * a.y;}
    bool near_zero() const {
        return (std::fabs(x) < 1e-8) && (std::fabs(y) < 1e-8);
    }
    inline void desc() const{
        std::cout << "| " << x << " " << y << " |\n";
    }
};
inline num operator*(vec2 &lhs, vec2 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
struct vec3 {
    num x, y, z;
    num &operator[]  (const int ind)       {return ind == 2 ? z : (ind == 1 ? y : x);}
    num  operator[]  (const int ind) const {return ind == 2 ? z : (ind == 1 ? y : x);}
    inline vec3 operator+(const vec3 &a) const {return vec3{x + a.x, y + a.y, z + a.z};}
    inline vec3 operator-(const vec3 &a) const {return vec3{x - a.x, y - a.y, z - a.z};} 
    inline vec3 operator-() const {return vec3{-x, -y, -z};}
    inline vec3 operator*(const num &a) const {return vec3{x * a, y * a, z * a};}
    inline vec3 norm() const {
        num len = std::sqrt(x * x + y * y + z * z);
        if(std::abs(len - 1) < 1e-8) {return vec3{x, y, z};}
        else { return vec3{x / len, y / len, z / len}; }
    };
    inline void desc() const{
        std::cout << "| " << x << " " << y << " " << z << " |\n";
    }
};
inline vec3 operator*(const num &lhs, const vec3 &rhs) {
    return rhs * lhs;
}  
inline num operator*(const vec3 &a, const vec3 &b) { 
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline vec3 cross(const vec3 &a, const vec3 &b) {
    num x = a.y * b.z - a.z * b.y;
    num y = a.x * b.z - a.z * b.x;
    num z = a.x * b.y - a.y * b.x;
    return vec3{x, y, z};
}
struct matr3 {
    num _data[9];
    num &operator[]  (const int ind)       {return _data[ind];}
    num  operator[]  (const int ind) const {return _data[ind];}
    inline matr3 inverse() const {
        num A = _data[4] * _data[8] - _data[5] * _data[7];
        num B = _data[2] * _data[7] - _data[1] * _data[8];
        num C = _data[1] * _data[5] - _data[2] * _data[4];
        num D = _data[5] * _data[6] - _data[3] * _data[8];
        num E = _data[0] * _data[8] - _data[2] * _data[6];
        num F = _data[2] * _data[3] - _data[0] * _data[5];
        num G = _data[3] * _data[7] - _data[4] * _data[6];
        num H = _data[1] * _data[6] - _data[0] * _data[7];
        num I = _data[0] * _data[4] - _data[1] * _data[3];
        num det = _data[0] * A + _data[1] * B + _data[2] * C;
        return matr3{A / det, B / det, C / det, 
                    D / det, E / det, F / det, 
                    G / det, H / det, I / det};
    }
    inline void desc() const{
        std::cout << "| " << _data[0] << " " << _data[1] << " " << _data[2] << " |\n";
        std::cout << "| " << _data[3] << " " << _data[4] << " " << _data[5] << " |\n";
        std::cout << "| " << _data[6] << " " << _data[7] << " " << _data[8] << " |\n\n";
    } 
};
inline matr3 operator* (const matr3 &lhs, const num &rhs) {
    matr3 res;
    for(int i=0;i<9;i++) {res[i] = lhs[i] * rhs;}
    return res;
}
inline vec3 operator* (const matr3 &lhs, const vec3 &rhs) {
    vec3 res;
    for(int i=0;i<3;i++) {
        res[i] = 0;
        for(int j=0;j<3;j++) {
            res[i] += lhs[j + i * 3] * rhs[j];
        }
    }
    return res;
}
inline matr3 operator* (const matr3 &lhs, const matr3 &rhs) {
    matr3 res;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            res[j + i * 3] = 0;
            for(int k=0;k<3;k++) {
                res[j + i * 3] += lhs[k + i * 3] * rhs[j + k * 3];
            }
        }
    }
    return res;
} 
inline matr3 operator/ (const matr3 &lhs, const num &rhs) {
    matr3 res;
    for(int i=0;i<9;i++) {res[i] = lhs[i] * rhs;}
    return res;
}

matr3 eul2mat(num xrot, num yrot, num zrot);