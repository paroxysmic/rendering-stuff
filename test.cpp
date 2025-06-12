#include "mlib.h"
#include <iostream>
#include <fstream>
#include <string>
int main(){
    matr3 A = matr3(1, 2, 3, 4, 5, 6, 7, 8, 9);
    vec3 x = vec3(0, 1, 2);
    A.desc();
    x.desc();
    A.transform(x).desc();
    return 0;
} 