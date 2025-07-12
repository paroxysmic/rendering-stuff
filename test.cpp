#include "matrlib.h"
#include "drawlib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main(){
    for(int i=0;i<1e7;i++) {
        vec2 A = vec2(rand() / (float) RAND_MAX, rand() / (float) RAND_MAX);
        vec2 B = vec2(rand() / (float) RAND_MAX, rand() / (float) RAND_MAX);
        vec2 C = vec2(rand() / (float) RAND_MAX, rand() / (float) RAND_MAX);
        vec2 tvec = vec2(rand() / (float) RAND_MAX, rand() / (float) RAND_MAX);
        vec3 bary = barycoords(A, B, C, tvec);
    }
    return 0;
} 