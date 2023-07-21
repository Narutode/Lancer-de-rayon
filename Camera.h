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
        float pixelX = 2 * x - 1;
        float pixelY = 2 * y- 1;
        Point3D  globalOrigin = localToGlobal(Point3D(pixelX, pixelY, 0));
        Vector3D globalVector = Vector3D(globalOrigin.x, globalOrigin.y, -focal).normalized();
        return Ray(globalOrigin, globalVector);
    }
};

#endif //UNTITLED_CAMERA_H
