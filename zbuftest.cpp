#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <time.h>
#include "matrlib.h"
#include "drawlib.h"
const int iw = 400;
const int ih = 400;
int main(int argc, char **argv) {
    if(argc == 2){
        std::ofstream out(argv[1], std::ios::binary);
        std::vector<long> scrarr(iw * ih, WHITE);
        std::string header = "P6\n" + std::to_string(iw) + "\n" + std::to_string(ih) + "\n255\n";
        out.write(header.c_str(), header.size());
        clock_t t = clock();
        std::vector<float> zbuf(iw * ih, 1e100);
        //do your things here
        std::vector<vec3> parr(3);
        std::vector<long> colarr = {RED, GREEN, BLUE, BLACK};
        for(int i=0;i<100;i++) {
            parr[0] = vec3(rand() % 400 - 200, rand() % 400 - 200, rand() % 400 - 200) + vec3(200, 200, 0);
            parr[1] = vec3(rand() % 400 - 200, rand() % 400 - 200, rand() % 400 - 200) + vec3(200, 200, 0);
            parr[2] = vec3(rand() % 400 - 200, rand() % 400 - 200, rand() % 400 - 200) + vec3(200, 200, 0);
            draw_tri_zbuf(parr, iw, ih, scrarr, zbuf, 0x010101 * (i * 255/ 100));
        }
        t = clock() - t;
        std::cerr << "done with writing to arr!\n";
        std::cerr << "took " << t << "ticks, or " << (float)t / 1000 << "seconds\n";
        std::vector<char> carr(3 * iw * ih, 0);
        for (int i=0;i<iw*ih;i++) {
            long cell = scrarr[i];
            carr[i * 3] = ((cell & RED) >> 16);
            carr[i * 3 + 1] = ((cell & GREEN) >> 8);
            carr[i * 3 + 2] = (cell & BLUE);
        }
        out.write(carr.data(), carr.size());
        std::cerr << "done writing to file!";
    }
    else {
        std::cerr << "submit the filename after!";
    }
    return 0;
}