#ifndef MLIB_H_
#define MLIB_H_
struct vec2 {
    float x, y, len;
    vec2(float a=0, float b=0);
    vec2 operator+(const vec2 &a);
    vec2 operator-(const vec2 &a); 
    vec2 operator*(const float a);
    vec2 operator/(const float a);
    vec2 norm();
    float dot(const vec2 &a);
};
void setpix(vec2 target, int bw, int bh, long* board, long color);
void draw_line(vec2 orig, vec2 endp, int bw, int bh, long *bptr, long color);
void draw_tri(vec2 cpa[3], int bw, int bh, long *bptr, long color);
void draw_rect(vec2 cpa[2], int bw, int bh, long *bptr, long color);
void draw_circle(vec2 centre, float radius, int bw, int bh, long *bptr, long color);
long floattocol(float r, float g, float b);
float sidecheck(vec2 test, vec2 orig, vec2 end);
float areacalc(vec2 cpa[], int pnum);
#endif