#include <iostream>
#include <random>
#include <vector>
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
    vec2 parr[3];
    long col;
    clock_t t = clock();
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 250; k++){
                parr[0] = vec2(20 * i + (rand() % 20), 20 * j + (rand() % 20));
                parr[1] = vec2(20 * i + (rand() % 20), 20 * j + (rand() % 20));
                parr[2] = vec2(20 * i + (rand() % 20), 20 * j + (rand() % 20));
                col = ((rand() & 0xff) << 16) + ((rand() & 0xff) << 8) + ((rand() & 0xff));
                draw_tri(parr, iw, ih, scrarr, col);
            }
        }
    }
    t = clock() - t;
    std::cerr << "done with writing to arr!\n";
    std::cerr << "took " << t << "ticks, or " << (float)t / 1000 << "seconds\n";
    for (int y = 0; y < ih; y++) {
        for (int x = 0; x < iw; x++) {
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