#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include "drawlib.h"
float sidecheck(vec2 test, vec2 orig, vec2 end) {
    //sidecheck gives a float back based on which side of the directed side the test point is on
    //positive if the point is on the left side 
    //zero if the point is on the line
    //and negative if the point in on the right side
    return (test.y  - orig.y) * (end.x - orig.x) - (test.x - orig.x) * (end.y - orig.y);
}
vec3 barycoords(vec2 A, vec2 B, vec2 C, vec2 P) {
    vec2 v0 = B - A, v1 = C - A, v2 = P - A;
    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;
    if (v < 0 || w < 0 || u < 0) {
        return vec3(-1, 1, 1);
    }
    return vec3(v, w, u);
}
long colorlerp(long a, long b, float t) {
    int red = ((a >> 16) & 0xff) * (1 - t) + ((b >> 16) & 0xff) * t;
    int gre = ((a >> 8) & 0xff) * (1 - t) + ((b >> 8) & 0xff) * t;
    int blu = (a & 0xff) * (1 - t) + (b & 0xff) * t; 
    //color channel names are three letters to avoid a conflict with b
    return (red << 16) + (gre << 8) + blu;
}
long floattocol(float r, float g, float b) {
    int ir = (int)(r * 255.999);
    int ig = (int)(g * 255.999);
    int ib = (int)(b * 255.999);
    return (ir << 16) + (ig << 8) + ib;
}
void draw_tri(std::vector<vec2> cpa, int bw, int bh, std::vector<long> *image, long color) {
    //THE POINTS SHOULD BE COUNTERCLOCKWISE (in the normal x-y plane, not graphics plane) TO WORK
    //this is because math loves counterclockwise and time is of the devil
    if(sidecheck(cpa[2], cpa[0], cpa[1]) < 0){
        int minx = std::min({0.0f, cpa[0].x, cpa[1].x, cpa[2].x});
        int miny = std::min({0.0f, cpa[0].x, cpa[1].y, cpa[2].y});
        int maxx = std::max({(float)bw, cpa[0].x, cpa[1].x, cpa[2].x});
        int maxy = std::max({(float)bh, cpa[0].y, cpa[1].y, cpa[2].y});
        vec2 tvec;
        for (int y = miny; y < maxy; y++) {
            for (int x = minx; x < maxx; x++) {
                tvec = vec2(x, y);
                if (sidecheck(tvec, cpa[0], cpa[1]) < 0 && sidecheck(tvec, cpa[1], cpa[2]) < 0 && sidecheck(tvec, cpa[2], cpa[0]) < 0){
                    (*image)[x + y * bw] = color; ;
                }
            }
        }
    }
}
void draw_conv(std::vector<vec2> *cpa, int bw, int bh, std::vector<long> *bptr, long color) {
    //cpa should be clockwise!!
    float minx, miny, maxx, maxy;
    float pixc;
    vec2 tvec;
    for(int i = 0; i < (*cpa).size(); i++) {
        if ((*cpa)[i].x > maxx) {
            maxx = (*cpa)[i].x;
        }
        if((*cpa)[i].y > maxy) {
            maxy = (*cpa)[i].y;
        }
        if((*cpa)[i].x < minx) {
            minx = (*cpa)[i].x;
        }
        if((*cpa)[i].y < miny) {
            miny = (*cpa)[i].y;
        }
    }
    for(int x = minx; x < maxx; x++) {
        for(int y = miny; y < maxy; y++) {
            pixc = 0.0f;
            for(int k = 0; k < 9; k++) {
                bool inpolyg = true;
                tvec = vec2(x + ((k % 3) + 1) / (float)9 , y + ((k / 3) * 2 + 1) / (float)9);
                for(int i = 0; i < cpa->size(); i++) {
                    if (sidecheck(tvec, (*cpa)[i], (*cpa)[(i + 1) % cpa->size()]) < 0) {
                        inpolyg = false;
                        break;
                    }
                }
                if(inpolyg) {
                    pixc++;
                }
            }
            (*bptr)[x + y * bw] = colorlerp((*bptr)[x + y * bw], color, pixc/9);
        }
    }
}
void draw_tri_zbuf(std::vector<vec3> &cpa, int iw, int ih, std::vector<long> &image, std::vector<float> &zbuf, long color) {
    int xmin = std::floor(std::min({(float)iw - 1, cpa[0].x, cpa[1].x, cpa[2].x}));
    int xmax = std::ceil(std::max({0.0f, cpa[0].x, cpa[1].x, cpa[2].x}));
    int ymin = std::floor(std::min({(float)ih - 1, cpa[0].y, cpa[1].y, cpa[2].y}));
    int ymax = std::ceil(std::max({0.0f, cpa[0].y, cpa[1].y, cpa[2].y}));
    vec2 triA = cpa[0].xy;
    vec2 triB = cpa[1].xy;
    vec2 triC = cpa[2].xy;
    for(int x=xmin;x<xmax;x++) {
        for(int y=ymin;y<ymax;y++) {
            //need to compute barycentric coords to find z-vals!!
            int idx = x + y * iw;
            if (idx < 0 || idx >= iw * ih) continue;
            vec2 tvec = vec2(x, y);
            vec3 bcoord = barycoords(triA, triB, triC, tvec);
            float zval = bcoord.x * cpa[0].z + bcoord.y * cpa[1].z + bcoord.z * cpa[2].z;
            if (bcoord.x >= 0 && zval < zbuf[idx]) {
                zbuf[idx] = zval;
                image[idx] = color;
            }
        }
    }
}
