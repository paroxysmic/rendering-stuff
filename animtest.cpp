#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <time.h>
#include <cmath>
#include "mlib.h"
const int iw = 400;
const int ih = 400;
const int urange = 40;
const int vrange = 40;
#define M_PI 3.14159265358979323846
int main(int argc, char **argv) {
    if(argc == 2){
        std::vector<long> scrarr;
        matr3 combrot = eul2mat(0.14, 0.68, 0.42);
        std::vector<vec3> donarr;
        for(int uind=0;uind<urange;uind++){
            for(int vind=0;vind<vrange;vind++){
                double u = M_PI * 2 * uind / urange;
                double v = M_PI * 2 * vind / vrange;
                vec3 dvec = vec3(sin(v) * (sin(u) + 2), cos(v) * (sin(u) + 2), cos(u));
                donarr.push_back(dvec);
            }
        }
        std::string header = "P6\n" + std::to_string(iw) + "\n" + std::to_string(ih) + "\n255\n";
        for(int i = 0; i < 10; i++) {
            scrarr.clear();
            for(int i=0;i<iw*ih;i++){
                scrarr.push_back(0xffffff);
            }
            for(int j = 0; j < urange * vrange; j++) {
                donarr[j] = combrot.transform(donarr[j]);
            }
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
                }
            }
            std::vector<char> carr;
            for (int y = 0; y < ih; y++) {
                for (int x = 0; x < iw; x++) {
                    long cell = scrarr[x + y * iw];
                    carr.push_back((cell & 0xff0000) >> 16);
                    carr.push_back((cell & 0x00ff00) >> 8);
                    carr.push_back(cell & 0x0000ff);
                }
            } 
            std::ofstream out(argv[1] + std::string("-") + std::to_string(i) + std::string(".ppm"), std::ios::binary);
            out.write(header.c_str(), header.size());
            out.write(carr.data(), carr.size());
            std::cout << "done with frame " << i << '\n';
        }
        //system(std::string("ffmpeg -f image2 -i ") + std::string(argv[1]) + std::string("-%d.ppm ") + std::string(argv[1]) + std::string(".mp4"));
    }
    return 0;
}