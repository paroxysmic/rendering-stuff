#include <stdint.h>

#include <iostream>

#include "mlib.h"
int main() {
    int image_width = 400;
    int image_height = 200;
    uint32_t scrn[image_height * image_width];
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";
    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            double r = double(i) / (image_height - 1);
            double g = double(j) / (image_width - 1);
            double b = 0.0;
            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);
            uint32_t pix = (uint32_t)((ir << 16) + (ig << 8) + ib);
            scrn[j + i * image_width] = pix;
        }
        std::cerr << double(i * 100) / image_height << "percent completed with writing to array!\n";
    }
    float farr[6] = {0.4, 40.4, 40.4, 10.4, 100.4, 100.4};
    draw_tri(farr, 400, 200, &scrn[0], 0xffffff);
    std::cerr << "done writing to arr!\n";
    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            uint32_t pix = scrn[j + i * image_width];
            int r = (pix & 0xff0000) >> 16;
            int g = (pix & 0x00ff00) >> 8;
            int b = (pix & 0x0000ff);
            std::cout << r << ' ' << g << ' ' << b << '\n';
        }
        std::clog << double(i * 100) / image_height << "percent completed with writing to the file!\n";
    }
    std::clog << "done writing to file!\n";
    return 0;
}