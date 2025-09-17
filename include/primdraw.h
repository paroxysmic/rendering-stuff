#ifndef _PRIMDRAW_H
#define _PRIMDRAW_H
#include "matrlib.h"
#include <algorithm>
#include <cmath>
#include <vector>
void setpix(vec2 t, int bw, int bh, std::vector<long> *bptr, long val);
void draw_line(vec2 orig, vec2 endp, int bw, int bh, std::vector<long> &image, long color);
void draw_rect(vec2 toplef, vec2 botrig, int bw, int bh, std::vector<long> *bptr, long color);
void draw_circle(vec2 centre, float r, int bw, int bh, std::vector<long> *bptr, long color);
#endif