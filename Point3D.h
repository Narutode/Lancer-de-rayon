//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_POINT3D_H
#define UNTITLED_POINT3D_H

#include <cmath>
#include "Vector3D.h"

class Point3D {
public:
    float x, y, z;
    Point3D();
    Point3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // Accès aux composantes du point
    float& operator[](int index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else return z;
    }

    // Produit scalaire
    float dot(const Point3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Opérateur d'addition
    Point3D operator+(const Point3D& other) const {
        return Point3D(x + other.x, y + other.y, z + other.z);
    }
    Point3D operator+(const Vector3D& vector) const {
        return Point3D(x + vector.x, y + vector.y, z + vector.z);
    }
    // Opérateur de soustraction
    Point3D operator-(const Point3D& other) const {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }

    // Opérateur de multiplication par un scalaire
    Point3D operator*(float scalar) const {
        return Point3D(x * scalar, y * scalar, z * scalar);
    }

    // Opérateur de division par un scalaire
    Point3D operator/(float scalar) const {
        return Point3D(x / scalar, y / scalar, z / scalar);
    }

    // Opérateur d'opposé
    Point3D operator-() const {
        return Point3D(-x, -y, -z);
    }
    float operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        return 0.0f;
    }


};


#endif //UNTITLED_POINT3D_H
