#include "imageio.h"
Image::Image(const int ih, const int iw) : m_ih(ih), m_iw(iw) {
    m_image.resize(m_ih * m_iw, WHITE);
}
void Image::fill_im(long color) {
    m_image.clear();
    m_image.resize(m_ih * m_iw, color);
}
Canvas::Canvas(const int ih, const int iw) : Image(ih, iw){
    m_zbuf.resize(m_ih * m_iw, 1e10);
}
void Canvas::clear() {
    m_image.clear();
    m_zbuf.clear();
    m_image.resize(m_iw * m_ih, WHITE);
    m_zbuf.resize(m_iw * m_ih, 1e10);
}
Image readImageFromPPM(std::string filename){
    std::ifstream in(filename);
    
    const int ih = 10;
    const int iw = 10;
    Image image(ih, iw);
    return image;
}
void writeCanvasToPPM(std::string filename, Canvas canvas) {
    std::ofstream out(filename, std::ios::binary);
    int cw = canvas.m_iw;
    int ch = canvas.m_ih;
    std::string header = "P6\n" + std::to_string(cw) + "\n" + std::to_string(ch) + "%d\n255\n";
    out.write(header.c_str(), header.size());
    std::vector<char> carr;
    carr.resize(cw * ch * 3, (char)0xff);
    for (int i = 0; i < cw * ch; i++) {
            long cell = canvas.m_image[i];
            int ind = i * 3;
            carr[ind] = (cell & 0xff0000) >> 16;
            carr[ind + 1] = (cell & 0x00ff00) >> 8;
            carr[ind + 2] = cell & 0x0000ff;
    }
    out.write(carr.data(), cw * ch * 3);
    out.close();
}
