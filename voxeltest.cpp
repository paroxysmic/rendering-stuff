#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <format>
#include <Windows.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "mlib.h"
const int iw = 400;
const int ih = 400;
const int frames = 120;
int main(int argc, char **argv) {
    if(argc == 2){
        for(int frame=0;frame<frames;frame++) {
            std::string num = std::to_string(frame);
            num.insert(num.begin(), 4 - num.length(), '0');
            std::ofstream out(argv[1] + num + ".ppm", std::ios::binary);
            std::vector<long> scrarr;
            for(int j=0;j<iw*ih;j++){
                scrarr.push_back(0xffffff);
            }
            std::string header = "P6\n" + std::to_string(iw) + "\n" + std::to_string(ih) + "\n255\n";
            out.write(header.c_str(), header.size());
            //do stuff here!
            matr3 rotmat = eul2mat(0, frame * 2 * M_PI / frames, 0);
            for (int i=0;i<5;i++) {
                for (int j=0;j<5;j++) {
                    for (int k=0;k<5;k++) {
                        vec3 pos = vec3(i-2, j-2, k-2);
                        pos = rotmat.transform(pos);
                        draw_circle(vec2(pos.x * 70 / (pos.z + 4) + 200, pos.y * 70 / (pos.z + 4) + 200), 4, iw, ih, &scrarr, 0x000000);
                    }
                }
            }
            //stop doing stuff!
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
            std::cout << "finished frame " << frame << '\n';
        }
        char buf[20];
        std::cout << "started gif conversion";
        sprintf(buf, "magick -delay 1.66 -loop 0 %s*.ppm %s.gif", argv[1], argv[1]);
        system(buf);
        std::cout << "done with gif conversion";
        for(int frame=0;frame<frames;frame++) {
            sprintf(buf, "del %s%04d.ppm", argv[1], frame);
            system(buf);
            std::cout << "deleted file " << frame << '\n'; 
        }
    }
    else {
        std::cerr << "submit the filename after!";
    }
    return 0;
}