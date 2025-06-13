#ifndef MLIB_H_
#define MLIB_H_
#include <vector>
struct vec2 {
    double x, y, len;
    vec2(double a=0, double b=0);
    vec2 operator+(const vec2 &a) const;
    vec2 operator-(const vec2 &a) const; 
    vec2 operator*(const double a) const;
    vec2 operator/(const double a) const;
    vec2 norm() const;
    double dot(const vec2 &a) const;
    vec2 projonto(const vec2 &a) const;
    void desc();
};
struct vec3 {
    double x, y, z, len;
    vec3(double a=0, double b=0, double c=0);
    vec3 operator+(const vec3 &a) const;
    vec3 operator-(const vec3 &a) const;
    vec3 operator*(const double a) const;
    vec3 operator/(const double a) const;
    vec3 norm() const;
    double dot(const vec3 &a) const;
    vec3 projonto(const vec3 &a) const;
    vec2 camproj() const;
    void desc();
};
struct matr3 {
    double a00, a01, a02, a10, a11, a12, a20, a21, a22, det, trace;
    matr3(double a, double b, double c, double d, double e, double f, double g, double h, double i);
    matr3 operator+(const matr3 &a) const;
    matr3 operator-(const matr3 &a) const;
    matr3 operator*(const double a) const;
    matr3 operator/(const double a) const;
    vec3 transform(const vec3 &a) const;
    matr3 matmul(const matr3 &a) const;
    matr3 transp() const;
    matr3 inver() const;
    void desc();
};
// template <class T> struct Matrix {
//     int width, height;
//     std::array<std::array<T, width>, height> data;
//     double det, trace;
//     Matrix();
//     Matrix<T> operator+(const Matrix<T> &a) const;
//     Matrix<T> operator-(const Matrix <T>&a) const;
//     Matrix<T> operator*(const Matrix<T> &a) const;
//     Matrix<T> operator/(const Matrix<T> &a) const;
//     Matrix<T> operator[](int ind) const;
//     Matrix<T> matmul(const Matrix<T> &a) const;
//     Matrix<T> transp() const;
//     Matrix<T> inver() const;
//     void desc();    
// };
long colorlerp(long a, long b, double t);
void setpix(vec2 t, int bw, int bh, std::vector<long> *board, long val);
void draw_line(double ox, double oy, double ex, double ey, int bw, int bh, std::vector<long> *board, long color);
void draw_tri(std::vector<vec2> cpa, int bw, int bh, std::vector<long> *bptr, long color);
void draw_rect(vec2 toplef, vec2 botrig, int bw, int bh, std::vector<long> *bptr, long color);
void draw_conv(std::vector<vec2> *cpa, int bw, int bh, std::vector<long> *bptr, long color);
void draw_circle(vec2 centre, double r, int bw, int bh, std::vector<long> *bptr, long color);
long doubletocol(double r, double g, double b);
double sidecheck(vec2 test, vec2 orig, vec2 end);
double areacalc(std::vector<vec2> *cpa);
matr3 eul2mat(double xrot, double yrot, double zrot);
#endif