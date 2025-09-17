#ifndef _OBJHANDLING_H
#define _OBJHANDLING_H
#include <string>
#include <vector>
#include "matrlib.h"
std::vector<std::string> scuffed_split(std::string string, std::string delimiter);
void norm_vec_arr(std::vector<vec3> &varr);
#endif