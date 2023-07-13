//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_SPHERE_H
#define UNTITLED_SPHERE_H
#include "Entity.h"

class Sphere : public Entity {
public:
    bool intersect(const Ray& ray, Point3D& impact) const {
        Ray local_ray = globalToLocal(ray);
        float t = 0;
        if (t < 0) {
            return false;
        }
        float a = local_ray.vector[0] * local_ray.vector[0] + local_ray.vector[1] * local_ray.vector[1] + local_ray.vector[2] * local_ray.vector[2];
        float b = 2 * (local_ray.vector[0] * local_ray.origin[0] + local_ray.vector[1] * local_ray.origin[1] + local_ray.vector[2] * local_ray.origin[2]);
        float c = local_ray.origin[0] * local_ray.origin[0] + local_ray.origin[1] * local_ray.origin[1] + local_ray.origin[2] * local_ray.origin[2] - 1;
        float delta = b * b - 4 * a * c;
        if (delta < 0) {
            return false;
        } else if (delta > 0) {
            float temp1 = (-b - sqrt(delta)) / (2 * a);
            float temp2 = (-b + sqrt(delta)) / (2 * a);
            if (temp1 < 0) {
                t = temp2;
            } else if (temp2 < 0) {
                t = temp1;
            } else if (temp1 > temp2) {
                t = temp2;
            } else {
                t = temp1;
            }
        } else {
            t = -b / (2 * a);
        }
        Point3D local_intersection = local_ray.origin +  local_ray.vector * t;
        impact = localToGlobal(local_intersection);
        return true;
    }
    Ray getNormal(const Point3D& p, const Point3D& o) const {
        Point3D lp = globalToLocal(p);
        Point3D lo = globalToLocal(o);
        Vector3D normal;
        if ((lo - Point3D(0, 0, 0)).norm() < 1)
            normal = -lp;
        else
            normal = lp;
        return localToGlobal(Ray(lp, normal)).normalized();
    }
};


#endif //UNTITLED_SPHERE_H
