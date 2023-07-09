//
// Created by zheng on 08/07/2023.
//

#ifndef UNTITLED_SCENE_H
#define UNTITLED_SCENE_H
#include <iostream>
#include <string>
#include <cstring>


class scene {
public:
    void performOperation(const std::string& operation,const int width,const int height,const std::string& outputname,const bool ombre, const std::string& materieu) {
        if (operation == "plan") {
            createImageFromPlan(width, height, outputname);
        }
        else if (operation == "cube") {
            createImageFromCube(width, height, outputname);
        }
        else if (operation == "carre") {
            createImageFromCarre(width, height, outputname);
        }
        else if (operation == "triangle") {
            createImageFromTriangle(width, height, outputname);
        }
        else if (operation == "sphere") {
            createImageFromSphere(width, height, outputname);
        }
        else if (operation == "cylindre") {
            createImageFromCylindre(width, height, outputname);
        }
        else if (operation == "cone") {
            createImageFromCone(width, height, outputname);
        }
        else {
            std::cerr << "Opération non prise en charge : " << operation << std::endl;
        }
    }
private:
    void createImageFromPlan(const int width, const int height, const std::string& outputname) {
        // Code pour créer une image avec un plan
        // Utilisez les dimensions (width et height) et le nom de sortie (outputname)
        // pour générer l'image du plan selon vos besoins.
        // Vous pouvez utiliser le modèle d'illumination de Phong, la gestion des ombres, etc.
    }

    void createImageFromCube(const int width, const int height, const std::string& outputname) {
        // Code pour créer une image avec un cube
        // Utilisez les dimensions (width et height) et le nom de sortie (outputname)
        // pour générer l'image du cube selon vos besoins.
    }

    void createImageFromCarre(const int width, const int height, const std::string& outputname) {
        // Code pour créer une image avec un carré
        // Utilisez les dimensions (width et height) et le nom de sortie (outputname)
        // pour générer l'image du carré selon vos besoins.
    }

    void createImageFromTriangle(const int width, const int height, const std::string& outputname) {
        // Code pour créer une image avec un triangle
        // Utilisez les dimensions (width et height) et le nom de sortie (outputname)
        // pour générer l'image du triangle selon vos besoins.
    }

    void createImageFromSphere(const int width, const int height, const std::string& outputname) {
        // Code pour créer une image avec une sphère
        // Utilisez les dimensions (width et height) et le nom de sortie (outputname)
        // pour générer l'image de la sphère selon vos besoins.
    }

    void createImageFromCylindre(const int width, const int height, const std::string& outputname) {
        // Code pour créer une image avec un cylindre
        // Utilisez les dimensions (width et height) et le nom de sortie (outputname)
        // pour générer l'image du cylindre selon vos besoins.
    }

    void createImageFromCone(const int width, const int height, const std::string& outputname) {
        // Code pour créer une image avec un cône
        // Utilisez les dimensions (width et height) et le nom de sortie (outputname)
        // pour générer l'image du cône selon vos besoins.
    }
};

#endif //UNTITLED_SCENE_H
