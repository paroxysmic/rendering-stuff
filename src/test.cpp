#include <iostream>
#include "matrlib.h"
#include "objhandling.h"
int main() {
    obj_3d OBJ = parse_OBJ("lpb/fixed.obj");
    for(std::array<int, 9> arr: OBJ.facearr) {
        for(int i=0;i<9;i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}