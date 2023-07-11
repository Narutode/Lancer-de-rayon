//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_HVECTOR_H
#define UNTITLED_HVECTOR_H

#include <cmath>

class HVector {
public:
    float x, y, z, w;

    HVector(float _x, float _y, float _z, float _w = 0.0f) : x(_x), y(_y), z(_z), w(_w) {}

    // Accès aux composantes du vecteur
    float& operator[](int index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else return z;
    }

    // Norme du vecteur
    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Version normalisée du vecteur
    HVector normalized() const {
        float n = norm();
        return HVector(x / n, y / n, z / n);
    }

    // Produit scalaire
    float dot(const HVector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Opérateur d'addition
    HVector operator+(const HVector& other) const {
        return HVector(x + other.x, y + other.y, z + other.z);
    }

    // Opérateur de soustraction
    HVector operator-(const HVector& other) const {
        return HVector(x - other.x, y - other.y, z - other.z);
    }

    // Opérateur de multiplication par un scalaire
    HVector operator*(float scalar) const {
        return HVector(x * scalar, y * scalar, z * scalar);
    }

    // Opérateur de division par un scalaire
    HVector operator/(float scalar) const {
        return HVector(x / scalar, y / scalar, z / scalar);
    }

    // Opérateur d'opposé
    HVector operator-() const {
        return HVector(-x, -y, -z);
    }


};

#endif //UNTITLED_HVECTOR_H
