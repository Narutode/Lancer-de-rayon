//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_SPHERE_H
#define UNTITLED_SPHERE_H
#include "Object.h"

class Sphere : public Object {
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

        Point3D temp=lo - Point3D(0, 0, 0);
        Vector3D normal = Vector3D(temp.x,temp.y,temp.z);
        Vector3D normalLp=Vector3D(lp.x,lp.y,lp.z);
        if (Vector3D(lo.x, lo.y, lo.z).norm() < 1) {
            normal = -normal;
        }
        else
            normal = normalLp;
        return localToGlobal(Ray(lp, normal)).normalized();
    }
    Material getMaterial(const Point3D& p) const {
        Material material;
        material.ka = Color(0.0, 0.0, 0.0);  // Composante ambiante
        material.kd = Color(0.0, 1.0, 0.0);  // Composante diffuse (vert)
        material.ks = Color(0.0, 0.0, 0.0);  // Composante spéculaire (noir)
        material.shininess = 0.0;  // Exposant de brillance (aucun effet de spécularité)
        return material;
    }
    Point3D getTextureCoordinates(const Point3D& p) const {
        Point3D lp = globalToLocal(p);
        float rho = std::sqrt(lp.dot(lp));
        float theta = std::atan2(lp[1], lp[0]);
        float sigma = std::acos(lp[2] / rho);
        float x = -theta / (2 * M_PI) + 0.5;
        float y = sigma / M_PI;

        return Point3D(x, y, 0);
    }
};


#endif //UNTITLED_SPHERE_H
