#include "matrlib.h"

matr3 eul2mat(float xrot, float yrot, float zrot) {
    float sx, cx, sy, cy, sz, cz;
    sx = sin(xrot);
    cx = cos(xrot);
    sy = sin(yrot);
    cy = cos(yrot);
    sz = sin(zrot);
    cz = cos(zrot);
    matr3 xrotmat = matr3(1, 0, 0, 0, cx, -sx, 0, sx, cx); 
    matr3 yrotmat = matr3(cy, 0, sy, 0, 1, 0, -sy, 0, cy);
    matr3 zrotmat = matr3(cz, -sz, 0, sz, cz, 0, 0, 0, 1);
    return zrotmat.matmul(yrotmat.matmul(xrotmat));
}
void vec2::desc() const noexcept{
    std::cout << x << ' ' << y << '\n';
}
void vec3::desc() const noexcept{
    std::cout << x << ' ' << y << ' ' << z << '\n';
}
void matr3::desc() const noexcept{
    for(int i=0;i<3;i++) {
        std::cout << data[3 * i] << ' ' << data[3 * i + 1] << ' ' << data[3 * i + 2] << "\n";
    }
}