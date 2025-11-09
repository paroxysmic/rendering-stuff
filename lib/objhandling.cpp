#include "objhandling.h"
std::vector<std::string> scuffed_split(std::string s, std::string delim) {
    std::vector<std::string> chunks;
    if (delim.empty()) return chunks;
    size_t pos = 0;
    while ((pos = s.find(delim)) != std::string::npos) {
        chunks.push_back(s.substr(0, pos));
        s.erase(0, pos + delim.length());
    }
    chunks.push_back(s);
    return chunks;
}

obj_3d parse_OBJ(std::string objpath){
    std::string line;
    std::fstream objfile(objpath);
    obj_3d obj;
    obj.faceformat = NONE;
    obj.gonebad = false;
    int lineind = 0;
    while(std::getline(objfile, line) && !obj.gonebad){
        std::vector<std::string> linechunks = scuffed_split(line, " ");
        int chunknum = linechunks.size();
        if(linechunks[0] == "v"){
            if(chunknum == 4 || chunknum == 5){
                float x = std::stof(linechunks[1]);
                float y = std::stof(linechunks[2]);
                float z = std::stof(linechunks[3]);
                if(chunknum == 5) {
                    float w = std::stof(linechunks[4]);
                    x /= w;
                    y /= w;
                    z /= w;
                }
                obj.vposarr.push_back(vec3{x, y, z});
            }
            else {obj.gonebad = true;}
        }
        if(linechunks[0] == "vt"){
            if(chunknum == 3 || chunknum == 4) {
                float u = std::stof(linechunks[1]);
                float v = std::stof(linechunks[2]);
                if(chunknum == 4) {
                    float w = std::stof(linechunks[3]);
                    u /= w;
                    v /= w;
                }
                obj.vtexarr.push_back(vec2{u, v});
            }
            else {obj.gonebad = true;}
        }
        if(linechunks[0] == "vn"){
            if(chunknum == 4) {
                float x = std::stof(linechunks[1]);
                float y = std::stof(linechunks[2]);
                float z = std::stof(linechunks[3]);
                obj.vnormarr.push_back((vec3{x, y, z}.norm()));
            }
            else {obj.gonebad = true;}
        }
        if(linechunks[0] == "f"){
            std::array<int, 9> face;
            face.fill(0);
            if(obj.faceformat == NONE){
                std::vector<std::string> chunk1 = scuffed_split(linechunks[1], "/");
                switch(chunk1.size()){
                    case 1:
                        obj.faceformat = PLAIN;
                        break;
                    case 2:
                        obj.faceformat = TEXTURE;
                        break;
                    case 3:
                        if(chunk1.at(1) == "") {obj.faceformat = NORMAL;}
                        else {obj.faceformat = BOTH;}
                        break;
                    default:
                        obj.gonebad = true;
                        break;
                }
            }
            std::vector<std::string> chunknums;
            for(int i=0;i<3;i++) {
                switch(obj.faceformat) {
                    case PLAIN:
                        face.at(i * 3) = std::stoi(linechunks.at(i + 1)) - 1;
                        break;
                    case TEXTURE:
                        chunknums = scuffed_split(linechunks.at(i + 1), "/");
                        face.at(i * 3) = std::stoi(chunknums.at(0)) - 1;
                        face.at(i * 3 + 1) = std::stoi(chunknums.at(1)) - 1;
                        break;
                    case NORMAL:
                        chunknums = scuffed_split(linechunks.at(i + 1), "//");
                        face.at(i * 3) = std::stoi(chunknums.at(0)) - 1;
                        face.at(i * 3 + 2) = std::stoi(chunknums.at(1)) - 1;
                        break;
                    case BOTH:
                        chunknums = scuffed_split(linechunks.at(i + 1), "/");
                        for(int j=0;j<3;j++) {
                            face.at(i * 3 + j) = std::stoi(chunknums.at(j)) - 1;   
                        }
                        break;
                }
            }
            obj.facearr.push_back(face);
        }   
        lineind++;
    }
    if(obj.gonebad) {
        std::cerr << "FILE FORMATTED BADLY\nFILENAME: " + objpath 
        + "\nAT LINE " << lineind << "\nFORMAT: " << obj.faceformat; 
    }
    if(!objfile.is_open()) {
        std::cerr << "this file does not exist!\n";
    }
    return obj;
}
void normalize_OBJ(obj_3d &obj) {
    vec3 avg{0, 0, 0};
    vec3 minvec{INFINITY, INFINITY, INFINITY};
    vec3 maxvec{-INFINITY, -INFINITY, -INFINITY};
    for(vec3 vec: obj.vposarr) { 
        avg = avg + vec; 
        minvec.x = std::min(vec.x, minvec.x);
        minvec.y = std::min(vec.y, minvec.y);
        minvec.z = std::min(vec.z, minvec.z);
        maxvec.x = std::max(vec.x, maxvec.x);
        maxvec.y = std::max(vec.y, maxvec.y);
        maxvec.z = std::max(vec.z, maxvec.z);        
    }
    vec3 size = maxvec - minvec;
    float maxdim = std::max({size.x, size.y, size.z});
    avg = avg * (1.0 / obj.vposarr.size());
    for(vec3 &vec: obj.vposarr) { vec = (vec - avg) * (1 / maxdim); }
}
