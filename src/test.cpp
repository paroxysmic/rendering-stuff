#include <iostream>
#include "drawlib.h"
#include "imageio.h"
#include "objhandling.h"
int main() {
    Image image(1024, 1024);
    std::cout << image.m_ih << image.m_iw << '\n';
    obj_3d OBJ = parse_OBJ("d3p/d3p.obj");
    int ctr = 0;
    auto issue = OBJ.facearr.at(96);
    for(int i=0;i<9;i++) {
        std::cout << issue.at(i) << ' ';
        if(i % 3 == 0) {
            OBJ.vtexarr.at(issue.at(i + 1)).desc();
        }
    }
    std::cout << '\n';
    for(std::array<int, 9> arr: OBJ.facearr) {
        std::cout << ctr++ << '\n';
        std::array<vec2, 3> poi;
        for(int i=0;i<3;i++) {
            poi.at(i) = OBJ.vtexarr.at(arr.at(3 * i + 1));
            poi.at(i).x = std::ceil(poi.at(i).x * 1024);
            poi.at(i).y = std::ceil(poi.at(i).y * 1024);
        }
        draw_line(poi.at(0), poi.at(1), BLACK, image);
        draw_line(poi.at(1), poi.at(2), BLACK, image);
        draw_line(poi.at(2), poi.at(0), BLACK, image);        
    }
    writeImageToPPM("test.ppm", image);
    return 0;
}