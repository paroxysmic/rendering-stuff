#pragma once
#define WHITE (long)0xffffff
#define RED (long)0xff0000
#define GREEN (long)0x00ff00
#define BLUE (long)0x0000ff
#define BLACK (long)0x000000
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
struct Image{
    const int m_iw, m_ih;
    std::vector<long> m_image;
    Image(const int iw, const int ih);
    void fill_im(long color);
};
struct Canvas : public Image{
    std::vector<float> m_zbuf;
    Canvas(const int iw, const int ih);
    void clear(); 
};
Image readImageFromPPM(std::string filename);
void writeCanvasToPPM(std::string filename, Canvas canvas);
