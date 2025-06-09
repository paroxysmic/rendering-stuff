#include <iostream>
#include <random>
#include <vector>

#include "mlib.h"
int iw = 400;
int ih = 400;
int main() {
    long scrarr[iw * ih];
    std::cout << "P3\n"
              << iw << '\n'
              << ih << "\n"
              << 255 << '\n';
    for (int x = 0; x < iw; x++) {
        for (int y = 0; y < ih; y++) {
            setpix(vec2(x, y), iw, ih, scrarr, 0xffffff);
        }
    }
    vec2 parr[3];
    long col;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            parr[0] = vec2(20 * i + (rand() % 20), 20 * j + (rand() % 20));
            parr[1] = vec2(20 * i + (rand() % 20), 20 * j + (rand() % 20));
            parr[2] = vec2(20 * i + (rand() % 20), 20 * j + (rand() % 20));
            col = ((rand() & 0xff) << 16) + ((rand() & 0xff) << 8) + ((rand() & 0xff));
            draw_tri(parr, iw, ih, scrarr, col);
            std::cerr << "done with iter " << i << ' ' << j << '\n';
        }
    }
    std::cerr << "done with writing to arr!\n";
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