#include <iostream>

#include <vector>

#include "mlib.h"
int main() {
    int iw = 400;
    int ih = 200;
    long scrarr[iw * ih];
    std::cout << "P3\n" << iw << '\n' << ih << "\n" << 255 << '\n'; 
    for(int x=0;x<iw;x++){
        for(int y=0;y<ih;y++){
            long col = floattocol((double)x / iw, (double)y / ih, 0);
            float poiarr[2] = {(float)x, (float)y};
            setpix(poiarr, iw, ih, scrarr, col);
        }
    }
    float poiarr[6] = {0.0, 0.0, 100.0, 100.0, 50.0, 200.0};
    draw_tri(&poiarr[0], iw, ih, &scrarr[0], (long)0x00000000);
    std::cerr << "done with writing to arr";
    for(int y=0;y<ih;y++){
        for(int x=0;x<iw;x++){
            long col = scrarr[x + y * iw];
            int r = (col & 0xff0000) >> 16;
            int g = (col & 0x00ff00) >> 8;
            int b = (col & 0x0000ff);
            std::cout << r << ' ' << g << ' ' << b << '\n';
        }
    }
    std::cerr << "done writing to file";
    return 0;
}