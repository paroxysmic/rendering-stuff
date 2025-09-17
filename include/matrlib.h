#ifndef MATRLIB_H
#define MATRLIB_H
#include <array>
#include <cstdint>
struct vec2 {
    float x, y, len;
    vec2(const float a=0, const float b=0);
    vec2 operator+(const vec2 &a) const;
    vec2 operator-(const vec2 &a) const; 
    vec2 operator*(const float a) const;
    vec2 operator/(const float a) const;
    vec2 norm() const;
    vec2 rot(const float a) const;
    float dot(const vec2 &a) const;
    vec2 projonto(const vec2 &a) const;
    void desc();
};
struct vec3 {
    float x, y, z, len;
    vec2 xy;
    vec3(float a=0, float b=0, float c=0);
    vec3 operator+(const vec3 &a) const;
    vec3 operator-(const vec3 &a) const;
    vec3 operator*(const float a) const;
    vec3 operator/(const float a) const;
    vec3 norm() const;
    vec3 cross(const vec3 &a) const;
    float dot(const vec3 &a) const;
    vec3 projonto(const vec3 &a) const;
    vec2 camproj() const;
    void desc();
};
struct matr3 {
    float data[9];
    float det;
    matr3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
    matr3(float arr[9]);
    matr3();
    matr3 operator+(const matr3 &a) const;
    matr3 operator-(const matr3 &a) const;
    matr3 operator*(const float &a) const;
    matr3 operator/(const float &a) const;
    vec3 transform(const vec3 &a) const;
    matr3 matmul(const matr3 &a) const;
    matr3 transp() const;
    void desc();
};
matr3 eul2mat(float xrot, float yrot, float zrot);
#endif