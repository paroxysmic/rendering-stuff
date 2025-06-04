#ifndef MLIB_H_
#define MLIB_H_
#define EPSILON 1e-8
void draw_tri(float fpa[6], int bw, int bh, long *bptr, long color);
void setpix(float par[2], int bw, int bh, long* board, long color);
void draw_rect(float cpa[4], int bw, int bh, long *bptr, long color);
long floattocol(float r, float g, float b);
struct vec2 {
    float x, y, len;
    vec2(float a, float b){}
    void desc(){}
    vec2 operator+(const vec2 &a) const {}
    vec2 operator-(const vec2 &a) const {}
    vec2 operator*(const float a) const {}
    vec2 operator/(const float a) const {}
    vec2 norm(){}
};
#endif