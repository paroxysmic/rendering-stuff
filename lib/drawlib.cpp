#include "drawlib.h"
class canvas{
    private:
        int iw;
        int ih;
    public:
        std::vector<long> image;
        std::vector<float> zbuf;
        void draw_tri(std::array<vec3, 3> cpa, long color) {
            int xmin = std::floor(std::min({(float)iw - 1, cpa[0].x, cpa[1].x, cpa[2].x}));
            int xmax = std::ceil(std::max({0.0f, cpa[0].x, cpa[1].x, cpa[2].x}));
            int ymin = std::floor(std::min({(float)ih - 1, cpa[0].y, cpa[1].y, cpa[2].y}));
            int ymax = std::ceil(std::max({0.0f, cpa[0].y, cpa[1].y, cpa[2].y}));
            vec2 triA = vec2(cpa[0].x, cpa[0].y);
            vec2 triB = vec2(cpa[1].x, cpa[1].y);
            vec2 triC = vec2(cpa[2].x, cpa[2].y);
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
};
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
//going to put all this bs into a camera class or smngth...
void draw_tri_zbuf(std::array<vec3, 3> cpa, int iw, int ih, std::vector<long> &image, std::vector<float> &zbuf, long color) {
    int xmin = std::floor(std::min({(float)iw - 1, cpa[0].x, cpa[1].x, cpa[2].x}));
    int xmax = std::ceil(std::max({0.0f, cpa[0].x, cpa[1].x, cpa[2].x}));
    int ymin = std::floor(std::min({(float)ih - 1, cpa[0].y, cpa[1].y, cpa[2].y}));
    int ymax = std::ceil(std::max({0.0f, cpa[0].y, cpa[1].y, cpa[2].y}));
    vec2 triA = vec2(cpa[0].x, cpa[0].y);
    vec2 triB = vec2(cpa[1].x, cpa[1].y);
    vec2 triC = vec2(cpa[2].x, cpa[2].y);
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
    return;
}
