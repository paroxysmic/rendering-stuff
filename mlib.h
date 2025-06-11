#ifndef MLIB_H_
#define MLIB_H_
#include <vector>
struct vec2 {
    float x, y, len;
    vec2(float a=0, float b=0);
    vec2 operator+(const vec2 &a) const;
    vec2 operator-(const vec2 &a) const; 
    vec2 operator*(const float a) const;
    vec2 operator/(const float a) const;
    vec2 norm() const;
    float dot(const vec2 &a) const;
    vec2 projonto(const vec2 &a) const;
    void desc();
};
struct vec3 {
    float x, y, z, len;
    vec3(float a=0, float b=0, float c=0);
    vec3 operator+(const vec3 &a) const;
    vec3 operator-(const vec3 &a) const;
    vec3 operator*(const float a) const;
    vec3 operator/(const float a) const;
    vec3 norm() const;
    float dot(const vec3 &a) const;
    vec3 projonto(const vec3 &a) const;
};
void setpix(vec2 t, int bw, int bh, std::vector<long> *board, long val);
void draw_line(float ox, float oy, float ex, float ey, int bw, int bh, std::vector<long> *board, long color);
void draw_tri(std::vector<vec2> cpa, int bw, int bh, std::vector<long> *board, long color);
void draw_rect(vec2 toplef, vec2 botrig, int bw, int bh, std::vector<long> *board, long color);
void draw_circle(vec2 centre, float r, int bw, int bh, std::vector<long> *board, long color);
long floattocol(float r, float g, float b);
float sidecheck(vec2 test, vec2 orig, vec2 end);
float areacalc(std::vector<vec2> *cpa);
#endif