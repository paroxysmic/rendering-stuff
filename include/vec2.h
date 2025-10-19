#pragma once
#include <cmath>
struct vec2 {
    float x, y;
    inline vec2(float a = 0.0f, float b = 0.0f) noexcept : x(a), y(b) {}
    inline vec2 operator+(const vec2 &a) const noexcept {return vec2(x + a.x, y + a.y);}
    inline vec2 operator-(const vec2 &a) const noexcept {return vec2(x - a.x, y - a.y);} 
    inline vec2 operator-() const noexcept {return vec2(-x, -y);}
    inline vec2 operator*(const float a) const noexcept {return vec2(x * a, y * a);}
    inline vec2 norm() const noexcept {
        float len = std::sqrt(x * x + y * y);
        if(std::abs(len - 1) < 1e-8) {return *this;}
        else { return *this * (1 / len); }
    };
    inline float dot(const vec2 &a) const noexcept {return x * a.x + y * a.y;}
    bool near_zero() const {
        return (std::fabs(x) < 1e-8) && (std::fabs(y) < 1e-8);
    }
    inline void desc() const noexcept;
};
