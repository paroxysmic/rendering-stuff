#ifndef MATRLIB_H
#define MATRLIB_H
#include <array>
#include <cstdint>
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
    vec2 xy;
    vec3(float a=0, float b=0, float c=0);
    vec3 operator+(const vec3 &a) const;
    vec3 operator-(const vec3 &a) const;
    vec3 operator*(const float a) const;
    vec3 operator/(const float a) const;
    vec3 norm() const;
    vec3 cross(const vec3 &a) const;
    float dot(const vec3 &a) const;
    vec3 projonto(const vec3 &a) const;
    vec2 camproj() const;
    void desc();
};
struct matr3 {
    float data[9];
    float det;
    matr3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
    matr3(float arr[9]);
    matr3();
    matr3 operator+(const matr3 &a) const;
    matr3 operator-(const matr3 &a) const;
    matr3 operator*(const float &a) const;
    matr3 operator/(const float &a) const;
    vec3 transform(const vec3 &a) const;
    matr3 matmul(const matr3 &a) const;
    matr3 transp() const;
    matr3 inver() const;
    void desc();
};
template <typename T, uint16_t rownum, uint16_t colnum>
class Matrix {
    private: 
    std::array<T, colnum * rownum> data;
    public:
        uint16_t getCols() { return colnum; }
        uint16_t getRows() { return rownum; }
        //stands for get element at, does what it says on the tin
        T gea(uint16_t row, uint16_t col) { return data.at(col + row * colnum); }
        //stands for set element at, does what it says on the tin
        void sea(uint16_t row, uint16_t col, T val) { data.at(col + row * colnum) = val; }
        Matrix operator+ (const Matrix& other) {
            if((other.getCols() != colnum) || (other.getRows() != rows)) {
                throw std::invalid_argument("columns and rows must be equal!");
            }
            Matrix res;
            for(int i=0;i<rows;i++) {
                for(int j=0;j<cols;j++) {
                    sea(j, i, gea(j, i) + other.gea(j, i));
                }
            }
            return res;
        }
        Matrix operator- (const Matrix& other) {
            if((other.getCols() != colnum) || (other.getRows() != rows)) {
                throw std::invalid_argument("columns and rows must be equal!");
            }
            Matrix res;
            for(int i=0;i<rows;i++) {
                for(int j=0;j<cols;j++) {
                    sea(j, i, gea(j, i) - other.gea(j, i));
                }
            }
            return res;
        }
        Matrix operator* (const Matrix& other) {
            if(getCols() != other.getRows()) {
                throw std::invalid_argument("m1's cols need to equal m2's rows!");
            }
            Matrix<T, rownum, other.getCols()> res;
            for(int i=0;i<other.getCols();i++) {
                for(int j=0;j<rownum;j++) {
                    T rt = 0;
                    for(int k=0;k<colnum;k++) {
                        rt += gea(i, k) * other.gea(k, j);
                    }
                    sea(i, j, rt);
                }
            }
        }
        //TODO: implement this 
        Matrix gaussianElim(const Matrix& mat) {
            //how to efficiently do elementary ops?
                  
        }
    };
#endif