//
// Created by zheng on 08/07/2023.
//

#ifndef UNTITLED_SCENE_H
#define UNTITLED_SCENE_H
#include <iostream>
#include <string>
#include "vector"
#include <cstring>

#include "Object.h"
#include "Light.h"


class Scene {
private:
    std::vector<Object*> objects;
    std::vector<Light*> lights;
    Color background;
    Color ambient;

public:
    Scene(const Color& background, const Color& ambient)
            : background(background), ambient(ambient) {}
    Color getBackground() const {
        return background;
    }

    Color getAmbient() const {
        return ambient;
    }

    int nbLights() const {
        return lights.size();
    }

    const Light* getLight(int index) const {
        if (index < 0 || index >= lights.size()) {
            return nullptr;
        }
        return lights[index];
    }

    Object* closer_intersected(const Ray& ray, Point3D& impact) const {
        float minDist = std::numeric_limits<float>::max();
        Object* closestObject = nullptr;

        for (Object* object : objects) {
            Point3D currentImpact;
            if (object->intersect(ray, currentImpact)) {
                Point3D temp= currentImpact - ray.origin;
                Vector3D temp2=Vector3D(temp2.x,temp2.y,temp2.z);
                float dist = temp2.norm();
                if (dist < minDist) {
                    minDist = dist;
                    closestObject = object;
                    impact = currentImpact;
                }
            }
        }

        return closestObject;
    }
    void addObject(Object* object) {
        objects.push_back(object);
    }
    void addLight(Light* light) {
        lights.push_back(light);
    }
};

#endif //UNTITLED_SCENE_H
