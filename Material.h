//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_MATERIAL_H
#define UNTITLED_MATERIAL_H

#include "Color.h"

class Material {
public:
    Color ka;  // Composante ambiante
    Color kd;  // Composante diffuse
    Color ks;  // Composante spéculaire
    float shininess;  // Exposant de brillance

    Material(const Color& ambient = Color(), const Color& diffuse = Color(),
             const Color& specular = Color(), float shine = 0.0f)
            : ka(ambient), kd(diffuse), ks(specular), shininess(shine) {}

};


#endif //UNTITLED_MATERIAL_H
