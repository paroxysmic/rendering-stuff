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
#include "matrlib.h"
#include "drawlib.h"
const int iw = 400;
const int ih = 400;
const int frames = 60;
int main(int argc, char **argv) {
    if(argc == 4){
        std::ifstream obj(argv[2]);
        std::vector<vec3> vposarr;
        std::vector<int> triindarr;
        std::string line;
        while(std::getline(obj, line)) {
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
        norm_vec_arr(vposarr);
        vec3 sceneligvec{1, 1, 1};
        for(int frame=0;frame<frames;frame++) { 
            std::vector<float> zbuf(iw * ih, INFINITY);
            std::string num = std::to_string(frame);
            num.insert(num.begin(), 4 - num.length(), '0');
            std::ofstream out(argv[1] + num + ".ppm", std::ios::binary);
            std::vector<long> scrarr(iw * ih, 0xffffff);
            std::string header = "P6\n" + std::to_string(iw) + "\n" + std::to_string(ih) + "\n255\n";
            out.write(header.c_str(), header.size());
            //do stuff here!
            matr3 rotmat = eul2mat(0, TAU * frame / frames, 0);
            for(int i=0;i<triindarr.size();i+=3) {
                std::vector<vec3> parr = {rotmat.transform(vposarr.at(triindarr[i] - 1)) * 180 + vec3(200, 200, 0), 
                                          rotmat.transform(vposarr.at(triindarr[i + 1] - 1)) * 180 + vec3(200, 200, 0), 
                                          rotmat.transform(vposarr.at(triindarr[i + 2] - 1)) * 180 + vec3(200, 200, 0)};
                vec3 ligvec = (parr[0] - parr[2]).cross(parr[1] - parr[2]).norm(); 
                //finding cross product gives us the normal ofthe polygon without having to compute vertex normals
                //then after finding the normal, we can then dot it with a constant lighting vector
                //giving us the relative "alignment" of the two as a dihedral angle 
                //bcz we normed the vectors in a previous step, this will simply return the cosine of the dihedral angle
                //which ranges from -1 to 1, which we then normalize to 0 to 1, giving us the lighting
                long col = 0x010101 * (int)(255 * (ligvec.dot(sceneligvec.norm()) + 1) / 2);
                draw_tri_zbuf(parr, iw, ih, scrarr, zbuf, col);
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
        std::cout << "done with image creation, starting video conversion\n";
        sprintf(buf, "magick -delay 1.66 -loop 0 %s*.ppm %s%s", argv[1], argv[1], argv[3]);
        system(buf);
        std::cout << "done with video conversion, starting cleanup\n";
        for(int frame=0;frame<frames;frame++) {
            sprintf(buf, "del %s%04d.ppm", argv[1], frame);
            system(buf);
        }
        std::cout << "done cleaning up\n";
    }
    else {
        std::cerr << "arguments go output file name, input file name, and then output file extension\n";
        std::cerr << "ex: ./ar testFile object.obj .gif";
    }
    return 0;
}