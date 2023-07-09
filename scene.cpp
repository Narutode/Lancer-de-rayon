//
// Created by zheng on 08/07/2023.
//

#include "scene.h"
#include <cmath>

struct Point3D {
    float x, y, z;
};


struct Material {
    Vector3D ambientColor;
    Vector3D diffuseColor;
    Vector3D specularColor;
    float shininess;
};

struct PointLight {
    Point3D position;
    Vector3D color;
    float intensity;
};
Vector3D calculatePhongShading(const Point3D& point, const Vector3D& normal, const Material& material, const PointLight& light) {
    Vector3D ambient = material.ambientColor;
    Vector3D diffuse = material.diffuseColor;
    Vector3D specular = material.specularColor;

    Vector3D lightDirection = normalize(subtract(light.position, point));
    Vector3D viewDirection = normalize(subtract(cameraPosition, point));
    Vector3D reflectionDirection = reflect(lightDirection, normal);

    float diffuseFactor = max(dot(lightDirection, normal), 0.0f);
    float specularFactor = pow(max(dot(reflectionDirection, viewDirection), 0.0f), material.shininess);

    Vector3D ambientTerm = multiply(ambient, light.intensity);
    Vector3D diffuseTerm = multiply(diffuse, diffuseFactor * light.intensity);
    Vector3D specularTerm = multiply(specular, specularFactor * light.intensity);

    return add(add(ambientTerm, diffuseTerm), specularTerm);
}