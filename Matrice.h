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
        data.fill(0.0f);
    }

    // Accès à la case (i, j) de la matrice
    float& operator()(int i, int j) {
        return data[i][j];
    }

    // Inversion de la matrice
    Matrix inverse() const {
        Matrix result;

        // Vérifier si la matrice est inversible
        if (determinant() == 0.0f) {
            throw std::runtime_error("La matrice n'est pas inversible");
        }

        // Copier la matrice d'origine dans une matrice temporaire
        Matrix temp = *this;

        // Concaténer avec une matrice identité correspondante
        Matrix identity;
        temp.concatenate(identity);

        int n = 4; // Dimension de la matrice

        // Appliquer la méthode de Gauss-Jordan
        for (int i = 0; i < n; i++) {
            // Trouver le pivot pour la colonne i
            int pivotRow = i;
            for (int j = i + 1; j < n; j++) {
                if (std::abs(temp(j, i)) > std::abs(temp(pivotRow, i))) {
                    pivotRow = j;
                }
            }

            // Échanger les lignes pour mettre le pivot en haut
            if (pivotRow != i) {
                temp.swapRows(pivotRow, i);
                result.swapRows(pivotRow, i);
            }

            // Normaliser la ligne du pivot
            float pivotValue = temp(i, i);
            for (int j = i; j < n * 2; j++) {
                temp(i, j) /= pivotValue;
            }

            // Éliminer les autres lignes
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    float factor = temp(j, i);
                    for (int k = i; k < n * 2; k++) {
                        temp(j, k) -= factor * temp(i, k);
                    }
                }
            }
        }

        // Extraire la matrice inverse de la matrice temporaire
        for (int i = 0; i < n; i++) {
            for (int j = n; j < n * 2; j++) {
                result(i, j - n) = temp(i, j);
            }
        }

        return result;
    }

    // Multiplication de la matrice avec une autre matrice
    Matrix operator*(const Matrix& other) const {
        Matrix result;

        // Effectuer la multiplication de la matrice avec une autre matrice
        // ... (code pour la multiplication des matrices)

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
