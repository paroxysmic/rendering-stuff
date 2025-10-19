#pragma once
#include <cmath>
struct vec3 {
    float x{}, y{}, z{};
    inline vec3(float a = 0.0f, float b = 0.0f, float c = 0.0f) noexcept : x(a), y(b), z(c) {}
    inline vec3 operator+(const vec3 &a) const noexcept {return vec3(x + a.x, y + a.y, z + a.z);}
    inline vec3 operator-(const vec3 &a) const noexcept {return vec3(x - a.x, y - a.y, z - a.z);} 
    inline vec3 operator-() const noexcept {return vec3(-x, -y, -z);}
    inline vec3 operator*(const float a) const noexcept {return vec3(x * a, y * a, z * a);}
    inline vec3 norm() const noexcept {
        float len = std::sqrt(x * x + y * y + z * z);
        if(std::abs(len - 1) < 1e-8) {return *this;}
        else { return *this * (1 / len); }
    };
    bool near_zero() const {
        return (std::fabs(x) < 1e-8) && (std::fabs(y) < 1e-8) && (std::fabs(z) < 1e-8);
    }
    inline void desc() const noexcept;
};
inline float dot(const vec3 &a, const vec3 &b) noexcept { 
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline vec3 cross(const vec3 &a, const vec3 &b) noexcept {
    float x = a.y * b.z - a.z * b.y;
    float y = a.x * b.z - a.z * b.x;
    float z = a.x * b.y - a.y * b.x;
    return vec3(x, y, z);
}