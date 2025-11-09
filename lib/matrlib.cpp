#include "matrlib.h"
matr3 eul2mat(float xrot, float yrot, float zrot) {
    float sx = sin(xrot);
    float cx = cos(xrot);
    float sy = sin(yrot);
    float cy = cos(yrot); 
    float sz = sin(zrot);
    float cz = cos(zrot);
    matr3 xrotmat{1, 0, 0, 0, cx, -sx, 0, sx, cx}; 
    matr3 yrotmat{cy, 0, sy, 0, 1, 0, -sy, 0, cy};
    matr3 zrotmat{cz, -sz, 0, sz, cz, 0, 0, 0, 1};
    return zrotmat * yrotmat * xrotmat;
}