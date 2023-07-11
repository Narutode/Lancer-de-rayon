//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_MATRICE_H
#define UNTITLED_MATRICE_H

#include <array>
#include "HPoint.h"
#include "HVector.h"

class Matrix {
public:
    Matrix() {
        // Initialiser la matrice avec des valeurs par défaut
        data.fill({{0.0f, 0.0f, 0.0f, 0.0f}});
    }

    // Accès à la case (i, j) de la matrice
    float& operator()(int i, int j) {
        return data[i][j];
    }

    // Accès à la case (i, j) de la matrice
    float operator()(int i, int j) const{
        return data[i][j];
    }

    // Inversion de la matrice
    Matrix inverse() const {

    }

// Multiplication de matrices
    Matrix operator*(const Matrix& other) const {

    }

    // Multiplication de la matrice avec un point en coordonnées homogènes
    HPoint operator*(const HPoint& point) const {
        float x = data[0][0] * point.x + data[0][1] * point.y + data[0][2] * point.z + data[0][3] * point.w;
        float y = data[1][0] * point.x + data[1][1] * point.y + data[1][2] * point.z + data[1][3] * point.w;
        float z = data[2][0] * point.x + data[2][1] * point.y + data[2][2] * point.z + data[2][3] * point.w;
        float w = data[3][0] * point.x + data[3][1] * point.y + data[3][2] * point.z + data[3][3] * point.w;

        return HPoint(x, y, z, w);
    }

    // Multiplication de la matrice avec un vecteur en coordonnées homogènes
    HVector operator*(const HVector& vector) const {
        float x = data[0][0] * vector.x + data[0][1] * vector.y + data[0][2] * vector.z + data[0][3] * vector.w;
        float y = data[1][0] * vector.x + data[1][1] * vector.y + data[1][2] * vector.z + data[1][3] * vector.w;
        float z = data[2][0] * vector.x + data[2][1] * vector.y + data[2][2] * vector.z + data[2][3] * vector.w;
        float w = data[3][0] * vector.x + data[3][1] * vector.y + data[3][2] * vector.z + data[3][3] * vector.w;

        return HVector(x, y, z, w);
    }

private:
    std::array<std::array<float, 4>, 4> data;
};



#endif //UNTITLED_MATRICE_H
