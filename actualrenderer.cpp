#define _USE_MATH_DEFINES
#define NOMINMAX
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <format>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include "mlib.h"
const int iw = 400;
const int ih = 400;
const int frames = 60;
int main(int argc, char **argv) {
    if(argc == 2){
        std::ifstream pumpkin("pumpkin.obj");
        std::vector<vec3> vposarr;
        std::vector<int> triindarr;
        std::string line;
        while(std::getline(pumpkin, line)) {
            if(line[0] == 'v') {
                std::stringstream ss (line.substr(2));
                float pos[3];
                int ind = 0;
                std::string coord;
                while(std::getline(ss, coord, ' ')) {
                    pos[ind++] = std::atof(coord.c_str());
                }
                vposarr.push_back(vec3(pos[0], pos[1], pos[2]));
            }
            if(line[0] == 'f') {
                std::stringstream ss (line.substr(2));
                int pos[3];
                int ind = 0;
                std::string coord;
                while(std::getline(ss, coord, ' ')) {
                    triindarr.push_back(std::atoi(coord.c_str()));
                    ind++;
                }
            }
        }
        vec3 minvec, maxvec, avgvec;
        minvec.x = 1000;
        minvec.y = 1000;
        minvec.z = 1000;
        maxvec.x = -1000;
        maxvec.y = -1000;
        maxvec.z = -1000;
        for (int i=0;i<vposarr.size();i++) {
            avgvec = avgvec + vposarr.at(i);
        }
        avgvec = avgvec / (float)vposarr.size();
        for (int i=0;i<vposarr.size();i++) {
            vposarr.at(i) = vposarr.at(i) - avgvec;
        }
        for (int i=0;i<vposarr.size();i++) {
            vec3 tvec = vposarr.at(i);
            minvec.x = std::min(minvec.x, tvec.x);
            minvec.y = std::min(minvec.y, tvec.y);
            minvec.z = std::min(minvec.z, tvec.z);
            maxvec.x = std::max(maxvec.x, tvec.x);
            maxvec.y = std::max(maxvec.y, tvec.y);
            maxvec.z = std::max(maxvec.z, tvec.z);
        }
        avgvec = avgvec / (float)vposarr.size();
        float maxdim = std::max(abs(minvec.x - maxvec.x), std::max(abs(minvec.y - maxvec.y), abs(minvec.z - maxvec.z)));
        for (int i=0;i<vposarr.size();i++) {
            vposarr.at(i) = vposarr.at(i) * 2 / maxdim;
        }
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
            matr3 rotmat = eul2mat(0, 2 * M_PI * frame / frames, 0);
            for(int i=0;i<triindarr.size();i+=3) {
                std::vector<vec2> parr = {(rotmat.transform(vposarr.at(triindarr.at(i) - 1))).camproj(), 
                                (rotmat.transform(vposarr.at(triindarr.at(i + 1) - 1))).camproj(), 
                                (rotmat.transform(vposarr.at(triindarr.at(i + 2) - 1))).camproj()};
                draw_tri(parr, iw, ih, scrarr, 0x010101 * (255 * i / triindarr.size()));
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
        }
        char buf[20];
        std::cout << "done with image creation, starting gif conversion\n";
        sprintf(buf, "magick -delay 1.66 -loop 0 %s*.ppm %s.gif", argv[1], argv[1]);
        system(buf);
        std::cout << "done with gif conversion, starting cleanup\n";
        for(int frame=0;frame<frames;frame++) {
            sprintf(buf, "del %s%04d.ppm", argv[1], frame);
            system(buf);
        }
        std::cout << "done cleaning up\n";
    }
    else {
        std::cerr << "submit the filename after!";
    }
    return 0;
}