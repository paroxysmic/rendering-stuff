#include "objhandling.h"
std::vector<std::string> scuffed_split(std::string string, std::string delimiter){
    size_t found = string.find(delimiter);
    std::vector<size_t> split_points;
    std::vector<std::string> chunks;
    if(delimiter == "") {
        return chunks;
    }
    while(found != std::string::npos) {
        split_points.push_back(found);
        found = string.find(delimiter, found+1);
    }
    if(split_points.size() == 0) {
        chunks.push_back(string);
        return chunks;
    }
    int start, end;
    for(int i=0;i<split_points.size();i++) {
        start = i == 0 ? 0 : split_points[i - 1] + delimiter.size();
        end = split_points[i];
        //not including the end, so we can drop the -1 in the size calc
        if(i != 0 || end != 0) {
            chunks.push_back(string.substr(start, end - start)); 
        }
    }
    if(string.size() - delimiter.size() != end) {
        chunks.push_back(string.substr(end + delimiter.size(), string.size()));
    }
    return chunks;
}
void norm_vec_arr(std::vector<vec3> &varr) {
    vec3 minvec, maxvec, avgvec;
    int vs = varr.size();
    minvec.x = 1000;
    minvec.y = 1000;
    minvec.z = 1000;
    maxvec.x = -1000;
    maxvec.y = -1000;
    maxvec.z = -1000;
    for (int i=0;i<vs;i++) {
        avgvec = avgvec + varr.at(i);
    }
    avgvec = avgvec * (1.0f / vs);
    for (int i=0;i<vs;i++) {
        varr.at(i) = varr.at(i) - avgvec;
    }
    for (int i=0;i<vs;i++) {
        vec3 tvec = varr.at(i);
        minvec.x = std::min(minvec.x, tvec.x);
        minvec.y = std::min(minvec.y, tvec.y);
        minvec.z = std::min(minvec.z, tvec.z);
        maxvec.x = std::max(maxvec.x, tvec.x);
        maxvec.y = std::max(maxvec.y, tvec.y);
        maxvec.z = std::max(maxvec.z, tvec.z);
    }
    float maxdim = std::max(abs(minvec.x - maxvec.x), std::max(abs(minvec.y - maxvec.y), abs(minvec.z - maxvec.z)));
    for (int i=0;i<vs;i++) {
        varr.at(i) = varr.at(i) * (2 / maxdim);
    }
}
obj_3d parse_OBJ(std::string objpath){
    std::string line;
    std::fstream objfile(objpath);
    obj_3d obj;
    obj.gonebad = false;
    int lineind = 0;
    while(std::getline(objfile, line)){
        std::vector<std::string> linechunks = scuffed_split(line, " ");
        int chunknum = linechunks.size();
        if(linechunks[0] == "v"){
            if(chunknum == 4 | chunknum == 5){
                float x = std::stof(linechunks[1]);
                float y = std::stof(linechunks[2]);
                float z = std::stof(linechunks[3]);
                if(chunknum == 5) {
                    float w = std::stof(linechunks[4]);
                    x /= w;
                    y /= w;
                    z /= w;
                }
                obj.vposarr.push_back(vec3(x, y, z));
            }
            else {obj.gonebad = true;}
        }
        if(linechunks[0] == "vt"){
            if(chunknum == 3 | chunknum == 4) {
                float u = std::stof(linechunks[1]);
                float v = std::stof(linechunks[2]);
                if(chunknum == 4) {
                    float w = std::stof(linechunks[3]);
                    u /= w;
                    v /= w;
                }
                obj.vtexarr.push_back(vec2(u, v));
            }
            else {obj.gonebad = true;}
        }
        if(linechunks[0] == "vn"){
            if(chunknum == 4) {
                float x = std::stof(linechunks[1]);
                float y = std::stof(linechunks[2]);
                float z = std::stof(linechunks[3]);
                obj.vnormarr.push_back(vec3(x, y, z).norm());
            }
            else {obj.gonebad = true;}
        }
        if(linechunks[0] == "f"){
            std::vector<std::string> chunk1 = scuffed_split(line, "/");
            std::array<int, 9> face;
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
            switch(obj.faceformat) {
                case PLAIN:
                    
                    break;
                case TEXTURE:
                    break;
                case NORMAL:
                    break;
                case BOTH:
                    break;
            }
            obj.facearr.push_back(face);
        }   
        if(obj.gonebad) {
            break;
        }
    }
    if(obj.gonebad) {
        std::cerr << "FILE FORMATTED BADLY\nFILENAME: " + objpath 
        + "\nAT LINE " + std::to_string(lineind); 
    }
    return obj;
}
