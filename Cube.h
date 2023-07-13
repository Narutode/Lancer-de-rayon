//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_CUBE_H
#define UNTITLED_CUBE_H

#include "Entity.h"
#include "Ray.h"
#include "Point3D.h"

class Cube : public Entity {
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
};


#endif //UNTITLED_CUBE_H
