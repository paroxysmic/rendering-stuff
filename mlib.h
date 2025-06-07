#ifndef MLIB_H_
#define MLIB_H_
struct vec2 {
    float x, y, len;
    vec2(float a=0, float b=0);
    void desc();
    vec2 operator+(const vec2 &a);
    vec2 operator-(const vec2 &a); 
    vec2 operator*(const float a);
    vec2 operator/(const float a);
    vec2 norm();
    float dot(const vec2 &a);
};
float sidecheck(vec2 test, vec2 orig, vec2 end);
void draw_tri(vec2 cpa[3], int bw, int bh, long *bptr, long color);
void setpix(vec2 target, int bw, int bh, long* board, long color);
void draw_rect(vec2 cpa[2], int bw, int bh, long *bptr, long color);
long floattocol(float r, float g, float b);
#endif