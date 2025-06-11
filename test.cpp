#include "mlib.h"
#include <iostream>
#include <fstream>
#include <string>
int main(){
    vec2 v0 = vec2(2, 0);
    vec2 v1 = vec2(1, 1);
    vec2 v2 = v1.projonto(v0);
    v2.desc();
    v0.x = 0;
    v0.desc();
    return 0;
} 