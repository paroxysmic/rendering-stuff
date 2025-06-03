#ifndef MLIB_H_
#define MLIB_H_
#include <stdint.h>
void draw_tri(float fpa[6], int bw, int bh, long *bptr, long color);
void setpix(float par[2], int bw, int bh, long* board, long color);
void draw_rect(float cpa[4], int bw, int bh, long *bptr, long color);
long floattocol(float r, float g, float b);
#endif