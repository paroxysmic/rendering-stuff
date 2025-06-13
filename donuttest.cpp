#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <time.h>
#include "mlib.h"
#include <cmath>
#define _USE_MATH_DEFINES
const int iw = 400;
const int ih = 400;
const int urange = 20;
const int vrange = 20;
int main(int argc, char **argv) {
    if(argc == 2){
        std::ofstream out(argv[1], std::ios::binary);
        std::vector<long> scrarr;
        for(int i=0;i<iw*ih;i++){
            scrarr.push_back(0xffffff);
        }
        std::vector<vec3> donarr;
        matr3 combrot = eul2mat(0.7, 3.4, 2.1);
        for(int uind=0;uind<urange;uind++){
            for(int vind=0;vind<vrange;vind++){
                //[sin(v)(sin(u)+2), cos(v)(sin(u)+2), cos(u)]
                //hole is facing the z-axis
                double u = M_PI * 2 * uind / urange;
                double v = M_PI * 2 * vind / vrange;
                vec3 dvec = vec3(sin(v) * (sin(u) + 2), cos(v) * (sin(u) + 2), cos(u));
                donarr.push_back(combrot.transform(dvec));
            }
        }
        std::string header = "P6\n" + std::to_string(iw) + "\n" + std::to_string(ih) + "\n255\n";
        out.write(header.c_str(), header.size());
        clock_t t = clock();
        int su, sv;
        for(int u=0;u<urange;u++){
            for(int v=0;v<vrange;v++){
                su = (u + 1) % urange;
                sv = (v + 1) % vrange;
                //0.64 * y / (z + 3) is the projection formula
                vec2 v0 = donarr[u + v * urange].camproj() + vec2(iw/2, ih/2);
                vec2 v1 = donarr[su + v * urange].camproj() + vec2(iw/2, ih/2);
                vec2 v2 = donarr[su + sv * urange].camproj() + vec2(iw/2, ih/2);
                vec2 v3 = donarr[u + sv * urange].camproj() + vec2(iw/2, ih/2);
                std::vector<vec2> parr = {v0, v1, v2, v3};
                long col = ((int)(floor(255*u/urange)) << 16) + ((int)(floor(255*v/vrange)) << 8) + 0xff;
                draw_conv(&parr, iw, ih, &scrarr, col);
                std::cout << "finsihed tri " << u << ' ' << v << '\n';                
            }
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