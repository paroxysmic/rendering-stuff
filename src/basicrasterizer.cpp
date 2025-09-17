#define _USE_MATH_DEFINES
#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include "matrlib.h"
#include "drawlib.h"
const int iw = 200;
const int ih = 200;
const int frames = 60;
int main(int argc, char **argv) {
    if(argc == 4){
        std::string outputFileName(argv[1]);
        std::string inputFileName(argv[2]);
        std::string outputFileExtension(argv[3]);
        std::ifstream obj(inputFileName);
        std::vector<vec3> vposarr;
        std::vector<int> triindarr;
        std::string line;
        std::string filenamebuf;
        while(std::getline(obj, line)) {
            if(line[0] == 'v' && line[1] == ' ') {
                
            }
        }
        norm_vec_arr(vposarr);
        vec3 sceneligvec{1, 1, 1};
        clock_t t;
        t = clock();
        for(int frame=0;frame<frames;frame++) { 
            std::vector<float> zbuf(iw * ih, INFINITY);
            std::string num = std::to_string(frame);
            num.insert(num.begin(), 4 - num.length(), '0');
            std::ofstream out(outputFileName + num + ".ppm", std::ios::binary);
            filenamebuf += outputFileName + num + ".ppm ";
            std::vector<long> scrarr(iw * ih, 0xffffff);
            char header[30];
            sprintf(header, "P6\n%d\n%d\n255\n", iw, ih);
            out.write(header, strlen(header));
            //do stuff here!
            clock_t t;
            matr3 rotmat = eul2mat(TAU / 2, TAU * frame / frames, TAU * frame / frames);
            for(int i=0;i<triindarr.size();i+=3) {
                std::vector<vec3> parr = {rotmat.transform(vposarr.at(triindarr[i] - 1)) * 45 + vec3(50, 50, 0), 
                                          rotmat.transform(vposarr.at(triindarr[i + 1] - 1)) * 45 + vec3(50, 50, 0), 
                                          rotmat.transform(vposarr.at(triindarr[i + 2] - 1)) * 45 + vec3(50, 50, 0)};
                vec3 ligvec = (parr[0] - parr[2]).cross(parr[1] - parr[2]).norm(); 
                //finding cross product gives us the normal ofthe polygon without having to compute vertex normals
                //then after finding the normal, we can then dot it with a constant lighting vector
                //giving us the relative "alignment" of the two as a dihedral angle 
                //bcz we normed the vectors in a previous step, this will simply return the cosine of the dihedral angle
                //which ranges from -1 to 1, which we then normalize to 0 to 1, giving us the lighting
                long col = colorlerp(0xff00ff, 0x0000ff, (ligvec.dot(sceneligvec.norm()) + 1) / 2);
                draw_tri_zbuf(parr, iw, ih, scrarr, zbuf, col);
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
            out.write(carr.data(), carr.size());
        }
        double drawtime = clock() - t;
        t = clock();
        std::string buf;
        std::cout << "done with image creation, starting video conversion (took " << drawtime * 1e-3 << " seconds!)\n";
        buf = "magick -delay 4 -loop 0 " + outputFileName + "*.ppm " + outputFileName + outputFileExtension;
        system(buf.c_str());
        double convtime = clock() - t;
        t = clock();
        std::cout << "done with video conversion, starting cleanup (took " << convtime * 1e-3 << "seconds!)\n";
        system(("rm " + filenamebuf).c_str());
        double cleantime = clock() - t;
        std::cout << "done cleaning up (took " << cleantime * 1e-3 << "seconds!)\n";
    }
    else {
        std::cerr << "arguments go output file name, input file name, and then output file extension\n";
        std::cerr << "ex: ./rast testFile object.obj .gif";
    }
    return 0;
}