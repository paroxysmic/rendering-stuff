#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include "imageio.h"
#include "matrlib.h"
#include "objhandling.h"
#include "drawlib.h"
#define TICKSPERSEC 1e-6
const int iw = 500;
const int ih = 500;
const int frames = 240;
int main(int argc, char **argv) {
    if(argc == 3){
        std::string outputFileName(argv[1]);
        std::string inputFileName(argv[2]);
        clock_t t;
        t = clock();
        std::cout << "starting parsing the obj file!\n";
        obj_3d OBJ = parse_OBJ(inputFileName);
        double parsetime = clock() - t;
        t = clock();
        std::cout << "done parsing the obj file, took " << parsetime * TICKSPERSEC << " seconds!\n";
        normalize_OBJ(OBJ);
        vec3 sceneligvec{1, 1, 1};
        Canvas canvas(iw, ih);
        std::cout << "starting image creation!\n";
        for(int frame=0;frame<frames;frame++) {
            canvas.clear();
            canvas.fill_im(BLACK);
            std::string frameName = outputFileName + std::to_string(frame) + ".ppm"; 
            float rotval = TAU * frame / frames;
            matr3 rotmat = eul2mat(rotval, TAU / 2, 0);
            for(std::array<int, 9> face: OBJ.facearr) {
                std::array<vec3, 3> parr;
                for(int j=0;j<3;j++) {
                    parr.at(j) = ((rotmat * (OBJ.vposarr.at(face.at(j * 3)))) * 400 + vec3{iw / 2, ih / 2, 0});
                }
                vec3 ligvec = cross((parr[0] - parr[2]), (parr[1] - parr[2]));
                float ligval = (ligvec.norm() * sceneligvec.norm());
                float spec = 0.1; 
                float diff = (ligval + 1) * 0.4;
                float ambi = std::pow(std::max(0.0f, ligval), 32) * 0.5;
                draw_tri_zbuf(parr, canvas, collerp(BLACK, WHITE, spec + diff + ambi));
            }
            writeImageToPPM(frameName, canvas);
        }
        double drawtime = clock() - t;
        t = clock();
        std::cout << "done with image creation, took " << drawtime * TICKSPERSEC << " seconds!\n";
        std::cout << "starting video conversion!\n";
        std::string buf = "ffmpeg -hide_banner -loglevel error -f image2 -framerate 60 -i \"" + 
                outputFileName + "%d.ppm\" vids/" + outputFileName + ".mp4";
        if(system(buf.c_str()) != 0) {
            std::cout << "conversion failed! aborting now\n";
        }
        double convtime = clock() - t;
        t = clock();
        std::cout << "done with video conversion, took " << convtime * TICKSPERSEC << "seconds!\n";
        std::cout << "starting cleanup!\n";
        if(system("rm *.ppm") != 0) {
            std::cout << "cleanup failed! aborting now\n";
        }
        double cleantime = clock() - t;
        std::cout << "done cleaning up took " << cleantime * 1e-6 << "seconds!\n";
    }
    else {
        std::cout << "arguments go output file name, input file name\n";
        std::cout << "ex: ./rast testFile object.obj\n";
    }
    return 0;
} 