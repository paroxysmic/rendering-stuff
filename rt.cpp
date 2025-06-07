#include <iostream>

#include <vector>

#include "mlib.h"
int iw = 400;
int ih = 400;
int main() {
    long scrarr[iw * ih];
    std::cout << "P3\n" << iw << '\n' << ih << "\n" << 255 << '\n'; 
    for(int x=0;x<iw;x++){
        for(int y=0;y<ih;y++){
            setpix(vec2(x, y), iw, ih, scrarr, 0xffffff);
        }
    }
    vec2 parr[3] = {vec2(0.0, 0.0), vec2(50.0, 200.0), vec2(200.0, 50.0)};
    draw_tri(parr, iw, ih, scrarr, (long)0x00000000);
    std::cerr << "done with writing to arr!\n";
    for(int y=0;y<ih;y++){
        for(int x=0;x<iw;x++){
            long col = scrarr[x + y * iw];
            int r = (col & 0xff0000) >> 16;
            int g = (col & 0x00ff00) >> 8;
            int b = (col & 0x0000ff);
            std::cout << r << ' ' << g << ' ' << b << '\n';
        }
    }
    std::cerr << "done writing to file!";
    return 0;
}