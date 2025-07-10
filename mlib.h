#ifndef MLIB_H_
#define MLIB_H_
#include <vector>
struct vec2 {
    float x, y, len;
    vec2(const float a=0, const float b=0);
    vec2 operator+(const vec2 &a) const;
    vec2 operator-(const vec2 &a) const; 
    vec2 operator*(const float a) const;
    vec2 operator/(const float a) const;
    vec2 norm() const;
    vec2 rot(const float a) const;
    float dot(const vec2 &a) const;
    vec2 projonto(const vec2 &a) const;
    void desc();
};
struct vec3 {
    float x, y, z, len;
    vec3(float a=0, float b=0, float c=0);
    vec3 operator+(const vec3 &a) const;
    vec3 operator-(const vec3 &a) const;
    vec3 operator*(const float a) const;
    vec3 operator/(const float a) const;
    vec3 norm() const;
    float dot(const vec3 &a) const;
    vec3 projonto(const vec3 &a) const;
    vec2 camproj() const;
    void desc();
};
struct matr3 {
    float a00, a01, a02, a10, a11, a12, a20, a21, a22, det, trace;
    matr3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
    matr3 operator+(const matr3 &a) const;
    matr3 operator-(const matr3 &a) const;
    matr3 operator*(const float a) const;
    matr3 operator/(const float a) const;
    vec3 transform(const vec3 &a) const;
    matr3 matmul(const matr3 &a) const;
    matr3 transp() const;
    matr3 inver() const;
    void desc();
};
long colorlerp(long a, long b, float t);
void setpix(vec2 t, int bw, int bh, std::vector<long> *board, long val);
void draw_line(vec2 orig, vec2 endp, int bw, int bh, std::vector<long> &image, long color);
void draw_multi_tri(std::vector<vec2> cpa, int bw, int bh, std::vector<long> *bptr, long color);
void draw_tri(std::vector<vec2> cpa, int bw, int bh, std::vector<long> &image, long color);
void draw_rect(vec2 toplef, vec2 botrig, int bw, int bh, std::vector<long> *bptr, long color);
void draw_conv(std::vector<vec2> *cpa, int bw, int bh, std::vector<long> *bptr, long color);
void draw_circle(vec2 centre, float r, int bw, int bh, std::vector<long> *bptr, long color);
long floattocol(float r, float g, float b);
float sidecheck(vec2 test, vec2 orig, vec2 end);
float areacalc(std::vector<vec2> *cpa);
matr3 eul2mat(float xrot, float yrot, float zrot);
std::vector<double> msort(std::vector<double> arr);
void draw_conv_zbuf(std::vector<vec3> *cpa, vec3 campos, int bw, int bh, std::vector<long> *bptr, std::vector<float> zbuf, long color);
#endif