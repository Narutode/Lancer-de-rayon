//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_VECTOR3D_H
#define UNTITLED_VECTOR3D_H
#include <cmath>

class Vector3D {
public:
    float x, y, z;
    Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

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
    Vector3D normalized() const {
        float n = norm();
        return Vector3D(x / n, y / n, z / n);
    }

    // Produit scalaire
    float dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Opérateur d'addition
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    // Opérateur de soustraction
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // Opérateur de multiplication par un scalaire
    Vector3D operator*(float scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    // Opérateur de division par un scalaire
    Vector3D operator/(float scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    // Opérateur d'opposé
    Vector3D operator-() const {
        return Vector3D(-x, -y, -z);
    }


};


#endif //UNTITLED_VECTOR3D_H
