#include <iostream>
#include <imageio.h>
int main() {
    Image image = readImageFromPPM("diablo3_pose/d3p_diffuse.ppm");
    return 0;
}