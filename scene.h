//
// Created by zheng on 08/07/2023.
//

#ifndef UNTITLED_SCENE_H
#define UNTITLED_SCENE_H
#include <iostream>
#include <string>
#include "vector"
#include <cstring>
#include "Point3D.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Plan.h"
#include "Camera.h"
#include "Sphere.h"
#include "Square.h"
#include "Cube.h"
#include "Cylinder.h"


class scene {
public:
    void performOperation(const std::string& operation,const int width,const int height,const std::string& outputname,const bool ombre, const std::string& materieu) {
        std::vector<unsigned char> image(width * height * 3);
        Camera camera(45);
        camera.translate(2.2, 2.2, 100);
        std::vector<Entity*> objets;

        if (operation == "plan") {
            Plan plan;
            plan.translate(10,10,10);
            objets.push_back(&plan);
        }
        else if (operation == "cube") {
            Cube cube;
            cube.translate(1,2,0);
            cube.rotateZ(45);
            cube.rotateX(45);
            cube.rotateY(45);
            objets.push_back(&cube);
            Square carre;
            carre.translate(-2,-3,0);
            objets.push_back(&carre);
            Sphere sphere;
            sphere.translate(1,-2,0);
            objets.push_back(&sphere);
            Cylinder cylinder;
            cylinder.translate(4,4,0);
            objets.push_back(&cylinder);
        }
        else if (operation == "carre") {

        }
        else if (operation == "triangle") {

        }
        else if (operation == "sphere") {

        }
        else if (operation == "cylindre") {
        }
        else if (operation == "cone") {
        }
        else {
            std::cerr << "Opération non prise en charge : " << operation << std::endl;
        }
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Calcul des coordonnées du pixel dans l'espace de projection
                float px = 2.0f * (x + 0.5f) / width - 1.0f;
                float py = 2.0f * (y + 0.5f) / height - 1.0f;

                // Création du rayon
                Ray ray = camera.getRay(px, py);

                // Intersection avec le plan
                Point3D impact(0.0f, 0.0f, 0.0f);
                bool intersects =false;
                for(int i=0;i<objets.size();i++){
                    intersects = objets[i]->intersect(ray,impact);
                    if(intersects)break;
                }
                if (intersects) {
                    // Coloriage du pixel avec une couleur au choix (ici, rouge)
                    image[(y * width + x) * 3] = 0;     // Composante rouge
                    image[(y * width + x) * 3 + 1] = 0;   // Composante verte
                    image[(y * width + x) * 3 + 2] = 0;   // Composante bleue
                }
                else {
                    // Coloriage du pixel avec une autre couleur au choix (ici, bleu)
                    image[(y * width + x) * 3] = 255;       // Composante rouge
                    image[(y * width + x) * 3 + 1] = 255;   // Composante verte
                    image[(y * width + x) * 3 + 2] = 255; // Composante bleue
                }
            }
        }

        // Enregistrement de l'image au format JPG
        stbi_write_jpg(outputname.c_str(), width, height, 3, image.data(), 100);
    }
};

#endif //UNTITLED_SCENE_H
