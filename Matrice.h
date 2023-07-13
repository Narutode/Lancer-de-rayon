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
        data[0][0]=data[1][1]=data[2][2]=data[3][3]=1.0;
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
        Matrix copy = *this;
        Matrix result;

        // Créer une matrice identité
        for (int i = 0; i < 4; ++i) {
            result(i, i) = 1.0f;
        }

        // Appliquer l'algorithme de Gauss-Jordan
        for (int i = 0; i < 4; ++i) {
            // Rechercher le pivot dans la colonne i
            int pivotRow = i;
            float pivotValue = copy(i, i);
            for (int j = i + 1; j < 4; ++j) {
                if (std::abs(copy(j, i)) > std::abs(pivotValue)) {
                    pivotRow = j;
                    pivotValue = copy(j, i);
                }
            }

            // Échanger les lignes pour mettre le pivot en position (i, i)
            if (pivotRow != i) {
                for (int j = 0; j < 4; ++j) {
                    std::swap(copy(i, j), copy(pivotRow, j));
                    std::swap(result(i, j), result(pivotRow, j));
                }
            }

            // Normaliser la ligne du pivot
            float pivotInverse = 1.0f / pivotValue;
            for (int j = 0; j < 4; ++j) {
                copy(i, j) *= pivotInverse;
                result(i, j) *= pivotInverse;
            }

            // Éliminer les autres valeurs dans la colonne i
            for (int j = 0; j < 4; ++j) {
                if (j != i) {
                    float factor = copy(j, i);
                    for (int k = 0; k < 4; ++k) {
                        copy(j, k) -= factor * copy(i, k);
                        result(j, k) -= factor * result(i, k);
                    }
                }
            }
        }

        return result;
    }

// Multiplication de matrices
    Matrix operator*(const Matrix& other) const {
        Matrix result;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                float sum = 0.0;
                for (int k = 0; k < 4; ++k) {
                    sum += data[i][k] * other(k, j);
                }
                result(i, j) = sum;
            }
        }

        return result;

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
