#ifndef DRAWLIB_H_
#define DRAWLIB_H_
#include <vector>
#include "matrlib.h"
long colorlerp(long a, long b, float t);
void setpix(vec2 t, int bw, int bh, std::vector<long> *board, long val);
void draw_line(vec2 orig, vec2 endp, int bw, int bh, std::vector<long> *bptr, long color);
void draw_tri(std::vector<vec2> cpa, int bw, int bh, std::vector<long> *bptr, long color);
void draw_rect(vec2 toplef, vec2 botrig, int bw, int bh, std::vector<long> *bptr, long color);
void draw_conv(std::vector<vec2> *cpa, int bw, int bh, std::vector<long> *bptr, long color);
void draw_circle(vec2 centre, float r, int bw, int bh, std::vector<long> *bptr, long color);
long floattocol(float r, float g, float b);
float sidecheck(vec2 test, vec2 orig, vec2 end);
float areacalc(std::vector<vec2> *cpa);
matr3 eul2mat(float xrot, float yrot, float zrot);
std::vector<double> msort(std::vector<double> arr);
void draw_conv_zbuf(std::vector<vec3> *cpa, vec3 campos, int bw, int bh, std::vector<long> *bptr, std::vector<float> zbuf, long color);
vec3 barycoords(vec2 A, vec2 B, vec2 C, vec2 P);
#endif