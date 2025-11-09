#pragma once
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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
//this is bad, should be refactored/removed depending on the severity of this issue
std::vector<std::string> scuffed_split(std::string string, std::string delimiter);
obj_3d parse_OBJ(std::string objpath);
//NOT IMPLEMENTED YET
obj_3d parse_STL(std::string objpath);

void normalize_OBJ(obj_3d &obj);