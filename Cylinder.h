//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_CYLINDER_H
#define UNTITLED_CYLINDER_H
#include "Entity.h"

class Cylinder: public Entity {
    public:
        bool intersect(const Ray& ray, Point3D& impact) const {
            Ray r = globalToLocal(ray).normalized();

            float a = r.vector.x * r.vector.x + r.vector.z * r.vector.z;
            float b = 2 * (r.vector.x * r.origin.x + r.vector.z * r.origin.z);
            float c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1.0;
            float delta = b * b - 4 * a * c;

            if (delta < 0)
                return false;

            float t;
            if (delta < 0.0001) {
                t = -b / (2 * a);
            } else {
                t = (-b - std::sqrt(delta)) / (2 * a);
                if (t < 0)
                    t = (-b + std::sqrt(delta)) / (2 * a);
            }
            if (t < 0)
                return false;

            Point3D p = r.origin +  r.vector * t ;
            impact = localToGlobal(p);
            return true;
        }
};


#endif //UNTITLED_CYLINDER_H
