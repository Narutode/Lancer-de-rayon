//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_RAY_H
#define UNTITLED_RAY_H

#include "Point3D.h"
#include "Vector3D.h"

class Ray {
public:
    Point3D origin;
    Vector3D vector;

    Ray(float ox, float oy, float oz, float vx, float vy, float vz) : origin(ox, oy, oz), vector(vx, vy, vz) {}

    Ray(const Point3D& p, const Vector3D& v) : origin(p), vector(v) {}
};

#endif //UNTITLED_RAY_H
