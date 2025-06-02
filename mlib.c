#include "mlib.h"

#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
void draw_tri(float fpa[6], int bw, int bh, uint32_t *bptr, uint32_t color) {
    // uuuuh NOTE we will be using the standard graphics convection for x and y
    // this mean y goes downwards and the origin is the top left corner
    // its gonna be less of a headache i swear
    float minx = (fpa[0] > fpa[2]) ? (fpa[4] > fpa[2] ? fpa[2] : fpa[4]) : (fpa[4] > fpa[0] ? fpa[0] : fpa[4]);
    float miny = (fpa[1] > fpa[3]) ? (fpa[5] > fpa[3] ? fpa[3] : fpa[5]) : (fpa[5] > fpa[1] ? fpa[1] : fpa[5]);
    float maxx = (fpa[2] > fpa[0]) ? (fpa[2] > fpa[4] ? fpa[2] : fpa[4]) : (fpa[0] > fpa[4] ? fpa[0] : fpa[4]);
    float maxy = (fpa[3] > fpa[1]) ? (fpa[3] > fpa[5] ? fpa[3] : fpa[5]) : (fpa[1] > fpa[5] ? fpa[1] : fpa[5]);
    // Z = (p.x-p0.x) * (p1.y-p0.y) - (p1.x-p0.x) * (y-p0.y)
    // p is the point being tested here
    // if points are actually arranged in clockwise order:
    // Z > 0 means point is inside of triangle
    // Z = 0 means point is on border of triangle
    // Z < 0 means point is outside of triangle
    // and the numers get reversed if the points are counterclockwise
    if (minx < 0 || miny < 0 || maxx > bw || maxy > bh) {
        int lowx = floor(minx);
        int highx = ceil(maxx);
        int lowy = floor(miny);
        int highy = ceil(maxy);
        for (int px = lowx; px < highx; px++) {
            for (int py = lowy; py < highy; py++) {
                // note: we add 0.5 to each index to check the centre of each cell
                // this makes it so that <50% of the cell has to be covered by the triangle
                // to break this check, we would have to have a concave shape
                // and by just looking at the shape, triangles can never be concave
                int intriangle = 1;
                float tx = px + 0.5;
                float ty = py + 0.5;
                intriangle &= ((tx - fpa[0]) * (fpa[3] - fpa[1]) - (fpa[2] - fpa[0]) * (ty - fpa[1])) > 0;
                intriangle &= ((tx - fpa[2]) * (fpa[5] - fpa[3]) - (fpa[4] - fpa[2]) * (ty - fpa[3])) > 0;
                intriangle &= ((tx - fpa[4]) * (fpa[1] - fpa[5]) - (fpa[0] - fpa[4]) * (ty - fpa[5])) > 0;
                //so we're flattening the array
                //standard deal, left to right but top to bottom, like this
                //0 1 2
                //3 4 5
                //6 7 8
                if (intriangle) {
                    *bptr[px + bw * py] = color;
                }
            }
        }
    }
}