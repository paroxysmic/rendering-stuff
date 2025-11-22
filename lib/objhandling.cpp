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
std::vector<std::string> split(std::string s, char delim) {
    std::vector<std::string> chunks;
    std::string chunk;
    std::stringstream ss(s);
    while(std::getline(ss, chunk, delim)) {
        chunks.push_back(chunk);
    }
    return chunks;
}

obj_3d parse_OBJ(std::string objpath) {
    std::string line;
    std::fstream inp(objpath);
    if(!inp.is_open()) {
        inp.close();
        std::cout << "file does not exist! aborting now\n";
        exit(-1);
    }
    obj_3d obj;
    std::stringstream ss;
    while(std::getline(inp, line)) {
        ss.clear();
        ss << line;
        std::string tag;
        ss >> tag;
        if(tag == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            obj.vposarr.push_back(vec3{x, y, z});
        }
        if(tag == "vn") {
            float x, y, z;
            ss >> x >> y >> z;
            obj.vnormarr.push_back(vec3{x, y, z});
        }
        if(tag == "vt") {
            float x, y;
            ss >> x >> y;
            obj.vtexarr.push_back(vec2{x, y});
        }
        if(tag == "f") {
            std::array<int, 9> face{};
            face.fill(-1);
            std::string taggedVert;
            for(int i=0;i<3;i++) {
                ss >> taggedVert;
                std::vector<std::string> chunks = split(taggedVert, '/');
                for(int j=0;j<chunks.size();j++) {
                    if(!chunks.at(j).empty()) {
                        face[j + i * 3] = std::stoi(chunks.at(j)) - 1;
                    }
                }
            }
            obj.facearr.push_back(face);
        }
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
