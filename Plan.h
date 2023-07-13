//
// Created by zheng on 11/07/2023.
//

#ifndef UNTITLED_PLAN_H
#define UNTITLED_PLAN_H

#include "Entity.h"

class Plan : public Entity {
public:
    // ...

    bool intersect(const Ray& ray, Point3D& impact) const {
        Ray local_ray = globalToLocal(ray);
        float t = -local_ray.origin[2] / local_ray.vector[2];
        if (t < 0) {
            return false;
        }
        Point3D local_intersection = local_ray.origin + local_ray.vector * t;
        impact = localToGlobal(local_intersection);
        return true;
    }
    Ray getNormal(const Point3D& p, const Point3D& o) const {
        Point3D lp = globalToLocal(p);
        Point3D lo = globalToLocal(o);
        float z = 1;
        if (lo.z < 0)
            z = -1;
        return localToGlobal(Ray(lp, Vector3D(0, 0, z))).normalized();
    }
};
#endif //UNTITLED_PLAN_H
