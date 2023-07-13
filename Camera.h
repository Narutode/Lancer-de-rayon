//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

#include "Entity.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Ray.h"

class Camera : public Entity {
public:
    float focal;

    // Constructeur
    Camera(float _focal) : Entity(), focal(_focal) {}

    // Méthode pour obtenir un rayon correspondant à un point de l'écran
    Ray getRay(float x, float y) const {
        Point3D  globalOrigin = localToGlobal(Point3D(0, 0, 0));
        Vector3D globalVector = Vector3D(x * 2 - 1, y * 2 - 1, -focal).normalized();
        return Ray(globalOrigin, globalVector);
    }
    bool intersect(const Ray& ray, Point3D& impact) const override {
        return false;
    }
};

#endif //UNTITLED_CAMERA_H
