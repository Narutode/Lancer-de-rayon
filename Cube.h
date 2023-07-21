//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_CUBE_H
#define UNTITLED_CUBE_H

#include "Ray.h"
#include "Point3D.h"
#include "Object.h"

class Cube : public Object {
public:
    float interSide(const Ray& r, int dim, float offset) const {
        float t = -1;
        if (r.vector[dim] < 0.00001 && r.vector[dim] > -0.00001)
            return -1;
        t = (offset - r.origin[dim]) / r.vector[dim];
        if (t < 0)
            return -1;
        for (int d = 0; d < 3; d++) {
            if (d == dim)
                continue;
            float x = r.origin[d] + t * r.vector[d];
            if (x < -1 || x > 1)
                return -1;
        }
        return t;
    }

    bool intersect(const Ray& ray, Point3D& impact) const {
        Ray r = globalToLocal(ray).normalized();

        float mint = -1;
        float offsets[] = {-1, 1};
        for (int d = 0; d < 3; d++) {
            for (int o = 0; o < 2; o++) {
                float t = interSide(r, d, offsets[o]);
                if (t >= 0 && (mint < 0 || mint > t)) {
                    mint = t;
                }
            }
        }

        if (mint >= 0) {
            impact = localToGlobal(r.origin +  r.vector *mint );
            return true;
        }

        return false;
    }
    Ray getNormal(const Point3D& p, const Point3D& o) const {
        Point3D lp = globalToLocal(p);
        Point3D lo = globalToLocal(o);
        Vector3D v(0, 0, 0);

        if (lp[0] > 0.999)
            v[0] = 1.0;
        else if (lp[0] < -0.999)
            v[0] = -1.0;
        else if (lp[1] > 0.999)
            v[1] = 1.0;
        else if (lp[1] < -0.999)
            v[1] = -1.0;
        else if (lp[2] > 0.999)
            v[2] = 1.0;
        else if (lp[2] < -0.999)
            v[2] = -1.0;

        if (lo[0] < 1 && lo[0] > -1 && lo[1] < 1 && lo[1] > -1 && lo[2] < 1 && lo[2] > -1)
            return localToGlobal(Ray(lp, -v)).normalized();
        return localToGlobal(Ray(lp, v)).normalized();
    }

    Material getMaterial(const Point3D& p) const{
        Material material;
        material.ka = Color(0, 0, 0);  // Composante ambiante
        material.kd = Color(0.0, 1.0, 0.0);  // Composante diffuse (vert)
        material.ks = Color(0.0, 0.0, 0.0);  // Composante spéculaire (noir)
        material.shininess = 0.0;  // Exposant de brillance (aucun effet de spécularité)
        return material;
    }
    Point3D getTextureCoordinates(const Point3D& p) const {
        Point3D lp = globalToLocal(p);
        if (lp[0] > 0.999 || lp[0] < -0.999) {
            return Point3D(lp[2] / 2 + 0.5, lp[1] / 2 + 0.5, 0);
        }
        if (lp[1] > 0.999 || lp[1] < -0.999) {
            return Point3D(lp[0] / 2 + 0.5, lp[2] / 2 + 0.5, 0);
        }
        if (lp[2] > 0.999 || lp[2] < -0.999) {
            return Point3D(lp[0] / 2 + 0.5, lp[1] / 2 + 0.5, 0);
        }
        return Point3D(0, 0, 0);
    }

};


#endif //UNTITLED_CUBE_H
