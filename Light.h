//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_LIGHT_H
#define UNTITLED_LIGHT_H

#include "Entity.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Color.h"
class Light : public Entity {
public:
    // Constructeur
    Color id;
    Color is;
    Light(const Color& diffuse, const Color& specular) : id(diffuse), is(specular) {}
    Light() : id(Color()), is(Color()) {}
    // Méthodes pour générer des rayons et des vecteurs
    Ray getRayToLight(const Point3D& p) const {
        Point3D globalOrigin = localToGlobal(Point3D(0, 0, 0));
        Vector3D globalVector = Vector3D(p.x - globalOrigin.x, p.y - globalOrigin.y, p.z - globalOrigin.z);
        return Ray(p, globalVector.normalized());
    }

    Ray getRayFromLight(const Point3D& p) const {
        Point3D globalOrigin = localToGlobal(Point3D(0, 0, 0));
        Vector3D globalVector = Vector3D(globalOrigin.x - p.x, globalOrigin.y - p.y, globalOrigin.z - p.z);
        return Ray(p, globalVector.normalized());
    }

    Vector3D getVectorToLight(const Point3D& p) const {
        Point3D globalOrigin = localToGlobal(Point3D(0, 0, 0));
        return Vector3D(p.x - globalOrigin.x, p.y - globalOrigin.y, p.z - globalOrigin.z).normalized();
    }

    Vector3D getVectorFromLight(const Point3D& p) const {
        Point3D globalOrigin = localToGlobal(Point3D(0, 0, 0));
        return Vector3D(globalOrigin.x - p.x, globalOrigin.y - p.y, globalOrigin.z - p.z).normalized();
    }
};


#endif //UNTITLED_LIGHT_H
