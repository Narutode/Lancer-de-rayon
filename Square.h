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
    Material getMaterial(const Point3D& p) const {
        Material material;
        material.ka = Color(0, 0, 0);  // Composante ambiante
        material.kd = Color(0.0, 0.0, 1.0);  // Composante diffuse (vert)
        material.ks = Color(0.0, 0.0, 0.0);  // Composante spéculaire (noir)
        material.shininess = 0.0;  // Exposant de brillance (aucun effet de spécularité)
        return material;
    }
    Ray getNormal(const Point3D& p, const Point3D& o) const {
        Point3D lp = globalToLocal(p);
        Point3D lo = globalToLocal(o);

        Vector3D normal(0, 0, 1);
        if (lo[2] < 0)
            normal = -normal;

        return localToGlobal(Ray(lp, normal)).normalized();
    }
};

#endif //UNTITLED_SQUARE_H
