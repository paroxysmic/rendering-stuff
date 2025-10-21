#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include "matrlib.h"
#include "objhandling.h"
#include "drawlib.h"
const int iw = 1000;
const int ih = 1000;
const int frames = 60;
int main(int argc, char **argv) {
    if(argc == 3){
        std::string outputFileName(argv[1]);
        std::string inputFileName(argv[2]);
        std::ifstream obj(inputFileName);
        std::vector<vec3> vposarr;
        std::vector<std::vector<int>> faceindarr;
        std::string line;
        std::string filenamebuf;
        while(std::getline(obj, line)) {
            std::vector<std::string> linechunks = scuffed_split(line, " ");
            if(linechunks[0] == "v") {
                float x = std::stof(linechunks[1]);
                float y = std::stof(linechunks[2]);
                float z = std::stof(linechunks[3]);
                vposarr.push_back(vec3(x, y, z));
            }
            if(linechunks[0] == "f") {
                std::vector<int> face;
                for(int i=0;i<linechunks.size() - 1;i++) {
                    std::string chunk = linechunks[i + 1];
                    std::vector<std::string> faceindvert = scuffed_split(chunk, "/");
                    face.push_back(std::stoi(faceindvert[0]));
                }
                faceindarr.push_back(face);
            }
        }
        norm_vec_arr(vposarr);
        vec3 sceneligvec{1, 1, 1};
        clock_t t;
        t = clock();
        for(int frame=0;frame<frames;frame++) { 
            std::vector<float> zbuf(iw * ih, INFINITY);
            std::string num = std::to_string(frame);;
            std::ofstream out(outputFileName + num + ".ppm", std::ios::binary);
            std::vector<long> scrarr(iw * ih, 0xffffff);
            char header[30];
            sprintf(header, "P6\n%d\n%d\n255\n", iw, ih);
            out.write(header, strlen(header));
            //do stuff here!
            clock_t t;
            float rotval = TAU * frame / frames;
            matr3 rotmat = eul2mat(rotval, rotval, rotval);
            for(int i=0;i<faceindarr.size();i++) {
                std::array<vec3, 3> parr;
                for(int j=0;j<3;j++) {
                    parr.at(j) = (rotmat.transform(vposarr.at(faceindarr.at(i).at(j) - 1)) * 400 + vec3(iw / 2, ih / 2, 0));
                }
                vec3 ligvec = cross((parr[0] - parr[2]), (parr[1] - parr[2])).norm();
                long col = colorlerp(0xFF00FF, 0x0000FF, (dot(ligvec, sceneligvec.norm()) + 1) / 2);
                draw_tri_zbuf(parr, iw, ih, scrarr, zbuf, col);
            }
            std::vector<char> carr(iw * ih * 3);
            for (int y = 0; y < ih; y++) {
                for (int x = 0; x < iw; x++) {
                    long cell = scrarr[x + y * iw];
                    int ind = (x + y * iw) * 3;
                    carr[ind] = (cell & 0xff0000) >> 16;
                    carr[ind + 1] = (cell & 0x00ff00) >> 8;
                    carr[ind + 2] = cell & 0x0000ff;
                }
            }
            out.write(carr.data(), iw * ih * 3);
        }
        double drawtime = clock() - t;
        t = clock();
        std::string buf;
        std::cout << "done with image creation, starting video conversion (took " << drawtime * 1e-3 << " seconds!)\n";
        buf = "ffmpeg -hide_banner -loglevel error -f image2 -framerate 30 -i \"" + outputFileName + "%d.ppm\" " + outputFileName + ".mp4";
        system(buf.c_str());
        double convtime = clock() - t;
        t = clock();
        std::cout << "done with video conversion, starting cleanup (took " << convtime * 1e-3 << "seconds!)\n";
        system("del *.ppm");
        double cleantime = clock() - t;
        std::cout << "done cleaning up (took " << cleantime * 1e-3 << "seconds!)\n";
    }
    else {
        std::cout << "arguments go output file name, input file name\n";
        std::cout << "ex: ./rast testFile object.obj";
    }
    return 0;
} 