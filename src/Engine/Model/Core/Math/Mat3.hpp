#pragma once
#include "Vec2f.hpp"
#include <cmath>
#include <array>

// Matrice 3x3 pour transformations 2D homogènes
class Mat3 {
private:
    std::array<std::array<float,3>,3> m;

public:
    // Constructeur : matrice identité par défaut
    Mat3() {
        m = {{{1,0,0},{0,1,0},{0,0,1}}};
    }

    // Accès aux éléments
    float* operator[](size_t i) { return m[i].data(); }
    const float* operator[](size_t i) const { return m[i].data(); }

    // Créer une matrice de translation
    static Mat3 translation(float tx, float ty) {
        Mat3 mat;
        mat[0][2] = tx;
        mat[1][2] = ty;
        return mat;
    }

    // Créer une matrice de rotation (angle en radians)
    static Mat3 rotation(float angle) {
        Mat3 mat;
        float c = cos(angle);
        float s = sin(angle);
        mat[0][0] = c;  mat[0][1] = -s;
        mat[1][0] = s;  mat[1][1] = c;
        return mat;
    }

    // Créer une matrice de scale
    static Mat3 scale(float sx, float sy) {
        Mat3 mat;
        mat[0][0] = sx;
        mat[1][1] = sy;
        return mat;
    }

    // Créer directement une matrice combinée : scale -> rotate -> translate
    static Mat3 compose(const Vec2f& position, float rotation, const Vec2f& scale) {
        float c = cos(rotation);
        float s = sin(rotation);

        Mat3 mat;
        mat[0][0] = scale.x * c;
        mat[0][1] = -scale.y * s;
        mat[0][2] = position.x;

        mat[1][0] = scale.x * s;
        mat[1][1] = scale.y * c;
        mat[1][2] = position.y;

        mat[2][0] = 0;
        mat[2][1] = 0;
        mat[2][2] = 1;

        return mat;
    }

    // Multiplication de matrices
    Mat3 operator*(const Mat3& other) const {
        Mat3 result;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                result[i][j] = 0;
                for(int k=0;k<3;k++)
                    result[i][j] += m[i][k] * other[k][j];
            }
        }
        return result;
    }

    // Appliquer la matrice à un vecteur 2D
    Vec2f apply(const Vec2f& v) const {
        float x = m[0][0]*v.x + m[0][1]*v.y + m[0][2];
        float y = m[1][0]*v.x + m[1][1]*v.y + m[1][2];
        return Vec2f(x, y);
    }
};
