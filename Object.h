//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_OBJECT_H
#define UNTITLED_OBJECT_H

#include "Material.h"
#include "Color.h"
#include "Entity.h"
class Object : public Entity {
public:
    virtual Material getMaterial(const Point3D& p) const = 0;
    virtual Ray getNormal(const Point3D& p, const Point3D& o) const = 0;
    virtual bool intersect(const Ray& ray, Point3D& impact) const = 0;
};

#endif //UNTITLED_OBJECT_H
