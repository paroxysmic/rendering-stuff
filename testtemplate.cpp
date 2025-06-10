#include <iostream>
#include <fstream>
#include <time.h>
#include "mlib.h"
int iw = 400;
int ih = 400;
int main() {
    long scrarr[iw * ih];
    std::cout << "P3\n" << iw << '\n' << ih << "\n" << 255 << '\n';
    for (int x = 0; x < iw; x++) {
        for (int y = 0; y < ih; y++) {
            setpix(vec2(x, y), iw, ih, scrarr, 0x000000);
        }
    }
    clock_t t = clock();
    //do your things here
    t = clock() - t;
    std::cerr << "done with writing to arr!\n";
    std::cerr << "took " << t << "ticks, or " << (float)t / 1000 << "seconds\n";
    for (int y = 0; y < ih; y++) {
        for (int x = 0; x < iw; x++) {
            long col = scrarr[x + y * iw];
            char r = (col & 0xff0000) >> 16;
            char g = (col & 0x00ff00) >> 8;
            char b = (col & 0x0000ff);
            std::cout << r << ' ' << g << ' ' << b << '\n';
        }
    }
    std::cerr << "done writing to file!";
    return 0;
}