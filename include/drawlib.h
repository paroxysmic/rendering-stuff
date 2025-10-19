#pragma once
#define WHITE 0xffffff
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define BLACK 0x000000
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>
#include "matrlib.h"
float sidecheck(vec2 test, vec2 orig, vec2 end);
vec3 barycoords(vec2 A, vec2 B, vec2 C, vec2 P);
long colorlerp(long a, long b, float t);
void setpix(vec2 t, int bw, int bh, std::vector<long> *board, long val);
void draw_tri_zbuf(std::array<vec3, 3> cpa, int iw, int ih, std::vector<long> &image, std::vector<float> &zbuf, long color);
