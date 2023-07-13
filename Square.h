//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_SQUARE_H
#define UNTITLED_SQUARE_H
#include "Plan.h"

class Square : public Plan {
public:
    bool intersect(const Ray& ray, Point3D& impact) const {
        Ray local_ray = globalToLocal(ray);
        float t = -local_ray.origin[2] / local_ray.vector[2];
        if (t < 0) {
            return false;
        }
        Point3D intersection = local_ray.origin + local_ray.vector * t;

        if (std::abs(intersection[0]) > 1.0 || std::abs(intersection[1]) > 1.0) {
            return false;
        }

        impact = localToGlobal(intersection);
        return true;
    }
};

#endif //UNTITLED_SQUARE_H
