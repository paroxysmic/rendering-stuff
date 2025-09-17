#include "primdraw.h"
void setpix(vec2 t, int bw, int bh, std::vector<long> *bptr, long val) {
    if(t.x >= 0 && t.x < bw && t.y >= 0 && t.y < bh) {
        (*bptr)[(int)t.x + (int)t.y * bw] = val;
    }
}
void draw_line(vec2 orig, vec2 endp, int bw, int bh, std::vector<long> &image, long color) { 
    bool steep = false; 
    if (std::abs(orig.x-endp.x)<std::abs(orig.y-endp.y)) { 
        std::swap(orig.x, orig.y); 
        std::swap(endp.x, endp.y); 
        steep = true; 
    } 
    if (orig.x>endp.x) { 
        std::swap(orig.x, endp.x); 
        std::swap(orig.y, endp.y); 
    } 
    int dx = endp.x-orig.x; 
    int dy = endp.y-orig.y; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = orig.y; 
    for (int x=orig.x; x<=endp.x; x++) { 
        if (steep) { 
            image.at(y + x * bw) = color; 
        } else { 
            image.at(x + y * bw) = color; 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (endp.y>orig.y?1:-1); 
            error2 -= dx*2; 
        } 
    } 
} 
void draw_rect(vec2 toplef, vec2 botrig, int bw, int bh, std::vector<long> *bptr, long color) {
    for (int i = floor(toplef.x); i < botrig.x; i++) {
        for (int j = floor(botrig.y); j < toplef.y; j++) {
            (*bptr)[i + j * bw] = color;
        }
    }
}
void draw_circle(vec2 centre, float r, int bw, int bh, std::vector<long> *bptr, long color) {
    float lx, hx, ly, hy;
    lx = std::max((int)ceil(centre.x - r), 0);
    hx = std::min((int)ceil(centre.x + r), bw-1);
    ly = std::max((int)ceil(centre.y - r), 0);
    hy = std::min((int)ceil(centre.y + r), bh-1);
    for (int x = lx; x < hx; x++){
        for (int y = ly; y < hy; y++){
            float dx = x + 0.5 - centre.x;
            float dy = y + 0.5 - centre.y;
            if (dx * dx + dy * dy < r * r) {
                (*bptr)[x + y * bw] = color;
            }
        }
    }
}
