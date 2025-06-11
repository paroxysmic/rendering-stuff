#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <time.h>
#include "mlib.h"
const int iw = 400;
const int ih = 400;
int main(int argc, char **argv) {
    if(argc == 2){
        std::ofstream out(argv[1], std::ios::binary);
        std::vector<long> scrarr;
        for(int i=0;i<iw*ih;i++){
            scrarr.push_back(0x00ff00);
        }
        std::string header = "P6\n" + std::to_string(iw) + "\n" + std::to_string(ih) + "\n255\n";
        out.write(header.c_str(), header.size());
        clock_t t = clock();
        float sx, sy, fx, fy;
        long col = 0x000000;
        for(int i=0;i<1e6;i++){
            sx = rand() % 400;
            sy = rand() % 400;
            fx = rand() % 400;
            fy = rand() % 400;
            col = ((rand() & 0xff) << 16) + ((rand() & 0xff) << 8) + (rand() & 0xff);
            draw_line(sx, sy, fx, fy,iw, ih, &scrarr, col);
        }
        t = clock() - t;
        std::cerr << "done with writing to arr!\n";
        std::cerr << "took " << t << "ticks, or " << (float)t / 1000 << "seconds\n";
        std::vector<char> carr;
        for (int y = 0; y < ih; y++) {
            for (int x = 0; x < iw; x++) {
                long cell = scrarr[x + y * iw];
                carr.push_back((cell & 0xff0000) >> 16);
                carr.push_back((cell & 0x00ff00) >> 8);
                carr.push_back(cell & 0x0000ff);
            }
        }
        out.write(carr.data(), carr.size());
        std::cerr << "done writing to file!";
    }
    else {
        std::cerr << "submit the filename after!";
    }
    return 0;
}