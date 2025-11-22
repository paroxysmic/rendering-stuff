#include "drawlib.h"
vec3 barycoords(vec2 A, vec2 B, vec2 C, vec2 P) {
    vec2 v0 = B - A, v1 = C - A, v2 = P - A;
    float d00 = v0 * v0;
    float d01 = v0 * v1;
    float d11 = v1 * v1;
    float d20 = v2 * v0;
    float d21 = v2 * v1;
    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;
    if (v < 0 || w < 0 || u < 0) {
        return vec3{-1, 1, 1};
    }
    return vec3{v, w, u};
}
long collerp(long a, long b, float t) {
    int red = ((a >> 16) & 0xff) * (1 - t) + ((b >> 16) & 0xff) * t;
    int gre = ((a >> 8) & 0xff) * (1 - t) + ((b >> 8) & 0xff) * t;
    int blu = (a & 0xff) * (1 - t) + (b & 0xff) * t; 
    //color channel names are three letters to avoid a conflict with b
    return (red << 16) + (gre << 8) + blu;
}
void draw_line(vec2 sp, vec2 ep, long col, Image &image) {
    bool steep = abs(sp.x - ep.x) < abs(sp.y - ep.y);
    if(steep) {
        std::swap(sp.x, sp.y);
        std::swap(ep.x, ep.y);
    }
    if(sp.x > ep.x) {
        std::swap(sp.x, ep.x);
        std::swap(sp.y, ep.y);
    }
    for(int x=sp.x;x<ep.x;x++) {
        float t = (x - sp.x) / (ep.x - sp.x);
        int y = std::round(sp.y - (ep.y - sp.y) * t);
        if(steep) {
            image.m_image[y + x * image.m_iw] = col;
        } else {            
            image.m_image[x + y * image.m_iw] = col;
        }
    }
}
void draw_tri_zbuf(std::array<vec3, 3> cpa, Canvas &canvas, long color) {
    int xmin = std::min(canvas.m_iw - 1, (int)std::floor(std::min({cpa[0].x, cpa[1].x, cpa[2].x})));
    int xmax = std::max(0,             (int)std::ceil (std::max({cpa[0].x, cpa[1].x, cpa[2].x})));
    int ymin = std::min(canvas.m_ih - 1, (int)std::floor(std::min({cpa[0].y, cpa[1].y, cpa[2].y})));
    int ymax = std::max(0,             (int)std::ceil (std::max({cpa[0].y, cpa[1].y, cpa[2].y})));
    vec2 triA{cpa[0].x, cpa[0].y};
    vec2 triB{cpa[1].x, cpa[1].y};
    vec2 triC{cpa[2].x, cpa[2].y};
    for(int x=xmin;x<xmax;x++) {
        for(int y=ymin;y<ymax;y++) {
            int idx = x + y * canvas.m_iw;
            if (idx < 0 || idx >= canvas.m_iw * canvas.m_ih) {continue;}
            vec2 tvec{(float)x, (float)y};
            vec3 bcoord = barycoords(triA, triB, triC, tvec);
            float zval = bcoord.x * cpa[0].z + bcoord.y * cpa[1].z + bcoord.z * cpa[2].z;
            if (bcoord.x >= 0 && zval < canvas.m_zbuf[idx]) {
                canvas.m_zbuf[idx] = zval;
                canvas.m_image[idx] = color;
            }
        }
    }
    return;
}
void draw_tri_tricolor(std::array<vec3, 3> cpa, Canvas &canvas, std::array<long, 3> colors) {
    int xmin = std::min(canvas.m_iw - 1, (int)std::floor(std::min({cpa[0].x, cpa[1].x, cpa[2].x})));
    int xmax = std::max(0,             (int)std::ceil (std::max({cpa[0].x, cpa[1].x, cpa[2].x})));
    int ymin = std::min(canvas.m_ih - 1, (int)std::floor(std::min({cpa[0].y, cpa[1].y, cpa[2].y})));
    int ymax = std::max(0,             (int)std::ceil (std::max({cpa[0].y, cpa[1].y, cpa[2].y})));
    vec2 triA{cpa[0].x, cpa[0].y};
    vec2 triB{cpa[1].x, cpa[1].y};
    vec2 triC{cpa[2].x, cpa[2].y};
    for(int x=xmin;x<xmax;x++) {
        for(int y=ymin;y<ymax;y++) {
            int idx = x + y * canvas.m_iw;
            if (idx < 0 || idx >= canvas.m_iw * canvas.m_ih) {continue;}
            vec2 tvec{(float)x, (float)y};
            vec3 bcoord = barycoords(triA, triB, triC, tvec);
            float zval = bcoord.x * cpa[0].z + bcoord.y * cpa[1].z + bcoord.z * cpa[2].z;
            if (bcoord.x >= 0 && zval < canvas.m_zbuf[idx]) {
                canvas.m_zbuf[idx] = zval;
                int red = 0;
                int gre = 0;
                int blu = 0;
                for(int i=0;i<3;i++) {
                    red += (((colors[i] >> 16) & 0xff) * bcoord[i]);
                    gre += (((colors[i] >> 8 ) & 0xff) * bcoord[i]);
                    blu += (((colors[i]      ) & 0xff) * bcoord[i]);
                }
                red = std::clamp((int)(red + 0.5), 0, 255);
                gre = std::clamp((int)(gre + 0.5), 0, 255);
                blu = std::clamp((int)(blu + 0.5), 0, 255);
                long color = (red << 16) + (gre << 8) + blu;
                canvas.m_image[idx] = color;
            }
        }
    }
    return;
}
