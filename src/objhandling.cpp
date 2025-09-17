#include "objhandling.h"
std::vector<std::string> scuffed_split(std::string string, std::string delimiter){
    size_t found = string.find(delimiter);
    std::vector<size_t> split_points;
    std::vector<std::string> chunks;
    while(found != std::string::npos) {
        split_points.push_back(found);
        found = string.find(delimiter, found+1);
    }
    for(int i=0;i<=split_points.size();i++) {
        int start = i == 0 ? 0 : split_points[i - 1] + 1;
        int end = i == split_points.size() - 1 ? string.size() : split_points[i];
        //not including the end, so we can drop the -1 in the size calc
        chunks.push_back(string.substr(start, end - start)); 
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
    avgvec = avgvec / (float)vs;
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
        varr.at(i) = varr.at(i) * 2 / maxdim;
    }
}