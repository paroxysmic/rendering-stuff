#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <array>
#include "matrlib.h"
enum FaceFormat{
    PLAIN,
    TEXTURE,
    NORMAL,
    BOTH,
    NONE
};
//all indices are 0-indexed bcz of the way i load the obj file
struct obj_3d{
    std::vector<vec3> vposarr;
    std::vector<vec3> vnormarr;
    std::vector<vec2> vtexarr;
    std::vector<std::array<int, 9>> facearr;
    FaceFormat faceformat;
    bool gonebad;
};
std::vector<std::string> scuffed_split(std::string string, std::string delimiter);
void norm_vec_arr(std::vector<vec3> &varr);
//NOT IMPLEMENTED YET
obj_3d parse_OBJ(std::string objpath);
//NOT IMPLEMENTED YET
obj_3d parse_STL(std::string objpath);