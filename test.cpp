#include "mlib.h"
#include <iostream>
#include <fstream>
#include <string>
std::ofstream out ("otpt.txt", std::ios::binary);
int main(){
    char carr[95];
    for(int i=32;i<127;i++){
        carr[i-32] = i;
    }
    out.write(carr, 95);
    return 0;
} 