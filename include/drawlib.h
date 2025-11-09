#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>
#include "imageio.h"
#include "matrlib.h"
vec3 barycoords(vec2 A, vec2 B, vec2 C, vec2 P);
long collerp(long a, long b, float t);
void draw_tri_zbuf(std::array<vec3, 3> cpa, Canvas &canvas, long color);
void draw_tri_tricolor(std::array<vec3, 3> cpa, Canvas &canvas, std::array<long, 3> colors);