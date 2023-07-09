//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_HPOINT_H
#define UNTITLED_HPOINT_H

#include <cmath>

class HPoint {
public:
    float x, y, z, w;

    HPoint(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f) {}

    // Accès aux composantes du point
    float& operator[](int index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else if (index == 2) return z;
        else return w;
    }

    // Produit scalaire
    float dot(const HPoint& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // Opérateur d'addition
    HPoint operator+(const HPoint& other) const {
        return HPoint(x + other.x, y + other.y, z + other.z);
    }

    // Opérateur de soustraction
    HPoint operator-(const HPoint& other) const {
        return HPoint(x - other.x, y - other.y, z - other.z);
    }

    // Opérateur de multiplication par un scalaire
    HPoint operator*(float scalar) const {
        return HPoint(x * scalar, y * scalar, z * scalar);
    }

    // Opérateur de division par un scalaire
    HPoint operator/(float scalar) const {
        return HPoint(x / scalar, y / scalar, z / scalar);
    }

    // Opérateur d'opposé
    HPoint operator-() const {
        return HPoint(-x, -y, -z);
    }
};


#endif //UNTITLED_HPOINT_H
